package chanrpc

import (
	"errors"
	"fmt"
	"runtime"
	//"github.com/name5566/leaf/conf"
	"./conf"
	//"github.com/name5566/leaf/log"
	"./log"
)

// one server per goroutine (goroutine not safe)
// one client per goroutine (goroutine not safe)
type Server struct {
	// id -> function
	//
	// function:
	// func(args []interface{})
	// func(args []interface{}) interface{}
	// func(args []interface{}) []interface{}
	functions map[interface{}]interface{}
	ChanCall  chan *CallInfo /*一个chan，互斥用？*/
}

type CallInfo struct {
	f       interface{}
	args    []interface{}
	chanRet chan *RetInfo /*同步用？*/
	cb      interface{}
}

type RetInfo struct {
	// nil
	// interface{}
	// []interface{}
	ret interface{}
	err error
	// callback:
	// func(err error)
	// func(ret interface{}, err error)
	// func(ret []interface{}, err error)
	cb interface{}
}

type Client struct {
	s               *Server
	chanSyncRet     chan *RetInfo
	ChanAsynRet     chan *RetInfo
	pendingAsynCall int
}

/*纯粹是分配内存啊*/
func NewServer(l int) *Server {
	s := new(Server)
	s.functions = make(map[interface{}]interface{}) //这是一个map
	/*func make(Type, size IntegerType) Type  https://golang.org/pkg/builtin/#make 这说明make不是返回指针的，就是返回make出来的的Type*/
	s.ChanCall = make(chan *CallInfo, l) //这是一个chan *CallInfo 类型 ，
	return s
}

func assert(i interface{}) []interface{} {
	if i == nil {
		return nil
	} else {
		return i.([]interface{})
	}
}

// you must call the function before calling Open and Go
func (s *Server) Register(id interface{}, f interface{}) { /*给人的感觉是id和f都是任何类型都ok的*/
	switch f.(type) { /*.(type)是类型断言，配合swtich进行判断  http://studygolang.com/articles/3314*/
	/*函数的参数是 []interface{} （interface{}数组)*/
	case func([]interface{}):
		fmt.Println("func([]interface{}")
	case func([]interface{}) interface{}:
		fmt.Println("func([]interface{}) interface{}")
	case func([]interface{}) []interface{}:
		fmt.Println("func([]interface{}) []interface{}")
	default:
		panic(fmt.Sprintf("function id %v: definition of function is invalid", id))
	}

	if _, ok := s.functions[id]; ok { /*实际是在判断ok  这是map操作*/
		panic(fmt.Sprintf("function id %v: already registered", id))
	}

	s.functions[id] = f /*直接map*/
}

func (s *Server) ret(ci *CallInfo, ri *RetInfo) (err error) {
	if ci.chanRet == nil {
		return
	}

	defer func() {
		if r := recover(); r != nil {
			err = r.(error)
		}
	}()
	/*ci的直接复制给ri*/
	ri.cb = ci.cb
	/*这是互斥吧，*/
	ci.chanRet <- ri /*这是*RetInfo类型 ，ri的写入ci的这个retinfo，必需要求RetInfo可以写入？*/
	return
}

func (s *Server) exec(ci *CallInfo) (err error) {
	defer func() {
		if r := recover(); r != nil {
			if conf.LenStackBuf > 0 {
				buf := make([]byte, conf.LenStackBuf)
				l := runtime.Stack(buf, false)
				err = fmt.Errorf("%v: %s", r, buf[:l])
			} else {
				err = fmt.Errorf("%v", r)
			}

			s.ret(ci, &RetInfo{err: fmt.Errorf("%v", r)})
		}
	}()

	// execute
	switch ci.f.(type) {
	case func([]interface{}):
		ci.f.(func([]interface{}))(ci.args)
		return s.ret(ci, &RetInfo{})
	case func([]interface{}) interface{}:
		ret := ci.f.(func([]interface{}) interface{})(ci.args)
		return s.ret(ci, &RetInfo{ret: ret})
	case func([]interface{}) []interface{}:
		ret := ci.f.(func([]interface{}) []interface{})(ci.args)
		return s.ret(ci, &RetInfo{ret: ret})
	}

	panic("bug")
}

func (s *Server) Exec(ci *CallInfo) {
	err := s.exec(ci)
	if err != nil {
		log.Error("%v", err)
	}
}

// goroutine safe
func (s *Server) Go(id interface{}, args ...interface{}) {
	f := s.functions[id]
	if f == nil {
		return
	}

	defer func() {
		recover()
	}()

	s.ChanCall <- &CallInfo{
		f:    f,
		args: args,
	}
}

// goroutine safe
func (s *Server) Call0(id interface{}, args ...interface{}) error {
	return s.Open(0).Call0(id, args...)
}

// goroutine safe
func (s *Server) Call1(id interface{}, args ...interface{}) (interface{}, error) {
	return s.Open(0).Call1(id, args...)
}

// goroutine safe
func (s *Server) CallN(id interface{}, args ...interface{}) ([]interface{}, error) {
	return s.Open(0).CallN(id, args...)
}

func (s *Server) Close() {
	close(s.ChanCall)

	for ci := range s.ChanCall {
		s.ret(ci, &RetInfo{
			err: errors.New("chanrpc server closed"),
		})
	}
}

// goroutine safe
func (s *Server) Open(l int) *Client {
	c := NewClient(l)
	c.Attach(s)
	return c
}

func NewClient(l int) *Client {
	c := new(Client)
	c.chanSyncRet = make(chan *RetInfo, 1)
	c.ChanAsynRet = make(chan *RetInfo, l)
	return c
}

func (c *Client) Attach(s *Server) {
	c.s = s
}

func (c *Client) call(ci *CallInfo, block bool) (err error) {
	defer func() {
		if r := recover(); r != nil {
			err = r.(error)
		}
	}()

	if block {
		c.s.ChanCall <- ci
	} else {
		select {
		case c.s.ChanCall <- ci:
		default:
			err = errors.New("chanrpc channel full")
		}
	}
	return
}

func (c *Client) f(id interface{}, n int) (f interface{}, err error) {
	if c.s == nil {
		err = errors.New("server not attached")
		return
	}

	f = c.s.functions[id]
	if f == nil {
		err = fmt.Errorf("function id %v: function not registered", id)
		return
	}

	var ok bool
	switch n {
	case 0:
		_, ok = f.(func([]interface{}))
	case 1:
		_, ok = f.(func([]interface{}) interface{})
	case 2:
		_, ok = f.(func([]interface{}) []interface{})
	default:
		panic("bug")
	}

	if !ok {
		err = fmt.Errorf("function id %v: return type mismatch", id)
	}
	return
}

func (c *Client) Call0(id interface{}, args ...interface{}) error {
	f, err := c.f(id, 0)
	if err != nil {
		return err
	}

	err = c.call(&CallInfo{
		f:       f,
		args:    args,
		chanRet: c.chanSyncRet,
	}, true)
	if err != nil {
		return err
	}

	ri := <-c.chanSyncRet
	return ri.err
}

func (c *Client) Call1(id interface{}, args ...interface{}) (interface{}, error) {
	f, err := c.f(id, 1)
	if err != nil {
		return nil, err
	}

	err = c.call(&CallInfo{
		f:       f,
		args:    args,
		chanRet: c.chanSyncRet,
	}, true)
	if err != nil {
		return nil, err
	}

	ri := <-c.chanSyncRet
	return ri.ret, ri.err
}

func (c *Client) CallN(id interface{}, args ...interface{}) ([]interface{}, error) {
	f, err := c.f(id, 2)
	if err != nil {
		return nil, err
	}

	err = c.call(&CallInfo{
		f:       f,
		args:    args,
		chanRet: c.chanSyncRet,
	}, true)
	if err != nil {
		return nil, err
	}

	ri := <-c.chanSyncRet
	return assert(ri.ret), ri.err
}

func (c *Client) asynCall(id interface{}, args []interface{}, cb interface{}, n int) {
	f, err := c.f(id, n)
	if err != nil {
		c.ChanAsynRet <- &RetInfo{err: err, cb: cb}
		return
	}

	err = c.call(&CallInfo{
		f:       f,
		args:    args,
		chanRet: c.ChanAsynRet,
		cb:      cb,
	}, false)
	if err != nil {
		c.ChanAsynRet <- &RetInfo{err: err, cb: cb}
		return
	}
}

func (c *Client) AsynCall(id interface{}, _args ...interface{}) {
	if len(_args) < 1 {
		panic("callback function not found")
	}

	args := _args[:len(_args)-1]
	cb := _args[len(_args)-1]

	var n int
	switch cb.(type) {
	case func(error):
		n = 0
	case func(interface{}, error):
		n = 1
	case func([]interface{}, error):
		n = 2
	default:
		panic("definition of callback function is invalid")
	}

	// too many calls
	if c.pendingAsynCall >= cap(c.ChanAsynRet) {
		execCb(&RetInfo{err: errors.New("too many calls"), cb: cb})
		return
	}

	c.asynCall(id, args, cb, n)
	c.pendingAsynCall++
}

func execCb(ri *RetInfo) {
	defer func() {
		if r := recover(); r != nil {
			if conf.LenStackBuf > 0 {
				buf := make([]byte, conf.LenStackBuf)
				l := runtime.Stack(buf, false)
				log.Error("%v: %s", r, buf[:l])
			} else {
				log.Error("%v", r)
			}
		}
	}()

	// execute
	switch ri.cb.(type) {
	case func(error):
		ri.cb.(func(error))(ri.err)
	case func(interface{}, error):
		ri.cb.(func(interface{}, error))(ri.ret, ri.err)
	case func([]interface{}, error):
		ri.cb.(func([]interface{}, error))(assert(ri.ret), ri.err)
	default:
		panic("bug")
	}
	return
}

func (c *Client) Cb(ri *RetInfo) {
	c.pendingAsynCall--
	execCb(ri)
}

func (c *Client) Close() {
	for c.pendingAsynCall > 0 {
		c.Cb(<-c.ChanAsynRet)
	}
}

func (c *Client) Idle() bool {
	return c.pendingAsynCall == 0
}

package main

import (
	"errors"
	"fmt"
	"reflect"
	"runtime"
	"time"
)

var (
	layout = "2006-01-02 15:04:05"
)

type TimeMgr struct {
	TimestampBegin  int64
	TimestampEnd    int64
	TimeInsertBegin string
	TimeInsertEnd   string
}

func (this *TimeMgr) Run(backdays int, interval int /*天数*/, hour int, minute int, seconds int, jobFun interface{}, params ...interface{}) {
	//logger.Info("-------TimeMgr-Run-----len%v---params %v----",len(params),params)
	var intervalPeriod time.Duration
	intervalPeriod = time.Duration(interval) * 24 * time.Hour
	fmt.Printf("intervalPeriod %v \n", intervalPeriod)
	/*程序启动时填充*/
	//this.genTime(backdays)
	/*创建触发器*/
	fmt.Printf("new job ticker ... \n")
	jt := NewJobTicker(intervalPeriod, hour, minute, seconds)
	fmt.Printf("---do-----\n")
	if len(params) == 0 {
		jt.Do(jobFun)
	} else {
		fmt.Printf("NOT SUPPORT ! len(params),params %v \n", len(params), params)
	}

	fmt.Printf("[TimeMgr]Run-when started---\n")
	jt.Run()
	for {
		select {
		/*定时器超时*/
		case expire := <-jt.t.C:
			fmt.Printf("Expiration time: %v.\n", expire.Format("2006-01-02 15:04:05"))
			/*定时产生时间*/
			//this.genTime(backdays)
			jt.updateJobTicker()
			//logger.Warn("[jobTicker]=Run trigged by timer[%v] %v", this.TimeInfo(), time.Now().Format("2006-01-02 15:04:05"))
			jt.Run()
		}

	}
}

type jobTicker struct {
	t            *time.Timer
	interval     time.Duration /*调用方可设置*/
	hourTotick   int
	minuteTotick int
	secondTotick int

	// Map for the function task store
	funcs map[string]interface{}
	// Map for function and  params of function
	fparams map[string]([]interface{})
	// the job jobFunc to run, func[jobFunc]
	jobFunc string

	// datetime of last run
	lastRun time.Time
	// datetime of next run
	nextRun time.Time
}

func getNextTickDuration(interval time.Duration, hourTotick int, minuteTotick int, secondTotick int) time.Duration {
	now := time.Now()
	nextTick := time.Date(now.Year(), now.Month(), now.Day(), hourTotick, minuteTotick, secondTotick, 0, time.Local)
	if nextTick.Before(now) {
		nextTick = nextTick.Add(interval)
	}
	ret := nextTick.Sub(time.Now())
	fmt.Printf("next tick %v \n", ret)
	fmt.Printf("set period ")
	ret = 1 * time.Minute
	return ret
}

func NewJobTicker(interval time.Duration, hour int, minute int, seconds int) *jobTicker {
	fmt.Printf("new tick with interval %v \n", interval)
	return &jobTicker{
		/*定时器*/
		time.NewTimer( /*getNextTickDuration(interval, hour, minute, seconds)*/
			2 * time.Second, /*试试这个两秒的定时器*/
		),
		interval, hour, minute, seconds,
		make(map[string]interface{}),
		make(map[string]([]interface{})),
		"",
		time.Unix(0, 0),
		time.Unix(0, 0),
	}
}

func (jt *jobTicker) updateJobTicker() {
	period := getNextTickDuration(jt.interval, jt.hourTotick, jt.minuteTotick, jt.secondTotick)
	fmt.Printf("reset timer :next tick here %v \n", period)
	/*定时器重置*/
	jt.t.Reset( /*getNextTickDuration(jt.interval, jt.hourTotick, jt.minuteTotick, jt.secondTotick)*/
		period,
	)
}

// Specifies the jobFunc that should be called every time the job runs
//
func (j *jobTicker) Do(jobFun interface{}, params ...interface{}) {
	typ := reflect.TypeOf(jobFun)
	if typ.Kind() != reflect.Func {
		fmt.Printf("only function can be schedule into the job queue. \n")
		return
	}
	fmt.Printf("jobTicker do len(params) %v params %v \n", len(params), params) /* len(params) 1 params [[]]*/
	fname := getFunctionName(jobFun)
	j.funcs[fname] = jobFun
	j.fparams[fname] = params
	j.jobFunc = fname
	fmt.Printf("fname %v \n", fname) /*fname main.(*CPusher).CPushTarget-fm*/
}

// for given function fn , get the name of funciton.
func getFunctionName(fn interface{}) string {
	return runtime.FuncForPC(reflect.ValueOf((fn)).Pointer()).Name()
}

//Run the job and immdiately reschedule it
func (j *jobTicker) Run() (result []reflect.Value, err error) {
	fmt.Printf("------jobTicker-----Run-----------")
	f := reflect.ValueOf(j.funcs[j.jobFunc])
	params := j.fparams[j.jobFunc]
	fmt.Printf("----len(params)  %v  f.Type().NumIn() %v params %v \n", len(params), f.Type().NumIn(), params)
	if len(params) != f.Type().NumIn() {
		err = errors.New("The number of param is not adapted.")
		fmt.Printf(err.Error())
		/*TODO 参数的个数的判断*/
		return
	}
	in := make([]reflect.Value, len(params))
	for k, param := range params {
		in[k] = reflect.ValueOf(param)
	}
	fmt.Printf("[jobTicker]=call f %v with params %v \n", f, params)
	fmt.Printf("[jobTicker]=Run begin==%v \n", time.Now().Format("2006-01-02 15:04:05"))
	result = f.Call(in)
	j.lastRun = time.Now()
	fmt.Printf("[jobTicker]=Run over==%v \n", time.Now().Format("2006-01-02 15:04:05"))
	return
}
func CPushTarget() {
	fmt.Printf(" cpush target do sth ...\n")
}
func main() {
	CTimeMgr := &TimeMgr{}
	CTimeMgr.Run(333, 1, 8,
		59, 59, CPushTarget)

	fmt.Printf("-------end of main----\n")
}

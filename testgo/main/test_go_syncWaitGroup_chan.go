package main

import (
	"fmt"
	"strconv"
	"sync"
	"time"
)

func main() {
	//传入一个函数TestChan到另一个函数执行
	TestFunc("testchan", myfunc)
}

//传入的是一个func（）类型，无参数、无返回值
func TestFunc(name string, f func()) {
	st := time.Now().UnixNano()
	f()
	/*打印耗时*/
	fmt.Printf("task %s cost %d \r\n", name, (time.Now().UnixNano()-st)/int64(time.Millisecond))
}

//testtest 的新版本，使用chan
func myfunc() {
	var num int
	num = 10
	var wg sync.WaitGroup
	c := make(chan string) //分配一个chan内存类型是string，这是一个channel，所以可以close

	/*这里加1，是因为下面的go的协程里会done，减去1*/
	wg.Add(1) //每次go都要+1
	/* 几乎就是实时输出的啊，两个协程，一个实时写入，另一个实时输出
	   zhangbin@DESKTOP-1QV8QU4 MINGW64 /e/huanju/transcode/daobo/testCPP/testgo/main (master)
	   $ ./test_go_syncWaitGroup_chan.exe
	   c :  zhangbin0
	   c :  zhangbin1
	   c :  zhangbin2
	   c :  zhangbin3
	   c :  zhangbin4
	   c :  zhangbin5
	   c :  zhangbin6
	   c :  zhangbin7
	   c :  zhangbin8
	   c :  zhangbin9
	   task testchan cost 0

	   zhangbin@DESKTOP-1QV8QU4
	*/
	go func() {
		/*次协程试图从chan里读取数据*/
		for v := range c { //遍历c？  循环 `for i := range c` 会不断从 channel 接收值，直到它被关闭。
			fmt.Println("c : ", v) //这里会打印出一大堆123啊
		}
		wg.Done() //然后-1，此时go这个携程ok了
	}()
	/*这个算是myfunc的主线程*/
	//不断的往c里写入数据
	for i := 0; i < num; i++ {
		/*主线程试图写入到chan*/
		str := "zhangbin" + strconv.Itoa(i)
		c <- str
	}

	//https://go-tour-zh.appspot.com/concurrency/4
	/*只有发送者才能关闭 channel，而不是接收者。向一个已经关闭的 channel 发送数据会引起 panic。
	还要注意： channel 与文件不同；通常情况下无需关闭它们。只有在需要告诉接收者没有更多的数据的时候才有必要进行关闭，例如中断一个 `range`。*/
	/*要关闭一个channel*/
	close(c) //为什么用close啊 ，发送者可以 close 一个 channel 来表示再没有值会被发送了
	/*主携程会等待次协程执行完毕*/
	wg.Wait()

}

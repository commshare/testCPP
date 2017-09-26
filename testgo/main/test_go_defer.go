package main

import (
	"fmt"
	"time"
)

/*
GO ROUTINUE里的俩defer都没有执行啊
main的执行了
zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_defer.exe
----------begin--------
----------end--------
-----get from chan ----
-----push to chan---
------cmd:%v 0
------cmd:%v 1
------cmd:%v 2
------cmd:%v 3
------cmd:%v 4
####SET HOLD
----------true--------
--$$$$$-main-enter defer :%v 1505382410480538400

*/
func main() {
	defer func() {
		now := time.Now().UnixNano()
		fmt.Println("--$$$$$-main-enter defer :%v", now)
	}()
	var hold chan bool
	hold = make(chan bool, 1)
	var incomingQ chan int
	incomingQ = make(chan int, 1)
	fmt.Println("----------begin--------")
	go func() {
		fmt.Println("-----push to chan---")
		for i := 0; i < 5; i++ {
			incomingQ <- i
		}
		fmt.Println("####SET HOLD")
		hold <- true
	}()
	go func() {
		defer func() {
			now := time.Now().UnixNano()
			fmt.Println("--$$$$$-2-enter defer :%v", now)
		}()
		fmt.Println("-----get from chan ----")
		for {
			defer func() {
				now := time.Now().UnixNano()
				fmt.Println("--$$$$$-1-enter defer :%v", now)
			}()
			cmd, ok := <-incomingQ
			if ok {
				fmt.Println("------cmd:%v", cmd)
			}
		}
		time.Sleep(time.Second * 2)

	}()
	fmt.Println("----------end--------")
	/*begin和end的打印非常的快，所以要阻塞在这里等着，然两个routine搞定*/
	ret := <-hold
	if ret == true {
		fmt.Println("----------true--------")

	}
	fmt.Println("b return:", b()) // 打印结果为 b return: 2
	time.Sleep(time.Second * 2)
}

/*
$ ./test_go_defer.exe
----------begin--------
----------end--------
-----get from chan ----
-----push to chan---
------cmd:%v 0
------cmd:%v 1
------cmd:%v 2
------cmd:%v 3
------cmd:%v 4
####SET HOLD
----------true--------

*/
func b() (i int) {
	defer func() {
		i++
		fmt.Println("b defer2:", i) // 打印结果为 b defer2: 2
	}()
	defer func() {
		i++
		fmt.Println("b defer1:", i) // 打印结果为 b defer1: 1
	}()
	return i // 或者直接 return 效果相同
}

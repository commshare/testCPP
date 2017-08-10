package main

import (
	"fmt"
	"time"
)

func main() {
	ch1 := make(chan int)
	//一个协程在无限循环中给通道发送整数数据。不过因为没有接收者，只输出了一个数字 0
	go pump(ch1)       // pump hangs
	fmt.Println(<-ch1) // prints only 0

	go suck(ch1)
	//给程序 1 秒的时间来运行：输出了上万个整数
	time.Sleep(1e9)
}

func pump(ch chan int) {
	for i := 0; ; i++ {
		ch <- i
	}
}

//为通道解除阻塞定义了 suck 函数来在无限循环中读取通道，
func suck(ch chan int) {
	for {
		fmt.Println(<-ch)
	}
}

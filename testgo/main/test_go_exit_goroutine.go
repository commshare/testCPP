package main

import (
	"fmt"
	"time"
)

func run(done chan int) {
	for {
		select {
		case <-done: //等待done有值好读取
			fmt.Println("exiting...")
			done <- 20 //写入20,在这个函数里竟然可以修改形参！！！TODO
			break
		default:
		}

		time.Sleep(time.Second * 1)
		fmt.Println("do something")
	}
}

func main() {
	c := make(chan int)

	go run(c) //此时发给run的c是没有值的

	fmt.Println("wait for 5 seconds")
	time.Sleep(time.Second * 5)

	c <- 1 //五秒后c 里有值了
	value, ok := <-c
	fmt.Printf("value %v ok %v\n", value, ok) /*value 20 ok true*/
	fmt.Println("main exited")
}

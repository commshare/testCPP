package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan string)
	go sendData(ch)
	go getData(ch)
	time.Sleep(1e9)
}

func sendData(ch chan string) {
	ch <- "Washington"
	ch <- "Tripoli"
	ch <- "London"
	ch <- "Beijing"
	ch <- "Tokio"
}

func getData(ch chan string) {
	var input string
	// time.Sleep(1e9)
	//for循环退出的条件是什么？？？
	//getData() 使用了无限循环：它随着 sendData() 的发送完成和 ch 变空也结束了
	for {
		input = <-ch
		//go是先入先出的
		fmt.Printf("%s ", input)
	}
}

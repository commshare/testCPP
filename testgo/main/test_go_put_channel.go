package main

import (
	"fmt"
	"runtime"
	"time"
)

var doneChan chan int
var quit chan struct{}

func g1() {
	var i int = 0
	for {
		m := i * 2
		//fmt.Println("put m : ", m)
		doneChan <- m
		//time.Sleep(1 * time.Nanosecond)
		i = i + 1
		if i > 10 {
			fmt.Println("exit i ", i)
			return
		}
	}
}
func g2() {
	var j int = 0
	for {
		n := j*2 + 1
		//fmt.Println("put n : ", n)
		doneChan <- n
		//time.Sleep(1 * time.Nanosecond)
		j = j + 1
		if j > 10 {
			fmt.Println("exit j ", j)
			return
		}
	}

}
func g3() {
	for {
		select {
		case value, _ := <-doneChan:
			fmt.Printf("%v \n", value)
		case <-time.After(10 * time.Second):
			fmt.Println("---timeout -quit--")
			quit <- struct{}{}
		}
	}

}
func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	doneChan = make(chan int, 10)
	quit = make(chan struct{})
	go g3()
	go g1()
	go g2()
	<-quit
}

package main

import "time"
import "fmt"

/*Timers are for when you want to do something once in the future -
tickers are for when you want to do something repeatedly at regular intervals. Here’s a basic example:*/
func test_ticker() {
	ticker := time.NewTicker(time.Millisecond * 500)
	go func() {
		for t := range ticker.C {
			fmt.Println("Tick at", t)
		}
	}()
	time.Sleep(time.Millisecond * 1500)
	ticker.Stop()
	fmt.Println("Ticker stopped")
}

func test_timer() {
	/*
			   Timers represent a single event in the future. You tell the timer how long you want to wait,
		        and it gives you a channel that will be notified at that time. For example, to wait 2 seconds:
	*/
	timer1 := time.NewTimer(time.Second * 2) /*告诉定时器你要等待多久，这里是2秒*/
	<-timer1.C                               /*等待2s时就可以通知你*/
	println("Timer expired")

	/*

	   If you just wanted to wait, you could have used time.Sleep. One reason a timer may be useful is that you can cancel the timer before it expires.
	*/
	timer := time.NewTimer(time.Second)
	go func() {
		<-timer.C
		println("Timer expired")
	}()
	stop := timer.Stop() /*可在定时器过期之前干掉它*/
	println("Timer cancelled:", stop)
}

/*
A great feature of Go’s timers and tickers is that they hook into Go’s built-in concurrency mechanism: channels.
This allows timers and tickers to interact seamlessly with other concurrent goroutines. For example:
*/

func testChan() {
	timeChan := time.NewTimer(time.Second).C

	tickChan := time.NewTicker(time.Millisecond * 400).C

	doneChan := make(chan bool)
	go func() {
		time.Sleep(time.Second * 2)
		doneChan <- true
	}()

	for {
		select {
		case <-timeChan:
			fmt.Println("Timer expired")
		case <-tickChan:
			fmt.Println("Ticker ticked")
		case <-doneChan:
			fmt.Println("Done")
			return
		}
	}
}

func main() {

}

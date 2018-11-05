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
		if j > 30 {
			fmt.Println("exit j ", j)
			fmt.Println("close chan ")
			close(doneChan)
			return
		}
	}

}
func g3() {
	for {
		select {
		case value, more := <-doneChan:
			if more == false {
				if value == 0 {
					fmt.Println("#####chan closed###the last value in the chan ###########")
					/*通知退出，否则会一直more为false，循环打印上面那句话*/
					/*看打印，这里会执行两次，然后才退出，quit这个chan是没有容量的？*/
					quit <- struct{}{}
				} else { /*TODO 我最想看的是这个打印有木有，怎么才能看到呢？*/
					/*从打印看，more为false时，value一定是zero-value？？？！！！！*/
					fmt.Println("####ERROR ??? CLOSED CHAN AND VALUE NOT  ZERO-VALUE ", value)
				}
			} else {
				fmt.Printf("#%v \n", value)
				/*把时间让出来，让go2先跑*/
				time.Sleep(1 * time.Nanosecond)
			}

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

	//go g1()
	go g2()
	/*让g2先跑，chan里充满数据，看g3怎么个消费*/
	time.Sleep(2 * time.Nanosecond)
	go g3()
	/*上面俩go跟下面的这个来自main的打印不冲突，会快速执行到这里*/
	fmt.Println("all task done,prepare to quit")
	/*main不退出是因为阻塞在这里*/
	<-quit
}

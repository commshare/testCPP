package main

import (
	"fmt"
	"runtime"
	"time"
)

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	fmt.Println("vim-go")
	bchan := make(chan bool, 0)
	go func() {
		/*先让select的default跑，跑起来阻塞10s，10s内发送true*/
		time.Sleep(2 * time.Second)
		bchan <- true
		fmt.Println("--send true to notify --", time.Now().Unix())
	}()
	go func() {
		//EXIT_LOOP:
		for {

			select {
			case value, _ := <-bchan:

				fmt.Printf("got notify %v %v\n", value, time.Now().Unix())
			//  break EXIT_LOOP
			default:
				fmt.Printf("in default\n")
				time.Sleep(10 * time.Second)
				fmt.Printf("after 10 seconds %v\n", time.Now().Unix())
			}
		}
	}()

	fmt.Println("----end of main-----")
	select {}
}

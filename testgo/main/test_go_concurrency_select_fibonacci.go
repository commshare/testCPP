package main

import "fmt"

/*https://tour.golang.org/concurrency/5*/
func fibonacci(c, quit chan int) {
	x, y := 0, 1
	for {
		select {
		case c <- x:
			x, y = y, x+y /*不断的改变x和y的值，这样x一直有值，每次都能读取到c的值*/
		case <-quit: /*一直在等待quit*/
			fmt.Println("quit")
			return
		}
	}
}

func main() {
	c := make(chan int)
	quit := make(chan int)
	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(<-c)
		}
		/*打印10次之后，就quit了*/
		quit <- 0
	}()
	fibonacci(c, quit)
}

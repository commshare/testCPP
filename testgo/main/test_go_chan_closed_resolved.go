package main

import "fmt"

/*
http://1234n.com/?post/m4zt31
第二段实验代码中，加入了另外一个channel，用以在B进程退出时发送退出通知，这时候再运行代码将得到以下结果。
看起来好像已经可以满足需求了？但是还有个问题，B进程发送退出通知到channel里的时候，只能由一个进程先接收到，
如果此时是多个进程都在等待B进程接收消息，该如何处理呢？留个疑问大家自己思考吧 ：）
*/
func main() {
	a := make(chan int)
	b := make(chan int)
	c := make(chan int)

	go func(a, b, c chan int) {
		fmt.Println("A wait")
		select {
		case b <- 1: /*b可写*/
			fmt.Println("This will never happen")
		case <-a: /*a可读*/
			fmt.Println("A knows B exit")
		}
		fmt.Println("A exit")
		c <- 1 /*通知main A退出*/
	}(a, b, c)

	go func(a, b chan int) {
		fmt.Println("B exit")
		close(b)
		a <- 1 /*通知A，B已经退出*/
	}(a, b)

	<-c /*阻塞等待A退出*/

	fmt.Println("C exit")
}

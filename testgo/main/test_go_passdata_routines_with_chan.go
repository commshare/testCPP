package main

import (
	"fmt"
)

// https://golangcode.com/basic-channels/
func main() {

	messages := make(chan string) /*传递字符串*/

	go work(messages)

	/*这是从chan里读取数据，如果没有数据就等着*/
	msg := <-messages
	fmt.Println(msg)
	/*这里不需要关闭chan么？*/
	/*TODO 这句话加不加都能通过编译和运行啊*/
	close(messages)
}

/*这个生命很费解啊，看来chan 的生命就是  chan <- string 这样的*/
func work(messages chan<- string) {
	messages <- "done"
}

/*
Go, as a language, makes it very easy to work in parallel on data through it use of go routines (more info on go routines here).
 One of the tricky parts about using go routines however is
 a) to know when they are finished and b) to pass data back from the go routine.
 channels make both of these things possible.

 通道可以实现知道并发的两个协程什么时候结束，也能传递数据给彼此。
*/

//https://my.oschina.net/wtsoftware/blog/803720
//sync.WaitGroup是等待一组协程结束。它实现了一个类似任务队列的结构，你可以向队列中加入任务，任务完成后就把任务从队列中移除，如果队列中的任务没有全部完成，队列就会触发阻塞以阻止程序继续运行。
package main

import (
	"fmt"
	"sync"
)

var waitgroup sync.WaitGroup

func test(shownum int) {
	fmt.Println(shownum)
	waitgroup.Done() //任务完成，将任务队列中的任务数量-1，其实.Done就是.Add(-1)
}

func main() {
	for i := 0; i < 10; i++ {
		waitgroup.Add(1) //每创建一个goroutine，就把任务队列中任务的数量+1
		go test(i)
	}
	waitgroup.Wait() //.Wait()这里会发生阻塞，直到队列中所有的任务结束就会解除阻塞  (计数不为0, 阻塞Wait()的运行。 )
	fmt.Println("done!")
}

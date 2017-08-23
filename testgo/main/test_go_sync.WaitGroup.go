//https://my.oschina.net/wtsoftware/blog/803720
//sync.WaitGroup是等待一组协程结束。它实现了一个类似任务队列的结构，你可以向队列中加入任务，任务完成后就把任务从队列中移除，如果队列中的任务没有全部完成，队列就会触发阻塞以阻止程序继续运行。
package main

import (
	"fmt"
	"net/http"
	"sync"
)

////测试1
var waitgroup sync.WaitGroup

func test(shownum int) {
	fmt.Println(shownum)
	waitgroup.Done() //任务完成，将任务队列中的任务数量-1，其实.Done就是.Add(-1)
}

////测试2  http://www.cnblogs.com/ghj1976/p/4537999.html
var wg sync.WaitGroup //WaitGroup的用途：它能够一直等到所有的goroutine执行完成，并且阻塞主线程的执行，直到所有的goroutine执行完成。
var urls = []string{  //同时开三个协程去请求网页， 等三个请求都完成后才继续 Wait 之后的工作。
	"http://www.golang.org/",
	"http://www.google.com/",
	"http://www.somestupidname.com/",
}

func testtest() {
	for _, url := range urls {
		// Increment the WaitGroup counter.
		wg.Add(1)
		// Launch a goroutine to fetch the URL.  这是go一个函数啊
		go func(url string) {
			// Decrement the counter when the goroutine completes.  当携程完成，就执行计数-1
			defer wg.Done()
			// Fetch the URL.  请求网页
			http.Get(url)
		}(url)
	}
	// Wait for all HTTP fetches to complete.  通过wg来等待所有的http请求都结束
	wg.Wait()

}

const (
	num = 12
)

func main() {
	/*一个goroutine需要等待一批goroutine执行完毕以后才继续执行，那么这种多线程等待的问题就可以使用WaitGroup了。
	 */
	for i := 0; i < 10; i++ {
		waitgroup.Add(1) //每创建一个goroutine，就把任务队列中任务的数量+1
		go test(i)
	}
	waitgroup.Wait() //.Wait()这里会发生阻塞，直到队列中所有的任务结束就会解除阻塞  (计数不为0, 阻塞Wait()的运行。 )
	fmt.Println("done!")

}

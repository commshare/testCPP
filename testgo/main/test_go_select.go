package main

/*
http://studygolang.com/articles/7203
*/
import (
	"fmt"
	"time"
)

/*早期的select函数是用来监控一系列的文件句柄，
一旦其中一个文件句柄发生IO操作，该select调用就会被返回。
golang在语言级别直接支持select，用于处理异步IO问题。*/
/*基于这种机制，可以使用select实现channel读取超时的机制*/

func testTimeOut() {
	timeout := make(chan bool, 1)
	go func() {
		time.Sleep(3e9) // sleep 3 seconds
		timeout <- true
	}()
	ch := make(chan int)
	select {
	case <-ch:
	case <-timeout:
		fmt.Println("timeout!")
		/*注意，如果没有default，select 会一直等待等到某个 case 语句完成， 也就是等到成功从 ch 或者 timeout 中读到数据，否则一直阻塞。*/
		/*注意这里一定不能用default，否则3s超时还未到直接执行default，case2便不会执行，
		  超时机制便不会实现。timeout会在3s超时后读取到数据。*/
	}
}

/*虽然两个chan都用make初始化了，但没有值，所以执行default*/
func simpleSelect() {
	timeout := make(chan bool, 1)
	ch := make(chan int) /*ch初始化后，case1读取失败，，timeout同样失败，因为channel中无数据，直接跳至default执行并返回。*/
	select {
	case <-ch:
	case <-timeout:
		fmt.Println("timeout!")
	default:
		fmt.Println("default case is running")
	}
}

/*使用select判断channel是否存满
此时因为 ch1 和 ch2 都为空，所以 case1 和 case2 都不会读取成功。 则 select 执行 default 语句。
如果case1、case2均未执行，则说明ch1&ch2已满，over.....
*/
func checkChannel() {
	fmt.Println("checkChannel")
	ch1 := make(chan int, 1)
	ch2 := make(chan int, 1)
	/*此时因为 ch1 和 ch2 都为空，所以 case1 和 case2 都不会读取成功。 则 select 执行 default 语句。*/
	select {
	case <-ch1: /*这是读取 */
		fmt.Println("ch1 pop one element")
	case <-ch2:
		fmt.Println("ch2 pop one element")
	default:
		fmt.Println("default")
	}
}

/*
因为 ch 插入 1 的时候已经满了， 当 ch 要插入 2 的时候，发现 ch 已经满了（case1 阻塞住），
 则 select 执行 default 语句。 这样就可以实现对 channel 是否已满的检测， 而不是一直等待。

比如我们有一个服务， 当请求进来的时候我们会生成一个 job 扔进 channel，
由其他协程从 channel 中获取 job 去执行。 但是我们希望当 channel 瞒了的时候，
将该 job 抛弃并回复 【服务繁忙，请稍微再试。】 就可以用 select 实现该需求。
*/
func checkChannel_2() {
	fmt.Println("checkChannel_2")

	ch := make(chan int, 1)
	ch <- 1
	select {
	case ch <- 2: /*ch已经满了 ，所以写不进去 */
	default:
		fmt.Println("channel is full !")
	}

}

func main() {
	simpleSelect()
	testTimeOut()
	checkChannel()
	checkChannel_2()
}

/*$ ./test_go_select.exe
default case is running
timeout!
checkChannel
default
*/

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

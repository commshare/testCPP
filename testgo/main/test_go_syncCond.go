package main

/*这里当主goroutine进入cond.Wait的时候，就会进入等待，当从goroutine发出信号之后，主goroutine才会继续往下面走。
 */
import (
	"fmt"
	"sync"
	"time"
)

func main() {
	locker := new(sync.Mutex)    /*互斥锁*/
	cond := sync.NewCond(locker) /*条件变量啊，也要传入一个锁来构造*/
	done := false

	cond.L.Lock() /*加锁*/

	/*次协程*/
	go func() {
		time.Sleep(2e9)
		done = true
		cond.Signal() /*发信号*/
	}()

	/*主携程*/
	if !done { /*这个地方只读，不写，所以不加锁？？*/
		cond.Wait() /*只有done为false才会进入等待，过了2e9之后，不会第二次执行cond.Wait，随后被signal叫醒*/
	}

	fmt.Println("now done is ", done)
}

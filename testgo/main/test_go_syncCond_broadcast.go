package main

import (
	"fmt"
	"sync"
	"time"
)

var locker = new(sync.Mutex)
var cond = sync.NewCond(locker)

func test(x int) {

	cond.L.Lock() // 获取锁
	cond.Wait()   // 等待通知  暂时阻塞
	fmt.Println(x)
	time.Sleep(time.Second * 1)
	cond.L.Unlock() // 释放锁，不释放的话将只会有一次输出
}
func main() {
	for i := 0; i < 40; i++ {
		go test(i)
	}
	fmt.Println("start all")
	cond.Broadcast() //  下发广播给所有等待的goroutine
	time.Sleep(time.Second * 60)
}

/*
主gouroutine开启后，可以创建多个从gouroutine，从gouroutine获取锁后，进入cond.Wait状态，
当主gouroutine执行完任务后，通过BroadCast广播信号。 处于cond.Wait状态的所有gouroutine收到信号后将全部被唤醒并往下执行。需要注意的是，
从gouroutine执行完任务后，需要通过cond.L.Unlock释放锁， 否则其它被唤醒的gouroutine将没法继续执行。 通过查看cond.Wait 的源码就明白为什么需要需要释放锁了
func (c *Cond) Wait() {
    c.checker.check()
    if raceenabled {
        raceDisable()
    }
    atomic.AddUint32(&c.waiters, 1)
    if raceenabled {
        raceEnable()
    }
    c.L.Unlock()  //自动释放锁，等待信号到来
    runtime_Syncsemacquire(&c.sema) //等待信号到来
    c.L.Lock()  //重新上锁
}
Cond.Wait会自动释放锁等待信号的到来，当信号到来后，第一个获取到信号的Wait将继续往下执行并从新上锁，如果不释放锁，
其它收到信号的gouroutine将阻塞无法继续执行。
由于各个Wait收到信号的时间是不确定的，因此每次的输出顺序也都是随机的。

TODO 上面后面两句话很关键啊
*/

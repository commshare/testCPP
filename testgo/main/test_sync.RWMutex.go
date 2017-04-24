package main

import (
	"sync"
	"time"
)

/*
http://studygolang.com/articles/2497
基本遵循两大原则：

1、可以随便读，多个goroutine同时读

2、写的时候，啥也不能干。不能读也不能写

RWMutex提供了四个方法：

func (*RWMutex) Lock // 写锁定

func (*RWMutex) Unlock // 写解锁

func (*RWMutex) RLock // 读锁定

func (*RWMutex) RUnlock // 读解锁
*/
var m *sync.RWMutex

func main() {
	m = new(sync.RWMutex)

	// 多个同时读
	go read(10)
	go read(20)

	//time.Sleep(2 * time.Second)

	// 写的时候啥也不能干
	go write(1) //写的时候还需等1写完
	go read(30)
	go write(3)
	time.Sleep(4 * time.Second)
}

func read(i int) {
	println(i, "read start")

	/*1 读还没有结束，2已经在读*/
	m.RLock()
	println(i, "reading")
	time.Sleep(1 * time.Second)
	m.RUnlock()

	println(i, "read over")
}

func write(i int) {
	println(i, "write start")

	m.Lock() //写锁定
	println(i, "writing")
	time.Sleep(1 * time.Second)
	m.Unlock()

	println(i, "write over")
}

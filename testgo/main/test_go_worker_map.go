// You can edit this code! https://play.golang.org/p/uLirjskGeN
// Click here and start typing.
package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	go accumulate()
	/*跑10个worker*/
	for i := 0; i < 10; i++ {
		go worker()
	}
	time.Sleep(1e8)
	fmt.Println(getTotal())
}

func worker() {
	workCounter := make(map[string]int)
	lastUpdated := time.Now()
	for {
		// do work
		time.Sleep(1e3)
		workCounter["type1"]++
		if time.Since(lastUpdated) > time.Second/10000 {
			accumulator <- workCounter
			workCounter = make(map[string]int)
			lastUpdated = time.Now()
		}
	}
}

var accumulator = make(chan map[string]int) /*map类型的chan*/
var totalWorkLock sync.Mutex
var totalWork = make(map[string]int) /*全局map*/

func accumulate() {
	for w := range accumulator { /*对于chan的每个元素map*/
		totalWorkLock.Lock()
		for i, v := range w { /*遍历map*/
			totalWork[i] += v /*写map*/
		}
		totalWorkLock.Unlock()
	}
}

func getTotal() map[string]int {
	m := make(map[string]int)
	totalWorkLock.Lock()
	for i, v := range totalWork {
		m[i] = v
	}
	totalWorkLock.Unlock()
	return m
}

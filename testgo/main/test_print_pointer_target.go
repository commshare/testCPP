package main

import (
	"fmt"
	"time"
)

type MyName struct {
	name string
	home string
}
type HerName struct {
	name string
	home string
	pMy  *MyName
}

func main() {
	pName := &MyName{
		name: "zhangbin",
		home: "feichegn",
	}

	fmt.Printf("pointer : %v \n", pName)
	fmt.Printf("non pointer : %v \n", *pName)

	pHer := &HerName{
		name: "her",
		home: "herHome",
		pMy:  pName,
	}
	fmt.Printf("pointer : %v \n", pHer)
	fmt.Printf("non pointer : %v \n", *pHer)
	/*这种嵌套指针的打印，要深入一层，加入*，否则会打印出一个地址*/
	fmt.Printf("non pointer : %v \n", *(pHer.pMy)) /*这样是可以的 non pointer : {zhangbin feichegn}*/

	fmt.Printf("time %v \n", CurrentTime())
}
func CurrentTime() string {
	x := time.Now().Format(time.UnixDate)
	return x
}

//Reverse will reverse a string considering runes
func Reverse(s string) string {
	r := []rune(s)
	for i, j := 0, len(r)-1; i < len(r)/2; i, j = i+1, j-1 {
		r[i], r[j] = r[j], r[i]
	}
	return string(r)
}

//GetCurrentTime return current time in millis https://github.com/ameykpatil/gotil/blob/1de2d13e1f375dd90d00140fc293e78bb461c677/timeutil.go
func GetCurrentTime() int64 {
	return time.Now().UnixNano() * int64(time.Nanosecond) / int64(time.Millisecond)
}

/*https://github.com/rainbowism/MeleeTags/blob/9ad786c0ddcd7a2624f9956a303c14b808062b54/util.go*/
func RunForever(fn func(), interval int) {
	var currentTime, accumTime, deltaTime int64
	currentTime = time.Now().UnixNano()
	accumTime = 0
	deltaTime = 1000000000 / int64(interval)

	for {
		newTime := time.Now().UnixNano()
		frameTime := newTime - currentTime
		currentTime = newTime
		accumTime += frameTime

		for accumTime >= deltaTime {
			fn()
			accumTime -= deltaTime
		}
	}
}

/*
$ ./test_print_pointer_target.exe
pointer : &{zhangbin feichegn}
non pointer : {zhangbin feichegn}


pointer : &{zhangbin feichegn}
non pointer : {zhangbin feichegn}
pointer : &{her herHome 0xc04204a400}
non pointer : {her herHome 0xc04204a400}
time Wed Nov 15 20:16:50 CST 2017

*/

package main

import (
	"fmt"
	"os"
	"os/signal"
)

func child(i int) {
	defer func() {
		fmt.Println("    quit   child  ", i) /*clt+c 之后，不会打印这个*/
	}()
	fmt.Println("       child  ", i)
	select {}
}

func test() {
	fmt.Println("----in first -----")
	for i := 0; i < 5; i++ {
		go child(i)
	}

	fmt.Println("----in first ----after child-")
}

func main() {
	go test()
	c := make(chan os.Signal, 1)
	fmt.Println("----in main -----")

	signal.Notify(c, os.Interrupt, os.Kill)
	sig := <-c
	fmt.Printf("Leaf closing down (signal: %v)\n", sig)
	select {}
}

/*

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_routine_in_routine.exe
----in main -----
----in first -----
       child   0
----in first ----after child-
       child   2
       child   3
       child   4
       child   1


*/

package main

import "fmt"

func panicOnFail(bad string) {
	panic(bad)
}

func test() {
	fmt.Println("test test test begin---")
	panicOnFail("testpaniconfail")
	fmt.Println("test test test end---") /*这个不执行的*/
}

func main() {
	go test()
	select {}
}

/*
$ ./test_onpanic.exe
test test test begin---
panic: testpaniconfail

goroutine 5 [running]:
main.panicOnFail(0x4b3035, 0xf)
        V:/RECORD_TEST/testCPP/testgo/main/test_onpanic.go:6 +0x6a
main.test()
        V:/RECORD_TEST/testCPP/testgo/main/test_onpanic.go:11 +0xb6
created by main.main
        V:/RECORD_TEST/testCPP/testgo/main/test_onpanic.go:16 +0x3c

*/

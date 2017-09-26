package main

/*http://1234n.com/?post/m4zt31*/ /*channel被关闭将导致发送端异常。*/
import (
	"fmt"

	"github.com/facebookgo/stackerr"
)

func DumpPanicStack(format string, args ...interface{}) error {
	err := stackerr.Newf(format, args)
	return err
}

func main() {
	a := make(chan int)
	b := make(chan int)

	go func(a, b chan int) {
		defer func() {
			r := recover()
			if r != nil {
				//err := stackerr.Newf("shoot panic: %s", r)
				err := DumpPanicStack("@@@@ panic: %s", r)
				fmt.Printf("###%v", err)
			}
		}()
		fmt.Println("A wait")
		a <- 1 /*导致panic，因为a已经被关闭了*/
		fmt.Println("A exit")
		b <- 1
	}(a, b) /*函数*/

	go func(a chan int) {
		fmt.Println("B exit")
		close(a)
	}(a)

	<-b

	fmt.Println("C exit")
}

/*
zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_chan_closed_panic.exe
A wait
B exit
panic: send on closed channel

goroutine 5 [running]:
main.main.func1(0xc04201a1e0, 0xc04201a240)
        V:/RECORD_TEST/testCPP/testgo/main/test_go_chan_closed_panic.go:12 +0xdb
created by main.main
        V:/RECORD_TEST/testCPP/testgo/main/test_go_chan_closed_panic.go:15 +0x95

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$

*/

/*
root@ubuntu:/home/zhangbin/ffmpeg/RECORD_TEST/testCPP/testgo/main# ./test_go_chan_closed_panic
B exit
A wait
panic: send on closed channel

goroutine 5 [running]:
main.main.func1(0xc420068060, 0xc4200680c0)
  /home/zhangbin/ffmpeg/RECORD_TEST/testCPP/testgo/main/test_go_chan_closed_panic.go:12 +0xd4
created by main.main
  /home/zhangbin/ffmpeg/RECORD_TEST/testCPP/testgo/main/test_go_chan_closed_panic.go:15 +0x8e
root@ubuntu:/home/zhangbin/ffmpeg/RECORD_TEST/testCPP/testgo/main#

*/

/*

$ ./test_go_chan_closed_panic.exe
B exit
A wait
###shoot panic: send on closed channel
V:/RECORD_TEST/testCPP/testgo/main/test_go_chan_closed_panic.go:18 main.func1.1
D:/Go/src/runtime/asm_amd64.s:514                                  call32
D:/Go/src/runtime/panic.go:489                                     gopanic
D:/Go/src/runtime/chan.go:180                                      chansend
D:/Go/src/runtime/chan.go:113                                      chansend1
V:/RECORD_TEST/testCPP/testgo/main/test_go_chan_closed_panic.go:23 main.func1
D:/Go/src/runtime/asm_amd64.s:2197                                 goexitfatal error: all goroutines are asleep - deadlock!

goroutine 1 [chan receive]:
main.main()
        V:/RECORD_TEST/testCPP/testgo/main/test_go_chan_closed_panic.go:33 +0xda

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$

*/

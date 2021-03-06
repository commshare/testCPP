package main

import "time"
import (
	"fmt"
)

func test(flag chan bool, done chan int) {
	ch := make(chan int, 10)
	for {
		fmt.Println("---begin of for")
		select {
		case value := <-ch: /*走不到，因为没有赋值的地方*/
			fmt.Println("read from ch %v", value)
		case <-flag: /*要靠mytimer给赋值*/
			fmt.Println("read from flag ok,notify main to move on")
			done <- 10
		}
		fmt.Println("----end of for")
	}

}

/*测试表明，break可以跳出select，但是不能跳出for循环的*/
func testFor(flag chan bool, done chan int) {
	ch := make(chan int, 10)
	for {
		fmt.Println("---begin of for")
		select {
		case value := <-ch: /*走不到，因为没有赋值的地方*/
			fmt.Println("read from ch %v", value)
		case <-flag: /*要靠mytimer给赋值*/

			fmt.Println("            read from flag ok, call @@@break or continue")
			break /*测试1：能break出select么？答案是，可以，此时下面那句不执行，然后激活了done<-10,会执行-end of for*/
			//continue /*测试2，看下continue是什么结果，continue不会结束for，但是跳出了select，而且不执行endfofor，直接去到-begin of for*/
			fmt.Println("如果跳出了select，这句话不执行的")
		case <-time.After(2 * time.Second):
			fmt.Println("            #####after 2 seconds####")
		}
		fmt.Println("----end of for")
		/*这个挪到mytimerFor去做*/
		//done <- 10
	}

}
func mytimer(timeout chan bool) {
	time.Sleep(5 * time.Second)
	timeout <- true

}
func mytimerFor(timeout chan bool, done chan int) {
	time.Sleep(5 * time.Second)
	timeout <- true
	/*五秒后，通知main退出*/
	time.Sleep(5 * time.Second)
	done <- 100
}

func main() {
	timeout := make(chan bool, 1)
	done := make(chan int, 1)
	go mytimerFor(timeout, done)

	go testFor(timeout, done)
	/*本身有阻塞作用*/
	<-done

	/*再等3秒，看看test的for走的怎么样,发现及时test携程阻塞，main退出，也会退出test携程*/
	time.Sleep(10 * time.Second)
}

/*
 build test_go_for_select_break.go

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_for_select_break.exe
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            read from flag ok, call @@@break or continue
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$

*/

/*这是break的，会继续执行select之后的语句，也就是说select加不加break的效果一样的，但是continue不是，
continue确实会会到for开始的地方执行。


zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_for_select_break.exe
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            read from flag ok, call @@@break or continue
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for
            #####after 2 seconds####
----end of for
---begin of for

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$


*/

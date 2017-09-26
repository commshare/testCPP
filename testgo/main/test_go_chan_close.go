package main

/*https://stackoverflow.com/questions/10437015/does-a-gos-channel-return-two-values*/
import (
	"fmt"
	"time"

	"github.com/facebookgo/stackerr"
)

func DumpPanicStack(format string, args ...interface{}) error {
	err := stackerr.Newf(format, args)
	return err
}

func onServer(i int) { println("S:", i) }
func onUser(i int)   { println("U:", i) }
func showfalse(str string) {
	fmt.Printf("%s is false \n", str)
}
func showChanLen(str string, a chan int) {
	fmt.Printf("%s chan len %d \n", str, len(a))
}

var fromServer chan int
var fromUser chan int

func main() {
	fromServer, fromUser = make(chan int, 100), make(chan int, 100)
	var serverData, userInput int
	var ok bool

	go func() {
		defer func() {
			r := recover()
			if r != nil {
				//err := stackerr.Newf("shoot panic: %s", r)
				err := DumpPanicStack("@@@@ panic: %s", r)
				fmt.Printf("###%v", err)
			}
		}()
		fromServer <- 1
		fromServer <- 2
		fromServer <- 3
		fromServer <- 4
		fromServer <- 5
		/*1秒之后，main关闭了chan，所以这里休眠1s，可以制造一个panic出来*/
		//time.Sleep(1 * time.Second)
		/*		fromServer <- 6
				fromServer <- 7
				fromServer <- 8
				fromServer <- 9*/
		fromUser <- 100
		/*如果只关闭掉formUser，不关闭fromServer，会卡主，可能是会阻塞在case fromSerer哪里？？？*/
		/*		fmt.Printf("---close chan fromServer \n")
				close(fromServer)*/
		time.Sleep(1 * time.Second)
		//runtime.Gosched()
		fromUser <- 200
		/*如果俩chan都关闭，那么会进入到case <-time.After(10 * time.Second): 执行*/
		/*		fmt.Printf("---close chan fromUser \n")
				close(fromUser)*/
	}()

	isRunning := true
	for isRunning {
		/*这里休眠1s，让前面的把chan写入足够的数据，做close操作，再休眠3s，让这里的select可以跑
		测试发现，chan被关闭之后，只要chan里有数据，select还可以从chan里读取数据出来，但是chan 被close了，写入数据会panic

		close之后，依然可以执行 这俩chan 的case语句
		*/
		time.Sleep(3 * time.Second)
		fmt.Printf("time after 3 seconds, do select \n")
		select { /*http://colobu.com/2016/06/27/dive-into-go-8/ 因为select语句会被阻塞，所以前面生成的所有的goroutine会被执行。*/
		case serverData, ok = <-fromServer:
			showChanLen("fromServer", fromServer)
			if ok {
				onServer(serverData)
			} else {
				//isRunning = false
				showfalse(" fromServer ")
			}

		case userInput, ok = <-fromUser:
			showChanLen("fromUser", fromUser)
			if ok {
				onUser(userInput)
			} else {
				//isRunning = false
				showfalse(" fromuser ")
			}
		case <-time.After(10 * time.Second): /*按照上面做了close的处理，那么俩case回执行到false语句里，这里一直得不到执行，
			如果上面不close俩chan，那么俩case会阻塞，10s后会执行到这个case，然后再执行close的话，上面里俩case 会执行到false语句。
			*/
			/*单纯在这里close chan ，不会让俩case 退出，俩case 会打印false语句，即使再外面协程里close chan，也会打印false语句*/
			fmt.Printf("#######time after 10 seconds, close chan#####")
			close(fromServer)
			close(fromUser)
			fmt.Printf("time after 1 seconds, close chan ok")

		}
	}
	println("end")
}

/*
zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_chan_close
---close chan fromServer
---close chan fromUser
time after 3 seconds, do select
fromServer chan len 8
S: 1
time after 3 seconds, do select
fromServer chan len 7
S: 2
time after 3 seconds, do select
fromUser chan len 1
U: 100
time after 3 seconds, do select
fromServer chan len 6
S: 3
time after 3 seconds, do select
fromServer chan len 5
S: 4
time after 3 seconds, do select
fromServer chan len 4
S: 5
time after 3 seconds, do select
fromServer chan len 3
S: 6
time after 3 seconds, do select
fromServer chan len 2
S: 7
time after 3 seconds, do select
fromUser chan len 0
U: 200
time after 3 seconds, do select
fromUser chan len 0
 fromuser  is false
time after 3 seconds, do select
fromUser chan len 0
 fromuser  is false
time after 3 seconds, do select
fromServer chan len 1
S: 8
time after 3 seconds, do select
fromServer chan len 0
S: 9
time after 3 seconds, do select
fromUser chan len 0
 fromuser  is false
time after 3 seconds, do select
fromServer chan len 0
 fromServer  is false
time after 3 seconds, do select
fromUser chan len 0
 fromuser  is false
time after 3 seconds, do select

*/

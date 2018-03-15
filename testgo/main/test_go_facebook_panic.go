package main /*https://godoc.org/github.com/facebookgo/stackerr*/
import (
	"fmt"
	"runtime/debug"
	"strings"

	"github.com/facebookgo/stackerr"
)

func DumpPanicStack(format string, args ...interface{}) error {
	err := stackerr.Newf(format, args)
	return err
}

func grandpa() {
	ret := father()
	fmt.Printf("Grandpa: ====ret %v\n\n", ret)
}

func father() (ret int) {
	//func() {
	/*最后执行这个*/
	defer func() {
		fmt.Println("=========defer func==========process recover=====================")
		// my son always messes things up..., do something
		if r := recover(); r != nil {
			stack := string(debug.Stack())
			stack = strings.Replace(stack, "\r", "-", -1)
			stack = strings.Replace(stack, "\n", "|", -1)
			fmt.Printf("[Father: recover stack:%s]\n\n", stack)
			fmt.Printf("[Father: I recover my son's panic, so I can continue my job, and my old man won't be affected either\n\n")
			fmt.Println("=====debug ===dump stack %v \n", string(debug.Stack()))
			fmt.Printf("=====facebook=====dump stack %v\n", DumpPanicStack("shoot panic :%s", r))
			ret = 4
			fmt.Printf("@@@@ 1 @@@@@ret [%v]\n\n", ret)

		}
	}()
	/*首先执行这个*/
	defer func() {
		fmt.Println("======defer func === output sth =-=====")
		fmt.Println("----hi i am a defer below defer recover ====")
		ret = 3
		fmt.Printf("@@@@ 2 @@@@@ret [%v]\n\n", ret)

	}()
	son()
	/*如果son的panic不捕获，那么father在son后面的都不执行了
	如果son捕获了自己的异常，那么下面的这些就可以得到执行
	*/
	ret = 2
	fmt.Printf("@@@@@@@@@@@@@@@===afater panic of son ret %v====", ret)
	//}()
	fmt.Printf("@@@@@ 3  @@@@ret [%v]\n\n", ret)
	//ret = 1
	return
}
func son() {
	defer func() {
		fmt.Println("@@@@@@@@defer in panic of son ")
		if r := recover(); r != nil {
			fmt.Printf("=====son=====dump stack %v\n", DumpPanicStack("shoot panic :%s", r))
		}
	}()
	uri := "h"
	offset := 1
	uri = uri[:offset]
	fmt.Printf("[Son: I'm doing good, uri:%v\n\n]", uri)
	panic("=========i am a panic of son =============")
}

func main() {
	grandpa()
}

/*
zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_facebook_panic.exe
[Son: I'm doing good, uri:h

]======defer func === output sth =-=====
----hi i am a defer below defer recover ====
=========defer func==========process recover=====================
[Father: recover stack:goroutine 1 [running]:|runtime/debug.Stack(0xc042035dd0, 0x4a8020, 0xc042008300)|        D:/Go/src/runtime/debug/stack.go:24 +0x80|main.father.func1.1()|        V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:26 +0x102|panic(0x4a8020, 0xc042008300)|   D:/Go/src/runtime/panic.go:489 +0x2dd|main.father.func1()|      V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:41 +0xac|main.father()|    V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:42 +0x29|main.grandpa()|   V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:16 +0x29|main.main()|      V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:53 +0x27|]

[Father: I recover my son's panic, so I can continue my job, and my old man won't be affected either

=====debug ===dump stack %v
 goroutine 1 [running]:
runtime/debug.Stack(0x4cdf00, 0x66, 0x0)
        D:/Go/src/runtime/debug/stack.go:24 +0x80
main.father.func1.1()
        V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:31 +0x2b7
panic(0x4a8020, 0xc042008300)
        D:/Go/src/runtime/panic.go:489 +0x2dd
main.father.func1()
        V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:41 +0xac
main.father()
        V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:42 +0x29
main.grandpa()
        V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:16 +0x29
main.main()
        V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:53 +0x27

=====facebook=====dump stack shoot panic :[===i am a panic ====]
V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:11 DumpPanicStack
V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:32 father.func1.1
D:/Go/src/runtime/asm_amd64.s:514                               call32
D:/Go/src/runtime/panic.go:489                                  gopanic
V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:41 father.func1
V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:42 father
V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:16 grandpa
V:/RECORD_TEST/testCPP/testgo/main/test_go_facebook_panic.go:53 main
D:/Go/src/runtime/proc.go:185                                   main
D:/Go/src/runtime/asm_amd64.s:2197                              goexit
[Father: son() is doing well]

Grandpa: seems my son is doing well, I've no idea what's going on with my grandchild


zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$

*/

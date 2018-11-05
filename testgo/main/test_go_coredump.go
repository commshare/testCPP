package main

import (
	"fmt"
	"os"
	"runtime/debug"
	"syscall"
)

/*https://guidao.github.io/go_debug.html
go build -gcflags "-N -l" test8.go

*/
func main() {
	test()
}

func test() {
	defer func() {
		if err := recover(); err != nil {
			/*  // recovering from a panic; err contains whatever was passed to panic()*/
			//打印栈信息
			stack := debug.Stack()
			fmt.Printf("%s\n", "-------print-----stack ------")
			fmt.Printf(string(stack))
			/*// if you just want to log the panic, panic again*/
			panic(err) //这里也可以温和的自己控制退出
		}
	}()
	var b map[string]string
	fmt.Printf("use cmd :%s to build", "go build -gcflags \"-N -l\" test8.go")
	b["one"] = "zhang"

	fmt.Println(b)
}

/*

$ ./test_go_coredump.exe
use cmd :go build -gcflags "-N -l" test8.go to buildgoroutine 1 [running]:
runtime/debug.Stack(0xc042035d80, 0x49e9c0, 0xc042008270)
        D:/Go/src/runtime/debug/stack.go:24 +0x80
main.test.func1()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:20 +0x61
panic(0x49e9c0, 0xc042008270)
        D:/Go/src/runtime/panic.go:489 +0x2dd
main.test()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:27 +0x118
main.main()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:13 +0x27
panic: assignment to entry in nil map [recovered]
        panic: assignment to entry in nil map

goroutine 1 [running]:
main.test.func1()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:22 +0xd7
panic(0x49e9c0, 0xc042008270)
        D:/Go/src/runtime/panic.go:489 +0x2dd
main.test()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:27 +0x118
main.main()
        E:/huanju/transcode/daobo/testCPP/testgo/main/test_go_coredump.go:13 +0x27

zhangbin@DESKTOP-1QV8QU4 MINGW64 /e/huanju/transcode/daobo/testCPP/testgo/main (master)
$


*/
/*https://stackoverflow.com/questions/34772012/capturing-panic-in-golang*/
// redirectStderr to the file passed in
func redirectStderr(f *os.File) {
	err := syscall.Dup2(int(f.Fd()), int(os.Stderr.Fd()))
	if err != nil {
		fmt.Printf("Failed to redirect stderr to file: %v", err)
	}
}

func createFile(path string) (file os.File) {
	// detect if file exists
	var _, err := os.Stat(path)

	// create file if not exists
	if os.IsNotExist(err) {
		 file, err = os.Create(path)
		if isError(err) {
			return
		}
		defer file.Close()
	}

	fmt.Println("==> done creating file", path)
}
func isError(err error) bool {
	if err != nil {
		fmt.Println(err.Error())
	}

	return (err != nil)
}
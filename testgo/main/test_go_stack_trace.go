package main

func main() {
	slice := make([]string, 2, 4)
	example(slice, "hello", 10)
}

func example(slice []string, str string, i int) {
	panic("want stack trace")
}

/*

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_stack_trace.exe
panic: want stack trace

goroutine 1 [running]:
main.example(0xc042035f38, 0x2, 0x4, 0x467c9c, 0x5, 0xa)
        V:/RECORD_TEST/testCPP/testgo/main/test_go_stack_trace.go:9 +0x6b   调用到的函数
main.main()
        V:/RECORD_TEST/testCPP/testgo/main/test_go_stack_trace.go:5 +0x7d  被第五行调用

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$
*/

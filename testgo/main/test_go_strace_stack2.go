package main

/*https://www.goinggo.net/2015/01/stack-traces-in-go.html*/
func main() {
	example(true, false, true, 25)
}

func example(b1, b2, b3 bool, i uint8) {
	panic("want stack strace")
}

/*
$ ./test_go_strace_stack2.exe
panic: want stack strace

goroutine 1 [running]:
main.example(0xc019010001)  //All four individual 8 bit values were packed together into a single word:
        V:/RECORD_TEST/testCPP/testgo/main/test_go_strace_stack2.go:8 +0x6b
main.main()
        V:/RECORD_TEST/testCPP/testgo/main/test_go_strace_stack2.go:4 +0x30

*/

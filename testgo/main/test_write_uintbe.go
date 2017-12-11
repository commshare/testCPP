package main

import "fmt"

func WriteUintBE(v uint32, n int) error {
	fmt.Println("----:")
	for i := 0; i < n; i++ {
		b := byte(v>>uint32((n-i-1)<<3)) & 0xff /*construct a new byte （8 bits）*/
		fmt.Printf("b =%v string(b)=%v \n", b, string(b))
	}
	return nil
}

func main() {
	var v uint32 = 1985
	WriteUintBE(v, 1)
	WriteUintBE(v, 2)
	WriteUintBE(v, 3)
	WriteUintBE(v, 4)

}

/*  到底怎么输出才对呢？
zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_write_uintbe.exe
----:
b =193 string(b)=Á
----:
b =7 string(b)=
b =193 string(b)=Á
----:
b =0 string(b)=
b =7 string(b)=
b =193 string(b)=Á
----:
b =0 string(b)=
b =0 string(b)=
b =7 string(b)=
b =193 string(b)=Á

*/

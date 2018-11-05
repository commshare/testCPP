package main

/*https://stackoverflow.com/questions/8039552/byte-endian-convert-by-using-encoding-binary-in-go
https://golangtc.com/t/55237dd8421aa9704b0000cb
*/
import (
	"bytes"
	"encoding/binary"
	"fmt"
)

type T struct {
	F1 [5]byte
	F2 int32
}

func main() {
	var t1, t2 T
	t1 = T{[5]byte{'a', 'b', 'c', 'd', 'e'}, 1234}
	fmt.Println("t1:", t1)
	buf := new(bytes.Buffer)
	/*string和切片等是引用类型，不能用binary.Write。
	binary.Write的第三个参数应该是固定大小的数据类型（uint8, int64...)，或者由固定大小的数据类型组成的复合类型。
	*/
	err := binary.Write(buf, binary.BigEndian, &t1)
	if err != nil {
		fmt.Println(err)
	}
	err = binary.Read(buf, binary.BigEndian, &t2)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("t2:", t2)
}

/*

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_byte_endian.exe
t1: {[97 98 99 100 101] 1234}
t2: {[97 98 99 100 101] 1234}

*/

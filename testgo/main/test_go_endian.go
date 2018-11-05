/*
https://github.com/virtao/GoEndian/blob/master/endian.go
*/

package endian

import (
	"encoding/binary"
	"fmt"
	"unsafe"
)

//保存机器大小端
var Endian binary.ByteOrder
var bigEndian bool

func IsBigEndian() bool {
	return bigEndian
}

func IsLittleEndian() bool {
	return !bigEndian
}

func init() {
	if getEndian() {
		Endian = binary.BigEndian
		bigEndian = true
	} else {
		Endian = binary.LittleEndian
		bigEndian = false
	}
}

//以下代码判断机器大小端
const INT_SIZE int = int(unsafe.Sizeof(0))

//true = big endian, false = little endian
func getEndian() (ret bool) {
	var i int = 0x1
	bs := (*[INT_SIZE]byte)(unsafe.Pointer(&i))
	if bs[0] == 0 {
		return true
	} else {
		return false
	}

}
func main() {
	printEndian()
	useEndian()
}

func printEndian() {
	fmt.Println("Machine byte order : ")
	if endian.IsBigEndian() {
		fmt.Println("Big Endian")
	} else {
		fmt.Println("Little Endian")
	}
}

func useEndian() {
	var iTest int32 = 0x12345678
	var bTest []byte = make([]byte, 4)
	fmt.Println("Int32 to Bytes : ")

	fmt.Println("0x12345678 to current endian : ")
	endian.Endian.PutUint32(bTest, uint32(iTest))
	fmt.Println(bTest)

	fmt.Println("0x12345678 to big endian : ")
	binary.BigEndian.PutUint32(bTest, uint32(iTest))
	fmt.Println(bTest)

	fmt.Println("0x12345678 to little endian : ")
	binary.LittleEndian.PutUint32(bTest, uint32(iTest))
	fmt.Println(bTest)

}

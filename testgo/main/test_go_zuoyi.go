package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
)

/* https://github.com/jemygraw/TechDoc/blob/master/Go%E7%A4%BA%E4%BE%8B%E5%AD%A6/Go%20String%E4%B8%8EByte%E5%88%87%E7%89%87%E4%B9%8B%E9%97%B4%E7%9A%84%E8%BD%AC%E6%8D%A2.markdown
#Go String与Byte切片之间的转换

String转换到Byte数组时，每个byte(byte类型其实就是uint8)保存字符串对应字节的数值。

注意Go的字符串是UTF-8编码的，每个字符长度是不确定的，一些字符可能是1、2、3或者4个字节结尾。

示例1：
*/
func testByte() {
	s1 := "abcd"
	b1 := []byte(s1)
	fmt.Println(b1) // [97 98 99 100]

	s2 := "中文"
	b2 := []byte(s2)
	fmt.Println(b2) // [228 184 173 230 150 135], unicode，每个中文字符会由三个byte组成

	r1 := []rune(s1)
	fmt.Println(r1) // [97 98 99 100], 每个字一个数值

	r2 := []rune(s2)
	fmt.Println(r2) // [20013 25991], 每个字一个数值
}

func main() {
	test := uint32(0)
	test = test << 8
	fmt.Println("ret :", test) /*这个值还是0啊*/

	var str string = "zhangbin"
	var name []byte = []byte(str)

	for i := 0; i < 4; i++ {
		var out byte
		out = name[i]
		fmt.Printf("i %d ret :%v \n", i, out)
	}

	var str1 string = "1024"
	var name1 []byte = []byte(str1)
	fmt.Println("name1 :", name1) /*name1 : [49 48 50 52]*/
	ret := uint32(0)
	for j := 0; j < 4; j++ {
		var outByte byte
		outByte = name1[j]
		fmt.Printf("j %d ret :%v \n", j, outByte)
		ret = ret<<8 + uint32(outByte) /*这么搞，最后打不出来啊 */
		fmt.Printf(" ---- j %d ret :%v \n", j, ret)
	}
	fmt.Printf(" ---final: ret :%d string(ret)=%s \n", ret, string(ret))

	/*https://golangtc.com/t/55237dd8421aa9704b0000cb*/
	/*
				string 不是固定大小数据类型。
				[]byte亲测可用。
				[]byte 是由固定大小数据类型(byte)构成的复合数据类型。但是[]byte不是固定大小的数据类型。

				a slice of fixed-size values这个是说值是固定大小的slice吗？[]byte不是值是固定大小的slice？
		这个是说最顶层可以是切片或者字符串，但是如果是切片其成员类型（或者非切片其类型）必须是定长的。

		定长就意味着，map不行，结构体内部有string/slice/map的不行。

	*/
	data := []byte("1024")
	w := bytes.NewBuffer(nil)
	binary.Write(w, binary.LittleEndian, data)
	size := binary.Size(data)
	orig := make([]byte, size)
	binary.Read(w, binary.LittleEndian, orig)
	/*
		[49 48 50 52]
		1024
	*/
	fmt.Println((orig))       /*直接打印[]byte*/
	fmt.Println(string(orig)) /*把[]byte转为string打印*/

	b := 3
	b = b << 8
	fmt.Println("b (b << 8)= ", b) /*<< 这个代表的是2的8次方啊*/
	fmt.Println("b (3*256) =", 3*256)
}

/* fmt.Println("i ret :", i, ret)
st_go_zuoyi.go

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_zuoyi.exe
ret : 0
i ret : 0 122
i ret : 1 104
i ret : 2 97
i ret : 3 110


		fmt.Printf("i %d ret :%v \n", i, ret)

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_zuoyi.exe
ret : 0
i 0 ret :122
i 1 ret :104
i 2 ret :97
i 3 ret :110


*/

/*
$ ./test_go_zuoyi.exe
ret : 0
i 0 ret :122
i 1 ret :104
i 2 ret :97
i 3 ret :110
name1 : [49 48 50 52]
j 0 ret :49
 ---- j 0 ret :49
j 1 ret :48
 ---- j 1 ret :12592
j 2 ret :50
 ---- j 2 ret :3223602
j 3 ret :52
 ---- j 3 ret :825242164
 ---final: ret :825242164 string(ret)=�
[49 48 50 52]
1024


*/

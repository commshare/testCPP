package main

import (
	"fmt"
	"strings"
)

/*
昨天准备用golang做一个简单的文本分析，需要简单的对字符串进行一些操作，在查看了strings和strconv库时，我没找到截取字符串的函数，同时strings.Index返回的是子串的字节位置，例如这个例子：strings.Index("早上好，张先生！","好") 的返回值是6，而不是2（从0开始算）。


于是我自己写了一个处理中文的返回字符串子串位置的函数，思想其实很简单，首先通过strings库中的Index函数获得子串的字节位置，再通过这个位置获得子串之前的字节数组pre，再将pre转换成[]rune，获得[]rune的长度，便是子串之前字符串的长度，也就是子串在字符串中的字符位置，具体代码如下：
*/
func UnicodeIndex(str, substr string) int {
	// 子串在字符串的字节位置
	result := strings.Index(str, substr)
	if result >= 0 {
		// 获得子串之前的字符串并转换成[]byte
		prefix := []byte(str)[0:result]
		// 将子串之前的字符串转换成[]rune
		rs := []rune(string(prefix))
		// 获得子串之前的字符串的长度，便是子串在字符串的字符位置
		result = len(rs)
	}

	return result
}

/*如果子串是  .ts

$ ./test_go_string_cut.exe
find substr:%v .ts 77
gotstr: http://yycloudlive15013.bs2dl.yy.com/crs_71e55565082f4f31997e98856d0b42df_bak
res: 77

*/
func main() {
	test3()
}

func test1() {

	s := "abcdefg"
	s = string([]byte(s)[:3])
	fmt.Println(s) //得到 "abc"

	/*
		 似乎简单啊，但如果碰到中文咋办？根据常识，一个中文字符肯定不止一个字节，难道我还得遍历每个字节，判断编码，判断ascii码范围？那也太麻烦了吧，当然如果必须这么处理的话，肯定人已经造过轮子，google一下定有收获。

		幸运的是我不需要考虑那么多，除了byte还有另外一个类型rune，使用它完全不用考虑unicode字节问题，一个中文就只站一个数组下标，代码也很简单：
	*/
	s = "a我cd"
	s = string([]rune(s)[:3])
	fmt.Println(s) //得到 "a我c"
}

/*test ok*/
func test2() {

	var str string = "http://yycloudlive15013.bs2dl.yy.com/crs_71e55565082f4f31997e98856d0b42df_bak.ts?s=0&e=553847&tc=0&ts=1493836391"

	substr := "?"

	index := strings.Index(str, substr)
	fmt.Println("find substr:%v", substr, index)
	/*把字符串转成字节数组，然后使用slice切片得到其中想要截取的一段，最后再通过 T() 强制类型转换还原成字符串，一开始比较简单：*/
	var gotstr string
	gotstr = string([]byte(str)[:index])
	fmt.Println("gotstr:", gotstr)
	/*中文*/
	res := UnicodeIndex(str, substr)
	fmt.Println("res:", res)
}

func test3() {
	var str string = "http://yycloudlive15013.bs2dl.yy.com/crs_71e55565082f4f31997e98856d0b42df.ts?s=0&e=553847&tc=0&ts=1493836391"

	substr := ".ts"

	index := strings.Index(str, substr)
	fmt.Println("find substr:%v", substr, index)
	/*把字符串转成字节数组，然后使用slice切片得到其中想要截取的一段，最后再通过 T() 强制类型转换还原成字符串，一开始比较简单：*/
	var gotstr string
	gotstr = string([]byte(str)[:index])
	fmt.Println("gotstr:", gotstr)
	gotstr = gotstr + "_bak.ts"
	fmt.Println("gotstr: ", gotstr)

	fmt.Println("------------------")
	str = string([]byte(str)[:index])
	fmt.Println("now the str:", str)

}

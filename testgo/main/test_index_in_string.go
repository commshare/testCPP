/*
Index 返回字符串 str 在字符串 s 中的索引（str 的第一个字符的索引），-1 表示字符串 s 不包含字符串 str：

strings.Index(s, str string) int



LastIndex 返回字符串 str 在字符串 s 中最后出现位置的索引（str 的第一个字符的索引），-1 表示字符串 s 不包含字符串 str：

strings.LastIndex(s, str string) int


如果 ch 是非 ASCII 编码的字符，建议使用以下函数来对字符进行定位：

strings.IndexRune(s string, r rune) int
*/
package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var str string = "Hi, I'm Marc, Hi."

	fmt.Printf("The position of \"Marc\" is: ")
	fmt.Printf("%d\n", strings.Index(str, "Marc"))

	fmt.Printf("The position of the first instance of \"Hi\" is: ")
	fmt.Printf("%d\n", strings.Index(str, "Hi"))
	fmt.Printf("The position of the last instance of \"Hi\" is: ")
	fmt.Printf("%d\n", strings.LastIndex(str, "Hi"))

	fmt.Printf("The position of \"Burger\" is: ")
	fmt.Printf("%d\n", strings.Index(str, "Burger"))

	var str2 = "15013_74617895_74617895_1506787200"
	fmt.Printf("The position of \"_\" is: ")
	index := strings.Index(str2, "_")
	fmt.Printf("%d\n", index)
	appid := str2[0:index]
	fmt.Printf("appid is: %s and getAppid %d", appid, getAppid(str2))

	tsurl := "http://1.2.3.2:4704/692213320842427481_9042_150143_2425503_14516287040.ts?org=man&uuid=a310c09419f94d0fb3f63ebf3b7d6079&ex_aname=15013_xa_69571171_69571171_0_0_0&ex_vname=15013_xv_69571171_69571171_0_0_0&seq=50408102&tk=1d491ab2814040c54d4b0e02b8fd8318&tc=0&r=852x480&topsid=1344673310"
	testResoultion(tsurl)
}

/*
$ ./test_index_in_string.exe
The position of "Marc" is: 8
The position of the first instance of "Hi" is: 0
The position of the last instance of "Hi" is: 14
The position of "Burger" is: -1

*/

func getAppid(str2 string) int64 {
	index := strings.Index(str2, "_")
	fmt.Printf("%d\n", index)
	appid := str2[0:index]
	fmt.Printf("appid is: %s", appid)
	int64_appid, _ := strconv.ParseInt(appid, 10, 64)
	return int64_appid
}

/*
http://www.voidcn.com/article/p-rgepaozy-kc.html

#string到int
int,err:=strconv.Atoi(string)
#string到int64
int64, err := strconv.ParseInt(string, 10, 64)
#int到string
string:=strconv.Itoa(int)
#int64到string
string:=strconv.FormatInt(int64,10)

*/

func testResoultion(tsurl string) {
	var resolution string /*如r=1280x720 , 异常 r=0x0*/
	resolutionIndex := strings.Index(tsurl, "r=")
	if resolutionIndex >= 0 {
		tmpstr := tsurl[resolutionIndex:]
		probe := strings.Index(tmpstr, "&")
		if probe == -1 {
			resolution = tmpstr
		} else {
			if probe > 0 {
				resolution = tmpstr[0:probe]
			}
		}
		fmt.Printf("\nresolution %v probe %v\n", resolution, probe)
	} else {
		fmt.Printf("\nerr : no r= \n")
	}
}

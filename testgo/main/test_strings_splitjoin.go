/*
4.7.8 修剪字符串

你可以使用 strings.TrimSpace(s) 来剔除字符串开头和结尾的空白符号；如果你想要剔除指定字符，则可以使用 strings.Trim(s, "cut") 来将开头和结尾的 cut 去除掉。
该函数的第二个参数可以包含任何字符，如果你只想剔除开头或者结尾的字符串，则可以使用 TrimLeft 或者 TrimRight 来实现。


*/
package main

import (
	"fmt"
	"strings"
)

func output(src string, dst string, operation string) {
	fmt.Println("")
	fmt.Printf("original : [%s]", src)
	fmt.Printf("after %s: [%s]", operation, dst)
	fmt.Println("")
}
func trim() {
	str := " gunzhangbin in shandongun "
	var s string
	/*去掉空格*/
	s = strings.TrimSpace(str)
	output(str, s, "TrimSpace")

	/**/
	dst := strings.Trim(s, "gun")
	output(s, dst, "Trim")
}

/*
4.7.9 分割字符串

strings.Fields(s) 将会利用 1 个或多个空白符号来作为动态长度的分隔符将字符串分割成若干小块，并返回一个 slice，如果字符串只包含空白符号，则返回一个长度为 0 的 slice。

strings.Split(s, sep) 用于自定义分割符号来对指定字符串进行分割，同样返回 slice。

因为这 2 个函数都会返回 slice，所以习惯使用 for-range 循环来对其进行处理（第 7.3 节）。

4.7.10 拼接 slice 到字符串

Join 用于将元素类型为 string 的 slice 使用分割符号来拼接组成一个字符串：

strings.Join(sl []string, sep string) string

*/
func main() {
	trim()
	str := "The quick brown fox jumps over the lazy dog"
	sl := strings.Fields(str)
	fmt.Printf("Splitted in slice: %v\n", sl)
	for _, val := range sl {
		fmt.Printf("%s - ", val)
	}
	fmt.Println()
	str2 := "GO1|The ABC of Go|25"
	sl2 := strings.Split(str2, "|")
	fmt.Printf("Splitted in slice: %v\n", sl2)
	for _, val := range sl2 {
		fmt.Printf("%s - ", val)
	}
	fmt.Println()
	str3 := strings.Join(sl2, ";")
	fmt.Printf("sl2 joined by ;: %s\n", str3)
}

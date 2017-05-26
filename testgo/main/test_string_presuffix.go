package main

import (
	"fmt"
	"strings"
)

/*
HasPrefix 判断字符串 s 是否以 prefix 开头：

strings.HasPrefix(s, prefix string) bool
HasSuffix 判断字符串 s 是否以 suffix 结尾：

strings.HasSuffix(s, suffix string) bool

*/
func main() {
	var str string = "This is an example of a string"
	/*\"转义之后，就可以打印出来了。*/
	fmt.Printf("T/F? Does the string \"%s\" have prefix %s? ", str, "Th")
	fmt.Printf("%t\n", strings.HasPrefix(str, "Th"))
}

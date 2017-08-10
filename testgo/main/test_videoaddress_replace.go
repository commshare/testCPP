package main

import (
	"fmt"
	"strings"
)

/*不会改变*/
func doreplace(addr string) {
	addr = strings.Replace(addr, ".ts", "_bak.ts", 1)
	fmt.Println("in replace :addr is : %v", addr)

}
func doreplacePointer(addr *string) {
	*addr = strings.Replace(*addr, ".ts", "_bak.ts", 1)
	fmt.Println("in replace :addr is : %v", *addr)

}

/*
2017/08/01 14:32:14 [playlist_generator.go:700] [I]
原来这个是带有s和e的
strLastTSAddress http://yycloudlive15013.bs2dl.yy.com/crs_db6888ecd3754e7b9376914410fd9b63
item.VideoAddress http://yycloudlive15013.bs2dl.yy.com/crs_db6888ecd3754e7b9376914410fd9b63.ts?s=34918932&e=35496655 ,
get name http://yycloudlive15013.bs2dl.yy.com/crs_db6888ecd3754e7b9376914410fd9b63
*/
func getTSName(str string) (name string) {
	substr := ".ts"
	index := strings.Index(str, substr)
	name = string([]byte(str)[:index])
	return
}
func main() {
	addr := "http://chaina.ts"
	fmt.Println("1 before replace :addr is : %v", addr)

	doreplace(addr)
	fmt.Println("1 after replace :addr is : %v", addr)
	addr = "http://chaina.ts"

	fmt.Println("2 before replace :addr is : %v name :%v", addr, getTSName(addr))
	doreplacePointer(&addr)
	fmt.Println("2 after replace :addr is : %v name %v", addr, getTSName(addr))

}

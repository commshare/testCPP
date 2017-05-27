package main

/*
http://blog.haohtml.com/archives/14239
*/
import (
	"fmt"
)

type Result struct {
	appid uint32
	flag  uint32
	home  string
}

func do(appid uint32, flag uint32, home string) (res Result) {
	res = Result{appid, flag, home}
	return
}

func main() {
	var res Result
	res = Result{100, 1, "zhangbin"}
	fmt.Println("res:", res, res.appid, res.flag)

	/*指针*/
	var pRes *Result
	pRes = &Result{200, 0, ""}
	fmt.Println("pRes: ", pRes, pRes.appid, pRes.flag)

	/*空的，默认的初值*/
	var eRes = Result{}
	fmt.Println("eRes:", eRes, eRes.appid, eRes.flag)

	if eRes.home == "" { /*执行这个*/
		fmt.Println("home is empty")
	} else {
		fmt.Println("not empty")
	}

	/*函数的返回值*/
	result := do(res.appid, res.flag, res.home)
	fmt.Println("result:", result)

	/*使用new , nRes是一个指针啊*/
	nPRes := new(Result)
	fmt.Println("nPRes:", nPRes)
	nPRes.appid = 300
	nPRes.flag = 20
	nPRes.home = "gz"
	fmt.Println("then nRes:", nPRes)
}

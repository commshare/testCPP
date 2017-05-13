/*https://github.com/astaxie/build-web-application-with-golang/blob/master/zh/04.1.md*/
package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"strconv"
	"strings"
)

func sayhelloName(w http.ResponseWriter, r *http.Request) {
	r.ParseForm() //解析url传递的参数,对于POST则解析响应包的主体(request body)
	//注意:如果没有调用ParseForm方法,下面无法获取表单的数据
	fmt.Println(r.Form) //这些信息是输出到服务器端的打印信息\
	fmt.Println("path", r.URL.Path)
	fmt.Println("scheme", r.URL.Scheme)
	fmt.Println(r.Form["url_long"])
	for k, v := range r.Form {
		fmt.Println("key:", k)
		fmt.Println("val:", strings.Join(v, ""))
	}
	fmt.Fprintf(w, "Hello wow!") //这个写入到w的是输出到客户端的
}
func login(w http.ResponseWriter, r *http.Request) {
	fmt.Println("method:", r.Method) //获取请求的方法
	if r.Method == "GET" {
		t, _ := template.ParseFiles("login.html")
		t.Execute(w, nil)
	} else {
		r.ParseForm() //解析url传递的参数,对于POST则解析响应包的主体(request body)
		//请求的是登陆数据,那么执行登陆的逻辑判断
		fmt.Println("username:", r.Form["username"])
		fmt.Println("password:", r.Form["password"])
		fmt.Fprintf(w, "Hello %s!", r.Form["username"]) //这个写入到w的是输出到客户端的
	}
}
func test(w http.ResponseWriter, r *http.Request) {
	r.ParseForm() //解析url传递的参数,对于POST则解析响应包的主体(request body)
	//注意:如果没有调用ParseForm方法,下面无法获取表单的数据
	fmt.Println(r.Form) //这些信息是输出到服务器端的打印信息\
	fmt.Println("path", r.URL.Path)
	fmt.Println("scheme", r.URL.Scheme)
	fmt.Println(r.Form["url_long"])
	for k, v := range r.Form {
		fmt.Println("key:", k)
		fmt.Println("val:", strings.Join(v, ""))
	}
	fmt.Fprintf(w, "Hello wow!") //这个写入到w的是输出到客户端的

	//var option int = 0
	var optionParam string

	if len(r.Form["option"]) > 0 {
		optionParam = r.Form["option"][0]
		//	testoptionParam = r.Form["option"][1]

		//fmt.Println("1 optionParam:", optionParam, "testoptionParam:", testoptionParam)
	}

	if optionParam == "vipstream" {
		fmt.Println("vipstream...")
	} else {
		fmt.Println("2 optionParam:", optionParam)
	}
	fmt.Println("3 optionParam:", optionParam)

	var req *http.Request
	req = r
	str_allow_delete := req.FormValue("allow_deleted")
	if str_allow_delete == "" {
		fmt.Println("str_allow_delete is empty")
	} else {
		fmt.Println("str_allow_delete is :", str_allow_delete)
	}
	param_allowdelted, err := strconv.ParseInt(str_allow_delete, 10, 32)
	if err != nil {
		fmt.Println("fail: str_allow_delete :", str_allow_delete, "param_allowdelted :", param_allowdelted)
	} else {
		fmt.Println("ok, str_allow_delete :", str_allow_delete, "param_allowdelted :", param_allowdelted)
	}
	if param_allowdelted == 1 {
		fmt.Fprintf(w, "you ask return deleted items")
	}
}
func main() {
	var err error
	http.HandleFunc("/test", test)          //设置访问的路由
	http.HandleFunc("/login", login)        //设置访问的路由
	err = http.ListenAndServe(":9090", nil) //设置监听的端口
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}

/*
localhost:9090/test?appid="020"&option=vipstream
输出：
map[appid:["020"] option:[vipstream]]
path /test
scheme
[]
key: appid
val: "020"
key: option
val: vipstream
1 optionParam: vipstream
vipstream...
3 optionParam: vipstream


localhost:9090/test?appid="020"&option=“vipstream”
输出：

$ ./test_go_httpsrv.exe
map[appid:["020"] option:["vipstream"]]
path /test
scheme
[]
key: appid
val: "020"
key: option
val: "vipstream"
1 optionParam: "vipstream"
2 optionParam: "vipstream"
3 optionParam: "vipstream"



localhost:9090/test?appid="020"&option=vipstream mystream

$ ./test_go_httpsrv.exe
map[appid:["020"] option:[vipstream mystream]]
path /test
scheme
[]
key: appid
val: "020"
key: option
val: vipstream mystream
2 optionParam: vipstream mystream
3 optionParam: vipstream mystream


localhost:9090/test?appid="020"&option=vipstream mystream
$ ./test_go_httpsrv.exe
map[appid:["020"] option:[vipstream mystream]]
path /test
scheme
[]
key: appid
val: "020"
key: option
val: vipstream mystream
2 optionParam: vipstream mystream
3 optionParam: vipstream mystream
str_allow_delete is empty
str_allow_delete :  param_allowdelted : 0



localhost:9090/test?appid="020"&option=vipstream mystream&allow_deleted=1

$ ./test_go_httpsrv.exe
map[allow_deleted:[1] appid:["020"] option:[vipstream mystream]]
path /test
scheme
[]
key: appid
val: "020"
key: option
val: vipstream mystream
key: allow_deleted
val: 1
2 optionParam: vipstream mystream
3 optionParam: vipstream mystream
str_allow_delete is : 1
ok, str_allow_delete : 1 param_allowdelted : 1

可以累加写的啊：
localhost:9090/test?appid="020"&option=vipstream mystream&allow_deleted=1
Hello wow!you ask return deleted items
*/

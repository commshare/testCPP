/*
https://gist.github.com/montanaflynn/b390b1212dada5864d9b#file-easyget-go-L33

*/
package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"os"

	"./easyget"
)

// Define response data
type Data struct {
	Date   string
	Cases  int
	Status string
}

func AutherTest() {

	// Create any headers we want to send
	headers := make(map[string][]string)
	headers["X-Header-Info"] = []string{"Something"}
	headers["X-Header-Array"] = []string{"One", "Two"}

	// Build the Request struct
	req := easyget.Request{
		BaseUrl:     "http://192.241.227.237/",
		Endpoint:    "ebola/project",
		QueryString: "?distance=5",
		Headers:     headers,
	}

	// Send the request
	res, err := easyget.Get(req)

	// Print error if it exists
	if err != nil {
		fmt.Println(err)
	}

	// Print the stuff in Response struct
	fmt.Println(res.Body.String)
	fmt.Println(res.Headers)
	fmt.Println(res.Status)
	fmt.Println(res.Protocol)

	// Since we have a JSON array lets turn it into a Go array
	var data []Data
	json.Unmarshal(res.Body.Bytes, &data)

	// Print what we got with keys
	fmt.Printf("%+v\n", data)

	// Loop over array and print some stuff we found
	for _, e := range data {
		fmt.Printf("%v total %v cases: %v \n", e.Date, e.Status, e.Cases)
	}
}

type MYData struct {
	Filestatus string `json:"filestatus"`
}
type Response1 struct {
	Page int
}
type Response2 struct {
	File int /*一定要大写*/
}
type Response3 struct {
	Filename string /*一定要大写*/
}

/*http://yycloudlive15013.bs2dl.yy.com/crs_06d2942cf16044f5b8a86fd497714e1f.ts
http://yycloudlive15013.bs2dl.yy.com/crs_06d2942cf16044f5b8a86fd497714e1f.ts?fileinformationv2
*/
func mytest() {

	/*
	   This variable m is a map of string keys to int values:

	   var m map[string]int
	   Map types are reference types, like pointers or slices, and so the value of m above is nil; it doesn't point to an initialized map.
	   A nil map behaves like an empty map when reading, but attempts to write to a nil map will cause a runtime panic; don't do that.
	   To initialize a map, use the built in make function:

	   m = make(map[string]int)
	*/
	/*http://yycloudlive15013.bs2dl.yy.com/crs_06d2942cf16044f5b8a86fd497714e1f.ts*/
	req := easyget.Request{
		BaseUrl:     "http://yycloudlive15013.bs2dl.yy.com/",
		Endpoint:    "crs_06d2942cf16044f5b8a86fd497714e1f.ts?",
		QueryString: "fileinformationv2",
		Headers:     nil,
	}
	/*发送请求*/
	res, err := easyget.Get(req)

	if err != nil {
		fmt.Println(err)
	}
	// Print the stuff in Response struct
	fmt.Println("-----Print the stuff in Response struct----")
	fmt.Println("====show body:")
	fmt.Println(res.Body.String)
	fmt.Println("====show headers:")
	fmt.Println(res.Headers)
	fmt.Println("====show res.Status:")
	fmt.Println(res.Status)
	fmt.Println("====show res.Protocol :")
	fmt.Println(res.Protocol)

	/*json转为go的数组，要存在这里*/
	var data MYData
	err1 := json.Unmarshal(res.Body.Bytes, &data)
	if err1 != nil {
		fmt.Println("Fatal error ", err1.Error())
		//os.Exit(0)
	}
	fmt.Printf("json:  %+v \n ", data)
	fmt.Println("value:", data.Filestatus)
	if data.Filestatus == "-1" {
		fmt.Println("file status is -1")
	}

	if data.Filestatus == "0" {
		fmt.Println("file status is 0")
	}
	fmt.Println("======show response one by one of data array ===========")
	/*	for i, _ := range data {
		fmt.Printf(" data[%v]=[%v]\n", i, data[i])
	}*/
	str := `{"page": 10 }`
	res1 := Response1{}
	json.Unmarshal([]byte(str), &res1)
	fmt.Println(res1)

	fmt.Println("-----------------")

	str2 := `{"File": 200 }` /*这里的File大小写都是ok的*/
	res2 := Response2{}
	json.Unmarshal([]byte(str2), &res2)
	fmt.Println(res2)

	fmt.Println("--------------")
	str3 := `{"Filename": "zhangbin"}`
	res3 := Response3{}
	json.Unmarshal([]byte(str3), &res3)
	fmt.Println(res3)
	//ms := res3.Get("Filename").MustString()
	fmt.Println("Filename value : ", res3.Filename)
}

/*
http://yycloudlive15013.bs2dl.yy.com/crs_71e55565082f4f31997e98856d0b42df_bak.ts?fileinformation
{"filestatus": "0"}



*/
func main() {
	/*ok with json*/
	mytest()

	//ok
	//getHTTPClinet()
}

/*
$ ./test_go_http_easyget.exe
-----Print the stuff in Response struct----

    <!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
    <html>
        <head>
            <title>Error: 404 Not Found</title>
            <style type="text/css">
              html {background-color: #eee; font-family: sans;}
              body {background-color: #fff; border: 1px solid #ddd;
                    padding: 15px; margin: 15px;}
              pre {background-color: #eee; border: 1px solid #ddd; padding: 5px;                                                                                                                                                                                               }
            </style>
        </head>
        <body>
            <h1>Error: 404 Not Found</h1>
            <p>Sorry, the requested URL <tt>&#039;http://yycloudlive15013.bs2dl.                                                                                                                                                                                               yy.com/crs_ba265a91789342f38c75694e427ef174_bak.ts/fileinformationv2&#039;</tt>
               caused an error:</p>
            <pre>File Not Found</pre>
        </body>
    </html>

map[Server:[openresty] Content-Length:[786] X-Cdn-Info:[36.250.240.113] X-Cache-                                                                                                                                                                                               Remote:[MISS] Access-Control-Expose-Headers:[X-Cdn-Info, Age, X-Cache-Remote] Da                                                                                                                                                                                               te:[Mon, 22 May 2017 03:09:13 GMT] Content-Type:[text/html; charset=UTF-8] Via:[                                                                                                                                                                                               1.1 jinchengwangtong61:2 (Cdn Cache Server V2.0)[453 404 2], 1.1 txz113:3 (Cdn C                                                                                                                                                                                               ache Server V2.0)[575 404 2]] Access-Control-Allow-Origin:[*]]
404
HTTP/1.1
got response:  []



*/

/*
zhangbin@DESKTOP-1QV8QU4 MINGW64 /j/MYSELF/testCPP/testgo/main (master)
$ ./test_go_http_easyget.exe
-----Print the stuff in Response struct----
====show body:
{"filestatus": "-1"}
====show headers:
map[Date:[Mon, 22 May 2017 04:10:41 GMT] Content-Type:[text/json] Accept-Ranges:[bytes] X-Cdn-Info:[36.250.240.113] Access-Control-Expose-Headers:[X-Cdn-Info, Age, X-Cache-Remote] Cache-Control:[public,max-age=86400] Via:[1.1 ngtong23:6 (Cdn Cache Server V2.0)[198 200 2], 1.1 txz113:3 (Cdn Cache Server V2.0)[311 200 2]] Connection:[keep-alive] X-Cache-Remote:[MISS] Access-Control-Allow-Origin:[*] Expires:[Tue, 23 May 2017 04:10:41 GMT] Server:[openresty] Content-Length:[20]]
====show res.Status:
200
====show res.Protocol :
HTTP/1.1
got response:  []
======show response one by one of data array ===========

zhangbin@DESKTOP-1QV8QU4 MINGW64 /j/MYSELF/testCPP/testgo/main (master)


这个有
http://yycloudlive15013.bs2dl.yy.com/crs_71e55565082f4f31997e98856d0b42df_bak.ts?fileinformation

*/
//"crs_ba265a91789342f38c75694e427ef174_bak.ts?"
func getHTTPClinet() {
	req := easyget.Request{
		BaseUrl:     "http://yycloudlive15013.bs2dl.yy.com/",
		Endpoint:    "crs_ba265a91789342f38c75694e427ef174_bak.ts?",
		QueryString: "fileinformationv2",
		Headers:     nil,
	}

	//生成client 参数为默认
	client := &http.Client{}

	//生成要访问的url
	var url string
	url += req.BaseUrl
	url += req.Endpoint
	url += req.QueryString
	fmt.Printf("============url :[%s]\n", url)
	//提交请求
	reqest, err := http.NewRequest("GET", url, nil)

	if err != nil {
		panic(err)
	}

	//处理返回结果
	response, _ := client.Do(reqest)

	//将结果定位到标准输出 也可以直接打印出来 或者定位到其他地方进行相应的处理
	stdout := os.Stdout
	_, err = io.Copy(stdout, response.Body)

	//返回的状态码
	status := response.StatusCode

	fmt.Println("response status : ", status)
	/*
		$ ./test_go_http_easyget.exe
		============url :[http://yycloudlive15013.bs2dl.yy.com/crs_ba265a91789342f38c75694e427ef174_bak.ts?fileinformationv2]
		{"filestatus": "-1"}200

	*/

	if status == 200 {
		fmt.Println("http get ok ")
	}
}

package main

import (
	"fmt"
	"net/http"
)

func main() {
	res, err := http.Head("https://golang.org")
	if err != nil {
		panic(err)
	}
	contentlength := res.ContentLength
	fmt.Printf("ContentLength:%v \n", contentlength)
	fmt.Printf("res:%+v \n", res)

}

/*
zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_http_head.exe
ContentLength:8485
res:&{Status:200 OK StatusCode:200
Proto:HTTP/2.0 ProtoMajor:2
ProtoMinor:0 Header:map[Strict-Transport-Security:[max-age=31536000; preload] Content-Type:[text/html; charset=utf-8] X-Cloud-Trace-Context:[69e5208a4ed3f02ad70266589da4a584] Date:[Thu, 07 Dec 2017 01:22:00 GMT] Server:[Google Frontend] Content-Length:[8485] Alt-Svc:[hq=":443"; ma=2592000; quic=51303431; quic=51303339; quic=51303338; quic=51303337; quic=51303335,quic=":443"; ma=2592000; v="41,39,38,37,35"]] Body:{Reader:0xc04204aa80} ContentLength:8485 TransferEncoding:[] Close:false Uncompressed:false Trailer:map[] Request:0xc042000700 TLS:0xc04207c6e0}

*/

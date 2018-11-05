package main

/*http://www.01happy.com/golang-http-client-get-and-post/*/
import (
	"fmt"
	"io/ioutil"
	"net/http"
	"net/url"
	"strings"
)

func httpGet(url string) {
	fmt.Printf("=-=-=-=-=-=-=-=-=-=-=-httpGet url %v \n", url)

	resp, err := http.Get(url)
	if err != nil {
		// handle error
		fmt.Printf("http get err: %v resp [%v] StatusCode[%v]", err, resp, resp.StatusCode)
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
		fmt.Printf("read http resp body fail err: [%v] body [%v]", err, body)
	}

	fmt.Printf("the http get resp body [%v] StatusCode[%v] \n", string(body), resp.StatusCode)
}

func httpPost() {
	resp, err := http.Post("http://www.01happy.com/demo/accept.php",
		"application/x-www-form-urlencoded",
		strings.NewReader("name=cjb"))
	if err != nil {
		fmt.Println(err)
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
	}

	fmt.Println(string(body))
}

func httpPostForm() {
	resp, err := http.PostForm("http://www.01happy.com/demo/accept.php",
		url.Values{"key": {"Value"}, "id": {"123"}})

	if err != nil {
		// handle error
	}

	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
	}

	fmt.Println(string(body))

}

func httpDo() {
	client := &http.Client{}

	req, err := http.NewRequest("POST", "http://www.01happy.com/demo/accept.php", strings.NewReader("name=cjb"))
	if err != nil {
		// handle error
	}

	req.Header.Set("Content-Type", "application/x-www-form-urlencoded")
	req.Header.Set("Cookie", "name=anny")

	resp, err := client.Do(req)

	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		// handle error
	}

	fmt.Println(string(body))
}

func main() {
	var url string
	url = "http://www.01happy.com/demo/accept.php?id=1"
	url = "http://hls.yy.com/newlive/1348445615_1348445615.m3u8?appid=0&uuid=caa87ac6073f4178bf82bb6b04c66793&org=yyxcrs&tk=68e403fe08e7a26d6bc0840a090e8ebc&t=1506678166&uid=0&ex_fm3=1&callback=cb&groupid=16381878&ex_coderate=0"
	url = "http://220.194.67.244:476/1348141098_1348141098_15013_0_0_15013.m3u8?uuid=1ff2a0d016214f839872e6af95f14593&org=yyxcrs&m=1d420231345dacfabdfd82bbb7fb158c&r=363426099&v=1&t=1506346576&uid=0&ex_coderate=0&ex_fm3=1"
	httpGet(url)
	/*	httpPost()
		httpPostForm()
		httpDo()*/
}

/*
subscribe m3u8 file subscribeAddr[http://220.194.67.244:476/1348141098_1348141098_15013_0_0_15013.m3u8?uuid=1ff2a0d016214f839872e6af95f14593&org=yyxcrs&m=1d420231345dacfabdfd82bbb7fb158c&r=363426099&v=1&t=1506346576&uid=0&ex_coderate=0&ex_fm3=1] error: Get http://220.194.67.244:476/1348141098_1348141098_15013_0_0_15013.m3u8?uuid=1ff2a0d016214f839872e6af95f14593&org=yyxcrs&m=1d420231345dacfabdfd82bbb7fb158c&r=363426099&v=1&t=1506346576&uid=0&ex_coderate=0&ex_fm3=1: net/http: request canceled (Client.Timeout exceeded while awaiting headers)
*/
/*
$ ./test_go_http_client.exe
=-=-=-=-=-=-=-=-=-=-=-httpGet url http://hls.yy.com/newlive/1348445615_1348445615.m3u8?appid=0&uuid=caa87ac6073f4178bf82bb6b04c66793&org=yyxcrs&tk=68e403fe08e7a26d6bc0840a090e8ebc&t=1506678166&uid=0&ex_fm3=1&callback=cb&groupid=16381878&ex_coderate=0
the http get resp body [not found] StatusCode[404]

这个错误就是这样的：
$ ./test_go_http_client.exe
=-=-=-=-=-=-=-=-=-=-=-httpGet url http://220.194.67.244:476/1348141098_134814109            8_15013_0_0_15013.m3u8?uuid=1ff2a0d016214f839872e6af95f14593&org=yyxcrs&m=1d4202            31345dacfabdfd82bbb7fb158c&r=363426099&v=1&t=1506346576&uid=0&ex_coderate=0&ex_f            m3=1
the http get resp body [{ "errCode": 205, "errMsg": "HTTP URL TIMEOUT"}] StatusC            ode[404]


*/

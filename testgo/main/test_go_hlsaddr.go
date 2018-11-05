package main

import (
	"fmt"
	"strings"
)

func main() {
	resp_body := "cb(\"http://2.12.11.4:8446/15013_xv_17559200_17559200_0_0_0-15013_xa_17559200_17559200_0_0_0-0-0.m3u8?uuid=55e1a89bca494f44b71cf457fea9cead&org=yyxcrs&m=3ca095aa9f890136130eb27519fa1e0d&r=2091918002&v=1&t=1521432105&uid=0&ex_coderate=0&ex_fm3=1\")"
	resparr := strings.Split(string(resp_body), "\"")
	if len(resparr) <= 1 {
		fmt.Printf("resparr <=1 : %v \n", resparr)
		return
	}
	fmt.Printf("resparr ok: %v \n", resparr)
}

package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	//tsuri := "http://175.6.128.18:664/32677847_10034_6634930815917905880_2014812193_1502269255_254_10034.ts?org=yyxcrs&uuid=91ac662328654a56a0f37b5948b826a0&seq=36392454&tk=15833be95c14c0695c62e51251aea3f4&tc=0&r=800x600"
	uri := "zhang.ts?tc=1"
	var tc uint32
	tcidx := strings.Index(uri, "tc=") /*从0开始计算的第九个位置。tc=前面有个9个字符*/
	if tcidx >= 0 {
		/*Atoi(s string) (i int, err error) 将字符串转换为int 型*/
		num, err := strconv.Atoi(uri[tcidx+3 : tcidx+4]) /*主要是这里看不懂啊*/
		if err == nil {
			tc = uint32(num)
			/*tcidex=9 tc=1 uri[tcidx+3:] is (1)
			 */
			fmt.Printf("tcidex=%d tc=%d uri[tcidx+3:] is (%v)\n", tcidx, tc, uri[tcidx+3:])
		}
	}

	tsurl := "http://175.6.128.18:664/32677847_10034_6634930815917905880_2014812193_1502269255_254_10034.ts?org=yyxcrs&uuid=91ac662328654a56a0f37b5948b826a0&seq=36392454&tk=15833be95c14c0695c62e51251aea3f4&tc=0&r=800x600"
	uri = tsurl
	uri = uri[strings.LastIndex(uri, "/")+1:]
	/*(32677847_10034_6634930815917905880_2014812193_1502269255_254_10034.ts?org=yyxcrs&uuid=91ac662328654a56a0f37b5948b826a0&seq=36392454&tk=15833be95c14c0695c62e51251aea3f4&tc=0&r=800x600)
	 */
	fmt.Printf("uri is (%s)\n", uri)

	/*uri is (32677847_10034_6634930815917905880_2014812193_1502269255_254_10034)*/
	uri = uri[:strings.Index(uri, ".")]
	fmt.Printf("uri is (%s)\n", uri)
	/*uri is ([32677847 10034 6634930815917905880 2014812193 1502269255 254 10034])*/
	fiveTuple := strings.Split(uri, "_")
	fmt.Printf("uri is (%s)\n", fiveTuple)

	resolutionIndex := strings.Index(tsurl, "r=")
	if resolutionIndex >= 0 {
		resolution := tsurl[resolutionIndex:]
		fmt.Printf("get resolution %s\n", resolution)
	} else {
		fmt.Println("get resolution fail")
	}

}

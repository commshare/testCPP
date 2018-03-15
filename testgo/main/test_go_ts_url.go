package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	olds := "http://1.1.1.1:472/32677847_10034_6634930814407032624_503780193_1514545448_437_10034.ts?org=yyxcrs&uuid=adbad1d2af5049e9a81d0e285da5fbb7&seq=48668637&tk=5a4b6da8ec64964ba6b83b01374e6c0a&tc=0&r=800x600"
	fmt.Println("olds :", olds)
	news := "http://1.0.1.1:548/54880976_15013_4077681207113680442_6973423_1514548797_3998_15013.ts?org=yyxcrs&uuid=c7c1ef26250249dda434b2ffa523224a&seq=48671117&tk=0831eb54b7c4c010313e889797b953cd&tc=0&r=1280x720"
	fmt.Println("news :", news)

	realNews := "http://1.88.1.1:1/11590473265366802950_17371218_1514544474_362_15013.ts?org=yyxcrs&uuid=c7c1ef26250249dda434b2ffa523224a&ex_aname=15013_xa_54880976_54880976_0_0_0&ex_vname=15013_xv54880976_54880976_0_0_0&seq=48667562&tk=dbb230aa66e8688e6533c2ab9787d7c3&tc=0&r=1280x720"
	fmt.Println("news :", realNews)
	yuhui := "http://1.1.7.3:5612/11591863657949991572_210_15013_27892299_1514555319.ts?org=yyxcrs&uuid=a53240777f6443299fb5eb0f79d851f4&ex_aname=15013_xa_22490906_22490906_0_0_0&ex_vname=15013_xv_22490906_22490906_0_0_0&seq=48678410&tk=8676e2b6ec8d1ea5a9cbc90384020b84&tc=0&r=1280x720"
	uri := yuhui
	uri = uri[strings.LastIndex(uri, "/")+1:]
	uri = uri[:strings.Index(uri, ".")]
	fiveTuple := strings.Split(uri, "_")
	if len(fiveTuple) < 5 {
		fmt.Printf("invalid segment uri: %s, five tuple: %v \n", uri, fiveTuple)

	}
	fmt.Printf("OK :five %v \n", fiveTuple)
	startTime, err := strconv.ParseUint(fiveTuple[4], 10, 64)
	if err != nil {
		fmt.Printf("ERR invalid segment uri: %s, parse start time error: %v \n", uri, err)
	}
	//continue
	fmt.Printf("OK segment uri: %v, parse start time %v \n", startTime, err)
	dts, err := strconv.ParseUint(fiveTuple[3], 10, 64)
	if err != nil {
		fmt.Printf(" invalid segment uri: %s, parse dts error: %v \n", dts, err)
		//continue
	}
	fmt.Printf("OK segment uri: %v, parse dts : %v \n", dts, err)
	if startTime < 1453366487000 { //兼容以前单位是秒的情况，以后前端传过来的是毫秒
		startTime = (startTime * 1000) + (dts % 1000)
	}
	//segmentFileName := fmt.Sprintf("%s_%d_%d_%d.ts", common.MD5(common.CutURI(piece.URI)), startTime, dts, t.perf.iServerIP)
}

/*

$ ./test_go_ts_url.exe
OK :five [32677847 10034 6634930814407032624 503780193 1514545448 437 10034]
OK segment uri: 1514545448, parse start time <nil>
OK segment uri: 503780193, parse dts : <nil>

OK :five [54880976 15013 4077681207113680442 6973423 1514548797 3998 15013]
OK segment uri: 1514548797, parse start time <nil>
OK segment uri: 6973423, parse dts : <nil>


OK :five [11590473265366802950 17371218 1514544474 362 15013]
OK segment uri: 15013, parse start time <nil>
OK segment uri: 362, parse dts : <nil>

OK :five [11591863657949991572 210 15013 27892299 1514555319]
OK segment uri: 1514555319, parse start time <nil>
OK segment uri: 27892299, parse dts : <nil>

*/

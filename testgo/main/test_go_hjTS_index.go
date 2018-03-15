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
	fmt.Printf("from LastIndex+1 :uri is (%s)\n", uri)

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

	/*$ ./test_go_hjTS_index.exe
	  tcidex=9 tc=1 uri[tcidx+3:] is (1)
	  uri is (32677847_10034_6634930815917905880_2014812193_1502269255_254_10034.ts?org=yyxcrs&uuid=91ac662328654a56a0f37b5948b826a0&seq=36392454&tk=15833be95c14c0695c62e51251aea3f4&tc=0&r=800x600)
	  uri is (32677847_10034_6634930815917905880_2014812193_1502269255_254_10034)
	  uri is ([32677847 10034 6634930815917905880 2014812193 1502269255 254 10034])
	  get resolution r=800x600
	  rIdx 88 and tcIdx 98
	  get resolution r=800x600

	*/
	newurl := "http://live10034.bs2dl.yy.com/crs_02899c9350644092ac1399ebef083b6c.ts?s=658000&e=758767&r=800x600&tc=0&ts=1502348602"
	rIdx := strings.Index(newurl, "r=")
	tcIdx := strings.Index(newurl, "tc=")
	fmt.Printf("rIdx %d and tcIdx %d \n", rIdx, tcIdx)
	if rIdx > 0 && tcIdx > 0 {
		res := newurl[rIdx : tcIdx-1]
		fmt.Printf("get resolution %s\n", res)
	}

	var temp string
	temp = ""

	out := "zhangbin.home" + temp + "feicheng"
	fmt.Printf("output:%s\n", out)

	tsurl1 := "http://175.6.128.18:664/32677847_10034_6634930815917905880_2014812193_1502269255_254_10034.ts?org=yyxcrs&uuid=91ac662328654a56a0f37b5948b826a0&seq=36392454&tk=15833be95c14c0695c62e51251aea3f4&tc=0&r=800x600"
	uri = tsurl1
	uri = uri[strings.LastIndex(uri, "/")+1:]
	/*(32677847_10034_6634930815917905880_2014812193_1502269255_254_10034.ts?org=yyxcrs&uuid=91ac662328654a56a0f37b5948b826a0&seq=36392454&tk=15833be95c14c0695c62e51251aea3f4&tc=0&r=800x600)
	 */
	fmt.Printf("uri is (%s)\n", uri)

	/*uri is (32677847_10034_6634930815917905880_2014812193_1502269255_254_10034)*/
	uri = uri[:strings.Index(uri, ".")]
	fmt.Printf("uri is (%s)\n", uri)
	/*uri is ([32677847 10034 6634930815917905880 2014812193 1502269255 254 10034])*/
	fiveTuple1 := strings.Split(uri, "_")
	fmt.Printf("uri is (%s)\n", fiveTuple1)

	fmt.Printf("%s\n", "=---------try to check & in resolution string------------")
	hahaurl := "http://175.6.128.18:664/32677847_10034_6634930815917905880_2014812193_1502269255_254_10034.ts?org=yyxcrs&uuid=91ac662328654a56a0f37b5948b826a0&seq=36392454&tk=15833be95c14c0695c62e51251aea3f4&tc=0&r=800x600&home=feicheng"
	var resolution1 string
	resolutionIndex1 := strings.Index(hahaurl, "r=")
	if resolutionIndex1 >= 0 {
		tmp := hahaurl[resolutionIndex1:]
		probe := strings.Index(tmp, "&")
		if probe == -1 {
			fmt.Printf(" the tmp %s does not contain &  %d\n", tmp, probe)
			resolution1 = tmp
		} else {
			if probe > 0 {
				resolution1 = tmp[0:probe]
				fmt.Printf(" the tmp %s contain &  %d \n", tmp, probe)
			}
		}
		/*tmp[0:]:get resolution r=800x600&home=feicheng*/
		fmt.Printf("tmp[0:]:get resolution %s\n", tmp[0:])
		/*tmp[0:probe]:get resolution r=800x600*/
		fmt.Printf("tmp[0:probe]:get resolution %s\n", resolution1)
	} else {
		fmt.Println("get resolution fail")
	}
	checknull()

	/*http://a.b.c.d/crs_db6888ecd3754e7b9376914410fd9b63.ts?s=34918932&e=35496655*/
	apath := "http://a.b.c.d/crs_db6888ecd3754e7b9376914410fd9b63.ts?s=34918932&e=35496655"
	fmt.Println("----TEST getTSName----")
	fmt.Printf("ts real name:  %s", getTSName(apath))
}

func checknull() {
	fmt.Printf("%s\n", "=---------try to check & in resolution string----checknull--------")
	hahaurl := "http://175.6.128.18:664/32677847_10034_6634930815917905880_2014812193_1502269255_254_10034.ts?org=yyxcrs&uuid=91ac662328654a56a0f37b5948b826a0&seq=36392454&tk=15833be95c14c0695c62e51251aea3f4&tc=0&r=0x0&home=feicheng"
	var resolution1 string
	resolutionIndex1 := strings.Index(hahaurl, "r=")
	if resolutionIndex1 >= 0 {
		tmp := hahaurl[resolutionIndex1:]
		probe := strings.Index(tmp, "&")
		if probe == -1 {
			fmt.Printf(" the tmp %s does not contain &  %d\n", tmp, probe)
			resolution1 = tmp
		} else {
			if probe > 0 {
				resolution1 = tmp[0:probe]
				fmt.Printf(" the tmp %s contain &  %d \n", tmp, probe)
			}
		}
		/*tmp[0:]:get resolution r=800x600&home=feicheng*/
		fmt.Printf("tmp[0:]:get resolution %s\n", tmp[0:])
		/*tmp[0:probe]:get resolution r=800x600*/
		fmt.Printf("tmp[0:probe]:get resolution %s\n", resolution1)
		if resolution1 == "r=0x0" {
			fmt.Printf("0x0 resolution exception : %s \n", resolution1)
		}
		if resolution1 == "r=0X0" {
			fmt.Printf("0X0 resolution exception : %s \n", resolution1)
		}
		ret := strings.EqualFold(resolution1, "r=0x0")
		fmt.Printf("check result : %v \n", ret)

	} else {
		fmt.Println("get resolution fail")
	}
}

/*item.VideoAddress http://a.b.c.d/crs_db6888ecd3754e7b9376914410fd9b63.ts?s=34918932&e=35496655 ,
get name http://a.b.c.d/crs_db6888ecd3754e7b9376914410fd9b63*/
func getTSFullName(str string) (name string) {
	substr := ".ts"
	index := strings.Index(str, substr)
	name = string([]byte(str)[:index])
	return
}

func getTSName(str string) (name string) {
	fullname := getTSFullName(str)
	name = fullname[strings.LastIndex(fullname, "/")+1:]
	return name + ".ts"
}

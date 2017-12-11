package main

import (
	"fmt"
	"time"
)

func showStartTime(startTime int64) {
	var wantTime int64
	/*这个不好理解，貌似是从今天8点开始算到现在的时间戳，比如我是17:56:44的：算出来就是这样的
	temp str: 1970-01-01 17:56:44 +0800 CST,日期是1970-01-01的
	*/
	wantTime = startTime % (3600 * 24 * 1)
	resultTime := startTime - wantTime
	//格式化为字符串,tm为Time类型
	tm := time.Unix(resultTime, 0)
	fmt.Println("startTime:", tm.Format("2006-01-02 03:04:05 PM"))
	fmt.Println("==> resultTime:", resultTime, "[", time.Unix(resultTime, 0), "]wantTime:", wantTime, "[", time.Unix(wantTime, 0), "]")
}

func getCurTime() (now int64) {
	//时间戳
	now = time.Now().Unix()
	/*now: 1501840732 now str : 2017-08-04 17:58:52 +0800 CST
	 */
	fmt.Println("---------now:", now, "now str :", time.Unix(now, 0))
	return
}

func main() {
	/*
					now: 1501840604
				startTime: 2017-08-04 08:00:00 AM
				==> starttime: 1501804800 temp: 35804 temp str: 1970-01-01 17:56:44 +0800 CST

				---------now: 1506765993 now str : 2017-09-30 18:06:33 +0800 CST


		$ ./test_ra_starttime.exe
		---------now: 1506766497 now str : 2017-09-30 18:14:57 +0800 CST
		startTime: 2017-09-30 08:00:00 AM
		==> resultTime: 1506729600 wantTime: 36897 [ 1970-01-01 18:14:57 +0800 CST ]



	*/
	t := getCurTime()
	showStartTime(t)
}

package main

import (
	"fmt"
	"time"
)

func showStartTime(startTime int64) {
	var temp int64
	/*这个不好理解，貌似是从今天8点开始算到现在的时间戳，比如我是17:56:44的：算出来就是这样的
	temp str: 1970-01-01 17:56:44 +0800 CST,日期是1970-01-01的
	*/
	temp = startTime % (3600 * 24 * 1)
	startTime = startTime - temp
	//格式化为字符串,tm为Time类型
	tm := time.Unix(startTime, 0)
	fmt.Println("startTime:", tm.Format("2006-01-02 03:04:05 PM"))
	fmt.Println("==> starttime:", startTime, "temp:", temp, "temp str:", time.Unix(temp, 0))
}

func getCurTime() (now int64) {
	//时间戳
	now = time.Now().Unix()
	/*now: 1501840732 now str : 2017-08-04 17:58:52 +0800 CST
	 */
	fmt.Println("now:", now, "now str :", time.Unix(now, 0))
	return
}

func main() {
	/*
			now: 1501840604
		startTime: 2017-08-04 08:00:00 AM
		==> starttime: 1501804800 temp: 35804 temp str: 1970-01-01 17:56:44 +0800 CST

	*/
	t := getCurTime()
	showStartTime(t)
}

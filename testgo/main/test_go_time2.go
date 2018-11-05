package main

import (
	"fmt"
	"time"
)

func main() {
	/*-1 测试1*/
	starttime := time.Now().Add(-time.Hour * 24 * 180) /*180天*/
	//endtime := time.Now().Add(-time.Hour * 24 * 1)     /*减去一天*/
	/*
		2017-12-27 12:01:42.4918011 +0800 CST

	*/
	fmt.Printf("%v \n %v \n %v \n", time.Now(), time.Now().Unix(), starttime)

	/*测试2*/
	/* format : 2017-06-30 12:01:42.4918011 +0800 CST
	   这个格式了还是这样的
	*/
	starttime.Format("2006-01-02 15:04:05")
	fmt.Printf("format : %v \n ", starttime)

	/*测试3  输出的还是这样的  loc startTime : 2017-06-30 14:29:46 +0800 CST*/
	sT := starttime.Format("2006-01-02 15:04:05")
	timeLayout := "2006-01-02 15:04:05" //转化所需模板
	loc, _ := time.LoadLocation("Local")
	/*字符串变time类型？*/
	startTime, _ := time.ParseInLocation(timeLayout, sT, loc) //使用模板在对应时区转化为time.time类型
	fmt.Printf("loc startTime : %v \n ", startTime)

	/*测试4 再测一测*/
	starttime1 := time.Now().Add(-time.Hour * 24 * 180) /*180天*/
	endtime1 := time.Now().Add(-time.Hour * 24 * 1)     /*减去一天*/
	/*这样会报错的*/
	//start2 := "2016-09-02 00:00:01"
	/*直接格式化,返回的都是字符串啊*/
	sT1 := starttime1.Format("2006-01-02 15:04:05")
	eT1 := endtime1.Format("2006-01-02 15:04:05")
	//st2 := start2.Format("2006-01-02 15:04:05")
	/*打印是字符串
	sT1: 2017-06-30 14:32:26 eT1: 2017-12-26 14:32:26
	*/
	fmt.Println("sT1:", sT1, "eT1:", eT1) /* "st2 : ", st2*/

	/*测试5 //时间戳转日期
	通过制定int64的数字，转为所要求的时间

		2017-12-27 15:03:54
		2016-09-01 00:00:01  1472659201
		2016-08-01 00:00:01  1469980801
			import "time"
			import "fmt"

			t := time.Unix(0, 1502712864232)
			fmt.Println(t.Format("02/01/2006, 15:04:05"))
	*/
	// 2016/09/01 00:00:01 1472659201
	//var my_timestamp int64
	//my_timestamp = 1472659201
	timeLayout1 := "2006-01-02 15:04:05"
	t := time.Unix(1514358234, 0)
	dataTimeStr := t.Format(timeLayout1)
	fmt.Println(dataTimeStr)

	//const epoch = 1234567890
	str := time.Unix(1472659201, 0).Format(timeLayout1)
	fmt.Println(str)

	/*测试6*/
	numHours := 1
	num := time.Duration(numHours)
	/*
		2016-09-01 00:00:01
		date 2016-08-31 23:00:01
	*/
	t1 := time.Unix(1472659201, 0).Add(-time.Hour * num) /*减去一天,num就是24*/
	date := t1.Format(timeLayout)
	fmt.Println("date", date)
}

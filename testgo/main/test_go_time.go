package main

import (
	"fmt"
	"log"
	"time"
)

func test() {

	/*时间比较*/
	time1 := "2015-03-20 08:50:29"
	time2 := "2015-03-21 09:04:25"
	//先把时间字符串格式化成相同的时间类型
	t1, err := time.Parse("2006-01-02 15:04:05", time1)
	t2, err := time.Parse("2006-01-02 15:04:05", time2)
	if err == nil && t1.Before(t2) {
		//处理逻辑
		fmt.Println("true")
	}
}

func test1() {
	p := fmt.Println

	// We'll start by getting the current time.
	now := time.Now()
	p(now)

	// You can build a `time` struct by providing the
	// year, month, day, etc. Times are always associated
	// with a `Location`, i.e. time zone.
	then := time.Date(
		2009, 11, 17, 20, 34, 58, 651387237, time.UTC)
	p(then)

	// You can extract the various components of the time
	// value as expected.
	p(then.Year())
	p(then.Month())
	p(then.Day())
	p(then.Hour())
	p(then.Minute())
	p(then.Second())
	p(then.Nanosecond())
	p(then.Location())

	// The Monday-Sunday `Weekday` is also available.
	p(then.Weekday())

	// These methods compare two times, testing if the
	// first occurs before, after, or at the same time
	// as the second, respectively.
	p(then.Before(now))
	p(then.After(now))
	p(then.Equal(now))

	// The `Sub` methods returns a `Duration` representing
	// the interval between two times.
	diff := now.Sub(then)
	p(diff)

	// We can compute the length of the duration in
	// various units.
	p(diff.Hours())
	p(diff.Minutes())
	p(diff.Seconds())
	p(diff.Nanoseconds())

	// You can use `Add` to advance a time by a given
	// duration, or with a `-` to move backwards by a
	// duration.
	p(then.Add(diff))
	p(then.Add(-diff))
}

func TestAdd() {

	starttime := time.Now().Add(-time.Hour * 24 * 180) /*180天*/
	endtime := time.Now().Add(-time.Hour * 24 * 1)     /*减去一天*/

	fmt.Println("now:", time.Now())
	fmt.Println("startime:", starttime)
	fmt.Println("endtime:", endtime)
}

func testTimestampWithAdd() {
	starttime := time.Now().Add(-time.Hour * 24 * 180) /*180天*/
	endtime := time.Now().Add(-time.Hour * 24 * 1)     /*减去一天*/

	/*直接格式化,返回的都是字符串啊*/
	sT := starttime.Format("2006-01-02 15:04:05")
	eT := endtime.Format("2006-01-02 15:04:05")
	/*打印是字符串*/
	fmt.Println("sT:", sT, "eT:", eT)

	timeLayout := "2006-01-02 15:04:05" //转化所需模板
	loc, _ := time.LoadLocation("Local")
	/*字符串变time类型？*/
	startTime, _ := time.ParseInLocation(timeLayout, sT, loc) //使用模板在对应时区转化为time.time类型
	endTime, _ := time.ParseInLocation(timeLayout, eT, loc)
	/*类型转时间戳*/
	startTS := startTime.Unix() //转化为时间戳 类型是int64
	endTS := endTime.Unix()
	fmt.Println("START_TS:", startTS, "endTS:", endTS) //打印输出theTime 2015-01-01 15:15:00 +0800 CST

}
func timeDurationInSecMicroMill() {
	//计算从Unix起始时间开始到某个时刻的秒数，毫秒数，微秒数等 https://www.kancloud.cn/itfanr/go-by-example/81697
	// 使用Unix和UnixNano来分别获取从Unix起始时间
	// 到现在所经过的秒数和微秒数
	now := time.Now()
	secs := now.Unix()
	nanos := now.UnixNano()
	fmt.Println(now)

	// 注意这里没有UnixMillis方法，所以我们需要将
	// 微秒手动除以一个数值来获取毫秒
	millis := nanos / 1000000
	fmt.Println(secs)
	fmt.Println(millis)
	fmt.Println(nanos)

	// 反过来，你也可以将一个整数秒数或者微秒数转换
	// 为对应的时间
	fmt.Println(time.Unix(secs, 0))
	fmt.Println(time.Unix(0, nanos))
}
func testTimestamp() {
	//获取本地location
	toBeCharge := "2015-01-01 00:00:00"                             //待转化为时间戳的字符串 注意 这里的小时和分钟还要秒必须写 因为是跟着模板走的 修改模板的话也可以不写
	timeLayout := "2006-01-02 15:04:05"                             //转化所需模板
	loc, _ := time.LoadLocation("Local")                            //重要：获取时区
	theTime, _ := time.ParseInLocation(timeLayout, toBeCharge, loc) //使用模板在对应时区转化为time.time类型
	sr := theTime.Unix()                                            //转化为时间戳 类型是int64
	fmt.Println(theTime)                                            //打印输出theTime 2015-01-01 15:15:00 +0800 CST
	fmt.Println(sr)                                                 //打印输出时间戳 1420041600

	//时间戳转日期
	dataTimeStr := time.Unix(sr, 0).Format(timeLayout) //设置时间戳 使用模板格式化为日期字符串
	fmt.Println(dataTimeStr)
}
func formatUnixTime() {
	// 获取当前时间，进行格式化
	fmt.Println(time.Now().Format("2006-01-02 15:04:05"))
	// output: 2016-07-27 08:57:46

	// 指定的时间进行格式化
	fmt.Println(time.Unix(1469579899, 0).Format("2006-01-02 15:04:05"))
	// output: 2016-07-27 08:38:19
}

/*时间字符串转换时间戳*/
// 将2016-07-27 08:46:15这样的时间字符串转换时间戳
func strToUnix() {
	// 先用time.Parse对时间字符串进行分析，如果正确会得到一个time.Time对象
	// 后面就可以用time.Time对象的函数Unix进行获取
	t2, err := time.Parse("2006-01-02 15:04:05", "2016-07-27 08:46:15")
	if err != nil {
		log.Fatalln(err)
	}
	fmt.Println(t2)
	fmt.Println(t2.Unix())
	// output:
	//     2016-07-27 08:46:15 +0000 UTC
	//     1469609175
}

// 根据时间戳获取当日开始的时间戳
// 这个在统计功能中会常常用到
// 方法就是通过时间戳取到2016-01-01 00:00:00这样的时间格式
// 然后再转成时间戳就OK了
// 获取月开始时间和年开始时间类似
func getDayStartUnix() {
	t := time.Unix(1469581066, 0).Format("2006-01-02")
	sts, err := time.Parse("2006-01-02", t)
	if err != nil {
		log.Fatalln(err)
	}
	fmt.Println(sts.Unix())
	// output: 1469577600
}

// 休眠
func sleep() {
	// 休眠1秒
	// time.Millisecond    表示1毫秒
	// time.Microsecond    表示1微妙
	// time.Nanosecond    表示1纳秒
	time.Sleep(1 * time.Second)
	// 休眠100毫秒
	time.Sleep(100 * time.Millisecond)

}
func getNow() {
	// 获取当前时间，返回time.Time对象
	fmt.Println(time.Now())
	// output: 2016-07-27 08:57:46.53277327 +0800 CST
	// 其中CST可视为美国，澳大利亚，古巴或中国的标准时间
	// +0800表示比UTC时间快8个小时

	// 获取当前时间戳
	fmt.Println(time.Now().Unix())
	// 精确到纳秒，通过纳秒就可以计算出毫秒和微妙
	fmt.Println(time.Now().UnixNano())
	// output:
	//    1469581066
	//    1469581438172080471
}

func main() {
	test()
	fmt.Println("------------")
	test1()
	fmt.Println("------------")
	TestAdd()
	fmt.Println("----------")
	testTimestamp()
	fmt.Println("-----------")
	timeDurationInSecMicroMill()
	fmt.Println("----------")
	testTimestampWithAdd()
}

/*
$ ./test_go_time.exe
true
------------
2017-05-24 17:48:48.9846473 +0800 CST
2009-11-17 20:34:58.651387237 +0000 UTC
2009
November
17
20
34
58
651387237
UTC
Tuesday
true
false
false
65869h13m50.333260063s
65869.23064812779
3.9521538388876677e+06
2.3712923033326006e+08
237129230333260063
2017-05-24 09:48:48.9846473 +0000 UTC
2002-05-14 07:21:08.318127174 +0000 UTC
------------
now: 2017-05-24 17:48:48.9996581 +0800 CST
startime: 2016-11-25 17:48:48.9996581 +0800 CST
endtime: 2017-05-23 17:48:48.9996581 +0800 CST

zhangbin@DESKTOP-1QV8QU4 MINGW64 /j/MYSELF/testCPP/testgo/main (master)
$

*/

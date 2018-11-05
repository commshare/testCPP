package main

import (
	"fmt"
	"time"
)

func GetDate(timestamp int64) (date string) {
	return timestamp2date(timestamp)
}

/*时间戳转为日期*/
func timestamp2date(timestamp int64) (date string) {
	timeLayout := "2006-01-02 15:04:05"
	fmt.Println("input ts: ", timestamp)
	date = time.Unix(timestamp, 0).Format(timeLayout)
	fmt.Println("date:", date)
	return
}
func removeHours(timestampBegin int64, numHours int) (date string) {
	timeLayout := "2006-01-02 15:04:05"
	num := time.Duration(numHours)
	t := time.Unix(timestampBegin, 0).Add(-time.Hour * num) /*减去一天,num就是24*/
	date = t.Format(timeLayout)
	return
}
func addHours(timestampBegin int64, numHours int) (date string) {
	timeLayout := "2006-01-02 15:04:05"
	num := time.Duration(numHours)
	t := time.Unix(timestampBegin, 0).Add(time.Hour * num) /*减去一天,num就是24*/
	date = t.Format(timeLayout)
	return
}
func Yesterday(timestampBegin int64) (date string) {
	return removeHours(timestampBegin, 24)
}

func LastDays(timestampBegin int64, days int) (date string) {
	return removeHours(timestampBegin, days*24)
}
func NextDays(timestampBegin int64, days int) (date string) {
	return addHours(timestampBegin, 24*days)
}
func GetSpecificPeriod(begin int64, end int64) (dateBegin string, dateEnd string) {
	/*
		    2016-09-01 00:00:01  1472659201
			2016-08-01 00:00:01  1469980801
	*/
	//specific20160901ts= 1472659201
	return timestamp2date(begin), timestamp2date(end)
}

/*
	get time after param d from now
*/
func getTime(d time.Duration) string {
	var dd time.Duration
	dd = 1 * 7 * 24 * time.Hour
	return time.Now().Add(dd).Format("2006-01-02 15:04:05")
}

/*
    start_time: 1517374986
      end_time: 1517375123
        status: 2
    video_time: 131
    video_size: 15557564
   is_notified: 1
    is_deleted: 5
failure_reason: sucess
      ext_info:
   notify_time: 2018-01-31 13:05:37
   insert_time: 2018-01-31 13:03:06
   modify_time: 2018-01-31 13:05:37
   delete_time: 1970-01-01 08:00:00
     __version: 6215168564741546253


*/
/*https://www.golangtc.com/t/51bd288c320b5264b800001c*/
func main() {
	//startStr := "2016-09-01"
	t := time.Now()
	year, month, _ := t.Date()
	thisMonthFirstDay := time.Date(year, month, 1, 1, 1, 1, 1, t.Location())
	thisMonthFirstDay.AddDate(0, -1, 0)

	/*Today:201801

	 */
	fmt.Printf("Today:%s\n", t.Format("200601"))
	fmt.Printf("Today:%s\n", t.Format("20060101"))

	//fmt.Printf("Yesterday:%s\n", Yesterday.Format("200601"))
	//fmt.Printf("Yesterdat before Yesterday:%s\n", bef_yes.Format("200601"))

	/*	  startTime 2013-02-26 16:29:13.0401516 +0800 CST
		endTime 2016-06-10 16:29:13.0401516 +0800 CST
	 startTimeFormt 2013-02-26 17:08:25

	*/
	startTime := time.Now().Add(-time.Hour * 24 * time.Duration(1800))
	endTime := time.Now().Add(-time.Hour * 24 * time.Duration(535))

	fmt.Printf("startTime %v \n endTime %v \n startTime.Unix() %v \n endTime.Unix() %v\n startTimeFormt %v \n",
		startTime, endTime, startTime.Unix(), endTime.Unix(), startTime.Format("2006-01-02 15:04:05"))

	/*https://stackoverflow.com/questions/38386762/running-code-at-noon-in-golang*/
	n := time.Date(t.Year(), t.Month(), t.Day(), 8, 0, 0, 0, t.Location())

	fmt.Printf("n %v \n", n)
	if t.After(n) {
		n = n.Add(24 * time.Hour) /*24小时之后*/
		fmt.Printf("n %v \n", n)
	}
	d := n.Sub(t)
	/*
		n 2018-01-31 08:00:00 +0800 CST
		n 2018-02-01 08:00:00 +0800 CST
		d 13h48m51.3115646s  还要过这么久
	*/
	fmt.Printf("d %v \n", d)
}

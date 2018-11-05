package main

import (
	"fmt"
	"time"
)

/* %  这个是取余的，去掉余数，得到一个整数，这个整数肯定是比实际的时间要早一点的整数*/
// the unit of these two param is second.
func BigTaskGetTimeBase(start_time int64, block_duration int64) (base int64) {
	remove := start_time % block_duration
	fmt.Printf("remove %v from starttime \n", remove)
	base = start_time - remove
	return
}

func main() {
	now := time.Now().Unix()
	next_time := BigTaskGetTimeBase(now, 7200)
	fmt.Printf("now %v next_time %v  \n", next_time, time.Now())
	//格式化为字符串,tm为Time类型
	timestamp := next_time
	tm := time.Unix(timestamp, 0)

	fmt.Println(tm.Format("2006-01-02 03:04:05 PM"))

	fmt.Println(tm.Format("02/01/2006 15:04:05 PM"))
}

/*
$ ./test_go_block_next_time.exe
remove 1716 from starttime
now 1521792000 next_time 2018-03-23 16:28:36.2669364 +0800 CST
2018-03-23 04:00:00 PM
23/03/2018 16:00:00 PM


*/

func testForward() {
	for {
		time.Sleep(1 * time.Second)
		cur := time.Now() + 7000
		next := BigTaskGetTimeBase(cur, 7200)
		for next <= time.Now()+ 7000*1 + 2098 {
			back := next + 7200 + 3600 
			if back < cur {
				fmt.Printf(format, ...)
			}
			next += 7200
		}
	}
}

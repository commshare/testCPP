package main

import (
	"fmt"
	"os"
	"strconv"
	"time"
)

func main() {
	array := os.Args
	if len(array) == 1 {
		fmt.Printf("no params \n")
		return
	}
	//fmt.Println(array)
	int64_ts, err := strconv.ParseInt(array[1], 10, 64)
	if err != nil {
		fmt.Printf("conv to int64 fail \n")
		return
	}
	var myst int64 = int64_ts
	tm := time.Unix(myst, 0)
	fmt.Println(tm.Format("2006-01-02 15:04:05 PM"))
}

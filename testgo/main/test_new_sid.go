package main

import (
	"flag"
	"fmt"
)

func main() {
	sid := flag.Int64("s", 0, "sid")

	flag.Parse()
	//var sid int
	//sid = 31700348
	data := (*sid) % 128

	fmt.Printf("sid %v data %v \n", *sid, data)

	if data >= 0 && data <= 64 {
		fmt.Println("DATA IS NEW SID")
	} else {
		fmt.Println("DATA IS NOT NEW SID")
	}

	/*灰度频道长号%128在[0,64]范围内的录制切到新系统*/

}

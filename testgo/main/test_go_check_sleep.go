package main

import (
	"fmt"
	"time"
)

func main() {
	i := 100
	linecnt := 0
	for {
		linecnt++
		if i > 0 {
			if linecnt%10 == 0 {
				time.Sleep(1 * time.Second)
				fmt.Println("---wait 1 seconds to read line-----")
			} else {
				fmt.Printf(" -linecnt %v--\n", linecnt)
			}
		}
		i--
	}

}

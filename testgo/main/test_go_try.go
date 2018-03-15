package main

import (
	"fmt"
)

func main() {
	j := 10
	for i := 0; i < 3; i++ {
		fmt.Println("---begin i = ", i)
		if j+i > 10 {
			break
		}
		if i == 3 { /*这个是不打印的*/
			fmt.Println(" try fail")
		}
		if i+1 == 3 {
			fmt.Println("yes, try fail")
		}
		fmt.Println("---end i = ", i)
	}
}

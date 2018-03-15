package main

import "fmt"

func main() {
	var num int
	interval := 5000
	num = 7300
	quzheng := num / interval
	quyu := num % interval
	fmt.Printf("quzheng %v \n", quzheng)
	fmt.Printf("quyu %v \n", quyu)
	if quzheng >= 0 {
		fmt.Printf("yes %v, 5000 倍数 \n", num)
		if 0 <= quyu && quyu < 2000 {
			fmt.Printf("yes %v, small  \n", num)
		} else {
			fmt.Printf("yes %v, big  \n", num)
		}

	} else {
		fmt.Printf(" no %v , not 5000 倍数 \n", num)
	}
	return
}

package main

import "fmt"

func main() {
	//这是我们使用range去求一个slice的和。使用数组跟这个很类似
	nums := []int{2, 3, 4}
	sum := 0
	for index, num := range nums {
		fmt.Println("index ", index) /*确实是从0开始*/
		sum += num
	}
	fmt.Println("sum:", sum)
}

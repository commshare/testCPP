package main

import "fmt"

func main() {
	array := []int64{10, 2, 30, 4, 11, 21, 33}
	for k, v := range array {
		/*$ ./test_go_slice.exe
		0 1
		1 2
		2 3
		3 4
		*/
		fmt.Println(k, v)
	}
	fmt.Println("do copy")
	out := make([]int64, 10)
	i := 0
	for _, v := range array {
		if v > 10 {
			out[i] = v
			i++
		}

	}
	fmt.Println("show out:")
	for k, v := range out {
		fmt.Println(k, v)
	}

	var out2 []int64
	fmt.Println("len of out2 ", len(out2))
	out2 = check(array)
	if out2 == nil {
		fmt.Println("check return nil")
	}
	fmt.Println("show out2:")
	for k, v := range out2 {
		fmt.Println(k, v)
	}
}

func check(src []int64) (dst []int64) {
	for _, v := range src {
		if v > 1 {
			fmt.Println("invalid v:", v)
			continue
		}
		dst = append(dst, v)
	}
	return
}

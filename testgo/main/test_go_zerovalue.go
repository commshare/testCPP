package main

import (
	"fmt"
)

func main() {
	b := new(bool)
	fmt.Println(*b) //false
	i := new(int)
	fmt.Println(*i) //0
	s := new(string)
	fmt.Println(*s) //难道是"" ?
	if *s == "" {
		panic("the string default :[ " + *s + "]")
	}
}

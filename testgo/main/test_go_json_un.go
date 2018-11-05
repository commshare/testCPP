package main

import (
	"encoding/json"
	"fmt"
)

func main() {
	var Error string

	strData := "OTc5MzE1OTM5NDksIlRhc2tJZCI6IjE1MDEzXzkzOTQyOTE2XzkzOTQyOTE2XzE1MTYzNzc2MDAiLCJEZWxheSI6MTUxNjQwNTAxMH0="
	err := json.Unmarshal([]byte(strData), &Error)
	if err != nil {
		fmt.Printf("has err :%v \n", err)
	} else {
		fmt.Println("STR :", Error)
	}
}

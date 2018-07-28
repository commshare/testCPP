package main

import "fmt"

func main() {
	filePath := "v:/test/1.ts"
	keyWord := "file"
	out := fmt.Sprintf("%s %s%s%s", keyWord, "'", filePath, "'")
	fmt.Println("out %v \n", out)
}

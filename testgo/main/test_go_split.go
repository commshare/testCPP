package main

import (
	"errors"
	"fmt"
	"strings"
)

func testLen() {
	s := strings.Split("127.0.0.1:5432", ":")
	ip, port := s[0], s[1]
	fmt.Printf("len of split out : %v \n", len(s)) /*这个值是2*/
	fmt.Println(ip, port)
}

type PyString string

func main() {
	var py PyString
	py = "127.0.0.1:5432"
	ip, port, err := py.Split(":") // Python Style
	fmt.Println(ip, port, err)

	testLen()
}

func (py PyString) Split(str string) (string, string, error) {
	s := strings.Split(string(py), str)
	if len(s) < 2 {
		return "", "", errors.New("Minimum match not found")
	}
	return s[0], s[1], nil
}

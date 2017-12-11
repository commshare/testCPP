package main

import "fmt"

type Msg struct {
	name string
	home string
}

func getInfo(msg *Msg) {
	msg.name = "zhangbin"
}

func handleInfo(msg *Msg) {
	msg.home = "feicheng"
}

func main() {
	msg := &Msg{}
	fmt.Printf("info %+v \n", msg)

	getInfo(msg)

	handleInfo(msg)

	fmt.Printf("info %+v \n", msg)

}

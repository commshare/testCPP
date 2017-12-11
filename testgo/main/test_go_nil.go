package main

import "fmt"

type MyList struct {
	name string
	id   int
}

func main() {
	list := make([]MyList, 100) /*这是在make一个slice*/
	fmt.Println("list : ", list)

	if list == nil {
		fmt.Println("list is nil ")
	} else {
		fmt.Println("list is not nil ") /*打印这个，可见make之后不是nil*/
	}
	/*因为分配了空间，所以slice是100*/
	fmt.Println("len of list is  :", len(list))

	list2 := make([]MyList, 0) /*这是在make一个slice,必需传入一个值，哪怕是0，make了就不是nil了*/
	fmt.Println("len of list2 is  :", len(list2))
	/*貌似这个时候，下面的不执行么？*/
	for index, value := range list2 {
		/*下面的不打印啊*/
		fmt.Println("index : ", index)
		fmt.Println("value : ", value)

	}
	fmt.Println("-----------------")

	for i := range list {
		fmt.Println("i : ", i)
	}

}

/*
zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_nil.exe
list :  [{ 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0} { 0}]

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$

*/

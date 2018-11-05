package main

import (
	"fmt"
)

/*
https://github.com/golang/go/issues/4536
*/

func main() {
	/*这个map此时是nil的*/
	var m map[int]int
	/* delete on nil map is a no-op.*/
	delete(m, 0)
	/*分配内存*/
	m = make(map[int]int)
	m[0] = 100
	m[1] = 200

	delete(m, 0)
	fmt.Printf("after delete 0 : len(m)=%d \n", len(m))
	/*因为2不存在，所以这个操作什么都没做*/
	delete(m, 2)
	fmt.Printf("after delete 2 : len(m)=%d \n", len(m))

	/*https://stackoverflow.com/questions/1736014/delete-mapkey-in-go*/
	/*v不再存在，所以ok是false，注意，v打印出来是 0*/
	v, ok := m[3]
	/*即使v不存在，delete也不会有问题*/
	delete(m, 3)
	fmt.Printf("after delete 3 : len(m)=%d  v=%v  ok=%v\n", len(m), v, ok)
	if v == nil {
		fmt.Println("not exist , v== nil [%v] ", v)
	}

}

/*
zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)
$ ./test_go_delete_nil_map.exe
after delete 0 : len(m)=1
after delete 2 : len(m)=1
after delete 3 : len(m)=1  v=0  ok=false

zhangbin@DESKTOP-1QV8QU4 MINGW64 /v/RECORD_TEST/testCPP/testgo/main (master)


*/

package main

import "fmt"

/*https://xiaozhou.net/something-about-range-of-go-2016-04-10.html

value是拷贝一份的
*/
type MyType struct {
	field string
}

type Foo struct {
	bar string
}

func testValuePass() {
	list := []Foo{
		{"A"},
		{"B"},
		{"C"},
	}
	/*错误的
	{A} {B} {C}
	&{C} &{C} &{C}
	value是临时变量，所以地址是同一个，而且是临时的
	*/
	list2 := make([]*Foo, len(list))
	for i, value := range list {
		list2[i] = &value
	}
	fmt.Println(list[0], list[1], list[2])
	fmt.Println(list2[0], list2[1], list2[2])

	//正确的例子
	for i, _ := range list {
		list2[i] = &list[i] //存内存地址
	}
	/*{A} {B} {C}
	&{A} &{B} &{C}
	*/
	fmt.Println(list[0], list[1], list[2])
	fmt.Println(list2[0], list2[1], list2[2])
}
func main() {
	var array [10]MyType
	/*错误的做法*/
	/*range的时候是值传递，所以这里的e是一个副本，什么都没有改变*/
	for _, e := range array {
		e.field = "foo"
	}
	for _, e := range array {
		fmt.Println(e.field)
		fmt.Println("-1-")
	}

	/*正确的做法*/
	for i, _ := range array {
		array[i].field = "goo"
	}
	for _, e := range array {
		fmt.Println(e.field)
		fmt.Println("-2-")
	}

	testValuePass()
}

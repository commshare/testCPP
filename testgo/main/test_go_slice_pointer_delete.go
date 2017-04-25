package main

import (
	"fmt"
	"time"
)

/*使用 数组指针类型   ，这是为了可以修改数组内容，slice是值传递的，数组传下去就是一个值副本
以及使用append来做delete*/
func del(value int, slice *[]int) {
	/*打印的是一个数组指针类型*/
	fmt.Println("before del : ", slice) /*before del :  &[0 1 2 3 4 5 6 7 8 9] 	 */
	for i, v := range *slice {          /*这里要用  *slice*/
		if v == value {
			fmt.Println("v =", v, "i =", i) /*value为6的时候，i也是6*/
			/*(*slice)[0:i] :  [0 1 2 3 4 5]
			(*slice)[i+1:] :  [7 8 9]
			*/
			fmt.Println("(*slice)[0:i] : ", (*slice)[0:i])
			fmt.Println("(*slice)[i+1:] : ", (*slice)[i+1:])
			(*slice) = append((*slice)[:i], (*slice)[i+1:]...)

		}
	}

	fmt.Println("after del : ", slice) /*after del :  &[0 1 2 3 4 5 7 8 9]*/
}

func main() {
	fmt.Println("zhangbin test")
	var temp []int = []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	fmt.Println("temp len :", len(temp))
	slice0 := temp[:]
	fmt.Println("slice0 :", slice0)
	/*初始化切片s,是数组arr的引用
	s := arr[startIndex:endIndex] */
	slice := temp[0:10] /*打印出来是0到9这10个*/
	slice1 := []int{0, 1, 2}
	fmt.Println("slice :", slice)
	for i, v := range slice {
		fmt.Println("cur v :", v, "cur i :", i)
	}
	fmt.Println("slice 1 : ", slice1)
	for i, v := range slice1 {
		fmt.Println("slice1 cur v :", v, "cur i :", i)
	}
	var slice2 []int /*未指定大小的数组来定义切片*/
	var slice3 []int = make([]int, 10)
	slice4 := make([]int, 10)
	slice5 := make([]int, 5, 10)
	slice6 := []int{1, 2, 3}
	fmt.Println("slice 2 : ", slice2)
	fmt.Println("slice 3 : ", slice3)
	fmt.Println("slice 4 : ", slice4)
	fmt.Println("slice 5 : ", slice5)
	fmt.Println("slice 6 : ", slice6)

	fmt.Println("try to delete 6 of slice with pointer")
	/*传递指针*/
	del(6, &slice)
	fmt.Println("now slice : ", slice) /*now slice :  [0 1 2 3 4 5 7 8 9]  确实6被删除了*/

	fmt.Println("testPointer")
	testPointer()

}

type field struct {
	name string
}

func (p *field) print() {
	fmt.Println(p.name)
}

/*
testPointer
one
two
three

*/
func testPointer() {
	/*这是一个什么类型啊,貌似data是一个数组，数组的元素是一个field类型的指针*/ /*打印ok*/
	data := []*field{{"one"}, {"two"}, {"three"}}
	for _, v := range data {
		go v.print()
	}

	time.Sleep(3 * time.Second)

	/*data_1是一个数组，数组元素只是一个field类型*/
	data_1 := []field{{"one"}, {"two"}, {"three"}}
	/*这么打印也ok*/
	for _, v := range data_1 {
		v := v /*搞一个临时变量*/
		go v.print()
	}
	time.Sleep(3 * time.Second)

	/*这么是不ok的
	three
	three
	three

	*/
	for _, v := range data_1 {
		go v.print()
	}
	time.Sleep(3 * time.Second)
}

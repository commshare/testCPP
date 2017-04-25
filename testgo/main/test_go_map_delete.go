package main

import "fmt"

/*delete
内建函数 delete 按照指定的键将元素从映射中删除。若 m 为 nil 或无此元素，delete 不进行操作。
函数结构：

func delete(m map[Type]Type1, key Type)*/
func main() {
	map1 := make(map[string]int) /*分配内存，但是没有数据*/

	/*插入数据*/
	map1["one"] = 1
	map1["two"] = 2
	map1["three"] = 3
	map1["four"] = 4

	fmt.Println(map1, len(map1))
	/*根据key来删除*/
	delete(map1, "two")
	fmt.Println(map1, len(map1))
}

/*map[one:1 two:2 three:3 four:4] 4
map[one:1 three:3 four:4] 3
*/

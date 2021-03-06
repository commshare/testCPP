package main

import "fmt"

/*
https://www.kancloud.cn/kancloud/the-way-to-go/72490

如果想增加切片的容量，我们必须创建一个新的更大的切片并把原分片的内容都拷贝过来。
下面的代码描述了从拷贝切片的 copy 函数和向切片追加新元素的 append 函数。


func append(s[]T, x ...T) []T 其中 append 方法将 0 个或多个具有相同类型 s 的元素追加到切片后面并且返回新的切片；
追加的元素必须和原切片的元素同类型。如果 s 的容量不足以存储新增元素，append 会分配新的切片来保证已有切片元素和新增元素的存储。
因此，返回的切片可能已经指向一个不同的相关数组了。append 方法总是返回成功，除非系统内存耗尽了。

如果你想将切片 y 追加到切片 x 后面，只要将第二个参数扩展成一个列表即可：x = append(x, y...)。
*/
func main() {
	sl_from := []int{1, 2, 3}
	sl_to := make([]int, 10)

	/*返回copy成功了多少个元素*/
	n := copy(sl_to, sl_from)
	fmt.Println(sl_to)
	fmt.Printf("Copied %d elements\n", n) // n == 3

	sl3 := []int{1, 2, 3}
	/*内存会自动扩展的，会返回一个新的slice，追加的元素必需跟原类型相同*/
	sl3 = append(sl3, 4, 5, 6)
	fmt.Println(sl3)

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

	del(6, &slice)
	fmt.Println("now slice : ", slice)
}

/* append 在大多数情况下很好用，但是如果你想完全掌控整个追加过程，你可以实现一个这样的 AppendByte 方法

func copy(dst, src []T) int copy 方法将类型为 T 的切片从源地址 src 拷贝到目标地址 dst，覆盖 dst 的相关元素，
并且返回拷贝的元素个数。源地址和目标地址可能会有重叠。拷贝个数是 src 和 dst 的长度最小值。
如果 src 是字符串那么元素类型就是 byte。如果你还想继续使用 src，在拷贝技术后执行 src = dst。

*/
func AppendByte(slice []byte, data ...byte) []byte {
	m := len(slice)
	n := m + len(data) /*最新元素个数*/
	/*原始slice空间不足*/
	if n > cap(slice) { // if necessary, reallocate
		// allocate double what's needed, for future growth.
		/*重新分配的是n+1 然后乘以2啊，为了以后增长所需，为啥要+1呢*/
		newSlice := make([]byte, (n+1)*2)
		/*执行copy啊*/
		copy(newSlice, slice)
		slice = newSlice
	}
	/*目前的slice是原始slice从0到n-1这些个位置的元素，所以要写0到n*/
	slice = slice[0:n] /*这里用的是直接赋值*/
	/*然后从m到n-1位置进行复制，所以要写m到n*/
	copy(slice[m:n], data) /*这里用的是copy*/
	return slice
}

/*
[1 2 3 0 0 0 0 0 0 0]   slice打印出来都是带有[]的
Copied 3 elements
[1 2 3 4 5 6]

*/

func del(id int, slice *[]int) {
	fmt.Println("before del : ", slice)
	for i, v := range *slice {
		if v == id {
			(*slice) = append((*slice)[:i], (*slice)[i+1:]...)
		}
	}

	fmt.Println("after del : ", slice)
}

package main

import (
	"fmt"
	"sync"
)

/*https://porson.github.io/2017/02/05/Go%E8%AF%AD%E8%A8%80append%E5%87%BD%E6%95%B0%E6%93%8D%E4%BD%9Cslice%E6%97%B6%E7%9A%84%E4%B8%80%E4%B8%AA%E5%B0%8F%E5%9D%91/*/
/*
查阅资料后得知，slice是引用类型，
在内存中并没有属于自己的内存空间，而是通过指针指向进行切片的队列。由于队列分配的内存空间是连续的，
所以如果slice的最后一个元素不是list的最后一个元素，那么在append的时候，新追加的元素就会覆盖掉原数组的元素。
而由于slice是指针组织的，所以这个list的所有slice都会被影响。如果切片末尾元素就是队列的末尾元素，
返回的 slice 数组指针将指向这个空间，而原数组的内容将保持不变，其它引用此数组的 slice 则不受影响。
由此拓展可以知道，所有对slice的修改都会对原list产生修改。所以使用的时候一定要小心。
*/

func sliceIsReference() {
	Array_list_1 := [10]byte{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'}
	Array_list_2 := [10]byte{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'}
	slice_list_1 := Array_list_1[2:5]
	slice_list_2 := Array_list_1[3:]
	b := append(slice_list_1, 'p')
	fmt.Println(Array_list_1)
	fmt.Println(Array_list_2)
	fmt.Println(slice_list_1)
	fmt.Println(slice_list_2)
	fmt.Println(b)
}

/*https://my.oschina.net/u/222608/blog/839602
多运行几次你就会发现，slice长度并不是1000，而是不停的在变，为什么呢？（如果这个代码你无法重现，你可以尝试将1000改为更大的数字）

因为append并不是并发安全的。
我们举一个简单例子，比如，当A和B两个协程运行append的时候同时发现s[1]这个位置是空的，
他们就都会把自己的值放在这个位置，这样他们两个的值就会覆盖，造成数据丢失。
*/
func sliceAppendBingFaError() /*并发*/ {
	var wg sync.WaitGroup
	s := make([]int, 0, 1000)

	for i := 0; i < 1000; i++ {
		v := i
		wg.Add(1)
		/*创建一个携程去append*/
		go func() {
			s = append(s, v)
			wg.Done()
		}()
	}

	wg.Wait()
	/*打印slice长度*/
	fmt.Printf("%v\n", len(s))

}

/*
运行一下这个例子就会发现，s的长度总是1000。
*/
func sliceAppendBingFaOK() {
	var (
		wg    sync.WaitGroup
		mutex sync.Mutex /*直接是一个锁*/
	)

	s := make([]int, 0, 1000) /*分配空间*/

	for i := 0; i < 1000; i++ {
		v := i
		wg.Add(1)
		go func() {
			mutex.Lock()
			s = append(s, v) /*挨个往slice里加*/
			mutex.Unlock()
			wg.Done()
		}()
	}

	wg.Wait()
	fmt.Printf("%v\n", len(s))
}

/*一定要传指针*/
func sliceModify(slice *[]int) {
	*slice = append(*slice, 6)
}

func main() {
	sliceIsReference()
	sliceAppendBingFaOK()
}

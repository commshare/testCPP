package main

import (
	"bytes"
	"fmt"
	// "time"
	"errors"
)

func loop() {
	for i := 0; i < 10; i++ {
		fmt.Printf("%d ", i)
	}
	fmt.Println(" ")
}

type item struct {
	Name string
}

//函数名是String
func (i item) String() string {
	return fmt.Sprintf("item name %v", i.Name)
}

type person struct {
	Name string
	Sex  string
}

func (p person) String() string {
	return fmt.Sprintf("person name : %v sex:%v ", p.Name, p.Sex)
}

/*interface{}作为函数参数和函数返回值
https://my.oschina.net/xlplbo/blog/293311

返回值也是interface{}
*/
func Parse(i interface{}) interface{} {
	switch i.(type) { /*强制转换类型？ type是系统关键字*/
	case string:
		return &item{ /*构造一个item*/
			Name: i.(string),
		}
	case []string:
		data := i.([]string)
		length := len(data)
		if length == 2 {
			return &person{
				Name: data[0], /*在赋值的时候必需加，啊*/
				Sex:  data[1],
			}
		} else {
			return nil
		}
	default:
		panic(errors.New("type match miss"))
	}
	return nil
}

/*https://www.oschina.net/translate/go-lang-slices?lang=chs&page=2#

给函数传递分片
理解这一点是很重要的：虽然片段包含指针，但是它本身却是只是一个值。解开这个秘密：它是一个含有指针和长度的结构的值。
它不是一个指向结构的指针。

虽然分片头是值传递的，但是这个头包含“指向数组元素的指针”，因此“原来的分片头”和“传递给函数的这个头的拷贝”都指向同一个数组。
因此，当这个函数返回的时候，已经修改的元素可以通过原来的分片变量看到修改过的元素值。

*/
/*（使用for range 循环）遍历，然后每个元素+1*/
func AddOneToEachElement(slice []byte) {
	for i := range slice {
		slice[i]++
	}
}

/*函数的参数实际上是一个拷贝

这时我们可以看到由函数修改的分片参数的内容，不过分片头没有更改。存储在分片变量里的长度也不能通过调用函数而修改，
这是因为传递给函数的是分片头的一个拷贝，不是原来的分片头。因此，如果我们想编写一个修改分片头的函数，
那么我们必须把它当作结果参数返回，
这儿我们就是这样做的。分片变量是无法做更改的，不过返回值具有新的长度，然后把这个返回值存储在新的分片中。
*/
func SubtractOneFromLength(slice []byte) []byte {
	slice = slice[0 : len(slice)-1] /*0到N，实际上是0到N-1这么多个index，现在是0到LEN-1，那么就是0到len-1-1个index，少了一个*/
	return slice
}

/*
分片指针：方法中的接收者

让函数修改分片头的另一个方法是给这个函数传送指针。下面是前面例子的一次修改，实现了给函数传递指针：
在这个例子里，这么做似乎很笨拙，尤其是在对额外增加的中间层的处理上（临时变量实现），不过，在这儿，
你可以看到指向分片的指针却是很常见的。对要修改分片的函数来说，使用指针实现参数接收是常见的做法。
*/
func PtrSubtractOneFromLength(slicePtr *[]byte) {
	slice := *slicePtr
	*slicePtr = slice[0 : len(slice)-1]
}

/*需要一个在最后一个斜杠处截短分片的方法*/
type path []byte

func (p *path) TruncateAtFinalSlash() {
	i := bytes.LastIndex(*p, []byte("/"))
	if i >= 0 {
		*p = (*p)[0:i]
	}
}

/*上面那个是指针，这个不是指针*/
func (p path) TestNotPointer() {
	fmt.Println("path len : %v", len(p))
}

/*要求传递指针*/
func (p *path) TestPointer() {
	fmt.Println("path len : ", len(*p)) //这里要传递值
}

/*
改变接收者的类型为一个数值而不是一个指针，然后继续运行
*/
func (p path) ToUpper() {
	for i, b := range p {
		if 'a' <= b && b <= 'z' {
			p[i] = b + 'A' - 'a'
		}
	}
}

/*通过传入一个元素扩展它的slice参数*/
func Extend(slice []int, element int) []int {
	n := len(slice)
	slice = slice[0 : n+1]
	slice[n] = element
	return slice
}

// Insert向分片的指定位置插入值,
// 位置必须在有效范围内.
// 分片必须有空间增加新元素.
func Insert(slice []int, index, value int) []int {
	// 给分片增加一个元素的空间.
	slice = slice[0 : len(slice)+1]
	//使用copy函数移动分片的前面部分，打开一个缺口.
	copy(slice[index+1:], slice[index:])
	// 存储新值.
	slice[index] = value
	// 返回结果
	return slice
}


func Extend2(slice []int, element int) []int {
    n := len(slice)
    if n == cap(slice) {
        // Slice is full; must grow.
        // We double its size and add 1, so if the size is zero we still grow.
        newSlice := make([]int, len(slice), 2*len(slice)+1)
        copy(newSlice, slice)
        slice = newSlice
    }
    slice = slice[0 : n+1]
    slice[n] = element
    /*为啥go可以返回局部make的对象*/
    return slice
}
func main() {
	/*	go loop()
		fmt.Println("------------1---------")
		go loop()
		fmt.Println("----------2-----------")
		go loop()
		fmt.Println("-------3-----------")
		time.Sleep(time.Second)*/

	//interface{}的强转
	var t interface{}
	t = 1
	t0 := (t).(int)
	fmt.Printf("%v %v", t0, &t0)

	/*interface和nil的比较*/
	var val interface{} = nil
	if val == nil {
		fmt.Println("val is nil")
	} else {
		fmt.Println("val is not nil")
	}

	//测试取地址运算符
	var i int  // i 的类型是int型
	i = 1      // i 的值为 1;
	var p *int // p 的类型是[int型的指针]
	p = &i     // p 的值为 [i的地址]

	fmt.Printf("i=%d;p=%d;*p=%d\n", i, p, *p)

	*p = 2 // *p 的值为 [[i的地址]的指针] (其实就是i嘛),这行代码也就等价于 i = 2
	fmt.Printf("i=%d;p=%d;*p=%d\n", i, p, *p)

	i = 3 // 验证想法
	fmt.Printf("i=%d;p=%d;*p=%d\n", i, p, *p)

	//测试struct的初始化
	//定义一个struct
	type Student struct {
		id      int
		name    string
		address string
		age     int
	}

	mStudent := &Student{}
	fmt.Println(mStudent.id)
	fmt.Println(mStudent.address)
	fmt.Println(mStudent.age)
	/*想测试下收包发包的*/
	/*	type Pack struct {
			buf       []byte
			offset    int
			bootstrap [512]byte
		}
		pack := &Pack{}*/

	/*返回值是interface{}*/
	p1 := Parse("apple ").(*item) /*强转*/
	fmt.Println(p1)

	p2 := Parse([]string{"zhangbin", "man"}).(*person)
	fmt.Println(p2)

	/*https://www.oschina.net/translate/go-lang-slices?lang=chs&page=2#*/
	var buffer [256]byte /*声明啊*/
	slice := buffer[10:20]
	fmt.Println("slice : %v  and len(slice) : %v", slice, len(slice)) //全是0，长度是10
	/*重新赋值吧*/
	for i := 0; i < len(slice); i++ {
		slice[i] = byte(i)
	}
	fmt.Println("before AddOneToEachElement", slice)
	AddOneToEachElement(slice)
	fmt.Println("after", slice)

	/*函数的参数实际上是一个拷贝*/
	fmt.Println("Before SubtractOneFromLength : len(slice) =", len(slice))
	newSlice := SubtractOneFromLength(slice)
	fmt.Println("After:  len(slice) =", len(slice))
	fmt.Println("After:  len(newSlice) =", len(newSlice))

	/*分片指针：方法中的接收者

	让函数修改分片头的另一个方法是给这个函数传送指针。*/
	fmt.Println("Before PtrSubtractOneFromLength : len(slice) =", len(slice))
	PtrSubtractOneFromLength(&slice)
	fmt.Println("After:  len(slice) =", len(slice))

	/*在最后一个斜杠处截短分片的方法*/
	pathName := path("/usr/bin/tso") // Conversion from string to path.
	pathName.TruncateAtFinalSlash()  /*pathName应该不是指针吧*/
	fmt.Printf("%s\n", pathName)

	/*pathName竟然在指针非指针的要求下都能直接传入*/
	fmt.Println("before TestNotPointer")
	pathName.TestNotPointer()
	fmt.Println("before TestPointer")
	pathName.TestPointer()
	fmt.Println("Before ToUpper : len(pathName) =", len(pathName))
	pathName.ToUpper()
	fmt.Printf("after ToUpper : %s\n", pathName)

	/*传入一个元素扩展它的slice参数*/
	const MAX_NUM = 14
	var iBuffer [MAX_NUM]int
	aSlice := iBuffer[0:0] /*aSlice最大只能是14个*/
	for i := 0; i < MAX_NUM; i++ {
		aSlice = Extend(aSlice, i)
		fmt.Println("cur i ", i, aSlice)
	}

	/*对int分片的容量实现了倍增，而其长度却保持不变*/
	bSlice := make([]int, 10, 15)
	fmt.Printf("len: %d, cap: %d\n", len(bSlice), cap(bSlice))
	bNewSlice := make([]int, len(bSlice), 2*cap(bSlice))
	for i := range bSlice {
		bNewSlice[i] = bSlice[i]
	}
	bSlice = bNewSlice
	fmt.Printf("len: %d, cap: %d\n", len(bSlice), cap(bSlice))

	/*创建slices的时候，slice的长度和它的容量是相同的。
	通用情况下在make内置一个数组。参数的长度默认就是它的容量，所有你可以把它们设置为相同的值。*/
	type Gopher []int
	gophers := make([]int, 10, 20)
	fmt.Printf("len: %d, cap: %d\n", len(gophers), cap(gophers))

	for i := range gophers {
		gophers[i] = i
	}
	fmt.Println("before Insert : ", gophers)
	gophers = Insert(gophers, 5, 99)
	fmt.Println("after Insert : ,gophers)
}

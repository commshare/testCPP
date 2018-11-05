package main

import (
	"encoding/json"
	"fmt"
	"reflect"
)

type Project struct {
	name string
}
type Proj struct {
	name string
}

func (p *Project) String() string {
	return "pname=" + p.name
}

type A struct {
	a int32
	B *B
}

type B struct{ b int32 }

func (aa *A) String() string {
	return fmt.Sprintf("A{a:%d, B:%v}", aa.a, aa.B)
}

func (bb *B) String() string {
	return fmt.Sprintf("B{b:%d}", bb.b)
}

func struct2string() {
	a := &A{a: 1, B: &B{b: 2}}

	// using the Stringer interface
	fmt.Printf("v ==== %v \n", a)

	// or just print it yourself however you want.
	fmt.Printf("v ==== A{a:%d, B:B{b:%d}}\n", a.a, a.B.b)

	// or just reference the values in the struct that are structs themselves
	// but this can get really deep
	fmt.Printf("v ==== A{a:%d, B:%v}", a.a, a.B)
}

/*http://blog.csdn.net/qq_29447481/article/details/72874847
转换顺序：先将struct结构体转为map,再将map转为string字符串
struct --> map --> string
*/
type demo struct {
	Id   string
	Name string
}

//结构体转为map
func Struct2Map(obj interface{}) map[string]interface{} {
	t := reflect.TypeOf(obj)
	v := reflect.ValueOf(obj)

	var data = make(map[string]interface{})
	for i := 0; i < t.NumField(); i++ {
		data[t.Field(i).Name] = v.Field(i).Interface()
	}
	return data
}
func struct2string2() {

	demo1 := demo{"1", "zs"}
	demo2 := demo{"2", "ls"}
	demo3 := demo{"3", "ww"}
	/*.\test_output_pointer_value.go:74: cannot use nil as type string in field value*/
	//demo5 := demo{nil, nil}
	demos := []demo{demo1, demo2, demo3} //, nil, demo5}  /.\test_output_pointer_value.go:75: cannot convert nil to type demo*/
	for _, v := range demos {
		tmpdata := Struct2Map(v)
		str, err := json.Marshal(tmpdata)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(string(str))
	}

}

/*
https://stackoverflow.com/questions/16976523/in-go-why-isnt-my-stringer-interface-method-getting-invoked-when-using-fmt-pr
*/
type Car struct {
	year int
	make string
}

func (c Car) String() string {
	return fmt.Sprintf("in String():{make:%s, year:%d}", c.make, c.year)
}

func noPointerString() {
	myCar := Car{year: 1996, make: "Toyota"}
	fmt.Println(myCar)
	fmt.Println(&myCar)
}

type CCar struct {
	year int
	make string
}

/*.\test_output_pointer_value.go:105: method redeclared: Car.String
  method(Car) func() string
  method(*Car) func() string

  不管是指针还是非指针，都认为String是属于同一个结构体的，所以只能结构体改名了
*/
func (c *CCar) String() string {
	return fmt.Sprintf("{maker:%s, produced:%d}", c.make, c.year)
}

func PointerString() {
	myCar := CCar{year: 1996, make: "Toyota"}
	myOtherCar := &CCar{year: 2013, make: "Honda"}
	fmt.Println(&myCar)
	fmt.Println(myOtherCar)
}
func main() {
	projs := []*Proj{&Proj{"p1"}, &Proj{"p2"}}
	fmt.Println("projs: ", projs)
	fmt.Printf("projs: % +v\n", projs)
	fmt.Printf("projs: %v\n", projs)

	projects := []*Project{nil, &Project{"p2"}}
	fmt.Println("projects: ", projects)
	fmt.Println("len projects: ", len(projects))
	fmt.Printf("projects: % +v\n", projects)
	fmt.Printf("projects: %v\n", projects)

	nilprojects := []*Project{}
	fmt.Println("nilprojects: ", nilprojects)
	fmt.Println("len nilprojects: ", len(nilprojects))
	fmt.Printf("nilprojects: % +v\n", nilprojects)
	fmt.Printf("nilprojects: %v\n", nilprojects)

	struct2string()
	struct2string2()
	noPointerString()
	PointerString()
}

/*
$ ./test_output_pointer_value.exe
projs:  [0xc042008250 0xc042008260]
projs: [ 0xc042008250  0xc042008260]
projs: [0xc042008250 0xc042008260]
projects:  [<nil> pname=p2]
len projects:  2
projects: [<nil> pname=p2]
projects: [<nil> pname=p2]
nilprojects:  []
len nilprojects:  0
nilprojects: []
nilprojects: []
v ==== A{a:1, B:B{b:2}}
v ==== A{a:1, B:B{b:2}}
v ==== A{a:1, B:B{b:2}}

*/

/* https://stackoverflow.com/questions/24489384/golang-how-to-print-the-values-of-arrays
You can try the %v, %+v or %#v verbs of go fmt:

fmt.Printf("%v", projects)
If your array (or here slice) contains struct (like Project), you will see their details.
For more precision, you can use %#v to print the object using Go-syntax, as for a literal:

%v  the value in a default format.
    when printing structs, the plus flag (%+v) adds field names
%#v a Go-syntax representation of the value
For basic types, fmt.Println(projects) is enough.

Note: for a slice of pointers, that is []*Project (instead of []Project), you are better off defining a String() method in order to display exactly what you want to see (or you will see only pointer address).
See this play.golang example.


$ ./test_output_pointer_value.exe
projs:  [0xc042008250 0xc042008260]
projs: [ 0xc042008250  0xc042008260]
projs: [0xc042008250 0xc042008260]
projects:  [pname=p1 pname=p2]
projects: [pname=p1 pname=p2]
projects: [pname=p1 pname=p2]
nilprojects:  []
nilprojects: []
nilprojects: []


*/

/*  http://blog.51cto.com/guanyu/1893143
 基本变量的初始化前面已经提到了字面量，在Go语言中，对复合类型变量(数组、切片、字典、结构体) 的初始化是有一些语法限制的，但对基本变量的初始化没有这些限制，比如：
1. 初始化表达式必须含有类型标签
2. 左花括号不能另起一行，必须在类型尾部
3. 多成员初始值必须用逗号","分隔
4. 允许多行编写，但是每行必须以逗号","或右花括号结束

type stu struct{
    name string
    age int
}
b := stu{
    "zhang",
    20       //unexpected semicolon or newline, expecting comma or }，须以逗号或右花括号结束
}
b := stu
{   //syntax error: unexpected }, expecting expression，左花括号不能另起一行
    "zhang",
    20,
}
var data stu = {"wang",20} //syntax error: missing operand，初始化表达式必须含有类型标签
*/

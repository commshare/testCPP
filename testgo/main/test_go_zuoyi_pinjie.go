package main

/*
http://xiaoyu.world/2017/02/27/go-offset-operation/
*/
/*
背景
今天有一个需求，是我需要拼接一个2字节的byte，且要根据要求按位拼接，这时候就需要我们用到位移操作。

Coding Now
位移操作很容易理解了，2字节我们先设置一个uint16类型的来存我们最终的值，这里我们假定两种情况，
*/

import (
	"encoding/binary"
	"fmt"

	"github.com/imroc/biu"
)

/*
情况一：16位都没有关系需要逐位拼接
*/
func s1() {
	var m uint16 = 0
	m = m | 1
	m = m << 1
	m = m | 0
	m = m << 1
	//....  // 省略同上
	m = m | 1
	m = m << 1
	m = m | 0
	//m = m << 1
	s := make([]byte, 2)
	binary.BigEndian.PutUint16(s, m)
	fmt.Println(biu.BytesToBinaryString(s)) // 这个函数是引用了github中的一个库，可以将[]byte转为二进制字符串
}

/*情况二：我们假定将16位分成前6位和后10位*/
func s2() {
	var x uint16 = 512 // 后10位
	var m uint16 = 0   // 初始化
	var l uint16 = 45  // 前6位
	m = m | l          // 先与前6位取或
	m = m << 10        // 然后左移10位
	m = m | x          // 与后10位取或
	s := make([]byte, 2)
	binary.BigEndian.PutUint16(s, m) // 用大端的方式将uint16的m放入我们新建的[]byte中
	fmt.Println(biu.BytesToBinaryString(s))
}
func add(x, y int) uint16 {
	return uint16(x + y)
}
func s3_1() {
	const m1 uint8 = 255
	fmt.Println(m1 << 4)

	var m uint16
	m = add(3, 4) /*const m uint16 = add(3, 4)  add(x, y int)只有在运行期才能知道返回结果，所以也会报错。*/
	fmt.Println(m)
}

/*
所以，你可能需要先用不定长度的uint类型绕开溢出的限制，
再用掩码(& 0xFFFF)运算去约束结果的范围，（如果是uint8就用0xFF），加了判断溢出的处理之后，代码是这样的
*/
func s3() {
	var size uint16 = 512
	var m uint16 = 0
	var l uint16 = 45
	m = m | l
	m = uint16(uint(m) << 10 & 0xFFFF)
	//m = m << 10
	m = m | size
	s := make([]byte, 2)
	binary.BigEndian.PutUint16(s, m)
	fmt.Println(biu.BytesToBinaryString(s))
}
func main() {
	s1()
	s2()
	/*溢出*/
	s3_1()
	s3()
}

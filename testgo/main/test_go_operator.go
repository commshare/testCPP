package main

/*http://www.cnblogs.com/piperck/p/6139369.html

&      位运算 AND
|      位运算 OR
^      位运算 XOR
&^     位清空 (AND NOT)
<<     左移
>>     右移

*/
import "fmt"

func main() {
	x := 4
	/*^(XOR) 在go语言中XOR是作为二元运算符存在的：

	但是如果是作为一元运算符出现，他的意思是按位取反，例如*/
	fmt.Println(^x) //输出-5 为啥是-5啊
	y := 2
	/*XOR是不进位加法计算，也就是异或计算。0000 0100 + 0000 0010 = 0000 0110 = 6

	https://github.com/Unknwon/the-way-to-go_ZH_CN/blob/master/eBook/04.5.md
	按位异或 ^：

	对应位置上的值根据以下规则组合：

	  1 ^ 1 -> 0
	  1 ^ 0 -> 1
	  0 ^ 1 -> 1
	  0 ^ 0 -> 0

	*/
	fmt.Println(x ^ y) //6

	/*	左移就2的n次方，右移就除以2的n次方

		位左移 <<：

		用法：bitP << n。

		bitP 的位向左移动 n 位，右侧空白部分使用 0 填充；如果 n 等于 2，则结果是 2 的相应倍数，即 2 的 n 次方。例如：

		  1 << 10 // 等于 1 KB
		  1 << 20 // 等于 1 MB
		  1 << 30 // 等于 1 GB

	*/
	fmt.Println(x << 1)
	fmt.Println(y >> 1)
}

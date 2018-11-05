package main

import (
	"fmt"
	"strings"
	"time"
)

/*
  continue ： 跳过此次循环
break 可用语 for, switch, select
continue 只能用语 for 循环

*/

func testBreak() {
	for i := 0; i < 3; i++ {
		for j := 0; j < 10; j++ {
			if j > 5 {
				break /*break 语句的作用结果是跳过整个代码块，执行后续的代码。会跳过for j=这层循环，继续for i= 的下一个*/
			}
			fmt.Println(j)
		}
		fmt.Printf(" ---end for i=%d -----\n", i)
	}
}

func testContinue() {
	fmt.Println("----------test_continue-----------")
	for i := 0; i < 10; i++ {
		if i == 5 {
			continue /*执行了continue之后，后面的俩打印不执行，执行for i==6 的打印*/
		}
		fmt.Printf("cur for i=%d\n", i)
		fmt.Printf(" ")
	}
}
func testBreakForSwitch() {
	fmt.Println("----------testBreakForSwitch-----------")
myloop:
	for x := 0; x < 7; x++ {
		fmt.Printf("%d ", x)
		switch {
		case x == 1:
			fmt.Println("start x==1")
		case x == 5: /*会走这里，不会走x>2的分支*/
			fmt.Println("stop x==5 break myloop")
			break myloop /*跳出for吧*/
		case x > 2:
			fmt.Println("crunching.. x>2  break")
			break /*跳出switch吧，这个break加和不加的一样的*/
		default:
			fmt.Println("default : idling..")
		}
	}
}

/*
----------testContinueLlabel-----------
0:0 0:1 0:2
--------continue L2 -----

--------continue L2 -----

1:0 1:1 1:2
--------continue L2 -----

--------continue L2 -----


----break L1
配合标签，goto,break,continue可以在循环内跳转

https://github.com/mebusy/notes/blob/master/dev_notes/GOLANG%20%E5%A4%87%E5%BF%982-%E8%A1%A8%E8%BE%BE%E5%BC%8F.md

*/
func testContinueLlabel() {
	fmt.Println("----------testContinueLlabel-----------")

L1:
	for x := 0; x < 3; x++ {
	L2:
		for y := 0; y < 5; y++ {
			if y > 2 {
				print("\n--------continue L2 -----\n")
				continue L2
			}
			if x > 1 {
				print("\n----break L1 \n")
				break L1
			}
			print(x, ":", y, " ")
		}
		println()
	}

}

/*https://golangtc.com/t/52e5ffb8320b524594000009*/
type channel struct {
	read  chan interface{}
	write chan interface{}
	done  chan bool
}

func testSelect() {
	//o := make(chan bool)
	c := channel{make(chan interface{}), make(chan interface{}), make(chan bool)}
	go func() {
		var value interface{}
		for {
			select {
			case c.read <- value:
				fmt.Println("          c.read has value ...")
			case value = <-c.write: /*等号是读取数据并赋值用的*/
				fmt.Println("          c.write has value ...")
				fmt.Println(value)
			case <-c.done:
				fmt.Println("   @@@@@        break")
				//o <- true    /*加入这句话会造成死锁么？*/
				break
			} //end select
			fmt.Println("           after select ,end of for") /*break 出select
			之后，还会走这句话*/
		} /*end for*/
		/**不管是不是最后一步是break，这个都不输出啊**/
		fmt.Println("  ---------will exit from this routine")
		time.Sleep(time.Second * 1)
	}()
	/*创建write*/
	p := c.write
	/*写入大写The Nice World
	 */
	p <- strings.Title("the nice world") //Title
	/*读取发现为true，写入true*/
	p <- strings.Contains((<-c.read).(string), "Nice")
	/*写入true*/
	p <- strings.ContainsAny("The Nice World", "Nice")
	/*写入1*/
	p <- strings.Count("string", "s")
	/*true*/
	p <- strings.EqualFold("the", "The")
	/*写入true*/
	p <- strings.HasPrefix("popar fish", "po")
	/*出发break*/
	c.done <- true
	/*再写入*/
	p <- strings.Title("zhangBin")
	p <- strings.HasSuffix("poplar fish", "fish")
	fmt.Println("--------------end of ----func----------")
	//time.Sleep(time.Second * 3)
	//<-o
}

/*https://github.com/SUTFutureCoder/go-practise/blob/d27f0ef54d30053e4f2d3ef47fc5af198c5b1824/section2/3.20.go
https://github.com/CodyGuo/Go-Cody/blob/f32583655d51c7fe9ca1920b4d2e9b98004df3a9/go_example/Test/2016/201612/03/test5/main.go
*/
func testSelectPractice() {
	c := make(chan int)
	o := make(chan bool)
	go func() {
		for i := 0; i < 10; i++ {
			c <- i
		}
	}()

	go func() {
		for {
			select {
			case v := <-c:
				println(v)
			case <-time.After(5 * time.Second):
				println("time out")
				o <- true
				break /*可以break出select和for么？*/
			}
			/*只要执行了select的case，就会执行这里*/
			println("=========after select===========")
		}
		/*for后面的这句话一直得不到打印*/
		println("=============end of for ==============")
	}()
	/*阻塞，等待退出*/
	/*可以看到，这个打印跟routine几乎是同一时间执行的，先打印的这个，然后routine才开始输出的*/
	print("88888888888888888888 wait for routine over....")
	<-o
}
func main() {
	testBreak()
	testContinue()
	testBreakForSwitch()
	testContinueLlabel()
	testSelect()
	testSelectPractice()
}

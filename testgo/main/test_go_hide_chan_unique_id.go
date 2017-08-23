//testuniqueid.go
package main

import "fmt"

func newUniqueIDService() <-chan string {
	id := make(chan string)
	go func() {
		var counter int64 = 0
		for {
			id <- fmt.Sprintf("%x", counter)
			counter += 1
			fmt.Printfln("gen id :%v", id)
		}
	}()
	/*上面的routine只要产生了一个数据写入到id里，那么就会被return吧*/
	return id
}
func main() {
	id := newUniqueIDService()
	for i := 0; i < 10; i++ {
		fmt.Println(<-id)
	}
}

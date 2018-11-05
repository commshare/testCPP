package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"os/signal"
)

func handleConn(c net.Conn) {
	defer c.Close() // 利用延迟函数进行关闭连接
	for {
		// begin to read from connection
		// begin to write to connection
	}
}
func main() {
	log.Println("begin listen")
	l, err := net.Listen("tcp", ":8000") // 监听本机的8000端口
	if err != nil {
		fmt.Println("listen error:", err)
		return
	}
	for {
		c, err := l.Accept()
		if err != nil {
			fmt.Println("accept error:", err)
			break
		}
		go handleConn(c)
	}
	log.Println("listen success")
	/*使用clt+c 可以快速退出*/
	// close
	c := make(chan os.Signal, 1)
	signal.Notify(c, os.Interrupt, os.Kill)
	sig := <-c
	fmt.Printf("Leaf closing down (signal: %v)\n", sig)
}

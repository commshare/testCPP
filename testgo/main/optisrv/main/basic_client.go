package main

import (
	"fmt"
	"net"
	"os"
	"time"
)

var connChan chan *net.TCPConn = make(chan *net.TCPConn)
var sendChan chan int = make(chan int)

func connection(tcpAddr *net.TCPAddr) {
	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}
	connChan <- conn
}

func sender(conn net.Conn) {
	words := "hello world!"
	conn.Write([]byte(words))
	fmt.Println("send over")
	sendChan <- 0
}

func main() {
	server := "127.0.0.1:3333"
	tcpAddr, err := net.ResolveTCPAddr("tcp4", server)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}

	for i := 0; i < 100; i++ {
		go connection(tcpAddr)
	}
	for i := 0; i < 100; i++ {
		connect := <-connChan
		fmt.Println("connect success")
		for j := 0; j < 500; j++ {
			go sender(connect)
		}
		fmt.Println(time.Now().Format("2006-01-02 15:04:05"))
		for j := 0; j < 500; j++ {
			<-sendChan
			fmt.Println(time.Now().Format("2006-01-02 15:04:05"))
		}
		connect.Close()

	}

}

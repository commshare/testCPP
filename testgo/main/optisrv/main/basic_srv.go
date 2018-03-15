package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"time"
)

var sendChan chan int = make(chan int)

func main() {

	ticker := time.NewTicker(10 * time.Second)
	time := <-ticker.C
	fmt.Println(time.String())
	//for i := 0; i < 10; i++ {
	//	time := <-ticker.C
	//	fmt.Println(time.String())
	//}

	//建立socket，监听端口
	netListen, err := net.Listen("tcp", "127.0.0.1:3333")
	fmt.Println("-------------")
	CheckError(err)
	defer netListen.Close()

	Log("Waiting for clients")
	for {
		conn, err := netListen.Accept()
		if err != nil {
			continue
		}
		Log(conn.RemoteAddr().String(), " tcp connect success")
		for j := 0; j < 500; j++ {
			go handleConnection(conn)
			<-sendChan
		}

	}
}

//处理连接
func handleConnection(conn net.Conn) {
	buffer := make([]byte, 2048)
	for {
		n, err := conn.Read(buffer)
		if err != nil {
			Log(conn.RemoteAddr().String(), " connection error: ", err)
			return
		}
		Log(conn.RemoteAddr().String(), "receive data string:\n", string(buffer[:n]))
	}
	sendChan <- 0
}

func Log(v ...interface{}) {
	log.Println(v...)
}

func CheckError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}
}

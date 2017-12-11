package main

/*
http://xiaoyu.world/2017/02/16/go-packet-splicing/
*/
import (
	"fmt"
	"log"
	"net"
	"os"
	"os/signal"
	"time"
)

func establishConn(i int) net.Conn {
	conn, err := net.Dial("tcp", ":8000")
	if err != nil {
		log.Printf("%d: dial error: %s", i, err)
		return nil
	}
	log.Println(i, ":connect to server ok")
	return conn
}
func main() {
	var sl []net.Conn
	for i := 1; i < 11; i++ {
		conn := establishConn(i)
		if conn != nil {
			sl = append(sl, conn)
		}
	}
	time.Sleep(time.Second * 10000)

	/**/
	// close
	c := make(chan os.Signal, 1)
	signal.Notify(c, os.Interrupt, os.Kill)
	sig := <-c
	fmt.Printf("Leaf closing down (signal: %v)\n", sig)
}

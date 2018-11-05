/*
https://gist.github.com/Bo0mer/2151250f2704076faa7ba250455cd376

这个是系统api，不是go的
int setsockopt(
SOCKET s,
int level,
int optname,
const char* optval,
int optlen
);
s(套接字): 指向一个打开的套接口描述字
level:(级别)： 指定选项代码的类型。
SOL_SOCKET: 基本套接口
IPPROTO_IP: IPv4套接口
IPPROTO_IPV6: IPv6套接口
IPPROTO_TCP: TCP套接口
optname(选项名)： 选项名称
optval(选项值): 是一个指向变量的指针 类型：整形，套接口结构， 其他结构类型:linger{}, timeval{ }
optlen(选项长度) ：optval 的大小
返回值：标志打开或关闭某个特征的二进制选项

*/

package main

import (
	"fmt"
	"log"
	"net"
	"os"
	"syscall"
	"time"
)

const req = `GET / HTTP/1.1
Host: localhost:8080
User-Agent: curl/7.43.0
Accept: */*
`

func main() {
	s, err := syscall.Socket(syscall.AF_INET, syscall.SOCK_STREAM, 6)
	if err != nil {
		log.Fatal(err)
	}

	if err := syscall.SetsockoptInt(s, syscall.SOL_SOCKET, syscall.SO_RCVBUF, 256); err != nil {
		log.Fatal(err)
	}

	addr := &syscall.SockaddrInet4{
		Port: 8080,
		Addr: [4]byte{127, 0, 0, 1},
	}
	if err := syscall.Connect(s, addr); err != nil {
		log.Fatal(err)
	}

	f := os.NewFile(uintptr(s), "name")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	c, err := net.FileConn(f)
	if err != nil {
		log.Fatal(err)
	}

	c.Write([]byte(req))

	time.Sleep(time.Second * 10)
	buf := make([]byte, 1024*20)
	n, err := c.Read(buf)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(string(buf))
	fmt.Printf("total of %d bytes\n", n)
}

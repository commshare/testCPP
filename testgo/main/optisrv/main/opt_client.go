package main

import (
	"encoding/binary"
	"fmt"
	"net"
	"os"
	"strconv"
	"time"
	//	"igen.com/bee/socket/optimizi/protocol"
)

func sender(conn net.Conn) {
	for i := 0; i < 500; i++ {
		//words := "{\"Id\":1,\"Name\":\"golang\",\"Message\":\"message\"}"
		words := "A502031042536710430031F1107C000702011105190E2E03E001140A36139024401002140139007A098613FE052204AD1F000060020300000000000107000000000A3018902440100117013A0079098A1311060B04711F000024020300000000000107000000000A3018902440100218013B007A098A1344062A04901F000024020300000000000107000000000A73179024401001000000000000000000000000751B000000000000000000000007000000000A73179024401002000000000000000000000000751B000000000000000000000007000000000A01189024401001000000000000000000000000901B000000000000000000000007000000000A01189024401002000000000000000000000000901B000000000000000000000007000000000A78560031E010007400000000000000430000007F1B00007C020000000000000007000000000A3410902440100115013C007409871326062504BB1F00002B020300000000000107000000000A341090244010020F013A006F098513E8051904AF1F00002C020300000000000107000000000A591790244010011501390073098713F10502049A1F00002A020300000000000107000000000A5917902440100211013A006F0985130D062204BA1F00002B020300000000000107000000000A6019902440100114013A006A098813FA050B04721F00002D020300000000000107000000000A601990244010021001390069098413F30517047E1F00002D020300000000000107000000000A8604902340100118013B00690988132D061D04841F000024020300000000000107000000000A8604902340100217013C0066098413690633049A1F000024020300000000000107000000000A1713902340100116013A00720989130C060804641F000010020300000000000107000000000A17139023401002180139006A098513FD051E047A1F000012020300000000000107000000000A037730224010011701390078098913FE050404701F000011020300000000000107000000000A0377302240100215013B00780985133E061B04871F000010020300000000000107000000003115"
		data := []byte(words)
		runningNumber := binary.BigEndian.Uint16(data[2:4])
		println(runningNumber)
		conn.Write(protocol.Packet(data))

	}
	fmt.Println("send over")
}

func main() {

	words := "A502031042536710430031F1107C000702011105190E2E03E001140A36139024401002140139007A098613FE052204AD1F000060020300000000000107000000000A3018902440100117013A0079098A1311060B04711F000024020300000000000107000000000A3018902440100218013B007A098A1344062A04901F000024020300000000000107000000000A73179024401001000000000000000000000000751B000000000000000000000007000000000A73179024401002000000000000000000000000751B000000000000000000000007000000000A01189024401001000000000000000000000000901B000000000000000000000007000000000A01189024401002000000000000000000000000901B000000000000000000000007000000000A78560031E010007400000000000000430000007F1B00007C020000000000000007000000000A3410902440100115013C007409871326062504BB1F00002B020300000000000107000000000A341090244010020F013A006F098513E8051904AF1F00002C020300000000000107000000000A591790244010011501390073098713F10502049A1F00002A020300000000000107000000000A5917902440100211013A006F0985130D062204BA1F00002B020300000000000107000000000A6019902440100114013A006A098813FA050B04721F00002D020300000000000107000000000A601990244010021001390069098413F30517047E1F00002D020300000000000107000000000A8604902340100118013B00690988132D061D04841F000024020300000000000107000000000A8604902340100217013C0066098413690633049A1F000024020300000000000107000000000A1713902340100116013A00720989130C060804641F000010020300000000000107000000000A17139023401002180139006A098513FD051E047A1F000012020300000000000107000000000A037730224010011701390078098913FE050404701F000011020300000000000107000000000A0377302240100215013B00780985133E061B04871F000010020300000000000107000000003115"
	data := []byte(words)
	runningNumber := binary.BigEndian.Uint16(data[2:4])
	println(runningNumber)
	fmt.Printf("%x\n", "02")

	println(strconv.FormatInt(10, 16))
	println(strconv.FormatInt(0x10, 10))
	server := "127.0.0.1:9988"
	tcpAddr, err := net.ResolveTCPAddr("tcp4", server)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}

	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}

	defer conn.Close()
	fmt.Println("connect success")
	go sender(conn)
	for {
		time.Sleep(1 * 1e9)
	}

}

/**
 * 十进制转十六进制
 */
func toHex(ten int) (hex []int, length int) {
	m := 0

	hex = make([]int, 0)
	length = 0

	for {
		m = ten / 16
		ten = ten % 16

		if m == 0 {
			hex = append(hex, ten)
			length++
			break
		}

		hex = append(hex, m)
		length++
	}
	return
}

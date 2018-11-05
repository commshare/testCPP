package main

import (
	"fmt"
	"net"
	"os"

	//"igen.com/bee/socket/optimizi/protocol"
	//"bytes"
	//"encoding/binary"
	"bytes"
	//"encoding/binary"
	"strconv"
)

func main() {
	//var num int16
	//buf := bytes.NewReader([]byte("0203"))
	//_ = binary.Read(buf, binary.BigEndian, &num)
	//println(num)

	println([]byte("0203"))
	fmt.Printf("%x\n", "0203")

	netListen, err := net.Listen("tcp", ":9988")
	CheckError(err)

	defer netListen.Close()

	Log("Waiting for clients")
	for {
		conn, err := netListen.Accept()
		if err != nil {
			continue
		}

		Log(conn.RemoteAddr().String(), " tcp connect success")
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	//声明一个临时缓冲区，用来存储被截断的数据
	tmpBuffer := make([]byte, 0)

	//声明一个管道用于接收解包的数据
	readerChannel := make(chan []byte, 16)
	go reader(readerChannel)

	buffer := make([]byte, 1024)
	for {
		n, err := conn.Read(buffer)
		if err != nil {
			Log(conn.RemoteAddr().String(), " connection error: ", err)
			return
		}

		tmpBuffer = protocol.Unpack(append(tmpBuffer, buffer[:n]...), readerChannel)
	}
}

func reader(readerChannel chan []byte) {
	for {
		select {
		case data := <-readerChannel:
			Log("A5" + string(data))
		}
	}
}

func Log(v ...interface{}) {
	fmt.Println(v...)
}

func CheckError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}
}

// 这是一个例子, 解码出 ">HHI"
func unpack(data []byte, edian byte) (uint16, uint16, uint32, []byte) {
	dataType := ToUInt16(data[0:2], edian)
	dataAttr := ToUInt16(data[2:4], edian)
	dataLen := ToUInt32(data[4:8], edian)
	extra := data[8:]

	return dataType, dataAttr, dataLen, extra
}

func ToUInt8(buf []byte, edian byte) uint8 {
	// len(buf) == 1    -->B
	t := uint8(buf[0])
	return t
}

func ToUInt16(buf []byte, edian byte) uint16 {
	// len(buf) == 2    -->H
	t := uint16(buf[0])
	if edian == 62 { // ">"
		t = t<<8 | uint16(buf[1])
	} else if edian == 60 { // "<"
		t = t | uint16(buf[1])<<8
	}

	return t
}

func ToUInt32(buf []byte, edian byte) uint32 {
	// len(buf) == 4    -->I
	t := uint32(buf[0])
	if edian == 62 {
		t = t << 24
		t = t | uint32(buf[1])<<16
		t = t | uint32(buf[2])<<8
		t = t | uint32(buf[3])

	} else if edian == 60 {
		t = t | uint32(buf[1])<<8
		t = t | uint32(buf[2])<<16
		t = t | uint32(buf[3])<<24
	}
	return t
}

func ToUInt64(buf []byte, edian byte) uint64 {
	//len(buf) == 8    -->Q
	t := uint64(buf[0])
	if edian == 62 {
		t = t << 56
		t = t | uint64(buf[1])<<48
		t = t | uint64(buf[2])<<40
		t = t | uint64(buf[3])<<32
		t = t | uint64(buf[4])<<24
		t = t | uint64(buf[5])<<16
		t = t | uint64(buf[6])<<8
		t = t | uint64(buf[7])
	} else if edian == 60 {
		t = t | uint64(buf[1])<<8
		t = t | uint64(buf[2])<<16
		t = t | uint64(buf[3])<<24
		t = t | uint64(buf[4])<<32
		t = t | uint64(buf[5])<<40
		t = t | uint64(buf[6])<<48
		t = t | uint64(buf[7])<<56
	}
	return t
}

func ByteToHex(data []byte) string {
	buffer := new(bytes.Buffer)
	for _, b := range data {

		s := strconv.FormatInt(int64(b&0xff), 16)
		if len(s) == 1 {
			buffer.WriteString("0")
		}
		buffer.WriteString(s)
	}

	return buffer.String()
}

package main

/*
https://github.com/ittechblog/godemo/blob/master/socket/optimizi/server/server.go
*/
import (
	"bytes"
	"encoding/binary"
	"strconv"
)

const (
	ConstHeader         = "A5"
	ConstHeaderLength   = 2
	ConstSaveDataLength = 0
)

//封包
func Packet(message []byte) []byte {
	return message
	//return append(append([]byte(ConstHeader), IntToBytes(len(message))...), message...)
}

//解包
func Unpack(buffer []byte, readerChannel chan []byte) []byte {
	length := len(buffer)

	var i int
	for i = 0; i < length; i = i + 1 {
		if length < i+ConstHeaderLength+ConstSaveDataLength {
			break
		}
		if string(buffer[i:i+ConstHeaderLength]) == ConstHeader {
			receiveMsg := string(buffer[:])
			strconv.Atoi(receiveMsg[2:4])
			l1, _ := strconv.Atoi(reverseString(receiveMsg[4:6]) + reverseString(receiveMsg[2:4]))
			if l1 > 1000 {
				l1 = l1 / 10
				//l2,_ := strconv.ParseInt("0x"+strconv.Itoa(l1), 10, 64)
				//l2 = strconv.FormatInt("0x"+strconv.Itoa(l1),10)
			}
			//hexL1 := strconv.FormatInt(int64(l1),16)
			//println(hexL1)
			//fmt.Printf("%x",l1)
			//l1,_ = strconv.Atoi(strconv.FormatInt(hexL1),10))
			messageLength := 1540 + 36
			if length < i+ConstHeaderLength+ConstSaveDataLength+messageLength {
				break
			}
			data := buffer[i+ConstHeaderLength+ConstSaveDataLength : i+ConstHeaderLength+ConstSaveDataLength+messageLength]
			readerChannel <- data

			i += ConstHeaderLength + ConstSaveDataLength + messageLength - 1
		}
	}

	if i == length {
		return make([]byte, 0)
	}
	return buffer[i:]
}

//整形转换成字节
func IntToBytes(n int) []byte {
	x := int32(n)

	bytesBuffer := bytes.NewBuffer([]byte{})
	binary.Write(bytesBuffer, binary.BigEndian, x)
	return bytesBuffer.Bytes()
}

//字节转换成整形
func BytesToInt(b []byte) int {
	bytesBuffer := bytes.NewBuffer(b)

	var x int32
	binary.Read(bytesBuffer, binary.BigEndian, &x)

	return int(x)
}

func reverseString(s string) string {
	runes := []rune(s)

	for from, to := 0, len(runes)-1; from < to; from, to = from+1, to-1 {
		runes[from], runes[to] = runes[to], runes[from]
	}

	return string(runes)
}

/* https://github.com/fzu-huang/calcnet/blob/master/calcnet.go
2015.2.1  更新
function：
AtoIPByte():将ip类型string转为byte数组，便于初始化net.IP

CalcNetAddr():获取两个ip（byte数组），计算这两个ip可以同属的范围最小的网络地址和段数。
              etc:  "192.168.24.203", "192.168.24.44" 两个ip的网络地址是 192.168.24/24
*/

package calcnet

import (
	"encoding/binary"
	"net"
	"strconv"
	"strings"
)

func CalcNetAddr(ip1, ip2 []byte) string {
	ipint1 := binary.BigEndian.Uint32(ip1[0:])
	ipint2 := binary.BigEndian.Uint32(ip2[0:])

	calc1 := ipint1 ^ ipint2
	count := 0
	for {
		if calc1 == 0 {
			break
		}
		calc1 = calc1 >> 1
		count++
	}
	//intipint1 := int(ipint1)
	ipnetint := (ipint1 >> uint32(count)) << uint32(count)
	ipnet := make([]byte, 4, 4)
	binary.BigEndian.PutUint32(ipnet[0:], ipnetint)
	return net.IPv4(ipnet[0], ipnet[1], ipnet[2], ipnet[3]).String() + "/" + strconv.Itoa(32-count)
}

func AtoIPByte(ip1, ip2 string) ([]byte, []byte) {
	ip1part := strings.SplitN(ip1, ".", 4)
	ip2part := strings.SplitN(ip2, ".", 4)
	ip1byte := make([]byte, 4, 4)
	ip2byte := make([]byte, 4, 4)
	for i := 0; i < 4; i++ {
		tint, _ := strconv.Atoi(ip1part[i])
		ip1byte[i] = uint8(tint)

		tint, _ = strconv.Atoi(ip2part[i])
		ip2byte[i] = uint8(tint)
	}
	return ip1byte, ip2byte
}

package broadcast

import (
	"NXProductionTest/common"
	"net"
	"strconv"
	"strings"
	"time"
)

var conn *net.UDPConn

func init() {
	localNet := common.GetLocalNet()
	ipDotValues := strings.Split(localNet.Ip, ".")
	a, _ := strconv.Atoi(ipDotValues[0])
	b, _ := strconv.Atoi(ipDotValues[0])
	c, _ := strconv.Atoi(ipDotValues[0])
	d, _ := strconv.Atoi(ipDotValues[0])

	// 这里设置发送者的IP地址，自己查看一下自己的IP自行设定
	laddr := net.UDPAddr{
		IP:   net.IPv4(byte(a), byte(b), byte(c), byte(d)),
		Port: 3000,
	}
	// 这里设置接收者的IP地址为广播地址
	raddr := net.UDPAddr{
		IP:   net.IPv4(255, 255, 255, 255),
		Port: 3000,
	}
	conn, _ = net.DialUDP("udp", &laddr, &raddr)

}

func BroadCast(content string) {
	if conn != nil {
		go func() {
			for true {
				time.Sleep(time.Duration(10) * time.Second) //10s sleep
				conn.Write([]byte(content))
			}
		}()
	}
}

func Close() {
	conn.Close()
}

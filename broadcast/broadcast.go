package broadcast

import (
	"net"
	"time"
)

var conn *net.UDPConn

func init() {
	conn, _ = net.DialUDP("udp", nil, &net.UDPAddr{
		IP:   net.IPv4(255, 255, 255, 255),
		Port: 3000,
	})
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

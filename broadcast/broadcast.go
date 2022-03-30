package broadcast

import (
	"net"
	"time"
)

var conn *net.UDPConn

func Open(port int) error {
	var err error
	conn, err = net.DialUDP("udp", nil, &net.UDPAddr{
		IP:   net.IPv4(255, 255, 255, 255),
		Port: port,
	})
	return err
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

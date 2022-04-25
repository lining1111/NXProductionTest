package broadcast

import (
	"fmt"
	"net"
	"time"
)

var conn *net.UDPConn
var localPort int

func Open(port int) error {
	localPort = port
	var err error
	conn, err = net.DialUDP("udp", nil, &net.UDPAddr{
		IP:   net.IPv4(255, 255, 255, 255),
		Port: port,
	})
	return err
}

func BroadCast(content []byte) {
	if conn != nil {
		go func() {
			for true {
				time.Sleep(time.Duration(10) * time.Second) //10s sleep
				_, err := conn.Write(content)
				if err != nil {
					fmt.Println("重新打开广播")
					Open(localPort)
				}
			}
			fmt.Println("广播退出")
		}()

	}
}

func Close() {
	conn.Close()
}

package broadcast

import (
	"NXProductionTest/common"
	"encoding/json"
	"fmt"
	"net"
	"time"
)

var conn *net.UDPConn
var localPort int
var Content []byte

func Open(port int) error {
	localPort = port
	var err error
	conn, err = net.DialUDP("udp", nil, &net.UDPAddr{
		IP:   net.IPv4(255, 255, 255, 255),
		Port: port,
	})
	return err
}

func GetContent() {
	//获取ip
	localNet, err := common.GetLocalNet()
	if err != nil {
		fmt.Println(err)
		fmt.Println("can get local net info broadcast,broadcast \"hello\"")
		Content = []byte("hello")
	} else {
		str, err1 := json.Marshal(localNet)
		if err1 != nil {
			fmt.Println(err1)
			Content = []byte("hello")
		} else {
			Content = str
		}
	}
}

func BroadCast() {
	if conn != nil {
		go func() {
			for true {
				time.Sleep(time.Duration(10) * time.Second) //10s sleep
				_, err := conn.Write(Content)
				if err != nil {
					fmt.Println("重新打开广播")
					Open(localPort)
					GetContent()
				}
			}
			fmt.Println("广播退出")
		}()

	}
}

func Close() {
	conn.Close()
}

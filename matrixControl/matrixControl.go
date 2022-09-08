package matrixControl

import (
	"fmt"
	"github.com/thinkeridea/go-extend/exnet"
	"net"
	"strconv"
)

var MClientMatrixControl ClientMatrixControl

type ClientMatrixControl struct {
	Ip   string //服务端ip
	Port int    //服务器端口
	conn net.Conn
	Run  bool
	//心跳帧内容
	HeartInfo    Heart
	ReceiveHeart bool
}

func (c *ClientMatrixControl) GetMatrixIp() {

	//打开udp连接
	net.InterfaceAddrs()
	laddr := net.UDPAddr{
		IP:   net.IPv4(0, 0, 0, 0), //写局域网下分配IP，0.0.0.0可以用来测试
		Port: 876,                  //矩阵控制器的udp端口
	}
	connMatrix, err := net.ListenUDP("udp", &laddr)
	if err != nil {
		c.Ip = ""
		return
	}
	defer connMatrix.Close()

	fmt.Println("matrix control udp connect")
	buf := make([]byte, 4096)
	n, err2 := connMatrix.Read(buf)
	if err2 != nil {
		c.Ip = ""
	} else {
		fmt.Println("matrix control receive:", buf[:n])
		//将接收的信息反译
		rspGetNet := Rsp_GetNetSn{}
		rspGetNet.Unpack(buf[0:n])
		c.Ip, err = exnet.Long2IPString(uint(rspGetNet.Ip))
		if err != nil {
			c.Ip = ""
		}
		c.Port = 5000
	}
}

func (c *ClientMatrixControl) Open() error {
	server := c.Ip + ":" + strconv.Itoa(c.Port)
	tcpAddr, err := net.ResolveTCPAddr("tcp", server)
	if err != nil {
		return err
	}
	c.conn, err = net.DialTCP("tcp", nil, tcpAddr)
	if err == nil {
		c.Run = true
	}
	fmt.Println("matrix control tcp open")
	return err
}

func (c *ClientMatrixControl) Close() {
	c.conn.Close()
	c.Run = false
}

func (c *ClientMatrixControl) ThreadGetReceive() {
	go func() {
		fmt.Println("matrixControl receive thread")
		for c.Run {
			content := make([]byte, 4096)
			n, err := c.conn.Read(content)
			if err != nil {
				fmt.Println("matrix sock receive err:", err)
			}
			fmt.Println("matrix control receive:", content[:n])
			if content[0] == 0x88 && content[1] == 0xa0 {
				c.HeartInfo.Unpack(content[3 : n-1]) //剔除头和尾
				fmt.Println(c.HeartInfo)
				c.ReceiveHeart = true
			}
		}
	}()
}

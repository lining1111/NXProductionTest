package matrixControl

import (
	"bufio"
	"fmt"
	"github.com/thinkeridea/go-extend/exnet"
	"net"
	"strconv"
)

type ClientMatrixControl struct {
	Ip   string //服务端ip
	Port int    //服务器端口
	conn net.Conn
	Run  bool
}

func (c *ClientMatrixControl) GetMatrixIp() {
	connMatrix, err := net.ListenUDP("udp", &net.UDPAddr{
		IP:   net.IPv4(0, 0, 0, 0),
		Port: 876, //矩阵控制器的udp端口
	})
	if err != nil {
		c.Ip = ""
	} else {
		reader := bufio.NewReader(connMatrix)
		buf := make([]byte, 1024)
		n, err1 := reader.Read(buf)
		if err1 != nil {
			c.Ip = ""
		} else {
			fmt.Println(string(buf))
			//将接收的信息反译
			rspGetNet := Rsp_GetNetSn{}
			rspGetNet.Unpack(buf[0:n])
			c.Ip, err = exnet.Long2IPString(uint(rspGetNet.Ip))
			if err != nil {
				c.Ip = ""
			}
		}
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

	return err
}

func (c *ClientMatrixControl) Close() {
	c.conn.Close()
	c.Run = false
}

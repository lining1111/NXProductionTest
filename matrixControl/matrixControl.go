package matrixControl

import (
	"net"
	"strconv"
)

type ClientMatrixControl struct {
	Ip   string //服务端ip
	Port int    //服务器端口
	conn net.Conn
	Run  bool
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

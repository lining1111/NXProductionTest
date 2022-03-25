package server

import (
	"fmt"
	"net"
	"strconv"
)

type Server struct {
	localClients map[net.Conn]LocalClient //客户端数组
	Port         int16                    //服务端端口
}

func (s *Server) AddClient(c LocalClient) {
	s.localClients[c.conn] = c
}

func (s *Server) RemoveClient(c LocalClient) {
	_, v := s.localClients[c.conn]
	if v {
		delete(s.localClients, c.conn)
	}
}

func (s *Server) handlerClient(c LocalClient) {
	clientAddr := c.conn.RemoteAddr().String()
	fmt.Printf("client:%s connect\n", clientAddr)
	c.Process()
}

func (s *Server) Run(port int16) error {
	addr := ":" + strconv.Itoa(int(port))
	tcpAddr, err := net.ResolveTCPAddr("tcp", addr)
	if err != nil {
		fmt.Println("tcp server get addr err:", err.Error())
		return err
	}
	listener, errListen := net.ListenTCP("tcp", tcpAddr)
	defer listener.Close()
	if errListen != nil {
		fmt.Println("tcp server listen err:", err.Error())
		return err
	}

	fmt.Println("server start success at port:", port)
	s.localClients = make(map[net.Conn]LocalClient)
	for {
		conn, errAccept := listener.Accept()
		if errAccept != nil {
			continue
		}
		c := LocalClient{}
		c.New(conn, tmpSize, rbSize)
		s.AddClient(c)
		go s.handlerClient(c)

		for _, localClient := range s.localClients {
			if !localClient.run {
				fmt.Println("关闭客户端", localClient.conn.RemoteAddr().String())
				localClient.Close()
				s.RemoveClient(localClient)
			}
		}
	}

	return nil
}

package server

import (
	"NXProductionTest/matrixControl"
	"fmt"
	"net"
	"strconv"
	"time"
)

type Server struct {
	localClients map[net.Conn]*LocalClient //客户端数组
	Port         int16                     //服务端端口
	run          bool
	Listener     *net.TCPListener
	//连接矩阵控制器的客户端
	matrixClient matrixControl.ClientMatrixControl
}

func (s *Server) AddClient(c *LocalClient) {
	s.localClients[c.conn] = c
}

func (s *Server) RemoveClient(c *LocalClient) {
	_, v := s.localClients[c.conn]
	if v {
		delete(s.localClients, c.conn)
	}
}

func (s *Server) handlerClient(c *LocalClient) {
	clientAddr := c.conn.RemoteAddr().String()
	fmt.Printf("client:%s connect\n", clientAddr)
	c.Process()
}

func (s *Server) OpenMatrixClient() {
	s.matrixClient.Open()
}

func (s *Server) CloseMatrixClient() {
	s.matrixClient.Close()
}

func (s *Server) Run(port int16) error {
	addr := ":" + strconv.Itoa(int(port))
	tcpAddr, err := net.ResolveTCPAddr("tcp", addr)
	if err != nil {
		fmt.Println("tcp server get addr err:", err.Error())
		return err
	}
	var errListen error
	s.Listener, errListen = net.ListenTCP("tcp", tcpAddr)
	if errListen != nil {
		fmt.Println("tcp server listen err:", err.Error())
		return err
	}

	fmt.Println("server start success at port:", port)
	s.run = true
	s.localClients = make(map[net.Conn]*LocalClient)
	//TODO 先获取控制板ip信息，后期需要通信的时候，再通过短连接通信
	go func() {
		fmt.Println("开始搜索矩阵控制器")
		s.matrixClient.Ip = ""
		s.matrixClient.GetMatrixIp()
		if s.matrixClient.Ip != "" {
			//s.OpenMatrixClient()
			fmt.Println("获取矩阵控制器ip成功")
		} else {
			fmt.Println("获取矩阵控制器ip失败")
		}
	}()
	go s.Monitor()
	for {
		conn, errAccept := s.Listener.Accept()
		if errAccept != nil {
			continue
		}
		c := new(LocalClient)
		c.New(s, conn, tmpSize, rbSize)
		s.AddClient(c)
		go s.handlerClient(c)
	}

	return nil
}

func (s *Server) Monitor() {
	for s.run {
		time.Sleep(time.Duration(10) * time.Millisecond)
		for _, localClient := range s.localClients {
			if !localClient.run {
				fmt.Println("关闭客户端", localClient.conn.RemoteAddr().String())
				localClient.Close()
				s.RemoveClient(localClient)
			}
		}
	}
}

func (s *Server) Close() {
	s.Listener.Close()
	s.matrixClient.Close()
	s.localClients = nil

}

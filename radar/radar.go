package radar

import (
	"errors"
	"fmt"
	"io/ioutil"
	"net"
	"strings"
	"time"
)

const MaxBufSize = 4096

type Info struct {
	Ip   string
	Port string
}

var Client *net.TCPConn
var LocalInfo = Info{
	"",
	"",
}

// udp port 20050
func GetContentFromUDP(port int) (string, error) {

	//打开udp连接
	net.InterfaceAddrs()
	laddr := net.UDPAddr{
		IP:   net.IPv4(0, 0, 0, 0), //写局域网下分配IP，0.0.0.0可以用来测试
		Port: port,
	}
	conn, err := net.ListenUDP("udp", &laddr)
	if err != nil {
		return "", err
	}
	defer conn.Close()

	fmt.Println("radar udp connect")
	buf := make([]byte, 4096)
	n, err2 := conn.Read(buf)
	if err2 != nil {
		return "", err2
	}
	//fmt.Println(string(buf[:n]))

	return string(buf[:n]), nil
}

/*
广播示例
Radar ip:192:168:61:21  port:5000     ---雷达IP和端口号
subnet mask:255:255:255:0 			  ---雷达子网掩码
subnet mask:255:255:255:0             ---雷达网关
mac:162:52:0:28:0:54                  ---雷达MAC地址
connect Num :1                        ---当前雷达客户端连接数
connect ip: 192:168:61:67             ---连接该雷达的客户端IP地址
status：encrypted	                  ---雷达为鉴权加密版，非加密版不显示该信息
time now: 2020/5/7 15:7:2.49          ---雷达时间戳
ntp time: 2020/5/7 15:6:50.130        ---最近一次发生NTP校时的时间戳
*/
func GetInfoFromContent(content string) Info {
	var info = Info{}
	info.Ip = ""

	//先以换行\n分开字符串
	contentSplit := strings.Split(content, "\n")
	//寻找含有ip、port的字符串
	for i := 0; i < len(contentSplit); i++ {
		findIp := false
		findPort := false
		//以空格分割
		contentSplit1 := strings.Split(contentSplit[i], " ")
		for j := 0; j < len(contentSplit1); j++ {
			ipIndex := strings.Index(contentSplit1[j], "ip")
			portIndex := strings.Index(contentSplit1[j], "port")
			if ipIndex != -1 {
				info.Ip = contentSplit1[j][ipIndex+3:]
				newIP := strings.ReplaceAll(info.Ip, ":", ".")
				info.Ip = newIP
				fmt.Println("find ip:", info.Ip)
				findIp = true
			}
			if portIndex != -1 {
				info.Port = contentSplit1[j][portIndex+5:]
				fmt.Println("find port:", info.Port)
				findPort = true
			}
			if findIp && findPort {
				fmt.Println("find radar ip port")
				break
			}
		}
		if findIp && findPort {
			fmt.Println("find radar ip port")
			break
		}
	}

	return info
}

func ThreadGetNetInfoFromUDP() {
	go func() {
		fmt.Println("radar udp receive thread")
		for true {
			time.Sleep(time.Duration(10) * time.Second) //10s sleep
			content, err := GetContentFromUDP(20050)
			if err == nil {
				info := GetInfoFromContent(content)
				if info.Ip != "" {
					LocalInfo.Ip = info.Ip
					LocalInfo.Port = info.Port
				}
			}
		}
	}()
}

func TestUDP() {
	//content, err := radar.GetContentFromUDP(3000)
	//if err != nil {
	//	fmt.Println(err)
	//	return
	//}
	//fmt.Println(content)

	//content := "Radar ip:192:168:61:21 port:5000\n"+
	//			"subnet mask:255:255:255:0\n"+
	//			"gate way:192:168:6:1"
	//			"mac:162:52:0:28:0:54\n"+
	//			"connect Num:1\n"+
	//			"connect ip: 192:168:61:67\n" +
	//			"status：encrypted\n" +
	//			"time now: 2020/5/7 15:7:2.49\n" +
	//			"ntp time: 2020/5/7 15:6:50.130"
	//
	//info :=radar.GetInfoFromContent(content)
	//fmt.Println(info)
}

func Open(info Info) error {
	server := info.Ip + ":" + info.Port
	fmt.Println("server:", server)
	tcpAddr, err := net.ResolveTCPAddr("tcp", server)
	if err != nil {
		return err
	}
	conn, err1 := net.DialTCP("tcp", nil, tcpAddr)
	if err1 != nil {
		return err1
	}
	fmt.Println("radar tcp open")
	Client = conn
	return nil
}

func Close() {
	Client.Close()
}

func SetMode3() error {
	if Client != nil {
		send := []byte{'C', 'A', 'P', 'M', 0, 0, 0, 4, 0, 200, 0, 3}

		fmt.Println("send:", send)
		_, err := Client.Write(send)
		if err != nil {
			return err
		}
		var receive [1024]byte
		n, err1 := Client.Read(receive[0:])
		if err1 != nil {
			return err1
		}
		fmt.Println(receive[:n])
		result := string(receive[:4])
		fmt.Println(result)
		if result != "DONE" {
			return errors.New("回复错误")
		}
		return nil
	} else {
		return errors.New("未打开链接")
	}
}

func Connect() error {
	if Client != nil {
		send := []byte{'I', 'N', 'I', 'T'}
		fmt.Println("send:", send)
		_, err := Client.Write(send)
		if err != nil {
			return err
		}
		var receive [1024]byte
		n, err1 := Client.Read(receive[0:])
		if err1 != nil {
			return err1
		}
		fmt.Println(receive[:n])
		result := string(receive[:4])
		fmt.Println(result)
		if result != "DONE" {
			return errors.New("回复错误")
		}
		return nil
	} else {
		return errors.New("未打开链接")
	}
}

func Disconnect() error {
	if Client != nil {
		send := []byte{'G', 'B', 'Y', 'E'}
		_, err := Client.Write(send)
		if err != nil {
			return err
		}
		receive, err1 := ioutil.ReadAll(Client)
		if err1 != nil {
			return err1
		}
		result := string(receive[:3])
		if result != "GBYE" {
			return errors.New("回复错误")
		}
		return nil
	} else {
		return errors.New("未打开链接")
	}
}

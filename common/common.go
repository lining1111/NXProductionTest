package common

import (
	"NXProductionTest/fileType"
	"archive/zip"
	"bufio"
	"bytes"
	"encoding/base64"
	"errors"
	"fmt"
	"io"
	"os"
	"os/exec"
	"strings"
)

/**
 * 整体通信大帧结构
 *  1byte   1byte   1byte       2bytes  4bytes  4bytes  N bytes      2bytes
 *  帧头      版本  命令标识符       帧号  设备编号    帧长  json格式正文    校验码
 */
var (
	Cmd1 = 1
	Cmd2 = 2
)

const HeadLen = 13
const CRCLen = 2

type Head struct {
	Tag      uint8  //固定的头开始 ‘$’ 0x24
	Version  uint8  //版本号 1.0 hex
	Cmd      uint8  //命令字类型 详见CmdType
	Sn       uint16 //帧号
	DeviceNO uint32 //设备编号
	Len      uint32 //整包长度，从包头到最后的校验位 <帧头>sizeof(PkgHead)+<正文>(json)+<校验>sizeof(PkgCRC)
}

type Crc struct {
	Data uint16 //校验值，从帧头开始到正文的最后一个字节
}

//帧体为json格式

type Eth struct {
	Type    string `json:"type"`
	Ip      string `json:"ip"`
	Mask    string `json:"mask"`
	GateWay string `json:"gateWay"`
}

type Eoc struct {
	Ip   string `json:"ip"`
	Port string `json:"port"`
}

type Net struct {
	Eth0     Eth    `json:"eth0"`
	Eth1     Eth    `json:"eth1"`
	MainDNS  string `json:"mainDNS"`
	SlaveDNS string `json:"slaveDNS"`
	Eoc      Eoc    `json:"eoc"`
	City     string `json:"city"`
}

type NTP struct {
	Ip   string `json:"ip"`
	Port string `json:"port"`
}

// ModifyLocalNet 修改net
func ModifyLocalNet(net Net) error {
	//1.获取参数
	eth0_type := net.Eth0.Type
	eth0_ip := net.Eth0.Ip
	eth0_mask := net.Eth0.Mask
	eth0_gateWay := net.Eth0.GateWay

	eth1_type := net.Eth1.Type
	eth1_ip := net.Eth1.Ip
	eth1_mask := net.Eth1.Mask
	eth1_gateWay := net.Eth1.GateWay

	mainDNS := net.MainDNS
	slaveDNS := net.SlaveDNS

	eocCloudIp := net.Eoc.Ip
	eocCloudPort := net.Eoc.Port

	city := net.City

	//1.执行shell指令
	shell := "/home/nvidianx/bin/set_nx_net_info " +
		eth0_type + " " + eth0_ip + " " + eth0_mask + " " + " " + eth0_gateWay + " " +
		eth1_type + " " + eth1_ip + " " + eth1_mask + " " + " " + eth1_gateWay + " " +
		mainDNS + " " + slaveDNS + " " + eocCloudIp + " " + eocCloudPort + " " + city
	cmd := exec.Command("/bin/bash", "-c", shell)
	err := cmd.Run()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		return err
	}

	return nil
}

// GetLocalNet 返回net
func GetLocalNet() (Net, error) {
	var net Net

	//1.执行shell指令
	shell := "/home/nvidianx/bin/get_nx_net_info"
	cmd := exec.Command("/bin/bash", "-c", shell)
	result, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		return Net{}, err
	}
	/*
		"* get_double_net_info $ip_type $curip $curmask $curgateway $eth1_ip_type $eth1_curip $eth1_curmask $eth1_curgateway $curmaindns $curslavedns $curcloudip $curcloudport $curdevicenum $cur_city $cur_mac $protocol_version *"
	*/
	//2.从结果中获取配置
	//从结果中获取含有get_double_net_info的那一行 按空格分开为 ip_type curip curmask curgateway eth1_ip_type eth1_curip eth1_curmask eth1_curgateway curmaindns curslavedns curcloudip curcloudport curdevicenum cur_city cur_mac protocol_version
	rd := bufio.NewReader(bytes.NewReader(result))
	var contents []string
	isFind := false
	for !isFind {
		line, _, err1 := rd.ReadLine()
		if err1 == io.EOF {
			isFind = false
			break
		}
		str := string(line)
		if strings.Index(str, "get_double_net_info") >= 0 {
			copy(contents, strings.Split(str, " "))
			isFind = true
			break
		}
	}
	if isFind {
		if len(contents) >= 17 {
			net.Eth0.Type = contents[1]
			net.Eth0.Ip = contents[2]
			net.Eth0.Mask = contents[3]
			net.Eth0.GateWay = contents[4]

			net.Eth1.Type = contents[5]
			net.Eth1.Ip = contents[6]
			net.Eth1.Mask = contents[7]
			net.Eth1.GateWay = contents[8]

			net.MainDNS = contents[9]
			net.SlaveDNS = contents[10]

			net.Eoc.Ip = contents[11]
			net.Eoc.Port = contents[12]

			//deviceNum contents[13]
			net.City = contents[14]
			//curMac contents[15]
			//protocol_version contents[16]
		}
	}

	return net, nil
}

// SetNtp 设置ntp配置
func SetNtp(ntp NTP) error {

	//2.2获取NTP服务器的ip port
	ip := ntp.Ip
	port := ntp.Port

	//2.3设置NTP服务器
	shell := "/home/nvidianx/bin/set_ntp_info " + ip + " " + port
	cmd := exec.Command("/bin/bash", "-c", shell)
	err := cmd.Run()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		return err
	}

	return nil
}

// GetNtp 返回ntp配置
func GetNtp() (NTP, error) {
	var ntp NTP

	//1.执行shell指令
	shell := "/home/nvidianx/bin/get_ntp_info"
	cmd := exec.Command("/bin/bash", "-c", shell)
	result, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		return NTP{}, err
	}
	/*
		"* get_ntp_info $ntpServer 123  *"
	*/
	//2.从结果中获取配置
	//从结果中获取含有get_ntp_info的那一行 按空格分开为 ntpIP ntpPort
	rd := bufio.NewReader(bytes.NewReader(result))
	var contents []string
	isFind := false
	for !isFind {
		line, _, err1 := rd.ReadLine()
		if err1 == io.EOF {
			isFind = false
			break
		}
		str := string(line)
		if strings.Index(str, "get_ntp_info") >= 0 {
			copy(contents, strings.Split(str, " "))
			isFind = true
			break
		}
	}
	if isFind {
		if len(contents) >= 3 {
			ntp.Ip = contents[1]
			ntp.Port = contents[2]
		}
	}

	return ntp, nil
}

// UpDate 固件升级
func UpDate(name string, file []byte) error {
	//1.base64解码
	var content []byte
	_, errDecode := base64.StdEncoding.Decode(content, file)
	if errDecode != nil {
		return errDecode
	}
	//2.检查文件类型 .zip解压并存入update路径
	buffer := content[0:10]
	contentType := fileType.GetFileType(buffer)

	var UpdateFilePath = "./update/" + name[0:strings.IndexByte(name, '.')] + "/"
	_, errStat := os.Stat(UpdateFilePath)
	if errStat != nil {
		if os.IsNotExist(errStat) {
			os.MkdirAll(UpdateFilePath, 0777)
		}
	}

	switch contentType {
	case "zip":
		{
			//解压出zip
			r, err := zip.OpenReader(name)
			if err != nil {
				fmt.Println(err)
				return err
			}

			for _, k := range r.Reader.File {
				//是目录的话创建目录
				if k.FileInfo().IsDir() {
					err = os.MkdirAll(UpdateFilePath+k.Name, 0644)
					if err != nil {
						fmt.Println(err)
					}
					continue
				}
				//是文件的话存储文件
				r1, err1 := k.Open()
				if err1 != nil {
					fmt.Println(err1)
					continue
				}
				fmt.Println("unzip:", k.Name)
				defer r1.Close()
				NewFile, err2 := os.Create(UpdateFilePath + k.Name)
				if err2 != nil {
					fmt.Println(err2)
					continue
				}
				io.Copy(NewFile, r1)
				NewFile.Sync()
				NewFile.Close()
			}
			fmt.Println("unzip all")
		}
	default:
		return errors.New("unsupported file type")
	}

	return nil
}

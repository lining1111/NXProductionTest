package server

import (
	"NXProductionTest/fileType"
	"archive/zip"
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

type NTP struct {
	Ip   string `json:"ip"`
	Port string `json:"port"`
}

// ModifyLocalNet ModifyLocalIp 修改ip
func ModifyLocalNet(eth Eth) error {
	//eth0_type := eth.Type
	//eth0_ip := eth.Ip
	//eth0_mask := eth.Mask
	//eth0_gateWay := eth.GateWay

	return nil
}

// GetIp 返回ip
func GetLocalNet() Eth {
	var eth Eth

	return eth
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
func GetNtp() NTP {
	var ntp NTP

	return ntp
}

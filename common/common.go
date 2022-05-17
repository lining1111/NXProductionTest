package common

import (
	"NXProductionTest/db"
	"bufio"
	"bytes"
	"fmt"
	"io"
	"os/exec"
	"strconv"
	"strings"
)

//帧体为json格式

type Eth struct {
	Type    string `json:"type"`
	Ip      string `json:"ip"`
	Mask    string `json:"mask"`
	GateWay string `json:"gateWay"`
}

type Eoc struct {
	Ip   string `json:"ip"`
	Port int    `json:"port"`
}

// NX_SetNet NX_GetNet
type Net struct {
	Eth0     Eth    `json:"eth0"`
	Eth1     Eth    `json:"eth1"`
	MainDNS  string `json:"mainDNS"`
	SlaveDNS string `json:"slaveDNS"`
	Eoc      Eoc    `json:"eoc"`
	City     string `json:"city"`

	Mac string `json:"mac,omitempty"`
}

// NX_SetNtp NX_GetNtp
type NTP struct {
	Ip   string `json:"ip"`
	Port int    `json:"port"`
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
	contents := make([]string, 20)
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
		if len(contents) >= 18 {
			net.Eth0.Type = contents[2]
			net.Eth0.Ip = contents[3]
			net.Eth0.Mask = contents[4]
			net.Eth0.GateWay = contents[5]

			net.Eth1.Type = contents[6]
			net.Eth1.Ip = contents[7]
			net.Eth1.Mask = contents[8]
			net.Eth1.GateWay = contents[9]

			net.MainDNS = contents[10]
			net.SlaveDNS = contents[11]

			net.Eoc.Ip = contents[12]
			net.Eoc.Port, _ = strconv.Atoi(contents[13])

			//deviceNum contents[14]
			net.City = contents[15]
			//curMac contents[16]
			net.Mac = contents[16]
			//protocol_version contents[17]
		}
	}

	return net, nil
}

type DeviceSN struct {
	Sn       string `json:"sn"`       //串号32位
	SerialNO string `json:"serialNO"` //序列号10位
}

func GetDeviceSN(dbPath string) (DeviceSN, error) {
	ret := DeviceSN{
		Sn:       "",
		SerialNO: "",
	}
	if !db.IsOpen {
		db.Open(dbPath)
	}
	result, err := db.GetUNameFromTable_CL_ParkingArea()
	result1, err1 := db.GetSnFromTable_CL_Config()
	if err != nil || err1 != nil {
		ret.Sn = ""
		ret.SerialNO = ""
	} else {
		ret.Sn = result
		ret.SerialNO = result1
	}
	return ret, err
}

func SetDeviceSN(dbPath string, deviceSN DeviceSN) error {
	if !db.IsOpen {
		db.Open(dbPath)
	}
	set := db.CL_ParkingArea{}
	set.UName = deviceSN.Sn
	set1 := db.CL_Config{}
	set1.Sn = deviceSN.SerialNO
	err := db.SetUNameInTable_CL_ParkingArea(&set)
	if err != nil {
		return err
	}
	return db.SetSnInTable_CL_Config(&set1)
}

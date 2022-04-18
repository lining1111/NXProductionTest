package common

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"os/exec"
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
	Port string `json:"port"`
}

// NX_SetNet NX_GetNet
type Net struct {
	Eth0     Eth    `json:"eth0"`
	Eth1     Eth    `json:"eth1"`
	MainDNS  string `json:"mainDNS"`
	SlaveDNS string `json:"slaveDNS"`
	Eoc      Eoc    `json:"eoc"`
	City     string `json:"city"`
}

// NX_SetNtp NX_GetNtp
type NTP struct {
	Ip   string `json:"ip"`
	Port string `json:"port"`
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
	contents := make([]string, 17)
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

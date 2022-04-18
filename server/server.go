package server

import (
	"NXProductionTest/common"
	"NXProductionTest/matrixControl"
	"archive/zip"
	"bufio"
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"os"
	"os/exec"
	"runtime"
	"strconv"
	"strings"
)

//连接矩阵控制器的客户端
var matrixClient matrixControl.ClientMatrixControl

var UpdateFilePath = "./update"

func OpenMatrixClient() {
	matrixClient.Open()
}

func CloseMatrixClient() {
	matrixClient.Close()
}

func Run(port int) {

	//TODO 先获取控制板ip信息，后期需要通信的时候，再通过短连接通信
	go func() {
		fmt.Println("开始搜索矩阵控制器")
		matrixClient.Ip = ""
		matrixClient.GetMatrixIp()
		if matrixClient.Ip != "" {
			//s.OpenMatrixClient()
			fmt.Println("获取矩阵控制器ip成功")
		} else {
			fmt.Println("获取矩阵控制器ip失败")
		}
	}()

	//NX_SetNet
	http.HandleFunc("/NX_SetNet", NXSetNet)
	//NX_GetNet
	http.HandleFunc("/NX_GetNet", NXGetNet)

	//NX_SetNtp
	http.HandleFunc("/NX_SetNtp", NXSetNtp)
	//NX_GetNtp
	http.HandleFunc("/NX_GetNtp", NXGetNtp)

	//Update
	http.HandleFunc("/NXUpdate", NXUpdate)

	addr := ":" + strconv.Itoa(port)
	err := http.ListenAndServe(addr, nil)
	if err != nil {
		fmt.Println(err)
	}
}

func NXUpdate(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()
	//1.获取上传的文件 uploadFile
	r.ParseForm()
	file, handle, err := r.FormFile("updateFile")
	if err != nil {
		w.WriteHeader(http.StatusGone)
		w.Write([]byte(err.Error()))
		return
	}

	//2.检查文件后缀
	buffer := make([]byte, 512)
	_, errRead := file.Read(buffer)
	if errRead != nil {
		w.WriteHeader(http.StatusGone)
		w.Write([]byte(errRead.Error()))
		file.Close()
		return
	}

	contentType := http.DetectContentType(buffer)

	if contentType != "application/zip" {
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("只支持 zip 压缩格式"))
		file.Close()
		return
	}
	//3.保存文件
	//3.1查看保存路径是否存在，不存在就创建
	_, errStat := os.Stat(UpdateFilePath)
	if errStat != nil {
		if os.IsNotExist(errStat) {
			os.Mkdir(UpdateFilePath, 0777)
		}
	}
	//3.2保存
	saveFile, errSave := os.OpenFile(UpdateFilePath+"/"+handle.Filename, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0666)
	if errSave != nil {
		fmt.Println("打开文件失败")
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("打开文件失败"))
		file.Close()
		return
	}
	//因为第2步的时候有读取动作，所以要设置读指针0
	file.Seek(0, io.SeekStart)
	io.Copy(saveFile, file)
	saveFile.Sync()
	saveFile.Close()
	file.Close()
	w.WriteHeader(http.StatusOK)
	w.Write([]byte("上传成功"))
	//4.解压文件
	//解压出zip
	read, err1 := zip.OpenReader(saveFile.Name())
	if err1 != nil {
		fmt.Println(err1)
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：打开zip文件失败"))
		return
	}

	for _, k := range read.Reader.File {
		//是目录的话创建目录
		if k.FileInfo().IsDir() {
			err = os.MkdirAll(UpdateFilePath+k.Name, 0644)
			if err != nil {
				fmt.Println(err)
			}
			continue
		}
		//是文件的话存储文件
		read1, err2 := k.Open()
		if err2 != nil {
			fmt.Println(err2)
			continue
		}
		fmt.Println("unzip:", k.Name)
		defer read1.Close()
		NewFile, err3 := os.Create(UpdateFilePath + "/" + k.Name)
		if err3 != nil {
			fmt.Println(err3)
			continue
		}
		io.Copy(NewFile, read1)
		NewFile.Sync()
		NewFile.Close()
	}
	fmt.Println("unzip all")

	//5.执行文件 update.sh
	shell := UpdateFilePath + "/" + "update.sh"
	//增加可执行属性
	cmd := exec.Command("chmod", "+x", shell)
	cmd.Run()
	cmd = exec.Command("/bin/bash", "-c", shell)
	output, errCmd := cmd.Output()
	if errCmd != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), errCmd.Error())
		return
	}
	fmt.Printf("Execute Shell:%s finished with output:\n%s", cmd.String(), string(output))
}

func NXGetNtp(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	var ntp common.NTP

	//1.执行shell指令
	shell := "/home/nvidianx/bin/get_ntp_info"
	cmd := exec.Command("/bin/bash", "-c", shell)
	result, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：执行命令失败"))
		return
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

	//3.json信息组织回复
	wBody, errBody := json.Marshal(ntp)
	if errBody != nil {
		fmt.Printf("json unmarshal err:%v\n", errBody.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
	}
	w.WriteHeader(http.StatusOK)
	w.Write(wBody)
}

func NXSetNtp(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//1.解析http请求
	rBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Printf("req body read err:%v\n", err.Error())
		return
	}
	fmt.Printf("body:%s\n", rBody)

	//2.将请求主体转换为json结构体
	var req common.NTP
	//2.1 读取
	err = json.Unmarshal(rBody, &req)
	if err != nil {
		fmt.Printf("json unmarshal err:%v\n", err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
		return
	}

	//2.2获取NTP服务器的ip port
	ip := req.Ip
	port := req.Port

	//2.3设置NTP服务器
	shell := "/home/nvidianx/bin/set_ntp_info " + ip + " " + port
	cmd := exec.Command("/bin/bash", "-c", shell)
	err = cmd.Run()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：设置NTP失败"))
		return
	}

	w.WriteHeader(http.StatusOK)
	w.Write([]byte("成功：设置NTP成功"))
}

func NXGetNet(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	var net common.Net

	//1.执行shell指令
	shell := "/home/nvidianx/bin/get_nx_net_info"
	cmd := exec.Command("/bin/bash", "-c", shell)
	result, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：执行命令失败"))
		return
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
	//4.json信息组织回复
	wBody, errBody := json.Marshal(net)
	if errBody != nil {
		fmt.Printf("json unmarshal err:%v\n", errBody.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
	}
	w.WriteHeader(http.StatusOK)
	w.Write(wBody)
}

func NXSetNet(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//1.解析http请求
	rBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Printf("req body read err:%v\n", err.Error())
		return
	}
	fmt.Printf("body:%s\n", rBody)

	//2.将请求主体转换为json结构体
	var req common.Net
	//2.1 读取
	err = json.Unmarshal(rBody, &req)
	if err != nil {
		fmt.Printf("json unmarshal err:%v\n", err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
		return
	}

	//2.2获取本地的ip port
	eth0_type := req.Eth0.Type
	eth0_ip := req.Eth0.Ip
	eth0_mask := req.Eth0.Mask
	eth0_gateWay := req.Eth0.GateWay

	eth1_type := req.Eth1.Type
	eth1_ip := req.Eth1.Ip
	eth1_mask := req.Eth1.Mask
	eth1_gateWay := req.Eth1.GateWay

	mainDNS := req.MainDNS
	slaveDNS := req.SlaveDNS

	eocCloudIp := req.Eoc.Ip
	eocCloudPort := req.Eoc.Port

	city := req.City

	//2.3设置网络
	shell := "/home/nvidianx/bin/set_nx_net_info " +
		eth0_type + " " + eth0_ip + " " + eth0_mask + " " + " " + eth0_gateWay + " " +
		eth1_type + " " + eth1_ip + " " + eth1_mask + " " + " " + eth1_gateWay + " " +
		mainDNS + " " + slaveDNS + " " + eocCloudIp + " " + eocCloudPort + " " + city
	cmd := exec.Command("/bin/bash", "-c", shell)
	err = cmd.Run()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：设置网络信息失败"))
		return
	}

	w.WriteHeader(http.StatusOK)
	w.Write([]byte("成功：设置网络信息成功"))
}

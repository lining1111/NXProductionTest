package server

import (
	"NXProductionTest/camera"
	"NXProductionTest/common"
	"NXProductionTest/matrixControl"
	"NXProductionTest/myLog"
	"NXProductionTest/radar"
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
var DbPath = "/home/nvidianx/bin/CLParking.db"

func OpenMatrixClient() {
	matrixClient.Open()
}

func CloseMatrixClient() {
	matrixClient.Close()
}

func Run(port int) {

	//TODO 先获取控制板ip信息，后期需要通信的时候，再通过短连接通信
	//go func() {
	//	fmt.Println("开始搜索矩阵控制器")
	//	matrixClient.Ip = ""
	//	matrixClient.GetMatrixIp()
	//	if matrixClient.Ip != "" {
	//		//s.OpenMatrixClient()
	//		fmt.Println("获取矩阵控制器ip成功")
	//	} else {
	//		fmt.Println("获取矩阵控制器ip失败")
	//	}
	//}()

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

	//GetDeviceSN
	http.HandleFunc("/GetDeviceSN", NXGetDeviceSN)
	//SetDeviceSN
	http.HandleFunc("/SetDeviceSN", NXSetDeviceSN)
	//GetDeviceInfo
	http.HandleFunc("/GetDeviceInfo", GetDeviceInfo)

	//静态文件服务器
	http.Handle("/", http.FileServer(http.Dir("./NPT")))
	//获取日志文件
	http.HandleFunc("/GetLog", GetLog)

	addr := ":" + strconv.Itoa(port)
	err := http.ListenAndServe(addr, nil)
	if err != nil {
		fmt.Println(err)
	}
}

func GetLog(w http.ResponseWriter, r *http.Request) {
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
	//2.获取 json中 file 属性，也就是文件的名称
	//type GetFile struct {
	//	File string `json:"file"`
	//}
	//fileInfo := GetFile{}
	//
	//err_json := json.Unmarshal(rBody, &fileInfo)
	//if err_json != nil {
	//	fmt.Println("json 解析错误:", err_json)
	//	return
	//}
	//3.下载文件
	file, _ := os.Open(myLog.LogPath)
	defer file.Close()

	fileStat, _ := file.Stat()

	w.WriteHeader(http.StatusOK)
	w.Header().Set("Content-Disposition", "attachment; filename="+file.Name())
	w.Header().Set("Content-Type", "text/plain")
	w.Header().Set("Content-Length", strconv.FormatInt(fileStat.Size(), 10))

	io.Copy(w, file)
}

func GetDeviceInfo(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//写入日志文件
	myLog.Logger.Println("接收获取设备信息命令")

	//1.解析http请求
	rBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Printf("req body read err:%v\n", err.Error())
		return
	}
	fmt.Printf("body:%s\n", rBody)

	//2.将请求主体转换为json结构体
	var getDeviceInfo common.GetDeviceInfo
	//2.1 读取
	err = json.Unmarshal(rBody, &getDeviceInfo)
	if err != nil {
		fmt.Printf("json unmarshal err:%v\n", err.Error())
		//写入日志文件
		myLog.Logger.Println("json unmarshal err:", err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))

		return
	}
	//3根据type值来进行不同的设备信息获取
	var value string
	switch getDeviceInfo.Type {
	case "TuoLuoYi": //陀螺仪芯片
		value = getGyroscopeState()
	case "Voltage": //电压
		value = getVoltage()
	case "TemWet": //温度，湿度
		value = getTemWet()
	case "Fan": //风扇
		value = getFan()
	case "HeatState": //加热状态
		value = getHeatState()
	case "SportAlarm": //运动告警
		value = getSportAlarm()
	case "AngleAlarm1": //角度告警1
		value = getAngleAlarm1()
	case "AngleAlarm2": //角度告警2
		value = getAngleAlarm2()
	case "AngleAlarm3": //角度告警3
		value = getAngleAlarm3()
	case "CameraFixedVersion": // 镜头模组固件版本
		value = getCameraFixedVersion()
	case "RadarConnection": //雷达通讯是否正常
		value = getRadarConnection()
	default:
		value = "unknown type"
	}
	var ret common.DeviceInfo
	ret.Type = getDeviceInfo.Type
	ret.Value = value

	//2.json信息组织回复
	wBody, errBody := json.Marshal(ret)
	if errBody != nil {
		fmt.Printf("json unmarshal err:%v\n", errBody.Error())
		//写入日志文件
		myLog.Logger.Println("json unmarshal err:", errBody.Error())

		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
	}
	w.WriteHeader(http.StatusOK)
	w.Write(wBody)

	//写入日志文件
	myLog.Logger.Printf("返回结果:%s\n", string(wBody))
}
func getGyroscopeState() string {
	retStr := ""
	if matrixControl.MClientMatrixControl.ReceiveHeart {
		detect := (matrixControl.MClientMatrixControl.HeartInfo.AlarmStatus & 0x0004) >> 2
		initiated := (matrixControl.MClientMatrixControl.HeartInfo.AlarmStatus & 0x0008) >> 3
		if detect == 1 {
			if initiated == 1 {
				retStr = "initiated"
			} else {
				retStr = "notInitiated"
			}
		} else {
			retStr = "notDetect"
		}
	} else {
		retStr = "notConnect"
	}

	return retStr

	//return "InitOK"
}
func getVoltage() string {
	retStr := ""
	if matrixControl.MClientMatrixControl.ReceiveHeart {
		voltage := matrixControl.MClientMatrixControl.HeartInfo.SwitchVoltage
		retStr = strconv.Itoa(int(voltage))
	} else {
		retStr = "notConnect"
	}

	return retStr

	//return "12V"
}
func getTemWet() string {
	retStr := ""
	if matrixControl.MClientMatrixControl.ReceiveHeart {
		temperature := matrixControl.MClientMatrixControl.HeartInfo.Temperature
		humidity := matrixControl.MClientMatrixControl.HeartInfo.Humidity
		retStr = strconv.Itoa(int(temperature))
		retStr += ","
		retStr += strconv.Itoa(int(humidity))
	} else {
		retStr = "notConnect"
	}
	return retStr

	//return "15,95"
}
func getFan() string {
	retStr := ""
	if matrixControl.MClientMatrixControl.ReceiveHeart {
		fan1State := (matrixControl.MClientMatrixControl.HeartInfo.AlarmStatus & 0x0200) >> 9
		fan2State := (matrixControl.MClientMatrixControl.HeartInfo.AlarmStatus & 0x0400) >> 10

		if fan1State == 1 {
			retStr = "ok"
		} else {
			retStr = "alarm"
		}
		retStr += ","

		if fan2State == 1 {
			retStr += "ok"
		} else {
			retStr += "alarm"
		}
	} else {
		retStr = "notConnect"
	}

	return retStr

	//return "on"
}
func getHeatState() string {
	retStr := ""
	if matrixControl.MClientMatrixControl.ReceiveHeart {
		heatState := (matrixControl.MClientMatrixControl.HeartInfo.AlarmStatus & 0x0010) >> 4

		if heatState == 1 {
			retStr = "heat"
		} else {
			retStr = "notHeat"
		}

	} else {
		retStr = "notConnect"
	}

	return retStr

	//return "on"
}

func getSportAlarm() string {
	retStr := ""
	if matrixControl.MClientMatrixControl.ReceiveHeart {
		sportAlarm := (matrixControl.MClientMatrixControl.HeartInfo.AlarmStatus & 0x0002) >> 1

		if sportAlarm == 1 {
			retStr = "alarm"
		} else {
			retStr = "notAlarm"
		}

	} else {
		retStr = "notConnect"
	}

	return retStr

	//return "on"
}
func getAngleAlarm1() string {
	retStr := ""
	if matrixControl.MClientMatrixControl.ReceiveHeart {
		angleAlarm1 := matrixControl.MClientMatrixControl.HeartInfo.AlarmStatus & 0x0001

		if angleAlarm1 == 1 {
			retStr = "alarm"
		} else {
			retStr = "notAlarm"
		}

	} else {
		retStr = "notConnect"
	}

	return retStr

}
func getAngleAlarm2() string {
	return "on"
}
func getAngleAlarm3() string {
	return "on"
}

func getCameraFixedVersion() string {
	retStr := ""
	infos, err := camera.GetDeviceInfo1()
	if err != nil {
		retStr = "notConnect"
	} else {
		bytes, err1 := json.Marshal(&infos)
		if err1 != nil {
			retStr = "jsonErr"
		} else {
			retStr = string(bytes)
		}
	}
	return retStr

	//return "0123456789"
}

func getRadarConnection() string {
	retStr := ""

	if radar.LocalInfo.Ip != "" {
		err1 := radar.Open(radar.LocalInfo)
		if err1 != nil {
			retStr = "notConnect"
		} else {
			radar.SetMode3()
			err2 := radar.Connect()
			if err2 != nil {
				retStr = "connectFail"
			} else {
				retStr = "connect"
			}
		}

	} else {
		retStr = "notConnect"
	}

	return retStr

	//return "ok"
}

func NXSetDeviceSN(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//写入日志文件
	myLog.Logger.Println("接收设置设备SN命令")
	//1.解析http请求
	rBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Printf("req body read err:%v\n", err.Error())
		return
	}
	fmt.Printf("body:%s\n", rBody)
	//写入日志文件
	myLog.Logger.Println("body:", rBody)

	//2.将请求主体转换为json结构体
	var deviceSN common.DeviceSN
	//2.1 读取
	err = json.Unmarshal(rBody, &deviceSN)
	if err != nil {
		fmt.Printf("json unmarshal err:%v\n", err.Error())
		//写入日志文件
		myLog.Logger.Println("json unmarshal err:", err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
		return
	}

	//3.写入数据库
	err = common.SetDeviceSN(DbPath, deviceSN)
	if err != nil {
		fmt.Printf("写入数据库失败:%v\n", err.Error())
		//写入日志文件
		myLog.Logger.Println("写入数据库失败:", err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：写入数据库失败"))
		return
	}
	w.WriteHeader(http.StatusOK)
	w.Write([]byte("成功：设置成功"))
	//写入日志文件
	myLog.Logger.Println("设置SN成功")
}

func NXGetDeviceSN(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//写入日志文件
	myLog.Logger.Println("接收获取设备SN命令")
	//1.数据库获取信息
	result, err := common.GetDeviceSN(DbPath)
	if err != nil {
		fmt.Printf("打开数据库失败:%v\n", err.Error())
		//写入日志文件
		myLog.Logger.Println("打开数据库失败:", err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：打开数据库失败"))
		return
	}
	//2.json信息组织回复
	wBody, errBody := json.Marshal(result)
	if errBody != nil {
		fmt.Printf("json unmarshal err:%v\n", errBody.Error())
		//写入日志文件
		myLog.Logger.Println("json unmarshal err:", errBody.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
	}
	w.WriteHeader(http.StatusOK)
	w.Write(wBody)

	//写入日志文件
	myLog.Logger.Printf("返回结果%s\n", string(wBody))
}

func NXUpdate(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//写入日志文件
	myLog.Logger.Println("接收更新命令")
	//1.获取上传的文件 uploadFile
	r.ParseForm()
	file, handle, err := r.FormFile("updateFile")
	if err != nil {
		w.WriteHeader(http.StatusGone)
		w.Write([]byte(err.Error()))
		//写入日志文件
		myLog.Logger.Println("返回错误结果:", err.Error())
		return
	}

	//2.检查文件后缀
	buffer := make([]byte, 512)
	_, errRead := file.Read(buffer)
	if errRead != nil {
		w.WriteHeader(http.StatusGone)
		w.Write([]byte(errRead.Error()))
		//写入日志文件
		myLog.Logger.Println("返回错误结果:", errRead.Error())
		file.Close()
		return
	}

	contentType := http.DetectContentType(buffer)

	if contentType != "application/zip" {
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("只支持 zip 压缩格式"))
		//写入日志文件
		myLog.Logger.Println("只支持 zip 压缩格式")
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
		//写入日志文件
		myLog.Logger.Println("打开文件失败")
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
	//写入日志文件
	myLog.Logger.Println("上传成功")
	//4.解压文件
	//解压出zip
	read, err1 := zip.OpenReader(saveFile.Name())
	if err1 != nil {
		fmt.Println(err1)
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：打开zip文件失败"))
		//写入日志文件
		myLog.Logger.Println("打开zip文件失败")
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

	//5.执行文件 install.sh
	shell := UpdateFilePath + "/" + "install.sh"
	//增加可执行属性
	cmd := exec.Command("chmod", "+x", shell)
	cmd.Run()
	cmd = exec.Command("/bin/bash", "-c", shell)
	output, errCmd := cmd.Output()
	if errCmd != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), errCmd.Error())
		//写入日志文件
		myLog.Logger.Printf("cmd %s exec fail:%v\n", cmd.String(), errCmd.Error())
		return
	}
	fmt.Printf("Execute Shell:%s finished with output:\n%s", cmd.String(), string(output))
	w.WriteHeader(http.StatusOK)
	w.Write([]byte("更新成功"))
	//写入日志文件
	myLog.Logger.Println("更新成功")
}

func NXGetNtp(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//写入日志文件
	myLog.Logger.Println("接收获取设备NTP信息命令")

	var ntp common.NTP

	//1.执行shell指令
	shell := "/home/nvidianx/bin/get_ntp_info"
	cmd := exec.Command("/bin/bash", "-c", shell)
	result, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		//写入日志文件
		myLog.Logger.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
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
	contents := make([]string, 4)
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
		if len(contents) >= 4 {
			ntp.Ip = contents[2]
			ntp.Port, _ = strconv.Atoi(contents[3])
		}
	}

	//3.json信息组织回复
	wBody, errBody := json.Marshal(ntp)
	if errBody != nil {
		fmt.Printf("json unmarshal err:%v\n", errBody.Error())
		//写入日志文件
		myLog.Logger.Printf("json unmarshal err:%v\n", errBody.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
	}
	w.WriteHeader(http.StatusOK)
	w.Write(wBody)

	//写入日志文件
	myLog.Logger.Printf("返回结果:%s\n", string(wBody))
}

func NXSetNtp(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//写入日志文件
	myLog.Logger.Println("接收设置设备NTP命令")

	//1.解析http请求
	rBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Printf("req body read err:%v\n", err.Error())
		//写入日志文件
		myLog.Logger.Printf("req body read err:%v\n", err.Error())
		return
	}
	fmt.Printf("body:%s\n", rBody)
	//写入日志文件
	myLog.Logger.Printf("body:%s\n", rBody)

	//2.将请求主体转换为json结构体
	var req common.NTP
	//2.1 读取
	err = json.Unmarshal(rBody, &req)
	if err != nil {
		fmt.Printf("json unmarshal err:%v\n", err.Error())
		//写入日志文件
		myLog.Logger.Printf("json unmarshal err:%v\n", err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
		return
	}

	//2.2获取NTP服务器的ip port
	ip := req.Ip
	port := req.Port

	//2.3设置NTP服务器
	shell := "/home/nvidianx/bin/set_ntp_info " + ip + " " + strconv.Itoa(port)
	cmd := exec.Command("/bin/bash", "-c", shell)
	err = cmd.Run()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		//写入日志文件
		myLog.Logger.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：设置NTP失败"))
		return
	}

	w.WriteHeader(http.StatusOK)
	w.Write([]byte("成功：设置NTP成功"))
	//写入日志文件
	myLog.Logger.Println("设置NTP成功")
}

func NXGetNet(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//写入日志文件
	myLog.Logger.Println("接收获取设备网络信息命令")
	var net common.Net

	//1.执行shell指令
	shell := "/home/nvidianx/bin/get_nx_net_info"
	cmd := exec.Command("/bin/bash", "-c", shell)
	result, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		//写入日志文件
		myLog.Logger.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
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
	//4.json信息组织回复
	wBody, errBody := json.Marshal(net)
	if errBody != nil {
		fmt.Printf("json unmarshal err:%v\n", errBody.Error())
		//写入日志文件
		myLog.Logger.Printf("json unmarshal err:%v\n", errBody.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：json解析失败"))
	}
	w.WriteHeader(http.StatusOK)
	w.Write(wBody)
	//写入日志文件
	myLog.Logger.Printf("返回结果:%s\n", string(wBody))
}

func NXSetNet(w http.ResponseWriter, r *http.Request) {
	defer func() {
		err := recover()
		switch err.(type) {
		case runtime.Error: //运行时错误
			fmt.Println("run time err:", err)
		}
	}()

	//写入日志文件
	myLog.Logger.Println("接收设置设备网络信息命令")
	//1.解析http请求
	rBody, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Printf("req body read err:%v\n", err.Error())
		//写入日志文件
		myLog.Logger.Printf("req body read err:%v\n", err.Error())
		return
	}
	fmt.Printf("body:%s\n", rBody)

	//2.将请求主体转换为json结构体
	var req common.Net
	//2.1 读取
	err = json.Unmarshal(rBody, &req)
	if err != nil {
		fmt.Printf("json unmarshal err:%v\n", err.Error())
		//写入日志文件
		myLog.Logger.Printf("json unmarshal err:%v\n", err.Error())
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
		mainDNS + " " + slaveDNS + " " + eocCloudIp + " " + strconv.Itoa(eocCloudPort) + " " + city
	fmt.Println(shell)
	cmd := exec.Command("/bin/bash", "-c", shell)
	err = cmd.Run()
	if err != nil {
		fmt.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		//写入日志文件
		myLog.Logger.Printf("cmd %s exec fail:%v\n", cmd.String(), err.Error())
		w.WriteHeader(http.StatusGone)
		w.Write([]byte("失败：设置网络信息失败"))
		return
	}

	w.WriteHeader(http.StatusOK)
	w.Write([]byte("成功：设置网络信息成功"))
	//写入日志文件
	myLog.Logger.Println("设置网络信息成功")
}

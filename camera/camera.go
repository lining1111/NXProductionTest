package camera

import (
	"NXProductionTest/cameralib"
	"encoding/json"
	"fmt"
	"os"
	"os/exec"
)

var Opened = false

type DeviceInfo struct {
	SoftVersion string `json:"softWareVersion,omitempty"`
	HardVersion string `json:"hardWareVersion,omitempty"`
	AiVersion   string `json:"aiVersion,omitempty"`
}

type DevicesInfo struct {
	DeviceInfo []DeviceInfo `json:"deviceInfo"`
}

func GetDeviceInfo() (DevicesInfo, error) {
	devicesInfo := DevicesInfo{}

	//执行程序获取执行结果
	cmd := exec.Command("./cameraCommon", "1")
	err := cmd.Run()
	if err != nil {
		return devicesInfo, err
	}
	//读取执行结果，结果存入到camera.out文件
	content, err1 := os.ReadFile("./camera.out")
	if err1 != nil {
		return devicesInfo, err1
	}
	//content是一个json串
	err2 := json.Unmarshal(content, devicesInfo)
	if err2 != nil {
		return devicesInfo, err2
	}
	return devicesInfo, nil
}

//use c lib
func GetDeviceInfo1() (DevicesInfo, error) {
	devicesInfo := DevicesInfo{}

	if !Opened {
		ret := cameralib.Open()
		if ret == 0 {
			Opened = true
		}
	}
	cameralib.GetDeviceInfo()
	result := cameralib.FormatDeviceInfo(cameralib.GetVector_DeviceConfig())
	fmt.Println(result)
	//content是一个json串
	err2 := json.Unmarshal([]byte(result), &devicesInfo)
	if err2 != nil {
		fmt.Println(err2)
		return devicesInfo, err2
	}

	return devicesInfo, nil
}

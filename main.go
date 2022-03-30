package main

import (
	"NXProductionTest/broadcast"
	"NXProductionTest/common"
	"NXProductionTest/matrixControl"
	"NXProductionTest/server"
	"encoding/json"
	"fmt"
	"sync"
)

func main() {

	////unpack head
	//buf := []byte{0x88, byte(matrixCommon.Req_GetNet), 4}
	//head := matrixControl.Head{}
	//err := head.Unpack(buf)
	//if err == nil {
	//	fmt.Printf("%02x,%02x,%02x", head.Start, head.Cmd, head.Len)
	//}

	//Req_SetSn 实验结构体内含有数组
	sn := []byte{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f}
	setSn := matrixControl.Req_SetSn{}
	setSn.Unpack(sn)
	//buf := make([]byte, 512)
	buf, _ := setSn.Pack()
	fmt.Println(buf)

	//Req_UpdateData 实验 c端是std::vector
	data := []byte{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f}

	updateData := matrixControl.Req_UpdateData{}
	updateData.Unpack(data)
	buf1, _ := updateData.Pack()
	fmt.Println(buf1)

	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		defer wg.Done()
		var s = server.Server{}
		s.Run(10000)
	}()

	wg.Add(1)
	go func() {
		defer wg.Done()
		//获取ip
		localNet, err := common.GetLocalNet()
		if err != nil {
			fmt.Println(err)
			return
		}
		localNetBytes, err1 := json.Marshal(localNet)
		if err1 != nil {
			fmt.Println(err1)
			return
		}
		broadcast.BroadCast(string(localNetBytes))
	}()

	wg.Wait()
}

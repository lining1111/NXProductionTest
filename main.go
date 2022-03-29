package main

import (
	"NXProductionTest/broadcast"
	"NXProductionTest/common"
	"NXProductionTest/matrixCommon"
	"NXProductionTest/matrixControl"
	"NXProductionTest/server"
	"encoding/json"
	"fmt"
	"sync"
)

func main() {

	buf := []byte{0x88, byte(matrixCommon.Req_GetNet), 4}
	head := matrixControl.Head{}
	err := head.Unpack(buf)
	if err == nil {
		fmt.Printf("%02x,%02x,%02x", head.Start, head.Cmd, head.Len)
	}

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

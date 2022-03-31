package main

import (
	"NXProductionTest/broadcast"
	"NXProductionTest/common"
	"NXProductionTest/server"
	"encoding/json"
	"fmt"
	"sync"
)

func main() {

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
		var broadcastBytes []byte
		if err != nil {
			fmt.Println(err)
			fmt.Println("can get local net info broadcast,broadcast \"hello\"")
			broadcastBytes = []byte("hello")
		} else {
			str, err1 := json.Marshal(localNet)
			if err1 != nil {
				fmt.Println(err1)
				broadcastBytes = []byte("hello")
			} else {
				broadcastBytes = str
			}
		}
		broadcast.Open(3000)
		broadcast.BroadCast(broadcastBytes)
	}()

	wg.Wait()
}

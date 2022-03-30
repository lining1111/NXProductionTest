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
		if err != nil {
			fmt.Println(err)
			fmt.Println("can get local net info broadcast exit")
			return
		}
		localNetBytes, err1 := json.Marshal(localNet)
		if err1 != nil {
			fmt.Println(err1)
			return
		}
		broadcast.Open(3000)
		broadcast.BroadCast(string(localNetBytes))
	}()

	wg.Wait()
}

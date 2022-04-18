package main

import (
	"NXProductionTest/broadcast"
	"NXProductionTest/common"
	"NXProductionTest/server"
	"encoding/json"
	"flag"
	"fmt"
	"os"
	"sync"
)

func main() {

	var version = "1.0.0"
	var port int
	var broadcastPort int

	//读取传入的参数
	flag.IntVar(&port, "port", 8080, "http 端口号 默认 8080")
	flag.IntVar(&broadcastPort, "broadcastPort", 3000, "http 端口号 默认 3000")

	if len(os.Args) == 2 {
		if os.Args[1] == "-v" {
			fmt.Println("version:", version)
			os.Exit(1)
		}

	}
	flag.Parse()

	var wg sync.WaitGroup

	wg.Add(1)
	go func() {
		defer wg.Done()
		server.Run(port)
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
		broadcast.Open(broadcastPort)
		broadcast.BroadCast(broadcastBytes)
	}()

	wg.Wait()
}

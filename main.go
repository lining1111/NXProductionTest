package main

import (
	"NXProductionTest/broadcast"
	"NXProductionTest/matrixControl"
	"NXProductionTest/myLog"
	"NXProductionTest/radar"
	"NXProductionTest/server"
	"flag"
	"fmt"
	"os"
	"sync"
)

func main() {

	//camera.GetDeviceInfo1()

	var showVersion bool
	var version = "1.0.1"
	var port int
	var broadcastPort int
	var dbPath string

	//读取传入的参数
	flag.BoolVar(&showVersion, "v", false, "显示版本号")
	flag.IntVar(&port, "port", 8080, "http 端口号 默认 8080")
	flag.IntVar(&broadcastPort, "broadcastPort", 3000, "udp广播端口号 默认 3000")
	flag.StringVar(&dbPath, "dbPath", "/home/nvidianx/bin/CLParking.db", "数据库位置，默认 /home/nvidianx/bin/CLParking.db")
	flag.Parse()
	if showVersion {
		fmt.Println("version:", version)
		os.Exit(0)
	}

	myLog.Logger.Println("开始")

	var wg sync.WaitGroup

	wg.Add(1)
	go func() {
		defer wg.Done()
		fmt.Println("web thread")
		server.DbPath = dbPath
		server.Run(port)
	}()

	wg.Add(1)
	go func() {
		defer wg.Done()
		fmt.Println("udpBroadcast thread")
		err := broadcast.Open(broadcastPort)
		if err != nil {
			fmt.Println(err)
		}

		broadcast.GetContent()
		broadcast.BroadCast()
	}()

	wg.Add(1)
	go func() {
		defer wg.Done()
		fmt.Println("matrixControl thread")
		matrixControl.MClientMatrixControl.Ip = "192.168.8.2"
		matrixControl.MClientMatrixControl.Port = 5000
		matrixControl.MClientMatrixControl.Run = false
		matrixControl.MClientMatrixControl.ReceiveHeart = false

		//根据udp广播信息获取ip信息
		//for matrixControl.MClientMatrixControl.Ip == "" {
		//	matrixControl.MClientMatrixControl.GetMatrixIp()
		//}
		fmt.Println("matrix control ip:", matrixControl.MClientMatrixControl.Ip)
		err := matrixControl.MClientMatrixControl.Open()
		if err != nil {
			fmt.Println(err)
		} else {
			matrixControl.MClientMatrixControl.ThreadGetReceive()
		}
	}()
	wg.Add(1)
	go func() {
		defer wg.Done()
		fmt.Println("radar thread")
		radar.ThreadGetNetInfoFromUDP()
	}()

	wg.Wait()
}

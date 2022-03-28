package main

/*
#include <stdint.h>
//强制内存对齐会影响go调用c
#pragma pack(1)
typedef struct {
  		uint8_t tag;//固定的头开始 ‘$’ 0x24
        uint8_t version;//版本号 1.0 hex
        uint8_t cmd;//命令字类型 详见CmdType
        uint16_t sn;//帧号
        uint32_t deviceNO;//设备编号
        uint32_t len;//整包长度，从包头到最后的校验位 <帧头>sizeof(PkgHead)+<正文>(json)+<校验>sizeof(PkgCRC)
}S1;
#pragma pack()
*/
import "C"
import (
	"NXProductionTest/broadcast"
	"NXProductionTest/server"
	"sync"
)

func main() {

	//queue := dstr.Queue{}
	//queue.Init()
	//type S1 struct {
	//	a int
	//	b int
	//}
	//
	//s := S1{a: 5, b: 6}
	//s1 := S1{a: 7, b: 8}
	//queue.Enqueue(s)
	//queue.Enqueue(s1)
	//
	//fmt.Println(queue.Size())
	//
	//get := S1{}
	//
	//get = queue.Dequeue().(S1)
	//fmt.Println(get)
	//
	//fmt.Println(queue.Size())
	//get = queue.Dequeue().(S1)
	//fmt.Println(get)

	//rb := ringbuffer.New(1024)
	//
	//var buff []byte
	//
	//buff = append(buff, 1, 2)
	//buff = append(buff, 3)
	//
	//rb.Write(buff[:3])
	//
	//buf16 := make([]byte, 2)
	//rb.Read(buf16)
	//sn := binary.LittleEndian.Uint16(buf16)
	//fmt.Println(sn)

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

		//TODO获取ip
		broadcast.BroadCast("hello")
	}()

	wg.Wait()
}

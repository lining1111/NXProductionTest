package matrixControl

import (
	"fmt"
	"testing"
)

func TestFun(t *testing.T) {
	////unpack head
	//buf := []byte{0x88, byte(matrixCommon.Req_GetNet), 4}
	//head := Head{}
	//err := head.Unpack(buf)
	//if err == nil {
	//	fmt.Printf("%02x,%02x,%02x", head.Start, head.Cmd, head.Len)
	//}

	//Req_SetSn 实验结构体内含有数组
	sn := []byte{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f}
	setSn := Req_SetSn{}
	setSn.Unpack(sn)
	success := true
	for i := 0; i < len(setSn.Sn); i++ {
		if setSn.Sn[i] != sn[i] {
			success = false
			break
		}
	}
	if !success {
		t.Errorf("解包失败")
	}
	buf, _ := setSn.Pack()
	fmt.Println(buf)
	success = true
	for i := 0; i < len(buf); i++ {
		if buf[i] != setSn.Sn[i] {
			success = false
			break
		}
	}
	if !success {
		t.Errorf("封包失败")
	}

	//Req_UpdateData 实验 c端是std::vector
	data := []byte{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f}

	updateData := Req_UpdateData{}
	updateData.Unpack(data)
	for i := 0; i < len(setSn.Sn); i++ {
		if setSn.Sn[i] != sn[i] {
			success = false
			break
		}
	}
	if !success {
		t.Errorf("解包失败")
	}
	buf1, _ := updateData.Pack()
	success = true
	for i := 0; i < len(buf); i++ {
		if buf[i] != setSn.Sn[i] {
			success = false
			break
		}
	}
	if !success {
		t.Errorf("封包失败")
	}

	fmt.Println(buf1)
}

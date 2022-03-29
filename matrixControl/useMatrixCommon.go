package matrixControl

import (
	"NXProductionTest/matrixCommon"
	"errors"
)

// Head 帧头
type Head struct {
	Start uint8
	Cmd   uint8
	Len   uint8
}

// Crc 校验和
type Crc struct {
	Data uint8
}

// Heart 心跳帧 0xa0
type Heart struct {
	AngleRoll     uint16 //翻滚角度 放大10倍
	AnglePitch    uint16 //俯仰角度 放大10倍
	AnglePos      uint16 //方位角度 放大10倍
	Temperature   uint16 //温度 放大10倍
	Humidity      uint16 //湿度 放大10倍
	SwitchVoltage uint16 //交换机电压 放大100倍
	AlarmStatus   uint16 //报警状态位（注释）：
	// 0bit：角度报警（1：报警 0：不报警）
	// 1bit：运动报警（1：报警 0：不报警）
	// 2bit：陀螺仪芯片检测（1：检测到芯片 0：未检芯片）
	// 3bit：陀螺初始化完成（1：成功0：未成功）
	// 4bit：加热工作状态（1：加热 0：不加热）
	// 5bit：风扇1工作状态（1：风扇1启动 0：风扇1停止）
	// 6bit：风扇2工作状态（1：风扇2启动0：风扇2停止）
	// 7bit：补光灯开关状态（1：补光灯开 0：补光灯关）（废弃）
	// 8bit：补光灯485连接状态（0：补光灯连接出错 1：补光灯连接正常）
	// 9bit：风扇1报警（0：风扇正常 1：风扇报警）
	// 10bit：风扇2报警（0：风扇正常 1：风扇报警）
	Version uint16 //版本号
}

// Req_SetSwitch 交换机重启/加热、远程升级帧 0xb2
type Req_SetSwitch struct {
	Heat1           uint8 //1（加热1启动）0（加热1停止）
	Heat2           uint8 //1（加热2启动）0（加热2停止
	Reboot          uint8 //交换机重启（1使能）
	EnterBootloader uint8 //更新程序进入bootloader（1使能）注意：要在开机两分钟后的时段使用(等待一秒钟,重新连接等待心跳.)远程升级命令
	ResetAngle      uint8 //复位角度（1使能）
}

// Req_SetFun 设置风扇开关 0xba
type Req_SetFun struct {
	On uint8 //1(风扇使能) 0（风扇失能）
}

// Req_SetIp 设置矩阵控制器IP 0xb6
type Req_SetIp struct {
	Ip uint32 //192.168.100.5--->C0A86405
}

// Req_SetNet 设置矩阵控制器网络参数 0xbb
type Req_SetNet struct {
	Gateway uint32 //192.168.100.1--->C0A86401
	Mask    uint32 //255.255.255.0--->FFFFFF00
	Ip      uint32 //192.168.100.5--->C0A86405
}

// Req_SetSn 设置矩阵控制器SN参数 0xbe
type Req_SetSn struct {
	Sn [32]byte //sn号（32字节）
}

// Req_GetNetSn 读取矩阵控制器SN和网络参数 0xbc
type Req_GetNetSn struct {
	Data uint8 //0X01固定（1字节）
}

// Rsp_GetNetSn 读取矩阵控制器SN和网络参数 0xac
type Rsp_GetNetSn struct {
	Gateway uint32    //192.168.100.1--->C0A86401
	Mask    uint32    //255.255.255.0--->FFFFFF00
	Ip      uint32    //192.168.100.5--->C0A86405
	Sn      [32]uint8 //sn
}

// Req_GetNet 读取局域网内矩阵控制器网络参数 0xbd
type Req_GetNet struct {
	Data uint8 //0X01固定（1字节）
}

// Rsp_GetNet 读取局域网内矩阵控制器网络参数 0xad
type Rsp_GetNet struct {
	Gateway  uint32 //192.168.100.1--->C0A86401
	Mask     uint32 //255.255.255.0--->FFFFFF00
	Ip       uint32 //192.168.100.5--->C0A86405
	Mac      [6]uint8
	RemoteIp uint32 //目标IP（4个字节）
}

// Req_SetLightThreshold 设置补光灯光敏开关阀值 0xbf
type Req_SetLightThreshold struct {
	ThresholdOn  uint16 //光敏开启阀值
	ThresholdOff uint16 //光敏关闭阀值
}

// Rsp_SetLightThreshold 设置补光灯光敏开关阀值 0xaf
type Rsp_SetLightThreshold struct {
	FarBrightness  uint8  //远灯亮度
	MidBrightness  uint8  //中灯亮度
	NearBrightness uint8  //近灯亮度
	ThresholdOn    uint16 //光敏开启阀值
	ThresholdOff   uint16 //光敏关闭阀值
	DeviceType     uint8  //设备型号55单组灯，33三组灯
	LightStatus    uint8  //单组补光灯状态
}

// Req_SetLightOn 设置单组补光灯开关 0xb8
type Req_SetLightOn struct {
	Status uint8 //1：补光灯开，0：补光灯关
}

// Rsp_SetLightOn 设置单组补光灯开关 0xa8
type Rsp_SetLightOn struct {
	Status uint8 //1：补光灯开，0：补光灯关
}

// Req_SetLightBrightness 设置三组补光灯光敏亮度值 0xb7
type Req_SetLightBrightness struct {
	FarBrightness  uint8 //远灯亮度
	MidBrightness  uint8 //中灯亮度
	NearBrightness uint8 //近灯亮度
}

// Rsp_SetLightBrightness 设置补光灯光敏开关阀值 0xa7
type Rsp_SetLightBrightness struct {
	FarBrightness  uint8  //远灯亮度
	MidBrightness  uint8  //中灯亮度
	NearBrightness uint8  //近灯亮度
	ThresholdOn    uint16 //光敏开启阀值
	ThresholdOff   uint16 //光敏关闭阀值
	DeviceType     uint8  //设备型号55单组灯，33三组灯
	LightStatus    uint8  //单组补光灯状态
}

// Req_GetLightPara 读取补光等信息 0xb9
type Req_GetLightPara struct {
	Data uint8 //0X01固定
}

// Rsp_GetLightPara 读取补光等信息 0xa9
type Rsp_GetLightPara struct {
	FarLightBrightness  uint8  //远灯亮度
	FarLightOn          uint8  //状态，1开0关
	MidLightBrightness  uint8  //远灯亮度
	MidLightOn          uint8  //状态，1开0关
	NearLightBrightness uint8  //远灯亮度
	NearLightOn         uint8  //状态，1开0关
	DeviceType          uint8  //设备型号（55 单组灯，33三组灯）判断是否00 如果00告知用户未接入补光灯
	ThresholdOn         uint16 //光敏开启阀值
	ThresholdOff        uint16 //光敏关闭阀值
}

/* *
 * 网络升级需要上位机发功能码0xB2的指令，矩阵控制器会断开tcp连接，在重新建立一次tcp连接（网络参数不变）。
 * 需要上位机再次连接到矩阵控制。连接成功后，矩阵控制器会每2s发送一次两个#字符（##）等待上位机升级操作，上位机收到字符##后可以进行升级操作
 * 升级说明 上位机发送0xb4 0xb5 依次返回0xa4 0xa5 0xa2
 * */

// Req_UpdateDataSize 矩阵控制器网络升级包数据大小 0xb4
type Req_UpdateDataSize struct {
	TotalLen uint32 //总更新包大小
}

// Rsp_UpdateDataSize 矩阵控制器网络升级包数据大小 0xa4
type Rsp_UpdateDataSize struct {
	TotalLen uint32 //总更新包大小
}

// Req_UpdateData 0xb5
type Req_UpdateData struct {
	Data []uint8
}

// Rsp_UpdateData 0xa5
type Rsp_UpdateData struct {
	EachLen uint32 //每帧更新包大小
}

// Rsp_UpdateStatus 0xa2
type Rsp_UpdateStatus struct {
	Status uint32 //第四个字节0：更新未成功。第四个字节1：更新成功。第一到三字节为00。注：当矩阵控制器收到不合法时序也会返回此指令。
}

func (h *Head) Pack() ([]byte, error) {
	head := matrixCommon.NewHead()
	defer matrixCommon.DeleteHead(head)
	//赋值
	head.SetStart(h.Start)
	head.SetCmd(h.Cmd)
	head.SetLen(h.Len)
	//转换
	buf := make([]byte, 4096)
	bufLen := uint(0)

	ret := matrixCommon.PackStructHead(&buf[0], &bufLen, head)
	if ret != 0 {
		return nil, errors.New("转换失败")
	} else {
		return buf, nil
	}
}

func (h *Head) Unpack(in []byte) error {
	if len(in) >= 3 {
		head := matrixCommon.NewHead()
		defer matrixCommon.DeleteHead(head)
		bufPtr := &in[0]
		bufLen := uint(len(in))
		//转换
		ret := matrixCommon.UnpackSawHead(head, bufPtr, bufLen)
		if ret != 0 {
			return errors.New("获取失败")
		}
		//赋值
		h.Start = head.GetStart()
		h.Cmd = head.GetCmd()
		h.Len = head.GetLen()
		return nil
	} else {
		return errors.New("not enough len")
	}
}

func (c *Crc) Pack() ([]byte, error) {
	crc := matrixCommon.NewCrc()
	defer matrixCommon.DeleteCrc(crc)
	//赋值
	crc.SetData(c.Data)
	//转换
	buf := make([]byte, 4096)
	bufLen := uint(0)

	ret := matrixCommon.PackStructCrc(&buf[0], &bufLen, crc)
	if ret != 0 {
		return nil, errors.New("转换失败")
	} else {
		return buf, nil
	}
}

func (c *Crc) Unpack(in []byte) error {
	crc := matrixCommon.NewCrc()
	defer matrixCommon.DeleteCrc(crc)
	bufPtr := &in[0]
	bufLen := uint(len(in))
	//转换
	ret := matrixCommon.UnpackSawCrc(crc, bufPtr, bufLen)
	if ret != 0 {
		return errors.New("获取失败")
	}
	//赋值
	c.Data = crc.GetData()
	return nil
}

func (h *Heart) Pack() ([]byte, error) {
	heart := matrixCommon.NewS_Heart()
	defer matrixCommon.DeleteS_Heart(heart)
	//赋值
	heart.SetAngleRoll(h.AngleRoll)
	heart.SetAnglePitch(h.AnglePitch)
	heart.SetAnglePos(h.AnglePos)
	heart.SetTemperature(h.Temperature)
	heart.SetHumidity(h.Humidity)
	heart.SetSwitchVoltage(h.SwitchVoltage)
	heart.SetAlarmStatus(h.AlarmStatus)
	heart.SetVersion(h.Version)
	//转换
	buf := make([]byte, 4096)
	bufLen := uint(0)

	ret := matrixCommon.PackStructHeart(&buf[0], &bufLen, heart.Swigcptr())
	if ret != 0 {
		return nil, errors.New("转换失败")
	} else {
		return buf, nil
	}
}

func (h *Heart) Unpack(in []byte) error {
	heart := matrixCommon.NewS_Heart()
	defer matrixCommon.DeleteS_Heart(heart)
	bufPtr := &in[0]
	bufLen := uint(len(in))
	//转换
	ret := matrixCommon.UnpackSawHeart(heart.Swigcptr(), bufPtr, bufLen)
	if ret != 0 {
		return errors.New("获取失败")
	}
	//赋值
	h.AngleRoll = heart.GetAngleRoll()
	h.AnglePitch = heart.GetAnglePitch()
	h.AnglePos = heart.GetAnglePos()
	h.Temperature = heart.GetTemperature()
	h.Humidity = heart.GetHumidity()
	h.SwitchVoltage = heart.GetSwitchVoltage()
	h.AlarmStatus = heart.GetAlarmStatus()
	h.Version = heart.GetVersion()
	return nil
}

func (r *Req_SetSwitch) Pack() ([]byte, error) {
	req := matrixCommon.NewS_Req_SetSwitch()
	defer matrixCommon.DeleteS_Req_SetSwitch(req)
	//赋值
	req.SetHeat1(r.Heat1)
	req.SetHeat2(r.Heat2)
	req.SetReboot(r.Reboot)
	req.SetEnterBootloader(r.EnterBootloader)
	req.SetResetAngle(r.ResetAngle)
	//转换
	buf := make([]byte, 4096)
	bufLen := uint(0)

	ret := matrixCommon.PackStructReq_SetSwitch(&buf[0], &bufLen, req.Swigcptr())
	if ret != 0 {
		return nil, errors.New("转换失败")
	} else {
		return buf, nil
	}
}

func (r *Req_SetSwitch) Unpack(in []byte) error {
	req := matrixCommon.NewS_Req_SetSwitch()
	defer matrixCommon.DeleteS_Req_SetSwitch(req)
	bufPtr := &in[0]
	bufLen := uint(len(in))
	//转换
	ret := matrixCommon.UnpackSawHeart(req.Swigcptr(), bufPtr, bufLen)
	if ret != 0 {
		return errors.New("获取失败")
	}
	//赋值
	r.Heat1 = req.GetHeat1()
	r.Heat2 = req.GetHeat2()
	r.Reboot = req.GetReboot()
	r.EnterBootloader = req.GetEnterBootloader()
	r.ResetAngle = req.GetResetAngle()
	return nil
}

func (r *Req_SetFun) Pack() ([]byte, error) {
	req := matrixCommon.NewS_Req_SetFun()
	defer matrixCommon.DeleteS_Req_SetFun(req)
	//赋值
	req.SetOn(r.On)
	//转换
	buf := make([]byte, 4096)
	bufLen := uint(0)

	ret := matrixCommon.PackStructReq_SetSwitch(&buf[0], &bufLen, req.Swigcptr())
	if ret != 0 {
		return nil, errors.New("转换失败")
	} else {
		return buf, nil
	}
}

func (r *Req_SetFun) Unpack(in []byte) error {
	req := matrixCommon.NewS_Req_SetFun()
	defer matrixCommon.DeleteS_Req_SetFun(req)
	bufPtr := &in[0]
	bufLen := uint(len(in))
	//转换
	ret := matrixCommon.UnpackSawReq_SetFun(req.Swigcptr(), bufPtr, bufLen)
	if ret != 0 {
		return errors.New("获取失败")
	}
	//赋值
	r.On = req.GetOn()
	return nil
}

func (r *Req_SetIp) Pack() ([]byte, error) {
	req := matrixCommon.NewS_Req_SetIp()
	defer matrixCommon.DeleteS_Req_SetIp(req)
	//赋值
	req.SetIp(uint(r.Ip))
	//转换
	buf := make([]byte, 4096)
	bufLen := uint(0)

	ret := matrixCommon.PackStructReq_SetSwitch(&buf[0], &bufLen, req.Swigcptr())
	if ret != 0 {
		return nil, errors.New("转换失败")
	} else {
		return buf, nil
	}
}

func (r *Req_SetIp) Unpack(in []byte) error {
	req := matrixCommon.NewS_Req_SetIp()
	defer matrixCommon.DeleteS_Req_SetIp(req)
	bufPtr := &in[0]
	bufLen := uint(len(in))
	//转换
	ret := matrixCommon.UnpackSawReq_SetFun(req.Swigcptr(), bufPtr, bufLen)
	if ret != 0 {
		return errors.New("获取失败")
	}
	//赋值
	r.Ip = uint32(req.GetIp())
	return nil
}

func (r *Req_SetNet) Pack() ([]byte, error) {
	req := matrixCommon.NewS_Req_SetNet()
	defer matrixCommon.DeleteS_Req_SetNet(req)
	//赋值
	req.SetGateway(uint(r.Gateway))
	req.SetMask(uint(r.Mask))
	req.SetIp(uint(r.Ip))
	//转换
	buf := make([]byte, 4096)
	bufLen := uint(0)

	ret := matrixCommon.PackStructReq_SetSwitch(&buf[0], &bufLen, req.Swigcptr())
	if ret != 0 {
		return nil, errors.New("转换失败")
	} else {
		return buf, nil
	}
}

func (r *Req_SetNet) Unpack(in []byte) error {
	req := matrixCommon.NewS_Req_SetNet()
	defer matrixCommon.DeleteS_Req_SetNet(req)
	bufPtr := &in[0]
	bufLen := uint(len(in))
	//转换
	ret := matrixCommon.UnpackSawReq_SetFun(req.Swigcptr(), bufPtr, bufLen)
	if ret != 0 {
		return errors.New("获取失败")
	}
	//赋值
	r.Gateway = uint32(req.GetGateway())
	r.Mask = uint32(req.GetMask())
	r.Ip = uint32(req.GetIp())
	return nil
}

func (r *Req_SetSn) Pack() ([]byte, error) {
	req := matrixCommon.NewS_Req_SetSn()
	defer matrixCommon.DeleteS_Req_SetSn(req)
	//赋值
	req.SetSn(&r.Sn[0])
	//转换
	buf := make([]byte, 4096)
	bufLen := uint(0)

	ret := matrixCommon.PackStructReq_SetSwitch(&buf[0], &bufLen, req.Swigcptr())
	if ret != 0 {
		return nil, errors.New("转换失败")
	} else {
		return buf, nil
	}
}

func (r *Req_SetSn) Unpack(in []byte) error {
	req := matrixCommon.NewS_Req_SetSn()
	defer matrixCommon.DeleteS_Req_SetSn(req)
	bufPtr := &in[0]
	bufLen := uint(len(in))
	//转换
	ret := matrixCommon.UnpackSawReq_SetFun(req.Swigcptr(), bufPtr, bufLen)
	if ret != 0 {
		return errors.New("获取失败")
	}
	//赋值

	//TODO
	//append(r.Sn, req.GetSn())
	return nil
}

func (r *Req_GetNetSn) Pack() ([]byte, error) {

}

func (r *Req_GetNetSn) Unpack(in []byte) error {

}

func (r *Rsp_GetNetSn) Pack() ([]byte, error) {

}

func (r *Rsp_GetNetSn) Unpack(in []byte) error {

}

func (r *Req_GetNet) Pack() ([]byte, error) {

}

func (r *Req_GetNet) Unpack(in []byte) error {

}

func (r *Rsp_GetNet) Pack() ([]byte, error) {

}

func (r *Rsp_GetNet) Unpack(in []byte) error {

}

func (r *Req_SetLightThreshold) Pack() ([]byte, error) {

}

func (r *Req_SetLightThreshold) Unpack(in []byte) error {

}

func (r *Rsp_SetLightThreshold) Pack() ([]byte, error) {

}

func (r *Rsp_SetLightThreshold) Unpack(in []byte) error {

}

func (r *Req_SetLightOn) Pack() ([]byte, error) {

}

func (r *Req_SetLightOn) Unpack(in []byte) error {

}

func (r *Rsp_SetLightOn) Pack() ([]byte, error) {

}

func (r *Rsp_SetLightOn) Unpack(in []byte) error {

}

func (r *Req_SetLightBrightness) Pack() ([]byte, error) {

}

func (r *Req_SetLightBrightness) Unpack(in []byte) error {

}

func (r *Rsp_SetLightBrightness) Pack() ([]byte, error) {

}

func (r *Rsp_SetLightBrightness) Unpack(in []byte) error {

}

func (r *Req_GetLightPara) Pack() ([]byte, error) {

}

func (r *Req_GetLightPara) Unpack(in []byte) error {

}

func (r *Rsp_GetLightPara) Pack() ([]byte, error) {

}

func (r *Rsp_GetLightPara) Unpack(in []byte) error {

}

func (r *Req_UpdateDataSize) Pack() ([]byte, error) {

}

func (r *Req_UpdateDataSize) Unpack(in []byte) error {

}

func (r *Rsp_UpdateDataSize) Pack() ([]byte, error) {

}

func (r *Rsp_UpdateDataSize) Unpack(in []byte) error {

}

func (r *Req_UpdateData) Pack() ([]byte, error) {

}

func (r *Req_UpdateData) Unpack(in []byte) error {

}

func (r *Rsp_UpdateData) Pack() ([]byte, error) {

}

func (r *Rsp_UpdateData) Unpack(in []byte) error {

}

func (r *Rsp_UpdateStatus) Pack() ([]byte, error) {

}

func (r *Rsp_UpdateStatus) Unpack(in []byte) error {

}

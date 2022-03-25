package server

/**
 * 整体通信大帧结构
 *  1byte   1byte   1byte       2bytes  4bytes  4bytes  Nbytes      2bytes
 *  帧头      版本  命令标识符       帧号  设备编号    帧长  json格式正文    校验码
 */
var (
	Cmd1 = 1
	Cmd2 = 2
)

const HeadLen = 13
const CRCLen = 2
type Head struct {
	Tag      uint8  //固定的头开始 ‘$’ 0x24
	Version  uint8  //版本号 1.0 hex
	Cmd      uint8  //命令字类型 详见CmdType
	Sn       uint16 //帧号
	DeviceNO uint32 //设备编号
	Len      uint32 //整包长度，从包头到最后的校验位 <帧头>sizeof(PkgHead)+<正文>(json)+<校验>sizeof(PkgCRC)
}

type Crc struct {
	Data uint16 //校验值，从帧头开始到正文的最后一个字节
}

//帧体为json格式

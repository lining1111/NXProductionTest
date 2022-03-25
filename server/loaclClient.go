package server

import "C"
import (
	"encoding/binary"
	"fmt"
	"github.com/smallnest/ringbuffer"
	"net"
	"unsafe"
)

/**
 * 整体通信大帧结构
 *  1byte   1byte   1byte       2bytes  4bytes  4bytes  Nbytes      2bytes
 *  帧头      版本  命令标识符       帧号  设备编号    帧长  json格式正文    校验码
 * 整包长度，从包头到最后的校验位 <帧头>sizeof(PkgHead)+<正文>(json)+<校验>sizeof(PkgCRC)
 */

const rbSize = (1024 * 1024 * 10)
const tmpSize = (1024 * 1024)

const maxStore = 100

var (
	Start        = 0 //开始
	GetHeadStart = 1 //获取开始符号'$'
	GetHead      = 2 //获取全部帧头
	GetBody      = 3 //获取全部帧体
	GetCRC       = 4 //获取校验
)

type Pkg struct {
	Head Head
	Body string
	Crc  Crc
}

type LocalClient struct {
	run    bool
	conn   net.Conn
	tmpBuf []byte                 //一次接收的缓存
	tmpLen int                    //一次接收的长度
	rb     *ringbuffer.RingBuffer //环形buffer
	//分包相关
	status int //Start---GetHeadStart---GetHead---GetBody---GetCRC
	//解包相关
	tmpPkg Pkg
	pkgs   chan Pkg
}

func (c *LocalClient) New(conn net.Conn, tmpSize int, rbSize int) {
	c.run = true
	c.conn = conn
	c.tmpBuf = make([]byte, tmpSize)
	c.tmpLen = 0
	c.rb = ringbuffer.New(rbSize)
	c.pkgs = make(chan Pkg, maxStore)
	c.status = Start
}

func (c *LocalClient) Close() {
	c.run = false
	c.conn.Close()
	close(c.pkgs)
}

//把读取的字节存入缓存中
func (c *LocalClient) dump() {
	fmt.Println("dump run")
	for c.run {
		var err error
		c.tmpLen, err = c.conn.Read(c.tmpBuf)
		if err != nil {
			fmt.Printf("client%s read err:%s", c.conn.RemoteAddr().String(), err.Error())
			c.run = false
		}
		//存入缓存
		c.rb.Write(c.tmpBuf[:c.tmpLen])
		fmt.Println("rb size read", c.rb.Length())
	}
	fmt.Println("dump exit")
}

// 从缓存中获取
func (c *LocalClient) getPkg() {
	fmt.Println("getPkg run")
	for c.run {
		switch c.status {
		case Start:
			{
				//读取‘$’
				if c.rb.Length() >= int(unsafe.Sizeof(c.tmpPkg.Head.Tag)) {
					tag, _ := c.rb.ReadByte()
					c.tmpPkg.Head.Tag = tag
					c.status = GetHeadStart
				}
			}

		case GetHeadStart:
			{
				if c.rb.Length() >= (HeadLen - int(unsafe.Sizeof(c.tmpPkg.Head.Tag))) {
					//version
					version, _ := c.rb.ReadByte()
					c.tmpPkg.Head.Version = version
					//cmd
					cmd, _ := c.rb.ReadByte()
					c.tmpPkg.Head.Cmd = cmd

					buf16 := make([]byte, 2)
					buf32 := make([]byte, 4)
					//sn
					c.rb.Read(buf16)
					c.tmpPkg.Head.Sn = binary.LittleEndian.Uint16(buf16)

					//deviceNO
					c.rb.Read(buf32)
					c.tmpPkg.Head.DeviceNO = binary.LittleEndian.Uint32(buf32)
					//len
					c.rb.Read(buf32)
					c.tmpPkg.Head.Len = binary.LittleEndian.Uint32(buf32)

					c.status = GetHead
				}
			}
		case GetHead:
			{
				bodySize := int(c.tmpPkg.Head.Len - uint32(HeadLen+CRCLen))
				if c.rb.Length() >= bodySize {
					//拷贝body
					body := make([]byte, bodySize)
					c.rb.Read(body)
					c.tmpPkg.Body = string(body)
					c.status = GetBody
				}
			}
		case GetBody:
			{
				if c.rb.Length() >= CRCLen {
					buf16 := make([]byte, 2)
					c.rb.Read(buf16)
					c.tmpPkg.Crc.Data = binary.LittleEndian.Uint16(buf16)
					c.status = GetCRC
				}
			}
		case GetCRC:
			{
				//将获得的包结构体存入
				c.pkgs <- c.tmpPkg
				c.status = Start
			}

		}
	}
	fmt.Println("getPkg exit")
}

func (c *LocalClient) getContent() {
	fmt.Println("getContent run")
	for c.run {
		pkg, ok := <-c.pkgs
		if ok {
			switch pkg.Head.Cmd {
			case uint8(Cmd1):
				fmt.Println(pkg.Body)
			case uint8(Cmd2):
				fmt.Println(pkg.Body)
			default:
				fmt.Printf("unknown cmd:%d,body:%s\n", pkg.Head.Cmd, pkg.Body)
			}
		}
	}
	fmt.Println("getContent run")
}

//主处理流程
func (c *LocalClient) Process() {
	fmt.Println("client process")
	if c.run {
		go c.dump()
		go c.getPkg()
		go c.getContent()
	}
}

#ifndef MATRIXCOMMON_H
#define MATRIXCOMMON_H

#include <cstdint>
#include <vector>

#ifdef __cplusplus
extern "C"
{
#endif

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define OFFSET(type, member)      \
    ( (size_t)( &( ((type*)0)->member)  ) )
#define MEMBER_SIZE(type, member) \
    sizeof(((type *)0)->member)
/**
 * 通信大帧结构体
 * 1byte       1byte   1byte    n bytes 2bytes
 * start(0x88)  cmd     len     data    crc
 */

enum Cmd {
    Heart = 0xa0,//心跳帧
    Req_SetSwitch = 0xb2,//交换机重启/加热、远程升级帧
    Req_SetFun = 0xba,//设置风扇开关
    Rsp_SetFun = 0xaa,//无数据内容
    Req_SetIp = 0xb6,//设置矩阵控制器IP
    Rsp_SetIp = 0xa6,//无数据内容
    Req_SetNet = 0xbb,//设置矩阵控制器网络参数
    Rsp_SetNet = 0xab,//无数据内容
    Req_SetSn = 0xbe,//设置矩阵控制器SN参数
    Rsp_SetSn = 0xae,//无数据内容
    Req_GetNetSn = 0xbc,//读取矩阵控制器网络和SN参数
    Rsp_GetNetSn = 0xac,
    Req_GetNet = 0xbd,//读取局域网内矩阵控制器网络参数
    Rsp_GetNet = 0xad,
    Req_SetLightThreshold = 0xbf,//设置矩阵控制器补光灯光敏开关阀值
    Rsp_SetLightThreshold = 0xaf,
    Req_SetLightOn = 0xb8,//设置矩阵控制器补光灯开关
    Rsp_SetLightOn = 0xa8,
    Req_SetLightBrightness = 0xb7,//设置矩阵控制器补光灯亮度值
    Rsp_SetLightBrightness = 0xa7,
    Req_GetLightPara = 0xb9,//读取补光灯参数
    Rsp_GetLightPara = 0xb9,
    Req_UpdateDataSize = 0xb4,//矩阵控制器网络升级包数据大小
    Rsp_UpdateDataSize = 0xa4,
    Req_UpdateData = 0xb5,//矩阵控制器网络升级包数据
    Rsp_UpdateData = 0xa5,
    Req_UpdateStart = 0xb2,//发送开始升级指令,无数据内容
    Rsp_UpdateStatus = 0xa2,//矩阵控制器网络升级成功返回帧
//    Req_SetAngleAlarmThreshold = 0xb3,//设置矩阵控制器角度报警阈值
//    Rsp_SetAngleAlarmThreshold = 0xa3,
//    Req_GetAngleAlarmThreshold = 0xc1,//读取矩阵控制器角度报警阈值
//    Rsp_GetAngleAlarmThreshold = 0xd1,
};

typedef struct {
    uint8_t start = 0x88;//开始字节
    uint8_t cmd;//命令字参考Cmd
    uint8_t len;//长度,只表示数据长度
} Head;

typedef struct {
    uint8_t data;//前所有字节累加包括帧头
} Crc;


#pragma pack(1)

typedef struct {
    uint16_t angleRoll;//翻滚角度 放大10倍
    uint16_t anglePitch;//俯仰角度 放大10倍
    uint16_t anglePos;//方位角度 放大10倍
    uint16_t temperature;//温度 放大10倍
    uint16_t humidity;//湿度 放大10倍
    uint16_t switchVoltage;//交换机电压 放大100倍
    uint16_t alarmStatus;//报警状态位（注释）：
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
    uint16_t version;//版本号
} S_Heart;//心跳帧 0xa0

typedef struct {
    uint8_t heat1;//1（加热1启动）0（加热1停止）
    uint8_t heat2;//1（加热2启动）0（加热2停止
    uint8_t reboot;//交换机重启（1使能）
    uint8_t enterBootloader;//更新程序进入bootloader（1使能）注意：要在开机两分钟后的时段使用(等待一秒钟,重新连接等待心跳.)远程升级命令
    uint8_t resetAngle;//复位角度（1使能）
} S_Req_SetSwitch;//交换机重启/加热、远程升级帧 0xb2

typedef struct {
    uint8_t on;//1(风扇使能) 0（风扇失能）
} S_Req_SetFun;//设置风扇开关 0xba

typedef struct {
    uint32_t ip;//192.168.100.5--->C0A86405
} S_Req_SetIp;//设置矩阵控制器IP 0xb6

typedef struct {
    uint32_t gateway;//192.168.100.1--->C0A86401
    uint32_t mask;//255.255.255.0--->FFFFFF00
    uint32_t ip;//192.168.100.5--->C0A86405
} S_Req_SetNet;//设置矩阵控制器网络参数 0xbb

typedef struct {
    uint8_t sn[32];//sn号（32字节）
} S_Req_SetSn;//设置矩阵控制器SN参数 0xbe

typedef struct {
    uint8_t data = 0x01;//0X01固定（1字节）
} S_Req_GetNetSn;//读取矩阵控制器SN和网络参数 0xbc

typedef struct {
    uint32_t gateway;//192.168.100.1--->C0A86401
    uint32_t mask;//255.255.255.0--->FFFFFF00
    uint32_t ip;//192.168.100.5--->C0A86405
    uint8_t sn[32];//sn
} S_Rsp_GetNetSn;//读取矩阵控制器SN和网络参数 0xac


typedef struct {
    uint8_t data = 0x01;//0X01固定（1字节）
} S_Req_GetNet;//读取局域网内矩阵控制器网络参数 0xbd

typedef struct {
    uint32_t gateway;//192.168.100.1--->C0A86401
    uint32_t mask;//255.255.255.0--->FFFFFF00
    uint32_t ip;//192.168.100.5--->C0A86405
    uint8_t mac[6];
    uint32_t remoteIp;//目标IP（4个字节）
} S_Rsp_GetNet;//读取局域网内矩阵控制器网络参数 0xad

typedef struct {
    uint16_t thresholdOn;//光敏开启阀值
    uint16_t thresholdOff;//光敏关闭阀值
} S_Req_SetLightThreshold;//设置补光灯光敏开关阀值 0xbf

typedef struct {
    uint8_t farBrightness;//远灯亮度
    uint8_t midBrightness;//中灯亮度
    uint8_t nearBrightness;//近灯亮度
    uint16_t thresholdOn;//光敏开启阀值
    uint16_t thresholdOff;//光敏关闭阀值
    uint8_t deviceType;//设备型号55单组灯，33三组灯
    uint8_t lightStatus;//单组补光灯状态
} S_Rsp_SetLightThreshold;//设置补光灯光敏开关阀值 0xaf

typedef struct {
    uint8_t status;//1：补光灯开，0：补光灯关
} S_Req_SetLightOn;//设置单组补光灯开关 0xb8

typedef struct {
    uint8_t status;//1：补光灯开，0：补光灯关
} S_Rsp_SetLightOn;//设置单组补光灯开关 0xa8

typedef struct {
    uint8_t farBrightness;//远灯亮度
    uint8_t midBrightness;//中灯亮度
    uint8_t nearBrightness;//近灯亮度
} S_Req_SetLightBrightness;//设置三组补光灯光敏亮度值 0xb7

typedef struct {
    uint8_t farBrightness;//远灯亮度
    uint8_t midBrightness;//中灯亮度
    uint8_t nearBrightness;//近灯亮度
    uint16_t thresholdOn;//光敏开启阀值
    uint16_t thresholdOff;//光敏关闭阀值
    uint8_t deviceType;//设备型号55单组灯，33三组灯
    uint8_t lightStatus;//单组补光灯状态
} S_Rsp_SetLightBrightness;//设置补光灯光敏开关阀值 0xa7

typedef struct {
    uint8_t data = 0x01;//0X01固定
} S_Req_GetLightPara;//读取补光等信息 0xb9

typedef struct {
    uint8_t farLightBrightness;//远灯亮度
    uint8_t farLightOn;//状态，1开0关
    uint8_t midLightBrightness;//远灯亮度
    uint8_t midLightOn;//状态，1开0关
    uint8_t nearLightBrightness;//远灯亮度
    uint8_t nearLightOn;//状态，1开0关
    uint8_t deviceType;//设备型号（55 单组灯，33三组灯）判断是否00 如果00告知用户未接入补光灯
    uint16_t thresholdOn;//光敏开启阀值
    uint16_t thresholdOff;//光敏关闭阀值
} S_Rsp_GetLightPara;//读取补光等信息 0xa9

/* *
 * 网络升级需要上位机发功能码0xB2的指令，矩阵控制器会断开tcp连接，在重新建立一次tcp连接（网络参数不变）。
 * 需要上位机再次连接到矩阵控制。连接成功后，矩阵控制器会每2s发送一次两个#字符（##）等待上位机升级操作，上位机收到字符##后可以进行升级操作
 * 升级说明 上位机发送0xb4 0xb5 依次返回0xa4 0xa5 0xa2
 * */

typedef struct {
    uint32_t totalLen;//总更新包大小
} S_Req_UpdateDataSize;//矩阵控制器网络升级包数据大小 0xb4

typedef struct {
    uint32_t totalLen;//总更新包大小
} S_Rsp_UpdateDataSize;//矩阵控制器网络升级包数据大小 0xa4

typedef struct {
    std::vector<uint8_t> data;
} S_Req_UpdateData;//0xb5

typedef struct {
    uint32_t eachLen;//每帧更新包大小
} S_Rsp_UpdateData;//0xa5

typedef struct {
    uint32_t status;//第四个字节0：更新未成功。第四个字节1：更新成功。第一到三字节为00。注：当矩阵控制器收到不合法时序也会返回此指令。
} S_Rsp_UpdateStatus;//0xa2

#pragma pack()


uint16_t reverse16(uint16_t value);

uint32_t reverse32(uint32_t value);

uint64_t reverse64(uint64_t value);

/**
 * 计算校验和
 * @param data 数据地址
 * @param len 数据长度
 * @return 校验和
 */
uint8_t crcSum(uint8_t *data, uint32_t len);

//命令类型对应的组包函数
typedef int (*packStruct)(uint8_t *out, uint32_t *len, void *sIn);
//命令类型对应的解包函数
typedef int (*unpackSaw)(void *sOut, uint8_t *in, uint32_t len);


int packStructHead(uint8_t *out, uint32_t *len, Head head);
int packStructCrc(uint8_t *out, uint32_t *len, Crc crc);

//具体组包函数
int packStructHeart(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_SetSwitch(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_SetFun(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_SetIp(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_SetNet(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_SetSn(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_GetNetSn(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_GetNetSn(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_GetNet(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_GetNet(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_SetLightThreshold(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_SetLightThreshold(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_SetLightOn(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_SetLightOn(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_SetLightBrightness(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_SetLightBrightness(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_GetLightPara(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_GetLightPara(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_UpdateDataSize(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_UpdateDataSize(uint8_t *out, uint32_t *len, void *sIn);
int packStructReq_UpdateData(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_UpdateData(uint8_t *out, uint32_t *len, void *sIn);
int packStructRsp_UpdateStatus(uint8_t *out, uint32_t *len, void *sIn);

/**
 * 组包发送开始升级指令，此命令就发送一个0xb2
 * @param out
 * @param len
 * @return
 */
int packSendUpdate(uint8_t *out, uint32_t *len);

/**
 * 从获取的字节中获取是否可以升级
 * @param in
 * @param len
 * @return
 */
bool unpackIsCanUpdate(uint8_t *in, uint32_t len);

int unpackSawHead(Head *head, uint8_t *in, uint32_t len);
int unpackSawCrc(Crc *crc, uint8_t *in, uint32_t len);
//具体解包函数
int unpackSawHeart(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_SetSwitch(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_SetFun(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_SetIp(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_SetNet(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_SetSn(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_GetNetSn(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_GetNetSn(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_GetNet(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_GetNet(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_SetLightThreshold(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_SetLightThreshold(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_SetLightOn(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_SetLightOn(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_SetLightBrightness(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_SetLightBrightness(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_GetLightPara(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_GetLightPara(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_UpdateDataSize(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_UpdateDataSize(void *sOut, uint8_t *in, uint32_t len);
int unpackSawReq_UpdateData(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_UpdateData(void *sOut, uint8_t *in, uint32_t len);
int unpackSawRsp_UpdateStatus(void *sOut, uint8_t *in, uint32_t len);


/**
 * 组包
 * @param out 组包后的数据指针
 * @param len 组包后的数据长度
 * @param cmd 命令类型
 * @param sIn 与命令类型相关的结构体指针
 * @return 0：成功 -1：失败
 */
int Pack(uint8_t *out, uint32_t *len, enum Cmd cmd, void *sIn);

/**
 * 解包
 * @param sOut 解包后与命令类型相关的结构体指针
 * @param cmd 解包后得到的命令类型
 * @param in 待解包的数据指针
 * @param len 待解包的数据长度
 * @return 0：成功 -1：失败
 */
int Unpack(void *sOut, enum Cmd *cmd, uint8_t *in, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif //MATRIXCOMMON_H

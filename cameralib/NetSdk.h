#pragma once

#ifdef __cplusplus
#ifdef WIN32
#define DLL_EXPORT  extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT  extern "C"
#endif
#define DEF_PARAM(x) = x
#else
#define DLL_EXPORT
#define DEF_PARAM(x)
#endif

#ifdef WIN32
#ifndef CALL_METHOD
#define CALL_METHOD	__stdcall  //__cdecl
#endif
#else
#define CALL_METHOD
#endif


#define NET_MAX_MAC_LEN             32          //MAC地址字符最大长度
#define NET_MAX_HOST_NAME_LEN       32          //主机名字符最大长度
#define NET_MAX_USER_NUM			60			//最多用户数
#define NET_MAX_GROUP_NUM			50			//最多组数
#define NET_MAX_NAME_PSW_LEN		64			//用户名密码最大长度
#define NET_MAX_FILTERIP_NUM		64			//IP地址最大过滤数
#define NET_MAX_CHANNUM				4			//最大通道数
#define NET_MAX_EMAIL_TITLE_LEN		64
#define NET_MAX_EMAIL_RECIEVERS		5
#define NET_MAX_ADDRESS_LEN			64
#define SDK_MAX_DISK_PER_MACHINE	8			//硬盘最大数
#define SDK_MAX_DRIVER_PER_DISK		8			//单个硬盘分区最大数
#define NET_MAX_RETURNED_LOGLIST	1024
#define NET_MAX_OPT_PERSONS_ONCES	16			//单次可操作最大人员数

//#define NET_ENCRYPTION_TYPE_MD5 "MD5"

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned long ulong;
typedef unsigned char uchar;
typedef void* puint;

#ifndef __cplusplus
#define bool _Bool
#define true 1
#define false 0
#endif

#ifndef NULL
#define NULL 0
#endif

enum E_SDK_RET_CODE {
	E_SDK_ERROR_NOERROR				   		= 0,			//没有错误
	E_SDK_ERROR_SUCCESS						= 1,			//返回成功
	E_SDK_ERROR_FAILURE						= -1,			//返回通用错误
	E_SDK_ERROR_NOTVALID					= -10000,		//非法请求,主连接可能已断开
	E_SDK_ERROR_NO_INIT						= -10001,		//SDK未经初始化
	E_SDK_ERROR_ILLEGAL_PARAM				= -10002,		//用户参数不合法
	E_SDK_ERROR_INVALID_HANDLE				= -10003,		//句柄无效
	E_SDK_ERROR_UNINIT_ERROR				= -10004,		//SDK清理出错
	E_SDK_ERROR_TIMEOUT						= -10005,		//等待超时
	E_SDK_ERROR_MEMORY_ERROR				= -10006,		//内存错误，创建内存失败
	E_SDK_ERROR_NET_ERROR					= -10007,		//网络错误
	E_SDK_ERROR_OPEN_FILE_ERROR				= -10008,		//打开文件失败
	E_SDK_ERROR_UNKNOWNERROR				= -10009,		//未知错误
	E_SDK_ERROR_DEV_VER_NOMATCH				= -11000,		//收到数据不正确，可能版本不匹配
	E_SDK_ERROR_NOTSUPPORT					= -11001,		//版本不支持
	E_SDK_ERROR_MSGFORMAT_ERROR				= -11002,		//消息格式错误

	E_SDK_ERROR_OPEN_CHANNEL_ERROR			= -11200,		//打开通道失败,可能检测到设备已经不在线
	E_SDK_ERROR_CLOSE_CHANNEL_ERROR			= -11201,		//关闭通道失败
	E_SDK_ERROR_SUB_CONNECT_ERROR			= -11202,		//建立媒体子连接失败,网络出错或者设备可能不在线
	E_SDK_ERROR_SUB_CONNECT_SEND_ERROR		= -11203,		//媒体子连接通讯失败,可能检测到设备已经不在线
	E_SDK_ERROR_NATCONNET_REACHED_MAX		= -11204,       //Nat视频链接达到最大，不允许新的Nat视频链接 
	E_SDK_ERROR_TCPCONNET_REACHED_MAX		= -11207,		//Tcp视频链接达到最大，不允许新的Tcp视频链接
	E_SDK_ERROR_OPENEDPREVIEW				= -11208,		//该通道已经打开预览(通道的打开关闭需要一一对应,打开几次需要关闭几次;不一致会打开提示该错误;预防客户端开发逻辑上的不合理设计增加该错误值)
	E_SDK_ERROR_OUT_OF_RESOURCE				= -11209,		//回放资源用尽，退出一些可继续使用

	/// 用户管理部分错误码
	E_SDK_ERROR_NOPOWER						= -11300,		//无权限
	E_SDK_ERROR_PASSWORD_NOT_VALID			= -11301,		//账号密码不对
	E_SDK_ERROR_LOGIN_USER_NOEXIST			= -11302,		//用户不存在
	E_SDK_ERROR_USER_LOCKED					= -11303,		//该用户被锁定
	E_SDK_ERROR_USER_IN_BLACKLIST			= -11304,		//该用户不允许访问(在黑名单中)
	E_SDK_ERROR_USER_HAS_USED				= -11305,		//该用户已登录
	E_SDK_ERROR_USER_NOT_LOGIN				= -11306,		//该用户没有登录
	E_SDK_ERROR_CONNECT_DEVICE_ERROR		= -11307,		//可能设备不存在
	E_SDK_ERROR_USER_EXISTED				= -11308,		//此用户已经存在
	E_SDK_ERROR_GROUP_EXISTED				= -11309,		//此用户组已经存在
	E_SDK_ERROR_GROUP_NOT_EXIST				= -11310,		//此用户组不存在
	E_SDK_ERROR_ACCOUNT_OBJECT_IN_USE		= -11312,		//对象正在使用
	E_SDK_ERROR_ACCOUNT_SUBSET_OVERLAP		= -11313,		//子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)
	E_SDK_ERROR_ACCOUNT_RESERVED			= -11316,		//保留帐号
	//GB35114鉴权错误码
	E_SDK_ERROR_AUTHENTICATE_INIT			= -11317,		// 初始化失败,可能没插加密U盘
	
	/// 配置管理相关错误码
	E_SDK_ERROR_OPT_RESTART					= -11400,		//保存配置后需要重启应用程序
	E_SDK_ERROR_OPT_REBOOT					= -11401,		//需要重启系统
	E_SDK_ERROR_OPT_FILE_ERROR				= -11402,		//写文件出错
	E_SDK_ERROR_OPT_CAPS_ERROR				= -11403,		//配置特性不支持
	E_SDK_ERROR_OPT_VALIDATE_ERROR			= -11404,		//配置校验失败
	E_SDK_ERROR_OPT_CONFIG_NOT_EXIST		= -11405,		//请求或者设置的配置不存在
	E_SDK_ERROR_OPT_CONFIG_PARSE_ERROR		= -11406,		//解析失败
	E_SDK_ERROR_OPT_SELF_REBOOT				= -11407,		//设备端主动重启
	E_SDK_ERROR_OPT_MULTICAST_MODIFY_ERROR	= -11408,		//跨网段修改失败
	E_SDK_ERROR_OPT_SEARCH_EXPORTKEY_ERROR	= -11409,		//导出密文失败
	E_SDK_ERROR_OPT_SEARCH_IMPORTKEY_ERROR	= -11410,		//导入密钥失败
	
	//
	E_SDK_ERROR_CTRL_PAUSE_ERROR			= -11500,		//暂停失败
	E_SDK_ERROR_NOTFOUND					= -11501,		//查找失败，没有找到对应文件
	E_SDK_ERROR_CFG_NOT_ENABLE				= -11502,       //配置未启用

	E_SDK_ERROR_SOCKET_DOMAIN				= -11602,		//域名解析失败
	E_SDK_ERROR_NO_CONNECT_FRONT			= -11614,		//前端设备未连接或者连接的前端设备分辨率未知

	// 文件管理
	E_SDK_ERROR_FM_TYPE_UNKNOWN				= -11700,		// 类型未知
	E_SDK_ERROR_FM_DIR_INVALID				= -11701,		// 目录非法
	E_SDK_ERROR_FM_DIR_NOT_EXIST			= -11702,		// 目录不存在
	E_SDK_ERROR_FM_DIR_NOT_SUPPORT_UPLOAD	= -11703,		// 目录下不支持上传
	E_SDK_ERROR_FM_DIR_NOT_SUPPORT_RENAME	= -11704,		// 目录下不支持修改
	E_SDK_ERROR_FM_DIR_NOT_SUPPORT_REMOVE	= -11705,		// 目录下不支持删除
	E_SDK_ERROR_FM_DIR_CREATE_FAILED		= -11706,		// 目录创建失败
	E_SDK_ERROR_FM_FILE_FORMAT_NOT_SUPPORT	= -11707,		// 文件格式不支持
	E_SDK_ERROR_FM_FILE_NUM_OUT_LIMIT		= -11708,		// 文件数量超出限制
	E_SDK_ERROR_FM_FILE_SIZE_OUT_LIMIT		= -11709,		// 文件大小超出限制
	E_SDK_ERROR_FM_FILE_NOT_EXIST			= -11710,		// 文件不存在
	E_SDK_ERROR_FM_FILE_EXISTED				= -11711,		// 文件已存在
	E_SDK_ERROR_FM_FILE_OPEN_FAILED			= -11712,		// 文件打开失败
	E_SDK_ERROR_FM_FILE_READ_FAILED			= -11713,		// 文件读取失败
	E_SDK_ERROR_FM_FILE_WRITE_FAILED		= -11714,		// 文件写入失败
	E_SDK_ERROR_FM_FILE_RENAME_FAILED		= -11715,		// 文件重命名失败
	E_SDK_ERROR_FM_FILE_REMOVE_FAILED		= -11716,		// 文件删除失败
	E_SDK_ERROR_FM_NO_SPACE					= -11717,		// 剩余空间不足

	//升级错误码
	E_SDK_ERROR_NOENOUGH_MEMORY				= -11804,		//内存不足
	E_SDK_ERROR_INVALID_FORMAT				= -11805,		//升级文件格式不对
	E_SDK_ERROR_UPDATE_PART_FAIL			= -11806,		//某个分区升级失败
	E_SDK_ERROR_INVALID_HARDWARE			= -11807,		//硬件型号不匹配
	E_SDK_ERROR_INVALID_VENDOR				= -11808,		//客户信息不匹配
	E_SDK_ERROR_INVALID_COMPALIBLE			= -11809,		//升级程序的兼容版本号比设备现有的小，不允许设备升级回老程序
	E_SDK_ERROR_INVALID_CRC					= -11810,		// CRC校验不对
	E_SDK_ERROR_INVALID_FLASH_SIZE			= -11811,		// 升级程序flash size不对
	E_SDK_ERROR_UPDATE_SWITCH_FAIL			= -11812,		// 切换分区失败
	//烧写硬件版本信息错误码
	E_SDK_ERROR_HWID_LENGTH					= -11900,		// 数据长度不对
	E_SDK_ERROR_HWID_MD5					= -11901,		// MD5值不对
	E_SDK_ERROR_HWID_BURN					= -11902,		// 烧写失败
	E_SDK_ERROR_HWID_MAC					= -11903,		// Mac地址不对
	//产测错误码
	E_SDK_ERROR_PRODUCE_DOUBLE_OK			= -12000,		// 需要人工二次确认的成功
	E_SDK_ERROR_PRODUCE_FAILED				= -12001,		// 失败
	E_SDK_ERROR_PRODUCE_UNSUPPORTED			= -12002,		// 不支持
	E_SDK_ERROR_PRODUCE_UNINITIALIZED		= -12003,		// 产测模式未初始化

	// 对讲
	E_SDK_ERROR_TALK_STARTED				= -12100,		// 开启对讲失败，已经开启对讲
	E_SDK_ERROR_TALK_NOT_START				= -12101,		// 关闭对讲失败，未开启对讲
};

typedef enum E_SDK_LOCAL_CFG_TYPE{
	E_SDK_LOCAL_CFG_BYTE_ENCODE = 1,				// 编码类型--对应结构体sByteEncodeConfig
	E_SDK_LOCAL_CFG_AV_PRIVATEHEAD = 2,				// 音视频私有头--对应结构体sAVPrivateHeadConfig
	E_SDK_LOCAL_CFG_LOGGER = 3,						// 日志等级--对应结构体sLoggerConfig
}eLocalCfgType;

typedef enum E_SDK_COMMAND_TYPE {
	E_SDK_CMD_NOTHING = 0,
	E_SDK_CMD_ATTRIBUTE_SYSINFO,					//系统信息---对应结构体sDeviceInfo
	E_SDK_CMD_ATTRIBUTE_GET_USER_MANAGER,			//获取用户---对应结构体sConfigUserManageInfo
	E_SDK_CMD_CONTROL_ADD_USER,						//增加用户---对应结构体sConfigUserInfo
	E_SDK_CMD_CONTROL_MODIFY_USER,					//修改用户---对应结构体sConfigModifyUser
	E_SDK_CMD_CONTROL_DELETE_USER,					//删除用户---对应结构体sConfigUserInfo
	E_SDK_CMD_CONTROL_ADD_GROUP,					//增加分组---对应结构体sConfigUserGroupInfo	已废弃
	E_SDK_CMD_CONTROL_MODIFY_GROUP,					//修改分组---对应结构体sConfigModifyGroup	已废弃
	E_SDK_CMD_CONTROL_DELETE_GROUP,					//删除分组---对应结构体sConfigUserGroupInfo	已废弃
	E_SDK_CMD_CONTROL_MODIFY_PSW,					//修改密码---对应结构体sConfigModifyPsw
	E_SDK_CMD_CONFIG_NET_IPFILTER = 10,				//黑白名单---对应结构体sNetIPFilterConfig
	E_SDK_CMD_CONFIG_SYSNORMAL,						//普通配置---对应结构体sGeneralConfig
	E_SDK_CMD_CONFIG_NET_INTERFACE_LIST,			//网络配置---对应结构体sNetInterfaceList
	E_SDK_CMD_CONFIG_SYSTIME,						//系统时间---对应结构体sSystemTime
	E_SDK_CMD_CONFIG_ENCODE,						//编码配置---对应结构体sEncodeConfigAll
	E_SDK_CMD_CONFIG_AUTO_MAINTAIN,					//自动维护---对应结构体sAutoMaintainConfig
	E_SDK_CMD_CONFIG_INTELLIGENCE_PARAM,			//智能配置---对应结构体sIntelligenceConfig
	E_SDK_CMD_CONFIG_TIME_NORMAL,					//时间配置---对应结构体sTimeNormal
	E_SDK_CMD_CONFIG_NET_FTP,						//FTP 配置---对应结构体sFtpServerConfig
	E_SDK_CMD_CONFIG_NET_FTP_PS,					//FTP 配置---对应结构体sPSFtpServerConfig---ps定制
	E_SDK_CMD_CONFIG_NET_CLOUD_SERVER = 20,			//联络中心---对应结构体sCloudServerConfig
	E_SDK_CMD_CONFIG_NET_CLOUD_SERVER_PS,			//联络中心---对应结构体sCloudServerConfig---ps定制
	E_SDK_CMD_CONFIG_NET_NTP,						//NTP 配置---对应结构体sNtpServerConfig
	E_SDK_CMD_ATTRIBUTE_SYSTEM_ABILITY,				//设备能力---对应结构体sSystemFuncAbility
	E_SDK_CMD_ATTRIBUTE_ABILTY_ENCODE,				//编码能力---对应结构体sEncodeAbility
	E_SDK_CMD_CONFIG_CAMERA_PARAM,					//像机参数---对应结构体sCameraParamConfigAll
	E_SDK_CMD_CONFIG_ALARM_IN,						//报警输入---对应结构体sAlarmInputConfigAll
	E_SDK_CMD_CONFIG_ALARM_OUT,						//报警输出---对应结构体sAlarmOutputConfigAll
	E_SDK_CMD_CONFIG_VIDEO_COVER,					//视频遮盖---对应结构体sVideoCoverConfigAll
	E_SDK_CMD_CONFIG_CHANNELTITLE_INFO,				//通道标题---对应结构体sChannelTitleConfigAll
	E_SDK_CMD_CONFIG_TIMETITLE_INFO = 30,			//时间标题---对应结构体sTimeTitleConfigAll
	E_SDK_CMD_CONFIG_OSD_INFO,						//叠加信息---对应结构体sCustomOSDInfoConfigAll
	E_SDK_CMD_CONFIG_NET_SMTP,						//SMTP配置---对应结构体sSmtpServerConfig
	E_SDK_CMD_CONTROL_NET_SMTP_TEST,				//邮件测试---对应结构体sSmtpServerConfig
	E_SDK_CMD_CONTROL_NET_FTP_TEST,					//FTP 测试---对应结构体sFtpServerConfig
	E_SDK_CMD_CONFIG_RECORD_CONFIG,					//录像配置---对应结构体sRecordConfigALL	已废弃
	E_SDK_CMD_SEARCH_RECORD_EXIST,					//有无录像---对应接口  F_SDK_SearchDeviceInfo
	E_SDK_CMD_SEARCH_RECORD_LIST,					//查询录像---对应接口  F_SDK_SearchDeviceInfo
	E_SDK_CMD_CONTROL_IMPORT_EXPORT_CONFIG,			//导入导出---对应导入导出二进制数据
	E_SDK_CMD_CONTROL_EXPORT_LOG,					//日志导出---对应导出二进制数据
	E_SDK_CMD_CONFIG_DISK_INFO = 40,				//硬盘信息---对应结构体sDiskInformationAll
	E_SDK_CMD_CONTROL_DISK_MANAGER,					//硬盘管理---对应结构体sDiskManagerControl
	E_SDK_CMD_CONTROL_DEFAULT_MANAGER,				//恢复默认---对应结构体sDefaultConfigTypes
	E_SDK_CMD_ATTRIBUTE_LANGUAGE_ABILITY,			//支持语言---对应结构体sLanguageAbility
	E_SDK_CMD_CONFIG_SNAPSHOT_CONFIG,				//抓图配置---对应结构体sSnapShotConfigALL
	E_SDK_CMD_CONFIG_NETSERVER_PORT,				//协议端口---对应结构体sNetserviceConfig
	E_SDK_CMD_CONFIG_WEB_PORT,						//网页端口---对应结构体sWebConfig
	E_SDK_CMD_CONFIG_RTSP_PORT,						//Rtsp端口---对应结构体sRtspConfig
	E_SDK_CMD_CONFIG_ONVIF_CONFIG,					//Onvif使能---对应结构体sOnvifConfig
	E_SDK_CMD_SEARCH_LOG_LIST,						//查询日志---对应接口  F_SDK_SearchDeviceInfo
	E_SDK_CMD_CONFIG_STORAGE_POLICY = 50,			//存储策略---对应结构体sStoragePolicyConfig
	E_SDK_CMD_CONTROL_PING_TEST,					//ping外网---对应结构体sPingTestConfig
	E_SDK_CMD_CONFIG_MOTION_DETECT,					//移动侦测---对应结构体sMotionDetectConfigAll
	E_SDK_CMD_CONFIG_BLIND_DETECT,					//视频遮挡---对应结构体sBlindDetectConfigAll
	E_SDK_CMD_CONFIG_AUDIO_ENCODE,					//音频编码---对应结构体sAudioEncodeAll
	E_SDK_CMD_CONFIG_NET_GB28181 = 55,				//GB 28181---对应结构体sGb28181Config
	E_SDK_CMD_CONFIG_NET_PPPOE,						//PPPOE   ---对应结构体sPppoeConfig
	E_SDK_CMD_CONFIG_PTZ_PATROL,					//PTZ 轮巡---对应结构体sPTZConfigPatrolChannelAll
	E_SDK_CMD_CONFIG_NET_WIFI_LIST,					//WIFI列表---对应结构体sNetWifiSearchList
	E_SDK_CMD_CONFIG_NET_WIFI,						//WIFI配置---对应结构体sNetWifiConfig
	E_SDK_CMD_CONFIG_NET_INTELLIF_HTTP = 60,		//HTTP服务---对应结构体sNetIntellifHttpConfig				E_NETWORK_ABILITY_INTELLIF_HTTP
	E_SDK_CMD_ATTRIBUTE_RESOURCE_INFO,				//资源信息---对应结构体sResourceInformation				E_OTHER_ABILITY_PSDOOR
	E_SDK_CMD_CONFIG_NET_SAFESOFT_HTTP,				//HTTP服务---对应结构体sNetSafeSoftHttpConfig				E_NETWORK_ABILITY_SAFESOFT_HTTP
	E_SDK_CMD_ATTRIBUTE_CLOUD_FIRMWARE_INFO,		//云固件信息--对应结构体sNetCloudUpgradeInfo				E_NETWORK_ABILITY_CLOUD_UPGRADE
	E_SDK_CMD_SEARCH_ALGORITHM_STATISTIC,			//智能统计---对应接口  F_SDK_SearchDeviceInfo				E_OTHER_ABILITY_STATISTIC
	E_SDK_CMD_CONFIG_CLOUD_UPGRADE_RULE = 65,		//远程升级---对应结构体sCloudUpgradeRuleConfig			E_NETWORK_ABILITY_CLOUD_UPGRADE
	E_SDK_CMD_CONFIG_AUDIO_PLAY,					//音频配置---对应结构体sAudioPlayConfigAll
	E_SDK_CMD_CONFIG_INTELLIGENCE_PARAM_PS,			//智能配置---对应结构体sPsIntelligenceParam
	E_SDK_CMD_CONFIG_NET_WWAN,						//移动网卡---对应结构体sNetWwanConfig
	E_SDK_CMD_CONTROL_NET_FTP_PS_TEST,				//FTP 测试---对应结构体sPSFtpServerConfig
	E_SDK_CMD_CONFIG_RECORD_V2 = 70,				//录像配置---对应结构体sRecordConfigAllV2
	E_SDK_CMD_CONFIG_NET_BCW_HTTP,					//HTTP服务---对应结构体sNetBcwHttpConfig					E_NETWORK_ABILITY_BCW_HTTP
	E_SDK_CMD_CONFIG_ALARM_DISK_FULL,				//硬盘已满---对应结构体sAlarmDiskFullConfig								
	E_SDK_CMD_CONFIG_ALARM_DISK_FAILURE,			//硬盘出错---对应结构体sAlarmDiskErrorConfig
	E_SDK_CMD_CONFIG_SIGNATURE_ANTELOPE,			//云验证码---对应结构体sAntelopeSignature
	E_SDK_CMD_CONFIG_VIDEO_ROTATION = 75,			//视频旋转---对应结构体sVideoRotationConfigAll
	E_SDK_CMD_CONFIG_GA1400_CLIENT,					//GA 1400---对应结构体sNetGa1400ClientConfig
	E_SDK_CMD_CONTROL_EXPORT_DIAGNOSEDINFO,			//诊断信息---对应导出数据
	E_SDK_CMD_CONFIG_LINKKIT_REGISTER,				//AL云认证---对应结构体sLinkkitRegisterConfig
	E_SDK_CMD_CONFIG_VIDEO_OUTPARAM,				//输出参数---对应结构体sVideoOutparamConfigAll
	E_SDK_CMD_SEARCH_CURRENT_STATISTIC = 80,		//当前统计---对应接口  F_SDK_SearchDeviceInfo
	E_SDK_CMD_CONFIG_ANRUAN_CFG_SERVER,				//配置服务---对应结构体sAnruanConfigServer
	E_SDK_CMD_CONFIG_EXTRA_OSD_INFO,				//额外 OSD---对应结构体sExtraOsdInfoConfigAll
	E_SDK_CMD_ATTRIBUTE_CAMERA_ABILITY,				//像机能力---对应结构体sCameraAbilityAll
	E_SDK_CMD_CONFIG_NET_WWAN_V2,					//移动网卡---对应结构体sWwanConfigAllV2
	E_SDK_CMD_CONFIG_NET_INTERFACE_ORDER = 85,		//网卡排序---对应结构体sNetInterfaceOrder
	E_SDK_CMD_CONFIG_PSCLOUD_REGISTER,				//Ps云认证---对应结构体sPsCloudRegisterConfig
	E_SDK_CMD_CONFIG_WXCLOUD_REGISTER,				//Wx云认证---对应结构体sWxCloudRegisterConfig
	E_SDK_CMD_CONTROL_AUDIO_TEST,					//音频测试---对应结构体sAudioTestReq
	E_SDK_CMD_CONFIG_GNSS_SIMPLE_DATA,				//GNSS数据---对应结构体sGnssSimpleDataCfg
	E_SDK_CMD_CONFIG_NET_SUPEREYE = 90,				//推图服务---对应结构体sNetSupereyeClientCfg				E_OTHER_ABILITY_SUPEREYE
	E_SDK_CMD_CONFIG_NET_PORT_MAPPING,				//端口映射---对应结构体sNetPortMappingList				E_NETWORK_ABILITY_PORT_MAPPING
	E_SDK_CMD_CONFIG_INTRUSION_DETECT,				//智能监测---对应结构体sIntrusionDetectAll
	E_SDK_CMD_CONFIG_360CLOUD_REGISTER,				//360云认证--对应结构体s360CloudRegisterConfig
	E_SDK_CMD_CONFIG_NET_GD_SMARTEYE,				//广东慧眼---对应结构体sNetGdSmarteyeCfg					E_NETWORK_ABILITY_GD_SMARTEYE
	E_SDK_CMD_CONFIG_GD_SMARTEYE_REGISTER = 95,		//慧眼认证---对应结构体sGdSmarteyeRegisterConfig
	E_SDK_CMD_CONFIG_CAMERA_CFG_MANAGER,			//参数管理---对应结构体sCameraCfgManagerAll
	E_SDK_CMD_CONFIG_CAMERA_EIS,					//电子防抖---对应结构体sCameraCfgEisAll
	E_SDK_CMD_CONFIG_CAMERA_AWB,					//白平衡-----对应结构体sCameraCfgAwbAll
	E_SDK_CMD_CONFIG_CAMERA_DNC,					//日夜转换---对应结构体sCameraCfgDncAll
	E_SDK_CMD_CONFIG_CAMERA_LIGHT = 100,			//补光灯-----对应结构体sCameraCfgLightAll
	E_SDK_CMD_CONFIG_CAMERA_EXPOSURE,				//曝光配置---对应结构体sCameraCfgExposureAll
	E_SDK_CMD_CONFIG_CAMERA_IMAGE,					//图像配置---对应结构体sCameraCfgImageAll
	E_SDK_CMD_CONFIG_CAMERA_DEH,					//去雾配置---对应结构体sCameraCfgDehAll
	E_SDK_CMD_CONFIG_CAMERA_BACKLIGHT,				//背光配置---对应结构体sCameraCfgBacklightAll
	E_SDK_CMD_CONFIG_CAMERA_WDR = 105,				//宽动态-----对应结构体sCameraCfgWdrAll
	E_SDK_CMD_CONFIG_CAMERA_NOISE_REDUCE,			//降噪配置---对应结构体sCameraCfgNoiseReduceAll
	E_SDK_CMD_CONFIG_CAMERA_IMAGE_FLIP,				//图像翻转---对应结构体sCameraCfgImageFlipAll
	E_SDK_CMD_CONFIG_CAMERA_IRCUT,					//ircut反序--对应结构体sCameraCfgIrcutAll
	E_SDK_CMD_ATTRIBUTE_ABILITY_EVENT_LINK,			//联动能力---对应结构体sEventLinkAbilityAll
	E_SDK_CMD_ATTRIBUTE_DEFAULT_ALARM_AUDIO = 110,	//报警音频---对应结构体sEventLinkAudioDefaultList	已废弃
	E_SDK_CMD_CONFIG_NET_BEITE_CLIENT,				//贝特定制---对应结构体sNetBeiteClientCfg					E_NETWORK_ABILITY_BEITE
	E_SDK_CMD_ATTRIBUTE_ONVIF_GET_USER_INFO,		//获取用户---对应结构体sOnvifAccountManageInfo
	E_SDK_CMD_CONTROL_ONVIF_ADD_USER,				//增加用户---对应结构体sOnvifUserInfo
	E_SDK_CMD_CONTROL_ONVIF_DELETE_USER,			//删除用户---对应结构体sOnvifUserInfo
	E_SDK_CMD_CONTROL_ONVIF_MODIFY_USER = 115,		//修改用户---对应结构体sOnvifUserInfo,仅支持修改分组
	E_SDK_CMD_CONTROL_ONVIF_MODIFY_PSW,				//修改密码---对应结构体sOnvifModifyPassword，不需要传原密码
	E_SDK_CMD_ATTRIBUTE_ABILITY_AUDIO_FILE,			//音频能力---对应结构体sAudioFileAbilityAll
	E_SDK_CMD_CONFIG_ROI_PARAM,						//感兴趣区域-对应结构体sRoiParamAll
	E_SDK_CMD_CONFIG_ALARM_NIC_BROKEN,				//网络断开---对应结构体sAlarmNicBrokenConfig
	E_SDK_CMD_CONFIG_ALARM_IP_CONFLICT = 120,		//IP 冲突---对应结构体sAlarmIpConflictConfig
	E_SDK_CMD_CONFIG_LOGIN_SECURITY,				//登录安全---对应结构体sLoginSecurityConfig
	E_SDK_CMD_CONFIG_ALARM_ILLEGAL_LOGIN,			//非法访问---对应结构体sAlarmIllegalLoginConfig
	E_SDK_CMD_CONFIG_ALARM_AUDIO_DETECT,			//音频侦测---对应结构体sAaDetectConfigAll					E_OTHER_ABILITY_AUDIO_DETECT
	E_SDK_CMD_CONFIG_ALARM_HUMAN_DETECT,			//人形侦测---对应结构体sAlarmHumanDetectAll				E_OTHER_ABILITY_VANILLA_HUMAN_DETECTION
	E_SDK_CMD_CONFIG_TELECOM_REGISTER = 125,		//电信认证---对应结构体sTelecomVisionSmartLink
	E_SDK_CMD_ATTRIBUTE_AUTO_FOCUS_STATUS,			//聚焦状态---对应结构体sAutoFocusStatus
	E_SDK_CMD_CONFIG_XUZN_SERVER,					//迅贞平台---对应结构体sNetXuznServerCfg					E_NETWORK_ABILITY_XUZN
	E_SDK_CMD_CONFIG_ANDLINK_REGISTER,				//杭移认证---对应结构体sAndlinkRegister
	E_SDK_CMD_CONFIG_TT_ENCRYPT_INFO = 129,			//算法加密---对应结构体sTtEncryptInfo
	E_SDK_CMD_CONFIG_OSD_PARAM_SERVER_INTERSTELL,	//XJ服务器---对应结构体sInterstellOsdParamServer
	E_SDK_CMD_CONFIG_SERIAL_LIST,					//串口列表---对应结构体sSerialList

	/*门禁机*/
	E_SDK_CMD_CONFIG_DOORCTRL_ACTIVATED = 0x401,	//激活状态---对应结构体sDoorActivatyState
	E_SDK_CMD_CONFIG_DOORCTRL_TAKEOVER_MODE,		//管理方式---对应结构体sDoorTakeoverMode
	E_SDK_CMD_CONFIG_DOORCTRL_USAGE_SCENE,			//使用场景---对应结构体sDoorUsageScene
	E_SDK_CMD_CONFIG_DOORCTRL_PARAM,				//门禁参数---对应结构体sDoorCtrlParam
	E_SDK_CMD_CONFIG_CUSTOMER_CLOUD_DATA,			//客户数据---对应结构体sCustomerCloudDataConfig
	E_SDK_CMD_CONFIG_DOORCTRL_RECOGNITION_PARAM,	//识别参数---对应结构体sDoorCtrlRecognitionParam
	E_SDK_CMD_CONFIG_DOORCTRL_IDENTIFY_TIP,			//提示规则---对应结构体sDoorCtrlIdentifyTip
	E_SDK_CMD_ATTRIBUTE_DOORCTRL_FIRMWARE_INFO,		//面板机固件-对应结构体sDcUsbUpgradeCheckInfo
	E_SDK_CMD_CONFIG_DOORCTRL_WIEGAND,				//韦根协议---对应结构体sDoorCtrlWiegandConfig
	E_SDK_CMD_CONFIG_DOORCTRL_PASS_SETTING,			//通行设置---对应结构体sDoorCtrlPassSettingConfig
	E_SDK_CMD_CONTROL_DOORCTRL_CHECK_STATUS,		//检测状态---对应结构体sDCCheckStatus
	E_SDK_CMD_CONFIG_DOORCTRL_ALARM_PARAM,			//报警接口---对应结构体sDcAlarmParamConfig
	E_SDK_CMD_CONFIG_DOORCTRL_SCREENSAVER,			//屏幕保护---对应结构体sDcScreensaver
	E_SDK_CMD_CONFIG_DOORCTRL_CALIBRATION_MGVL,		//双目标定---对应结构体sDcCalibrationMgvl
	E_SDK_CMD_CONTROL_DOORCTRL_LOG_CLEAR,			//记录清除---对应结构体sDcLogClearReq
	E_SDK_CMD_CONTROL_DOORCTRL_UNLOCK_PWD_MOD,		//解锁密码---对应结构体sUnlockModifyPsw
	E_SDK_CMD_CONTROL_DOORCTRL_TRAVEL_PLAN,			//通行计划---对应结构体sDcTravelTimePlanAll
	E_SDK_CMD_CONTROL_DOORCTRL_CARD_SCHEME,			//迎宾卡片---对应结构体sDcCardSchemeAll
	E_SDK_CMD_CONTROL_DOORCTRL_FACE_BOX,			//人脸画框---对应结构体sDcFaceBoxConfig
	E_SDK_CMD_CONFIG_DOORCTRL_CALIBRATION_DM,		//双目标定---对应结构体sDcCalibrationDm
	E_SDK_CMD_CONFIG_DOORCTRL_MASK_PARAM,			//口罩参数---对应结构体sDcPsMaskParam
	E_SDK_CMD_CONFIG_DOORCTRL_TEMP_PARAM_ONENET,	//测温参数---对应结构体sDcOneNetTempParam
	E_SDK_CMD_ATTRIBUTE_DOORCTRL_DETECT_TYPE,		//验证类型---对应结构体sDcPassSchemeAll
}eConfigCmdType;

//跨网段操作
enum E_SDK_OVERNET_CMD_TYPE {
	E_SDK_OVERNET_CMD_MODIFYIP,						//修改 IP---对应结构体sModifyIpOverNet
	E_SDK_OVERNET_CMD_EXPORT_KEY,					//获取密文---对应结构体sExportKey
	E_SDK_OVERNET_CMD_IMPORT_KEY,					//发送密钥---对应结构体sImportKey
};

typedef enum E_SDK_FACELIBRARY_CMDTYPE {
	E_SDK_CMD_NOTHING_FACE = 0,						//							lpInBuffer			lpOutBuffer
	E_SDK_CMD_CONTROL_FR_ADD_PERSON,				//增加人脸信息---对应结构体sFRPersonInfoOptReq	sFRPersonInfoOptRsp
	E_SDK_CMD_CONTROL_FR_DEL_PERSON,				//删除人脸信息---对应结构体sFRPersonInfoOptReq	sFRPersonInfoOptRsp
	E_SDK_CMD_CONTROL_FR_MDF_PERSON,				//修改人脸信息---对应结构体sFRPersonInfoOptReq	sFRPersonInfoOptRsp
	E_SDK_CMD_SEARCH_FR_PERSON_INFO,				//搜索人脸信息---对应结构体sFRSearchPersonReq	sFRSearchPersonRsp*			返回指针需要调用F_SDK_FreeBuffer接口释放
	E_SDK_CMD_CONTROL_FR_ADD_GROUP = 5,				//增加人脸分组---对应结构体sFRGroupOptReq		sFRGroupOptRsp
	E_SDK_CMD_CONTROL_FR_DEL_GROUP,					//删除人脸分组---对应结构体sFRGroupOptReq		sFRGroupOptRsp
	E_SDK_CMD_CONTROL_FR_MDF_GROUP,					//修改分组信息---对应结构体sFRGroupOptReq		sFRGroupOptRsp
	E_SDK_CMD_SEARCH_FR_GROUP_INFO,					//搜索分组信息---对应结构体sFRGroupSearchReq	sFRGroupSearchRsp*			返回指针需要调用F_SDK_FreeBuffer接口释放
	E_SDK_CMD_SEARCH_FR_EVENT_LOG,					//搜索识别记录---对应结构体sFRSearchEventLogReq	sFRSearchEventLogRsp*		返回指针需要调用F_SDK_FreeBuffer接口释放
	/*门禁机*/
	E_SDK_CMD_CONTROL_DOOR_ADD_FACE = 20,			//增加人脸信息---对应结构体sPersonInfoOptReq	sPersonInfoOptRsp
	E_SDK_CMD_CONTROL_DOOR_DEL_FACE,				//删除人脸信息---对应结构体sPersonInfoOptReq	sPersonInfoOptRsp
	E_SDK_CMD_CONTROL_DOOR_MDF_FACE,				//修改人脸信息---对应结构体sPersonInfoOptReq	sPersonInfoOptRsp
	E_SDK_CMD_SEARCH_DOOR_FACE_INFO,				//搜索人脸信息---对应结构体sSearchPersonReq		sSearchPersonRsp*			返回指针需要调用F_SDK_FreeBuffer接口释放
	E_SDK_CMD_SEARCH_DOOR_PASSED_LOG,				//搜索通行记录---对应结构体sSearchPassedLogReq	sSearchPassedLogRsp*		返回指针需要调用F_SDK_FreeBuffer接口释放
	
	E_SDK_CMD_CONTROL_DOOR_ADD_SCHEDULE = 25,		//增加时间计划---对应结构体sDoorScheduleOptReq		sDoorScheduleOptRsp
	E_SDK_CMD_CONTROL_DOOR_DEL_SCHEDULE,			//删除时间计划---对应结构体sDoorScheduleOptReq		sDoorScheduleOptRsp
	E_SDK_CMD_CONTROL_DOOR_MDF_SCHEDULE,		  	//修改时间计划---对应结构体sDoorScheduleOptReq		sDoorScheduleOptRsp
	E_SDK_CMD_SEARCH_DOOR_SCHEDULE_INFO,		  	//搜索时间计划---对应结构体sDoorScheduleSearchReq	sDoorScheduleSearchRsp*		返回指针需要调用F_SDK_FreeBuffer接口释放

	E_SDK_CMD_CONTROL_DOOR_ADD_GROUP,				//增加人脸分组---对应结构体sDoorGroupOptReq			sDoorGroupOptRsp
	E_SDK_CMD_CONTROL_DOOR_DEL_GROUP,				//删除人脸分组---对应结构体sDoorGroupOptReq			sDoorGroupOptRsp
	E_SDK_CMD_CONTROL_DOOR_MDF_GROUP,				//修改分组信息---对应结构体sDoorGroupOptReq			sDoorGroupOptRsp
	E_SDK_CMD_SEARCH_DOOR_GROUP_INFO,				//搜索分组信息---对应结构体sDoorGroupSearchReq		sDoorGroupSearchRsp*		返回指针需要调用F_SDK_FreeBuffer接口释放
	
	E_SDK_CMD_SEARCH_ALARM_EVENT_LOG,				//搜索报警事件记录---对应结构体sDCAlarmSearchEventLogReq	sDCAlarmSearchEventLogRsp*	

	E_SDK_CMD_SEARCH_IMPORT_FAIL_LOG,				//搜索导入失败的人员信息---对应结构体sSearchPersonReq		sSearchPersonRsp*			返回指针需要调用F_SDK_FreeBuffer接口释放

}eFaceLibCmd;

// 工装相关命令
typedef enum E_SDK_PRODUCETEST_CMDTYPE {
	E_SDK_CMD_NOTHING_PRODUCE = 0,					//							lpInBuffer			lpOutBuffer
	E_SDK_CMD_CONTROL_GET_STATUS,					//获取工装状态---对应结构体		NULL			sProduceStatus
	E_SDK_CMD_CONTROL_SET_STATUS,					//保存工装状态---对应结构体sProduceStatus			sPrduceTestRsp
	E_SDK_CMD_CONTROL_START,						//初始化设备  ---对应结构体		NULL			sPrduceTestRsp
	E_SDK_CMD_CONTROL_VO,							//			  ---对应结构体sProduceVoReq			sPrduceTestRsp
	E_SDK_CMD_CONTROL_WIFI = 5,						//			  ---对应结构体		NULL			sPrduceTestRsp
	E_SDK_CMD_CONTROL_4G,							//			  ---对应结构体		NULL			sPrduceTestRsp
	E_SDK_CMD_CONTROL_WIFI_BANDWIDTH,				//检测带宽    ---对应结构体sTestNetworkSpeedReq	sTestNetworkSpeedRsp
	E_SDK_CMD_CONTROL_4G_SPEED,						//			  ---对应结构体sTestNetworkSpeedReq	sTestNetworkSpeedRsp
	E_SDK_CMD_CONTROL_GPIO,							//			  ---对应结构体sTestGpioReq			sPrduceTestRsp
	E_SDK_CMD_CONTROL_AUDIO_PLAY = 10,				//			  ---对应结构体		NULL			sPrduceTestRsp
	E_SDK_CMD_CONTROL_RS485,						//			  ---对应结构体		NULL			sPrduceTestRsp
	E_SDK_CMD_CONTROL_RTC,							//			  ---对应结构体		NULL			sPrduceTestRsp

	E_SDK_CMD_CONTROL_GPT = 100,					//通用产测	  ---对应结构体sGeneralProduceTestReq sGeneralProduceTestRsp
	E_SDK_CMD_CONTROL_RS485_WRITE = 101,			//产测485写	  ---对应结构体sGPTRS485WriteReq			NULL					(废弃)
	E_SDK_CMD_CONTROL_RS485_READ = 102,				//产测485读	  ---对应结构体		NULL			sGPTRS485ReadRsp			(废弃)
}eProduceTestCmd;

typedef enum E_SDK_STREAM_TYPE {
	E_SDK_STREAM_TYPE_MAIN = 0,
	E_SDK_STREAM_TYPE_SECOND = 1,
	E_SDK_STREAM_TYPE_THIRD = 2,
}eStreamType;

typedef enum {
	E_SDK_CONNECT_TYPE_TCP = 0,
	E_SDK_CONNECT_TYPE_P2P = 1,						//P2P
	E_SDK_CONNECT_TYPE_NR
}eConnectType;

typedef enum E_SDK_SUBCONNECT_TYPE {
	conn_main = 0,									//主链接
	conn_realTimePlay = 1,							//预览子链接
	conn_talk,										//对讲子链接
	conn_playback,									//回放子链接
	conn_push,										//推图子链接
	conn_upgradeProgress,							//升级进度
}eSubConnType;

typedef enum E_SDK_ALARM_TYPE {						//				返回结构体				开启通道接口
	E_SDK_ALARM_TYPE_ALARM = 0,						//表示报警信息	sAlarmInfo				F_SDK_SetupUploadInfoChan
	E_SDK_ALARM_TYPE_PUSH = 1,						//表示推图信息	sPushData				F_SDK_SetupPushChan
	E_SDK_ALARM_TYPE_INTERACTIVE_D2C = 2,			//云交互事件		sDeviceToCloudReq		F_SDK_SetupUploadInfoChan
	E_SDK_ALARM_TYPE_INTERACTIVE_S2S = 3,			//客户端交互事件 sS2SInteractiveReq		F_SDK_SetupUploadInfoChan      （目前主要用来测试面板机屏幕）
	E_SDK_ALARM_TYPE_INTERACTIVE_GPT = 4,			//通用产测的事件 sGeneralProduceTestRsp	F_SDK_SetupUploadInfoChan
	E_SDK_ALARM_TYPE_CONFIG_OBSERVER = 5,			//配置修改事件	sConfigChangeObserver	F_SDK_ConfigChangeObserver
	E_SDK_ALARM_TYPE_AUDIO_STRENGTH = 6,			//声音强度上报事件	sAudioStrengthUpload	F_SDK_SetupUploadInfoChan
	E_SDK_ALARM_TYPE_SERIAL_UPLOAD = 7,				//串口数据上报事件	sSerialDataUpload	F_SDK_SetupUploadInfoChanV2
	// GUI
	E_SDK_ALARM_TYPE_UPLOAD_INFO = 10,				//GUI状态信息	sUploadInfo				F_SDK_SetupUploadInfoChan
	E_SDK_ALARM_TYPE_PASSED_EVENT_INFO = 11,		//GUI通行事件	sDoorCtrlEventInfo		(与E_SDK_ALARM_TYPE_UPLOAD_INFO “状态信息”一起开启，不需要重复开启)
	E_SDK_ALARM_TYPE_INTERACTIVE_D2G = 12,			//GUI交互事件	sDoorInteractiveD2G		(与E_SDK_ALARM_TYPE_UPLOAD_INFO “状态信息”一起开启，不需要重复开启)
	E_SDK_ALARM_TYPE_FR_EVENT_INFO = 13,			//GUI识别事件	sFaceRecognitionEvent	(与E_SDK_ALARM_TYPE_UPLOAD_INFO “状态信息”一起开启，不需要重复开启)
	E_SDK_ALARM_TYPE_ALARM_DATA_EVENT_INFO = 14,	//GUI报警事件	sDCAlarmEvent			(与E_SDK_ALARM_TYPE_UPLOAD_INFO “状态信息”一起开启，不需要重复开启)
}eAlarmType;

typedef enum E_SDK_INTEL_PUSH_TYPE {
	E_SDK_INTEL_PUSH_TYPE_FACE = 0,					//表示人脸
	E_SDK_INTEL_PUSH_TYPE_PENGSI = 1,				//ps
	E_SDK_INTEL_PUSH_TYPE_DOOR = 2,					//门禁机
	E_SDK_INTEL_PUSH_TYPE_NR,
}eIntelPicturePushType;

enum E_SDK_INTEL_PUSH_IMG_TYPE {
	E_SDK_INTEL_PUSHIMG_TYPE_FULL = 0x01,			//背景图
	E_SDK_INTEL_PUSHIMG_TYPE_TARGET = 0x02,			//人脸图
	E_SDK_INTEL_PUSHIMG_TYPE_FACEID = 0x04,			//识别人脸图
	E_SDK_INTEL_PUSHIMG_TYPE_DOORID = 0x08,			//门禁机识别
	E_SDK_INTEL_PUSHIMG_TYPE_HUMAN = 0x10,			//人形图
	E_SDK_INTEL_PUSHIMG_TYPE_PLATE = 0x20,			//车牌
	E_SDK_INTEL_PUSHIMG_TYPE_VEHICLE = 0x40,		//机动车
	E_SDK_INTEL_PUSHIMG_TYPE_CYCLE = 0x80,			//非机动车
	E_SDK_INTEL_PUSHIMG_TYPE_NR,
};

/// 设备类型										
typedef enum E_SDK_DEVICE_TYPE {
	E_SDK_DEVICE_TYPE_IPC,							///< IPC设备
	E_SDK_DEVICE_TYPE_NR
}eDeviceType;

///< IP权限设置
typedef enum E_SDK_FILTER_TYPE {
	E_FILTER_TYPE_CLOSE,
	E_FILTER_TYPE_BLACK,
	E_FILTER_TYPE_WHITE,
}eFilterType;

/// 捕获码流控制模式类型
typedef enum E_SDK_BITRATE_CONTROL {
	E_SDK_CAPTURE_BRC_CBR,							// 固定码流。
	E_SDK_CAPTURE_BRC_VBR,							// 可变码流。
}eBitrateControl;

/// 图像帧子类型
typedef enum E_SDK_FRAME_SUB_TYPE {
	E_SUB_VIDEO_FRAME_JPEG,
	E_SUB_VIDEO_FRAME_H264_I,
	E_SUB_VIDEO_FRAME_H264_P,
	E_SUB_VIDEO_FRAME_H265_I,
	E_SUB_VIDEO_FRAME_H265_P,
	E_SUB_VIDEO_FRAME_YUV420SP,
	// 音频
	E_SUB_AUDIO_FRAME_PCM,
	E_SUB_AUDIO_FRAME_G711A,
	E_SUB_AUDIO_FRAME_G711U,
	E_SUB_AUDIO_FRAME_AAC,
	E_SUB_AUDIO_FRAME_OPUS,
	E_SUB_FRAME_TYPE_NUM,							// 未知
} eSubFrameType;

typedef enum E_SDK_LANGUAGE_LIST {
	E_SDK_LANGUAGE_UNKNOWN = 0,
	E_SDK_LANGUAGE_ENGLISH = 1,
	E_SDK_LANGUAGE_CHINESE = 2,
	E_SDK_LANGUAGE_NR,
}eLanguageList;

typedef enum E_SDK_VIDEO_STANDARD {
	E_SDK_VIDEO_STANDARD_PAL = 0,
	E_SDK_VIDEO_STANDARD_NTSC = 1,
}eVideoStandard;

// 设备的登录方式
typedef enum E_SDK_LOGIN_TYPE {
	E_SDK_LOGIN_TYPE_UNKNOWN = 0,					// 未知方式登录
	E_SDK_LOGIN_TYPE_GUI = 1,						// 本地GUI登录
	E_SDK_LOGIN_TYPE_CONSOLE = 2,					// 控制台登录
	E_SDK_LOGIN_TYPE_WEB = 3,						// web登录
	E_SDK_LOGIN_TYPE_NETSDK = 4,					// netsdk登录
	E_SDK_LOGIN_TYPE_TOOL = 5,						// 设备管理工具登录
	E_SDK_LOGIN_TYPE_MOBILE = 6,					// 移动终端登录
	E_SDK_LOGIN_TYPE_LOCALSDK = 7,					// localsdk登录
}eLoginType;

// 设备的加密方式，暂只支持MD5加密
typedef enum E_SDK_ENCRYPT_TYPE {
	E_SDK_ENCRYPT_TYPE_NONE = 0,					// 无加密
	E_SDK_ENCRYPT_TYPE_MD5 = 1,						// MD5加密
}eEncryptType;

typedef enum E_SDK_PUSH_PICTURE_TYPE {
	E_PIC_TYPE_UNKNOWN = 0,
	E_PIC_TYPE_FACE_SMALL = 1,						// 人脸小图
	E_PIC_TYPE_FACE_BIG_BGP = 2,					// 背景大图
	E_PIC_TYPE_FACE_RECOGNITION = 3,				// 人脸识别(废弃)
	E_PIC_TYPE_DOOR_RECOGOITION = 4,				// 门禁机识别(废弃)
	E_PIC_TYPE_BODY = 5,							// 人形检测
	E_PIC_TYPE_PLATE_RECOGNITION = 6,				// 车牌识别
	E_PIC_TYPE_VEHICLE_RECOGNITION = 7,				// 汽车识别
	E_PIC_TYPE_CYCLE_RECOGNITION = 8,				// 非机动车
	E_PIC_TYPE_NR,
}ePushPictureType;

typedef struct S_SDK_IPADDRESS {
	char szIp[64];									// 可能是域名
}sIpAddress;

typedef struct S_SDK_SYSTEMTIME {
	uint year;										// 年。
	uint month;										// 月，January = 1, February = 2, and so on.
	uint day;										// 日。
	uint wday;										// 星期，Sunday = 0, Monday = 1, and so on.
	uint hour;										// 时。
	uint minute;									// 分。
	uint second;									// 秒。
	uint isdst;										// 夏令时标识。注：获取什么保存什么，不需要修改。
}sSystemTime;

// 时间段
typedef struct S_SDK_TIME_SECTION {
	bool bEnable;
	int nStartHour;
	int nStartMinute;
	int nStartSecond;
	int nEndHour;
	int nEndMinute;
	int nEndSecond;
}sTimeSection;

typedef struct S_SDK_DAY_SHEET {
	sTimeSection timeSection[8];					// 固定8个时间段
}sDaySheet;

typedef struct S_SDK_WORKSHEET_CONFIG {
	sDaySheet daySheet[7];							// 工作时间段，固定7个工作表 周日，周一，...周六
}sWorkSheetConfig;

typedef struct S_SDK_IDENTIFIER {
	uint nId;
	char szUuid[64];								// 云使用
}sIdentifier;

typedef struct S_SDK_POINT {
	int x;
	int y;
}sPoint;

typedef struct S_SDK_RECT {
	long left;
	long top;
	long right;
	long bottom;
}sRect;

typedef struct S_SDK_SIZE2I {
	int w;
	int h;
}sSize2i;

typedef struct S_SDK_RECT2I {
	int x;
	int y;
	int width;
	int height;
}sRect2i;

///////////////////本地配置相关结构体/////////////////////////////////
//字符串编码方式
typedef enum E_SDK_BYTE_ENCODE_TYPE {
	E_BYTE_ENCODE_ANSI = 1,
	E_BYTE_ENCODE_UNCOIDE = 2,
	E_BYTE_ENCODE_UTF8 = 3,
}eByteEncodeType;

typedef struct S_SDK_BYTE_ENCODE_CONFIG {
	eByteEncodeType in;								// 输入字符串编码格式
	eByteEncodeType out;							// 输出字符串编码格式
}sByteEncodeConfig;

typedef struct S_SDK_AV_PRIVATEHEAD_CONFIG {
	bool bNeedPrivateHead;							// 是否需要音视频私有协议头，默认为true
}sAVPrivateHeadConfig;

// 日志打印类型
typedef enum E_SDK_LOGGER_LEVEL_TYPE {
	E_LOGGER_LEVEL_TRACE,
	E_LOGGER_LEVEL_DEBUG,
	E_LOGGER_LEVEL_INFO,
	E_LOGGER_LEVEL_WARN,							// 警告
	E_LOGGER_LEVEL_ERROR,
	E_LOGGER_LEVEL_CRITICAL,
	E_LOGGER_LEVEL_OFF,
}eLoggerLevelType;

// 日志文件循环覆盖配置
typedef struct {
	int nFileMaxSize;								// 单个文件最大容量
	int nMaxFiles;									// 最大文件数
}sLogFileCoverageConfig;

// 日志文件配置
typedef struct {
	char szFilePath[256];							// 日志文件目录
	bool bCoverage;									// 是否循环覆盖，置false后每天更新一个log文件
	sLogFileCoverageConfig covCfg;					// 循环覆盖配置
}sLogFileConfig;

typedef struct S_SDK_LOGGER_CONFIG {
	eLoggerLevelType level;							// 日志打印等级
	bool bSaveToFile;								// 是否存储到文件
	sLogFileConfig file;
}sLoggerConfig;

//登录信息
typedef struct S_SDK_LOGIN_INFO {
	char szIp[64];
	int nPort;
	char szName[NET_MAX_NAME_PSW_LEN];
	char szPsw[NET_MAX_NAME_PSW_LEN];
	eLoginType loginType;
	eEncryptType encryptType;
	eConnectType connectType;
	bool bGb35114;
	/*S_SDK_LOGIN_INFO() {
		nPort = 51666;
		loginType = E_SDK_LOGIN_TYPE_WEB;
		encryptType = E_SDK_ENCRYPT_TYPE_MD5;
		connectType = E_SDK_CONNECT_TYPE_TCP;
	}*/
}sLoginInfo;

///////////////////云台管理相关结构体/////////////////////////////////
//云台控制参数
typedef enum E_SDK_PTZCMD_TYPE {					// 说明				配合参数					备注
	E_PTZ_CMD_UNKNOWN = 0,
	E_PTZ_CMD_LEN_INIT = 1,							// 镜头初始化		无						eOper：固定E_PTZ_OPER_TYPE_START
	E_PTZ_CMD_LIGHT = 2,							// 灯光				未启用
	E_PTZ_CMD_WIPER = 3,							// 雨刷				未启用
	E_PTZ_CMD_FAN = 4,								// 风扇				未启用
	E_PTZ_CMD_HEATER = 5,							// 加热器			未启用
	E_PTZ_CMD_AUX = 6,								// 辅助功能			未启用
	E_PTZ_CMD_ZOOM_TELE = 7,						// 变倍+				eOper					焦距变大，远景拉近图像变大
	E_PTZ_CMD_ZOOM_WIDE = 8,						// 变倍-				eOper					焦距变小，近景拉远图像变小
	E_PTZ_CMD_FOCUS_NEAR = 9,						// 聚焦+				eOper					焦点前调，近物清晰		
	E_PTZ_CMD_FOCUS_FAR = 10,						// 聚焦-				eOper					焦点后调，远物清晰		
	E_PTZ_CMD_IRIS_LARGE = 11,						// 光圈+				eOper					光圈扩大，图像变亮		
	E_PTZ_CMD_IRIS_SMALL = 12,						// 光圈-				eOper					光圈缩小，图像变暗		
	E_PTZ_CMD_UP = 13,								// 上仰				eOper +  nStep
	E_PTZ_CMD_DOWN = 14,							// 下俯				eOper +  nStep
	E_PTZ_CMD_LEFT = 15,							// 左转				eOper +  nStep
	E_PTZ_CMD_RIGHT = 16,							// 右转				eOper +  nStep
	E_PTZ_CMD_LEFTUP = 17,							// 左转和上仰		eOper +  nStep
	E_PTZ_CMD_LEFTDOWN = 18,						// 左转和下俯		eOper +  nStep
	E_PTZ_CMD_RIGHTUP = 19,							// 右转和上仰		eOper +  nStep
	E_PTZ_CMD_RIGHTDOWN = 20,						// 右转和下俯		eOper +  nStep
	E_PTZ_CMD_SET_PRESET = 21,						// 设置预置点		nPreset					eOper：固定E_PTZ_OPER_TYPE_START
	E_PTZ_CMD_CLEAR_PRESET = 22,					// 清除预置点		nPreset					eOper：固定E_PTZ_OPER_TYPE_START
	E_PTZ_CMD_GOTO_PRESET = 23,						// 转到预置点		nPreset					eOper：固定E_PTZ_OPER_TYPE_START
	E_PTZ_CMD_PATROL = 24,							// 巡航				eOper + nPatrol
	E_PTZ_CMD_MENU = 25,							// 菜单				无						eOper：固定E_PTZ_OPER_TYPE_START
	E_PTZ_CMD_AUXILIARY_FOCUSING = 26,				// 辅助聚焦			无
	E_PTZ_CMD_POSITION_3D = 27,						// 3d定位			position_3d				eOper：固定E_PTZ_OPER_TYPE_START
	E_PTZ_CMD_NR,
}ePTZCmdType;

typedef enum E_SDK_PTZOPER_TYPE {
	E_PTZ_OPER_TYPE_UNKNOWN = 0,
	E_PTZ_OPER_TYPE_START = 1,						// 操作开始
	E_PTZ_OPER_TYPE_STOP = 2,						// 操作结束
}ePTZOperType;

typedef struct S_SDK_PTZ_CONTROL_PARAM {
	int nChannel;
	ePTZCmdType eCmd;
	ePTZOperType eOper;
	union {
		struct {
			int nStep;								// 步长，配合E_PTZ_CMD_UP ~ E_PTZ_CMD_RIGHTDOWN
			int nPreset;							// 预置点编号
			int nPatrol;							// 巡航路径编号
		};
		sRect2i position_3d;						// 3d定位向量坐标
	};
}sPTZControlParam;

// 巡航路径
typedef struct S_SDK_PTZ_CONFIG_PATROL {
	struct sSequence {
		int nPreset;								// 预置点编号 [0,255]
		int nSpeed;									// 速度
		int nDelay;									// 时间(s) [3,120]
	}seq[32];
	int nSeqCount;
	//sSequence seq[32];							// 一系列巡航点
}sPTZConfigPatrol;

// 单个通道的巡航路径
typedef struct S_SDK_PTZ_CONFIG_PATROL_CHANNEL {
	int nPatrolCount;
	sPTZConfigPatrol patrol[8];						// 巡航路径
}sPTZConfigPatrolChannel;

// 所有通道的巡航路径
typedef struct S_SDK_PTZ_CONFIG_PATROL_CHANNELALL{
	int nChlCount;
	sPTZConfigPatrolChannel ch[NET_MAX_CHANNUM];	// 通道号
}sPTZConfigPatrolChannelAll;

/// 设备信息
typedef struct S_SDK_DEVICEINFO {
	char sSoftWareVersion[64];						// 软件版本信息
	char sHardWareVersion[64];						// 硬件版本信息
	char sEncryptVersion[64];						// 加密版本信息
	char szAiVersion[64];							// 算法版本信息
	char szBuildTime[32];							// 软件创建时间
	char sSerialNumber[64];							// 设备序列号
	int byChanNum;									// 视频输入通道数
	int iVideoOutChannel;							// 视频输出通道数
	int iAudioInChannel;							// 音频输入通道数
	int byAlarmInPortNum;							// 报警输入通道数
	int byAlarmOutPortNum;							// 报警输出通道数
	int iTalkInChannel;								// 对讲输入通道数
	int iTalkOutChannel;							// 对讲输出通道数
	int iDigChannel;								// 数字通道数
	eDeviceType deviceTye;							// 设备类型
	int nHwidinfoState;								// 0: 没烧加密（MAC）
	int nRemainLoginTimes;							// 当登陆失败原因为用户名密码错误时,剩余登陆次数
	int nRemainLockTime;							// 当登陆失败,用户解锁剩余时间（秒数）
	int status[29];
}sDeviceInfo, *LPS_SDK_DEVICEINFO;

// 登录安全配置
typedef struct S_SDK_LOGIN_SECURITY_CONFIG {
	bool nEnable;
	int nLoginTimes;								// 允许登录错误次数 [3,10]
	int nLockTime;									// 锁定时长(s) [300, 7200]
}sLoginSecurityConfig;

///////////////////用户帐号管理相关结构体/////////////////////////////////
typedef enum E_SDK_USERRIGHT_TYPE {
	E_SDK_USERRIGHT_TYPE_Monitor = 0,				// 预览
	E_SDK_USERRIGHT_TYPE_Playback = 1,				// 回放
	E_SDK_USERRIGHT_TYPE_Storage = 2,				// 存储
	E_SDK_USERRIGHT_TYPE_ConfigManager = 3,			// 配置
	E_SDK_USERRIGHT_TYPE_System = 4,				// 系统
	//E_SDK_USERRIGHT_TYPE_UserManager = 5,			// 用户管理
	E_SDK_USERRIGHT_TYPE_NR,
}eUserRightType;

typedef struct S_SDK_CONFIG_OPR_RIGHT {
	int rigthNum;
	eUserRightType type[E_SDK_USERRIGHT_TYPE_NR];
}sConfigOprRight;

typedef struct S_SDK_CONFIG_USER_INFO {
	sConfigOprRight rights;
	char Groupname[NET_MAX_NAME_PSW_LEN];
	char name[NET_MAX_NAME_PSW_LEN];
	char passWord[NET_MAX_NAME_PSW_LEN];
	char memo[NET_MAX_NAME_PSW_LEN];
}sConfigUserInfo;

typedef struct S_SDK_CONFIG_USER_GROUP_INFO {
	char name[NET_MAX_NAME_PSW_LEN];
	sConfigOprRight rights;
	char memo[NET_MAX_NAME_PSW_LEN];
}sConfigUserGroupInfo;

//用户信息配置结构
typedef struct S_SDK_USER_MANAGE_INFO {
	int groupNum;
	sConfigUserGroupInfo groupList[NET_MAX_GROUP_NUM];
	int userNum;
	sConfigUserInfo userList[NET_MAX_USER_NUM];
}sConfigUserManageInfo;

/// 修改用户密码请求
typedef struct S_SDK_CONFIG_MODIFY_PSW {
	char szUserName[NET_MAX_NAME_PSW_LEN];
	char szPassword[NET_MAX_NAME_PSW_LEN];
	char szNewPassword[NET_MAX_NAME_PSW_LEN];
	eEncryptType encryptType;
}sConfigModifyPsw;

/// 修改用户
typedef struct S_SDK_CONFIG_MODIFY_USER {
	char sUserName[NET_MAX_NAME_PSW_LEN];
	sConfigUserInfo userInfo;
}sConfigModifyUser;

/// 修改分组
typedef struct S_SDK_CONFIG_MODIFY_GROUP {
	char sGroupName[NET_MAX_NAME_PSW_LEN];
	sConfigUserGroupInfo groupInfo;
}sConfigModifyGroup;

///////////////////ONVIF用户帐号管理相关结构体/////////////////////////////////
typedef struct S_SDK_ONVIF_USER_INFO {
	char szUsername[32];
	char szPassword[32];
	char szGroup[32];
}sOnvifUserInfo;

typedef struct S_SDK_ONVIF_GROUP_INFO {
	char szName[32];
}sOnvifGroupInfo;

typedef struct S_SDK_ONVIF_ACCOUNT_INFO {
	int nUserNum;
	sOnvifUserInfo onvifUser[32];
	int nGroupNum;
	sOnvifGroupInfo onvifGroup[32];
}sOnvifAccountManageInfo;

typedef struct S_SDK_ONVIF_MODIFY_PASSWORD {
	char szUsername[32];
	char szOldPassword[32];
	char szNewPassword[32];
}sOnvifModifyPassword;

///////////////////网络配置相关结构体/////////////////////////////////
typedef struct S_SDK_IPv4Adress {
	bool bDHCP;
	char szIP[16];									//主机IP
	char szSubMask[16];								//子网掩码
	char szGateway[16];								//网关IP
	char szDns1[16];
	char szDns2[16];
}sIPv4Adress;

typedef struct S_SDK_IPv6Adress {
	bool bEnable;
	bool bDHCP;
	char szIP[64];									//主机IP
	int nSubNetPrefixLen;							//子网前缀长度
	char szGateway[64];								//网关IP
	char szLocal[64];
	char szDns1[16];
	char szDns2[16];
}sIPv6Adress;

typedef struct S_SDK_FILTER_CONFIG {
	eFilterType type;								// 是否开启
	sIpAddress BannedList[NET_MAX_FILTERIP_NUM];	// 黑名单列表
	sIpAddress TrustList[NET_MAX_FILTERIP_NUM];		// 白名单列表
}sNetIPFilterConfig;

typedef struct S_SDK_NET_INTERFACE {
	char szName[64];
	char szMac[NET_MAX_MAC_LEN];
	sIPv4Adress ipv4;
	sIPv6Adress ipv6;
	uint nMtu;
}sNetInterface;

typedef struct S_SDK_NET_INTERFACE_LIST {
	sNetInterface interFace[4];
	char szDefaultName[64];
	bool bAutoDns;									// 自动获取DNS
	char szDns1[16];
	char szDns2[16];
	char szDns1v6[64];
	char szDns2v6[64];
}sNetInterfaceList;

typedef struct S_SDK_NETSERVICE_CONFIG {
	int nTcpPort;
	int nUdpPort;
	int nMaxConnect;
	bool bDisable;
}sNetserviceConfig;

typedef struct S_SDK_WEW_CONFIG{
	bool bHttpEnable;
	int nHttpPort;
	bool bHttpsEnable;
	int nHttpsPort;
}sWebConfig;

typedef struct S_SDK_RTSP_CONFIG{
	bool bEnable;
	int nPort;
	int nMaxConnect;
}sRtspConfig;

typedef struct S_SDK_ONVIF_CONFIG{
	bool bEnable;									// 使能
	bool bAuth;										// 鉴权
	bool bDisableSetTime;							// 是否取消设置同步时间
	bool bDisableSetMotion;							// 是否取消设置移动侦测
	char reserve[16];
}sOnvifConfig;

typedef struct S_SDK_CLOUD_SERVER_CONFIG{
	bool bEnable;
	sIpAddress address;
	int nPort;
}sCloudServerConfig;

typedef enum {
	E_CONNECT_TYPE_UDP = 0,
	E_CONNECT_TYPE_TCP = 1,
}eGb28181ConnectType;

typedef struct S_SDK_GB28181_CONFIG {
	bool bEnable;
	char szServerId[NET_MAX_ADDRESS_LEN];
	char szServerDomain[NET_MAX_ADDRESS_LEN];
	char szServerIp[NET_MAX_ADDRESS_LEN];
	int  nServerPort;
	int  nLocalPort;
	eGb28181ConnectType nConnectType;
	char szDeviceName[NET_MAX_NAME_PSW_LEN];
	char szAuthId[NET_MAX_NAME_PSW_LEN];
	char szPasswd[NET_MAX_NAME_PSW_LEN];
	int  nExpiration;
	bool bRegisterState;
	int  nHeartbeatInterval;
	int  nHeartbeatCount;
	char szAlarmInId[2][NET_MAX_ADDRESS_LEN];
	char szVideoChannelId[1][NET_MAX_ADDRESS_LEN];
	char szAudioOutId[1][NET_MAX_ADDRESS_LEN];
	bool bEnable35114;								// 是否使能35114
	bool bSdcardState;								// 加密TF卡状态, true正常, false异常
	eStreamType streamType;							// 码流类型
	bool bEnable4g;									// 是否4G相机
	char szLteIp[NET_MAX_ADDRESS_LEN];				// 4G拨号ip
	bool bTcpBroadcast;								// 是否启用TCP主动拉流模式语音广播
}sGb28181Config;

typedef struct S_SDK_PPPOE_CONFIG {
	bool bEnable;
	char szIfname[NET_MAX_NAME_PSW_LEN];
	char szUsername[NET_MAX_NAME_PSW_LEN];
	char szAddress[NET_MAX_ADDRESS_LEN];
	char szPasswd[NET_MAX_NAME_PSW_LEN];
}sPppoeConfig;

typedef enum E_SDK_DIR_DEPTH {
	E_SDK_DIR_DEPTH_ROOT = 0,						// 保存在根目录
	E_SDK_DIR_DEPTH_FIRST = 1,						// 使用一级目录
	E_SDK_DIR_DEPTH_SECOND = 2,						// 使用二级目录
}eDirDepth;

// 一级目录名字规则枚举
typedef enum E_SDK_FIRSTDIR_TYPE {
	E_SDK_FIRSTDIR_TYPE_DEVNAME = 0,				// 设备名
	E_SDK_FIRSTDIR_TYPE_DEVIP = 1,					// 设备IP
	E_SDK_FIRSTDIR_TYPE_DEVSN = 2,					// 设备序列号
	E_SDK_FIRSTDIR_TYPE_CUSTOM = 3,					// 自定义
}eFirstDirType;

// 二级目录名字规则枚举
typedef enum E_SDK_SECONDDIR_TYPE {
	E_SDK_SECONDDIR_TYPE_CHNNAME = 0,				// 通道名
	E_SDK_SECONDDIR_TYPE_CHNID = 1,					// 通道号
	E_SDK_SECONDDIR_TYPE_CUSTOM = 2,				// 自定义
}eSecondDirType;

// ftp上传目录规则
typedef struct E_SDK_FTP_UPLOAD_DIR {
	eDirDepth dirDepth;
	eFirstDirType firstDir;
	char szFirstCustom[256];						// 一级目录选择自定义时的名字
	eSecondDirType secondDir;
	char szSecondCustom[256];						// 二级目录选择自定义时的名字
}sFtpUploadDir;

typedef struct S_SDK_FTPSERVER_CONFIG {
	bool bEnable;
	sIpAddress address;
	int nPort;
	char szUserName[NET_MAX_NAME_PSW_LEN];
	char szPassword[NET_MAX_NAME_PSW_LEN];
	char szPath[256];
	bool bAnonymity;
	int nMaxLen;
	sFtpUploadDir uploadDir;
}sFtpServerConfig;

typedef struct S_SDK_PINGTEST_CONFIG {
	sIpAddress ipaddr;
	int nCount;
	int nTimeout;
}sPingTestConfig;

typedef enum {
	E_PS_FTP_DEPTH_ROOT = 0,						// 保存在根目录
	E_PS_FTP_DEPTH_FIRST = 1,						// 使用一级目录
	E_PS_FTP_DEPTH_SECOND = 2,						// 使用二级目录
	E_PS_FTP_DEPTH_THIRD = 3,						// 使用三级目录
}ePsFtpPathDepth;

typedef enum {
	E_PS_FIRST_CATALOG_DEVIP = 0,					// 设备IP
	E_PS_FIRST_CATALOG_DEVSN = 1,					// 设备序列号
	E_PS_FIRST_CATALOG_CUSTOM = 2,					// 自定义
}ePsFtpFirstCatalogRule;

typedef enum {
	E_PS_SECOND_CATALOG_YMD = 0,					// 时间（年月日）
	E_PS_SECOND_CATALOG_CUSTOM = 1,					// 自定义
}ePsFtpSecondCatalogRule;

typedef enum {
	E_PS_THIRD_CATALOG_CUSTOM = 0,					// 自定义
}ePsFtpThirdCatalogRule;

typedef struct S_SDK_FTP_UPLOAD_DIR_PS {
	ePsFtpPathDepth depth;
	ePsFtpFirstCatalogRule firstRule;
	char szFirstName[64];							// 自定义目录（自定义模式时不能为空）
	ePsFtpSecondCatalogRule secondRule;
	char szSecondName[64];							// 自定义目录（自定义模式时不能为空）
	ePsFtpThirdCatalogRule thirdRule;
	char szThirdName[64];							// 自定义目录（自定义模式时不能为空）
}sPsFtpUploadDir;

typedef struct S_SDK_PS_FTPSERVER_CONFIG {
	bool bEnable;
	sIpAddress address;
	int nPort;
	char szUserName[NET_MAX_NAME_PSW_LEN];
	char szPassword[NET_MAX_NAME_PSW_LEN];
	//char szPath[256];
	sPsFtpUploadDir uploadDir;
	bool bUploadBg;									// 是否上传背景图
}sPSFtpServerConfig;

typedef struct S_SDK_NTPSERVER_CONFIG {
	bool bEnable;
	bool bAuto;
	sIpAddress address;
	int nPort;
	int nPeriod;
}sNtpServerConfig;

typedef enum {
	E_SDK_ENCRYPT_TYPE_Common = 0,
	E_SDK_ENCRYPT_TYPE_SSL = 1,
	E_SDK_ENCRYPT_TYPE_TLS = 2,
}eSmtpServerEncryptType;

typedef struct S_SDK_SMTPSERVER_CONFIG {
	bool bEnable;
	eSmtpServerEncryptType type;
	sIpAddress address;
	int nPort;
	char szUserName[NET_MAX_NAME_PSW_LEN];
	char szPsw[NET_MAX_NAME_PSW_LEN];
	char szSender[NET_MAX_ADDRESS_LEN];
	char szReceivers[NET_MAX_EMAIL_RECIEVERS][NET_MAX_ADDRESS_LEN];
	char szSubject[NET_MAX_EMAIL_TITLE_LEN];
}sSmtpServerConfig;

typedef enum {
	E_TYPE_AUTO = 0,
	E_TYPE_1 = 1,
	E_TYPE_2 = 2,
	E_TYPE_3 = 3,
	E_TYPE_4 = 4,
	E_TYPE_5 = 5,
	E_TYPE_6 = 6,
	E_TYPE_7 = 7,
	E_TYPE_8 = 8,
	E_TYPE_9 = 9,
	E_TYPE_10 = 10,
	E_TYPE_11 = 11,
	E_TYPE_12 = 12,
	E_TYPE_13 = 13,
	E_TYPE_14 = 14,
}eNetWifiChannelType;

typedef enum {
	E_MODE_INFRA = 0,								// 基础网 sta->ap
	E_MODE_ADHOC = 1,								// 自组网 sta<->sta
}eNetWifiTopologyMode;

typedef enum {
	E_MODE_NONE = 0,
	E_MODE_WEP_OPEN = 1,
	E_MODE_WEP_SHARED = 2,
	E_MODE_WPA_PSK = 3,
	E_MODE_WPA2_PSK = 4,
	E_MODE_WPA_WPA2_PSK = 5,
	E_MODE_WAPI_PSK = 6,
	E_MODE_WPA2_802_1X = 7,
	E_MODE_WPA_WPA2_802_1X = 8,
}eNetWifiSecurityMode;

typedef enum {
	E_CIPHER_MODE_NONE = 0,
	E_CIPHER_MODE_TKIP = 1,
	E_CIPHER_MODE_AES = 2,
	E_CIPHER_MODE_TKIPAES = 3,
	E_CIPHER_MODE_SMS4 = 4,
}eNetWifiCipherMode;

typedef enum {
	E_TYPE_NOT_CONNECT = 0,					// 未连接
	E_TYPE_CONNECT = 1,						// 已连接
	E_TYPE_WRONG_KEY = 2,					// 密码错误(只有上次输入密码的Wifi才会有这个错误)
	E_TYPE_TIMEOUT = 3,						// 连接超时
}eNetWifiStatusType;

typedef struct S_SDK_NETWIFI_INFO {
	char szSsid[64];								// 无线网络ID
	char szBssid[NET_MAX_MAC_LEN];					// mac
	int nRssi;										// 信号强度，单位dbm
	eNetWifiChannelType eChannel;					// 信道
	eNetWifiTopologyMode eTopology;					// 拓扑模式
	eNetWifiSecurityMode eSecurity;					// 认证模式
	eNetWifiCipherMode eCipher;						// 加密类型
	eNetWifiStatusType eStatus;						// 连接状态
}sNetWifiInfo;

typedef struct S_SDK_NETWIFI_SEARCH_LIST {
	int nCount;
	sNetWifiInfo wifi[32];							// [0,31]
}sNetWifiSearchList;

typedef struct S_SDK_NET_WIFI_CONFIG {
	bool bEnable;									// 使能
	char szSsid[64];								// 无线网络ID
	char szPsw[NET_MAX_NAME_PSW_LEN];				// 密码（不得低于8位）
}sNetWifiConfig;

typedef struct S_SDK_NET_INTELLIF_HTTP_CONFIG {
	bool bEnable;									// 使能
	char szUrl[64];
	char szCameraCode[64];
	char szNodeId[64];
	char szKey[NET_MAX_NAME_PSW_LEN];
}sNetIntellifHttpConfig;

typedef struct S_SDK_NET_SAFESOFT_HTTP_CONFIG {
	bool bEnable;									// 使能
	char szUrl[64];
	char szCameraId[64];
	char szKey[NET_MAX_NAME_PSW_LEN];
}sNetSafeSoftHttpConfig;

typedef struct S_SDK_NET_BCW_HTTP_CONFIG {
	bool bEnable;									// 使能
	char szUrl[64];
	char szCameraId[64];
	char szKey[NET_MAX_NAME_PSW_LEN];
}sNetBcwHttpConfig;

typedef struct S_SDK_NET_SUPEREYE_CLIENT_CONFIG {
	bool bEnable;									// 使能
	char szUrl[256];
	char szAppId[64];
	char szAppKey[64];
}sNetSupereyeClientCfg;

typedef struct S_SDK_NET_GD_SMARTEYE_CONFIG {
	bool bEnable;									// 使能
	char szTokenUrl[256];							// 获取token地址
	char szKeepaliveUrl[256];						// 心跳地址
	char szReportUrl[256];							// 配置上报地址
	int nTokenCycle;								// 获取token间隔
	int nKeepaliveCycle;							// 心跳间隔
	char szTokenKey[256];							// tokenkey
}sNetGdSmarteyeCfg;

// 贝特定制
typedef struct S_SDK_NET_BEITE_MQTT {
	bool bStatus;									// 在线状态
	sIpAddress address;								// 服务器ip
	int nPort;										// 服务器端口
	char szClientId[64];							// Client ID
	char szUsername[NET_MAX_NAME_PSW_LEN];			// 用户名
	char szPassword[NET_MAX_NAME_PSW_LEN];			// 密码
	char szTopic[128];								// 推送主题
}sNetBeiteMqttCfg;

typedef struct S_SDK_NET_BEITE_ALIOSS {
	bool bStatus;									// 在线状态
	char szEndpoint[NET_MAX_ADDRESS_LEN];			// 访问域名
	char szAccessKeyId[NET_MAX_NAME_PSW_LEN];		// 访问密钥id
	char szAccessKeySecret[NET_MAX_NAME_PSW_LEN];	// 访问密钥secret
	char szBucket[1024];							// 存储空间
}sNetBeiteAliOssCfg;

typedef struct S_SDK_NET_Beite_Client {
	bool bEnable;									// 是否启用
	sNetBeiteMqttCfg mqtt;							// mqtt相关配置
	sNetBeiteAliOssCfg aliOss;						// 阿里云OSS相关配置
}sNetBeiteClientCfg;

typedef struct S_SDK_NET_XUZN_SERVER_CONFIG {
	bool bEnable;									// 是否启用
	bool bStatus;									// 在线状态
	sIpAddress url;									// 服务器地址
	int nKeepaliveCycle;							// 心跳周期
	char reserve[16];
}sNetXuznServerCfg;

typedef struct S_SDK_INTERSTELL_OSD_PARAM_SERVER {
	bool bEnable;									// 是否启用
	sIpAddress url;									// 请求地址
	int nCycle;										// 请求周期
}sInterstellOsdParamServer;

// 串口配置
typedef enum E_SDK_SERIAL_TYPE {
	E_SERIAL_TYPE_UNKNOW = 0,
	E_SERIAL_TYPE_TTL = 1,
	E_SERIAL_TYPE_RS232 = 2,
	E_SERIAL_TYPE_RS485 = 3,
	E_SERIAL_TYPE_GNSS = 4,
	E_SERIAL_TYPE_AF = 5,
	E_SERIAL_TYPE_PTZ = 6,
	E_SERIAL_TYPE_TMPDEV = 7,
	E_SERIAL_TYPE_LED = 8,
	E_SERIAL_TYPE_AFV2 = 9,
}eSerialType;

typedef enum {
	E_SERIAL_STOP_BITS1 = 0,					// 停止位1
	E_SERIAL_STOP_BITS1_5 = 1,					// 停止位1.5
	E_SERIAL_STOP_BITS2 = 2,					// 停止位2
}eSerialStopBits;

typedef enum {
	E_SERIAL_PARITY_NONE = 0,
	E_SERIAL_PARITY_ODD = 1,					// 奇校验
	E_SERIAL_PARITY_EVEN = 2,					// 偶校验
}eSerialParityType;

typedef enum {
	E_SERIAL_FLOW_CTRL_NONE = 0,
	E_SERIAL_FLOW_CTRL_SOFTWARE = 1,
	E_SERIAL_FLOW_CTRL_HARDWARE = 2,
}eSerialFlowCtrlType;

typedef enum {
	E_SERIAL_WORK_TRANSPARENT = 0,				// 透明传输模式
	E_SERIAL_WORK_PROTOCOL = 1,					// 协议传输模式
}eSerialWorkMode;

typedef enum {
	E_SERIAL_CONTROL_PORTOCOL_PELCO_D = 0,
}eSerialControlProtocolType;

typedef struct S_SDK_SERIAL_PARAM {
	bool bSupport;									// 是否支持(只读)
	int nId;										// 串口id(只读)
	eSerialType serialType;							// 串口类型(只读)
	int nBaudRate;									// 波特率
	int nDataBits;									// 数据位
	eSerialStopBits stopBits;						// 停止位
	eSerialParityType parityType;					// 奇偶校验类型
	eSerialFlowCtrlType flowCtrlType;				// 流控类型
	eSerialWorkMode workMode;						// 工作模式
	eSerialControlProtocolType ctrlProtoType;		// 协议类型
	int nControlAddress;							// 协议地址
	char szReserve[16];
}sSerialParam;

typedef struct S_SDK_SERIAL_LIST {
	sSerialParam serialParam[16];
}sSerialList;

// 云固件信息
typedef enum E_SDK_CLOUD_UPGRADE_INFO_RET {
	E_UPGRADE_INFO_UNKNOWN = 0,
	E_UPGRADE_INFO_SUCCESS = 1,
	E_UPGRADE_INFO_OFFLINE = 2,
}eCloudUpgradeInfoRet;

typedef struct S_SDK_NET_CLOUD_UPGRADE_INFO {
	eCloudUpgradeInfoRet retValue;
	bool bAvailable;
	char szVersion[64];
	char szLog[1024];
}sNetCloudUpgradeInfo;

typedef enum {
	E_CLOUD_UPGRADE_AUTO_CLOSE = 0,					// 自动升级关闭
	E_CLOUD_UPGRADE_AUTO_NEW = 1,					// 自动升级新版本
	E_CLOUD_UPGRADE_AUTO_MAJOR = 2,					// 自动升级重要版本
}eCloudUpgradeAutoType;

typedef struct S_SDK_CLOUD_UPGRADE_RULE_CONFIG {
	bool bEnable;
	sIpAddress address;								// 服务器地址
	eCloudUpgradeAutoType type;						// 自动升级类型
	sSystemTime startTime;							// 自动升级开始时间(时分秒有效)
	sSystemTime stopTime;							// 自动升级结束时间(时分秒有效)
}sCloudUpgradeRuleConfig;

// 人脸抓拍算法参数配置
enum E_SDK_INTELLIGENCE_OBJECT_TYPE_PS {
	E_INTELLIGENCE_OBJECT_UNKNOWN = 0x0,
	E_INTELLIGENCE_OBJECT_FACE = 0x1,				// 人脸
	E_INTELLIGENCE_OBJECT_HUMAN = 0x2,				// 人体
	E_INTELLIGENCE_OBJECT_VEHICLE = 0x4,			// 机动车
	E_INTELLIGENCE_OBJECT_NONMOTOR = 0x8,			// 非机动车
};

typedef enum E_SDK_INTELLIGENCE_CAPTURE_MODE_PS {
	E_INTELLIGENCE_CAPTURE_UNKNOWN = 0,
	E_INTELLIGENCE_CAPTURE_OPTIMAL = 1,				// 最优抓拍模式
	E_INTELLIGENCE_CAPTURE_FAST = 2,				// 最快抓拍模式
	E_INTELLIGENCE_CAPTURE_INTERVAL = 3,			// 间隔抓拍模式
}ePsIntelligenceCaptureMode;

typedef enum E_SDK_INTELLIGENCE_PIC_LEVEL_PS {
	E_INTELLIGENCE_PIC_LEVEL_UNKNOWN = 0,
	E_INTELLIGENCE_PIC_LEVEL_HIGH = 1,				// 高
	E_INTELLIGENCE_PIC_LEVEL_NORMAL = 2,			// 中
	E_INTELLIGENCE_PIC_LEVEL_LOW = 3,				// 低
}ePsPicLevel;

typedef struct S_SDK_INTELLIGENCE_MINSIZE_PS {
	int nFace;										// [40,1080]
	int nHuman;										// [32,1080]
	int nVehicle;									// [40,1080]
	int nNonMotor;									// [32,1080]
}sPsObjectMinSize;

typedef enum S_SDK_INTELLIGENCE_BOXCOLOR_TYPE_PS {
	E_PS_INTELLIGENCE_BOX_COLOR_UNKNOWN = 0,
	E_PS_INTELLIGENCE_BOX_COLOR_GREEN = 1,			// 绿色
	E_PS_INTELLIGENCE_BOX_COLOR_RED = 2,			// 红色
	E_PS_INTELLIGENCE_BOX_COLOR_BLUE = 3,			// 蓝色
	E_PS_INTELLIGENCE_BOX_COLOR_PURPLE = 4,			// 紫色
	E_PS_INTELLIGENCE_BOX_COLOR_DARKGREEN = 5,		// 暗绿色
	E_PS_INTELLIGENCE_BOX_COLOR_YELLOW = 6,			// 黄色
	E_PS_INTELLIGENCE_BOX_COLOR_LIGHTBLUE = 7,		// 亮蓝色
	E_PS_INTELLIGENCE_BOX_COLOR_LIGHTPURPLE = 8,	// 亮紫
	E_PS_INTELLIGENCE_BOX_COLOR_DARKBLACK = 9,		// 暗黑色
	E_PS_INTELLIGENCE_BOX_COLOR_GRAY = 10,			// 灰色
	E_PS_INTELLIGENCE_BOX_COLOR_WHITE = 11,			// 白色
}ePsBoxColorType;

typedef struct S_SDK_INTELLIGENCE_BOX_COLOR_PS {
	ePsBoxColorType face;
	ePsBoxColorType human;
	ePsBoxColorType vehicle;
	ePsBoxColorType nonMotor;
}sPsBoxColor;

typedef struct S_SDK_INTELLIGENCE_PARAM_PS {
	uint nBoxMask;									// 显示框掩码，见枚举E_SDK_INTELLIGENCE_OBJECT_TYPE_PS
	ePsIntelligenceCaptureMode mode;				// 抓拍模式
	uint nPloyMask;									// 抓拍策略，见枚举E_SDK_INTELLIGENCE_OBJECT_TYPE_PS
	ePsPicLevel picLevel;							// 抓拍图片质量
	sPsObjectMinSize objectSize;					// 抓拍最小设置
	sPsBoxColor boxColor;							// 目标框的颜色
	sPoint roi[8];									// 检测区域(暂只支持矩形), 坐标相对于[0,8192]
	int nModeFastPeriod;							// 最快抓拍模式的时间间隔(s) [1,10]
	int nModeIntervalPeriod;						// 间隔抓拍模式的时间间隔(s) [1,10]
}sPsIntelligenceParam;

// 移动网卡(3G 4G 5G)
typedef enum {
	E_WWAN_STATUS_UNSUPPORT = 0,					// 功能不支持
	E_WWAN_STATUS_INIT_FAIL = 1,					// 初始化失败
	E_WWAN_STATUS_SIM_UNAVALIABLE = 2,				// SIM卡不存在
	E_WWAN_STATUS_OFFLINE = 3,						// 离线
	E_WWAN_STATUS_ONLINE = 4,						// 在线
	E_WWAN_STATUS_CARD_LOCK = 5,					// SIM卡被锁定
}eNetWwanStatus;

typedef struct S_SDK_NET_WWAN_CONFIG {
	bool bEnable;
	eNetWwanStatus status;							// 状态
	sIpAddress address;								// 连接成功之后IP地址
}sNetWwanConfig;

/*移动网卡(3G 4G 5G) V2*/
//状态参数
typedef struct S_SDK_WWAN_STATUS_V2 {
	eNetWwanStatus status;							// 模块状态
	int nSignal;									// 信号强度
	char szAddress[64];								// 拨号获取的IP地址
	char szNetworkMode[64];							// 当前网络模式，具体的无线接入技术名称
	char szNetworkOperator[64];						// 当前网络运营商
	uint64 nImei;									// 模块imei
}sWwanStatusV2;
//配置参数
typedef enum {
	E_WWAN_V2_PREFER_4G = 0,						// 4G优先
	E_WWAN_V2_PREFER_3G = 1,						// 3G优先
	E_WWAN_V2_ONLY_4G	= 2,						// 仅4G
	E_WWAN_V2_ONLY_3G	= 3,						// 仅3G
	E_WWAN_V2_ONLY_2G	= 4,						// 仅2G
}eWwanPreferType;

typedef enum {
	E_WWAN_V2_AUTO	= 0,							// 自动
	E_WWAN_V2_PAP	= 0,							// PAP
	E_WWAN_V2_CHAP	= 0,							// CHAP
}eWwanAuthenticationType;

typedef struct S_SDK_WWAN_CONFIG_PARAM_V2 {
	bool bEnable;									// 启用拨号
	eWwanPreferType ePreferred;						// 首选网络模式，暂不支持需屏蔽
	eWwanAuthenticationType eAuthType;				// 认证方式
	char szApn[64];									// APN
	char szDialNumber[64];							// 接入号，暂不支持需屏蔽
	char szUsername[64];							// 拨号用户名
	char szPassword[64];							// 拨号密码
}sWwanConfigParamV2;

typedef struct S_SDK_WWAN_CONFIG_V2 {
	char szIfname[64];								// 网卡名
	sWwanStatusV2 status;							// 状态参数
	sWwanConfigParamV2 config;						// 配置参数
}sWwanConfigV2;

typedef struct S_SDK_WWAN_CONFIG_ALL_V2 {
	int nCount;										// 能力级支持的个数
	sWwanConfigV2 wwanV2[4];
}sWwanConfigAllV2;

typedef struct {
	bool bSupport;
	char szIfname[64];								// 网卡名
	int nOrder;										// 优先级[1,16]，数字越小优先级越高，1为最高优先级
}sSignalNetInterfaceInfo;

// 网卡优先级，动态数组最大16
typedef struct S_SDK_NET_INTERFACE_ORDER {
	int nCount;
	sSignalNetInterfaceInfo ni[16];
}sNetInterfaceOrder;

// 端口映射
typedef enum {
	E_PORT_MAPPING_TYPE_TCP = 0,
	E_PORT_MAPPING_TYPE_UDP = 1,
}ePortMappingProtocolType;

typedef struct S_SDK_NET_PORT_MAPPING {
	bool bEnable;									// 是否使能
	ePortMappingProtocolType protocolType;			// 端口类型
	int nExternalPort;								// 外部端口
	int nInternalPort;								// 内部端口
	char szInternalIp[64];							// 内部ip
	char szIfanme[64];								// 网卡名	从sNetPortMappingList::szIfanmes中选择
}sNetPortMapping;

typedef struct S_SDK_NET_PortMappingList {
	int nCount;										// 映射信息个数
	sNetPortMapping mapping[16];					// 映射信息
	char szIfanmes[16][64];							// 网卡列表名
}sNetPortMappingList;

// GA1400客户端配置
typedef struct S_SDK_NET_GA1400_CLIENT_CONFIG {
	bool bEnable;									// 使能
	sIpAddress serverIp;							// 1400服务器ip
	int nServerPort;								// 1400服务器端口
	char szDeviceId[NET_MAX_ADDRESS_LEN];			// 设备id
	char szUserName[NET_MAX_NAME_PSW_LEN];			// 用户名
	char szPsw[NET_MAX_NAME_PSW_LEN];				// 密码
	int  nHeartbeatInterval;						// 心跳周期
	int  nHeartbeatCount;							// 心跳超时次数
	bool bOnline;									// 注册状态是否在线, true在线, false离线
}sNetGa1400ClientConfig;

///////////////////搜索相关结构体/////////////////////////////////
typedef struct S_SDK_SEARCHDEVICE_CONFIG {
	sNetInterface interFace;
	char szDefaultName[64];
	sNetserviceConfig netservice;
	sWebConfig web;
	char szBuildTime[32];
	char szSerialNumber[32];
	uint nAnalogChannel;
	uint nDigitalChannel;
	char szSoftWareVersion[64];						// 软件版本信息
	char szHardWareVersion[64];						// 硬件版本信息
	char szAiVersion[64];							// 算法版本信息
	int  nHwidinfoState;
}sSearchDeviceConfig;

typedef struct S_SDK_SEARCHDEVICE_CONFIG_ALL {
	uint nConfigNum;
	sSearchDeviceConfig *pConfig;
}sSearchDeviceConfigAll;

// 跨网段修改IP
typedef struct S_SDK_MODIFYIP_OVERNET {
	sSearchDeviceConfig devCfg;
	bool bForever;
	char szUserName[NET_MAX_NAME_PSW_LEN];
	char szPassword[NET_MAX_NAME_PSW_LEN];
	char szPcMac[NET_MAX_MAC_LEN];					//PC Mac， 不需要输入，NetSdk自动填充
	eEncryptType encryptType;
}sModifyIpOverNet;

// 跨网段恢复默认
// 获取密文
typedef struct S_SDK_SEARCHID {
	char szPcMac[NET_MAX_MAC_LEN];					//PC Mac， 不需要输入，NetSdk自动填充
	char szDevMac[NET_MAX_MAC_LEN];
}sSearchId;

typedef struct S_SDK_EXPORT_KEY {
	sSearchId id;									//校验参数 输入
	int nSize;
	char szKey[256];								//密文内容 输出
}sExportKey;

// 发送密钥
typedef struct S_SDK_IMPORT_KEY {
	sSearchId id;									//校验参数 输入
	int nSize;
	char szKey[256];								//密钥内容 输入
}sImportKey;

typedef struct S_SDK_PLAYINFO {
	int nChannel;									//通道号
	eStreamType nStream;
	//int nMode;									//0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-音视频分开(TCP)
}sPlayInfo,*lpsPlayInfo;

typedef struct S_SDK_START_TALK_INFO{
	int nChannel;
	eStreamType stream;								// 码流类型，目前只支持主码流
}sStartTalkInfo;

typedef enum E_SDK_EVENT_CODE_TYPES {
	E_SDK_EVENT_CODE_Unknown = 0,
	E_SDK_EVENT_CODE_ALARMIN = 1,					// 报警输入
	E_SDK_EVENT_CODE_MOTION = 2,					// 移动侦测
	E_SDK_EVENT_CODE_BLIND = 3,						// 视频遮挡
	E_SDK_EVENT_CODE_CROSS_LINE = 4,				// 绊线入侵
	E_SDK_EVENT_CODE_CROSS_REGION = 5,				// 区域入侵
	E_SDK_EVENT_CODE_SAFE_HELMET = 6,				// 未戴安全帽
	E_SDK_EVENT_CODE_ILLEGAL_PARKING = 7,			// 车辆违停
	E_SDK_EVENT_CODE_HUMAN = 8,						// 人形侦测
	E_SDK_EVENT_CODE_AUDIO_ANOMALY = 9,				// 音频输入异常
	E_SDK_EVENT_CODE_AUDIO_MUTATION = 10,			// 声强突变
	E_SDK_EVENT_CODE_RESPIRATOR = 11,				// 未戴口罩
}eEventCodeTypes;

///////////////////////////////////////////////////////////////////////////////
// 本地&网络事件通知
///////////////////////////////////////////////////////////////////////////////
typedef struct S_SDK_INTRUSION_DETECT_EXTRA {
	char szRuleName[64];
}sIntrusionExtra;

typedef enum E_SDK_EVENT_ACTION {
	E_SDK_EVENT_ACTION_START = 0,					// 事件开始
	E_SDK_EVENT_ACTION_STOP = 1,					// 事件结束
	E_SDK_EVENT_ACTION_CONFIG = 2,					// 事件配置变化，不作为事件响应参数
	E_SDK_EVENT_ACTION_LATCH = 3,					// 事件延时结束，不作为事件触发参数
	E_SDK_EVENT_ACTION_PULSE = 4,					// 脉冲事件，没有起始和结束
}eEventAction;

//报警信息
typedef struct S_SDK_ALARM_INFO {
	int nChannel;
	eEventCodeTypes event;
	eEventAction action;
	sSystemTime time;
	union {
		sIntrusionExtra intrusion;
		char szReserve[512];
	};
}sAlarmInfo;

// 验证类型
typedef enum E_VERIFICATION_TYPE {
	E_VERIFICATION_UNKNOWN = 0,
	E_VERIFICATION_FACE = 1,						// 人脸
	E_VERIFICATION_FACE_OR_CARD = 2,				// 人脸或刷卡
	E_VERIFICATION_FACE_AND_CARD = 3,				// 人脸和刷卡
	E_VERIFICATION_FACE_AND_PWD = 4,				// 人脸和密码
	E_VERIFICATION_FACE_OR_QRCODE = 5,				// 人脸或二维码
	E_VERIFICATION_FACE_OR_OTHER = 6,				// 人脸或其它
	E_VERIFICATION_CARD_AND_FACE = 7,				// 刷卡和人脸
	E_VERIFICATION_FACE_AND_TEMP = 101,				// 比对模式的人脸和温度
	E_VERIFICATION_ANYFACE_AND_TEMP = 102,			// 畅通模式的人脸和温度
}sPassedEventLog_eVerificationType;

/**********************************检测事件****************************************/
typedef struct S_SDK_FACE_DETECT_EVENT {
	int nLeft;										// 人脸框左边
	int nTop;										// 人脸框上边
	int nRight;										// 人脸框右边
	int nBottom;									// 人脸框下边
}sFaceDetectEvent;

// 设备状态
typedef enum {
	E_TYPE_UNKNOW = 0,
	E_TYPE_PERSON_COUNT = 1,						// 底库人脸数量
	E_TYPE_WIFI_SIGNAL = 2,							// WIFI信号强度
	E_TYPE_COMPANY = 3,								// 公司名
	E_TYPE_PLACE = 4,								// 部署点位
	E_TYPE_TIME_ZONE = 5,							// 时区
	E_TYPE_CLOSE_ALGORITHM = 6,						// 抽特征时，是否关闭算法
	E_TYPE_SCREENSAVER = 7,							// 屏保状态
	E_TYPE_WWAN_SIGNAL = 8,							// 4g信号强度
	E_TYPE_WIRED_NETWORK = 9,						// 是否连接有线网络
	E_TYPE_INTERNET = 10,							// 是否连通外网
	E_TYPE_MOUNT_USB = 11,							// 是否挂载U盘
	E_TYPE_STATE_CLOUD = 12,						// 是否连通云平台	
	E_TYPE_VERIFICATION = 13,						// 验证方式
	E_TYPE_CONFIG_CHANGED = 14,						// 配置改变
	E_TYPE_WIFI_CONN_STATUS = 15,					// wifi连接状态发生改变
	E_TYPE_IMPORT_FAIL_COUNT = 16,					// 云下发导入失败人数
	E_TYPE_FACE_DETECT_EVENT = 17,					// 人脸检测事件上报
	E_TYPE_IS_UPGRADING = 18,						// 开始升级
}eUploadInfoType;

typedef struct S_SDK_UPLOAD_INFO {
	eUploadInfoType type;
	union {
		int nPersonCount;								// 数据库中人数
		int nWifiSignal;								// WIFI信号强度
		char szCompanyName[64];							// 公司名称
		char szLocation[64];							// 部署地点
		int nMinutesWest;								// 和UTC时间的差值，单位分钟，可以为负
		bool bCloseAlgorithm;							// 抽特征时，是否关闭算法
		bool bScreensaver;								// 是否进入屏保
		int nWwanSignal;								// 4g信号强度
		int wiredNetwork;								// 是否连接有线网络
		bool bInternet;									// 是否联通外网
		bool bMountUsb;									// 是否挂载U盘
		bool bCloudLinked;								// 是否连通云平台
		sPassedEventLog_eVerificationType verType;		// 验证方式
		eConfigCmdType cfgType;							// 配置改变
		eNetWifiStatusType wifiStatus;					// wifi状态
		uint nImportFailCount;							// 云下发导入失败人数
		sFaceDetectEvent detectEvent;					// 人脸检测事件上报
		bool bUpgrading;								// 当前是否在升级
	};
}sUploadInfo;

///< 夏令时结构							   		
typedef struct S_SDK_DST_POINT {
	int year;
	int month;
	int week;										// 周1:first  to2 3 4 -1:last one 0:表示使用按日计算的方法  [-1,4]
	int weekday;									// weekday from sunday=0	[0, 6]
	int hour;
	int minute;
}sDSTPoint;

// 日期格式
typedef enum E_SDK_DATEFORMAT_TYPE {
	E_SDK_DATEFORMAT_TYPE_YYMMDD = 0,
	E_SDK_DATEFORMAT_TYPE_MMDDYY = 1,
	E_SDK_DATEFORMAT_TYPE_DDMMYY = 2,
}eDateFormatType;

// 日期分隔符
typedef enum E_SDK_DATESPLITER_TYPE {
	E_SDK_DATESPLITER_TYPE_DOT = 0,					// 点分格式 "."，废弃
	E_SDK_DATESPLITER_TYPE_DASH = 1,				// 杠分格式 "-"
	E_SDK_DATESPLITER_TYPE_SLASH = 2,				// 斜线格式 "/"
	E_SDK_DATESPLITER_TYPE_YMD = 3,					// 年月日文字格式
}eDateSpliterType;

// 时间格式
typedef enum E_SDK_TIMEFORMAT_TYPE {
	E_SDK_TIMEFORMAT_TYPE_24,						// 24小时制
	E_SDK_TIMEFORMAT_TYPE_12,						// 12小时制
}eTimeFormatType;

typedef struct S_SDK_TIME_NORMAL {
	int nMinutesWest;								// 和UTC时间的差值，单位分钟，可以为负
	eDateFormatType dateFormat;						// 日期格式  0:YYMMDD 1:MMDDYY 2:DDMMYY
	eDateSpliterType dateSeparatator;				// 日期分隔符
	eTimeFormatType timeFormat;						// 时间格式
	bool bEnableDst;								// 夏令时使能
	sDSTPoint dstStart;								// 夏令时开始时间
	sDSTPoint dstEnd;								// 夏令时结束时间
}sTimeNormal;

typedef enum E_SDK_PAYLOAD_TYPE {
	kPayloadPCMU = 0,
	kPayload1016 = 1,
	kPayloadG721 = 2,
	kPayloadGSM = 3,
	kPayloadG723 = 4,
	kPayloadDVI4_8K = 5,
	kPayloadDVI4_16K = 6,
	kPayloadLPC = 7,
	kPayloadPCMA = 8,
	kPayloadG722 = 9,
	kPayloadS16BE_STEREO = 10,
	kPayloadS16BE_MONO = 11,
	kPayloadQCELP = 12,
	kPayloadCN = 13,
	kPayloadMPEGAUDIO = 14,
	kPayloadG728 = 15,
	kPayloadDVI4_3 = 16,
	kPayloadDVI4_4 = 17,
	kPayloadG729 = 18,
	kPayloadG711A = 19,
	kPayloadG711U = 20,
	kPayloadG726 = 21,
	kPayloadG729A = 22,
	kPayloadLPCM = 23,
	kPayloadCelB = 25,
	kPayloadJPEG = 26,
	kPayloadCUSM = 27,
	kPayloadNV = 28,
	kPayloadPICW = 29,
	kPayloadCPV = 30,
	kPayloadH261 = 31,
	kPayloadMPEGVIDEO = 32,
	kPayloadMPEG2TS = 33,
	kPayloadH263 = 34,
	kPayloadSPEG = 35,
	kPayloadMPEG2VIDEO = 36,
	kPayloadAAC = 37,
	kPayloadWMA9STD = 38,
	kPayloadHEAAC = 39,
	kPayloadPCM_VOICE = 40,
	kPayloadPCM_AUDIO = 41,
	kPayloadMP3 = 43,
	kPayloadADPCMA = 49,
	kPayloadAEC = 50,
	kPayloadX_LD = 95,
	kPayloadH264 = 96,
	kPayloadD_GSM_HR = 200,
	kPayloadD_GSM_EFR = 201,
	kPayloadD_L8 = 202,
	kPayloadD_RED = 203,
	kPayloadD_VDVI = 204,
	kPayloadD_BT656 = 220,
	kPayloadD_H263_1998 = 221,
	kPayloadD_MP1S = 222,
	kPayloadD_MP2P = 223,
	kPayloadD_BMPEG = 224,
	kPayloadMP4VIDEO = 230,
	kPayloadMP4AUDIO = 237,
	kPayloadVC1 = 238,
	kPayloadJVC_ASF = 255,
	kPayloadD_AVI = 256,
	kPayloadDIVX3 = 257,
	kPayloadAVS = 258,
	kPayloadREAL8 = 259,
	kPayloadREAL9 = 260,
	kPayloadVP6 = 261,
	kPayloadVP6F = 262,
	kPayloadVP6A = 263,
	kPayloadSORENSON = 264,
	kPayloadH265 = 265,
	kPayloadVP8 = 266,
	kPayloadMVC = 267,
	kPayloadPNG = 268,
	kPayloadAMR = 1001,
	kPayloadMJPEG = 1002,
	kPayloadAMRWB = 1003,
	kPayloadPRORES = 1006,
	kPayloadOPUS = 1007,
}ePayloadType;

typedef struct S_SDK_MEDIA_FORMAT {
	bool bVideoEnable;
	bool bAudioEnable;
	ePayloadType payloadType;						// 有效载荷类型，即编码模式
	char resolutionName[32];						// 分辨率名字
	uint nWidth;						    		// 宽
	uint nHeight;									// 高
	uint nFPS;										// 帧率
	uint nQuality;						    		// [0, 5]
	uint profile;									// [0,3] (H.264: 0:baseline 1:MP 2:HP 3:SVC-T) (H.265 0:MP)
	eBitrateControl bitrateControl;					// 码流控制类型
	uint iGOP;										// I帧间隔
	uint nBitRate;									// 码流值(Kb/s)
}sMediaFormat;

typedef struct S_SDK_ENCODE_CONFIG{
	sMediaFormat dstMainFmt;
	sMediaFormat dstExtraFmt;
	sMediaFormat dstThirdFmt;
}sEncodeConfig;

typedef struct S_SDK_ENCODE_CONFIGAll {
	int nCount;
	sEncodeConfig vEncodeConfigAll[NET_MAX_CHANNUM];
}sEncodeConfigAll;

///////////////////////////////////////////////////////////////////////////////
// audio Encode config
///////////////////////////////////////////////////////////////////////////////
typedef struct S_SDK_AUDIO_FORMAT {
	ePayloadType payloadType;						// 有效载荷类型，即编码模式
	int nSamplerate;								// 采样率
}sAudioFormat;

typedef struct S_SDK_AUDIO_ENCODEALL {
	int nCount;
	sAudioFormat audio[NET_MAX_CHANNUM];
}sAudioEncodeAll;

///////////////////////////////////////////////////////////////////////////////
// audio out config
///////////////////////////////////////////////////////////////////////////////
typedef struct S_SDK_AUDIO_PLAY_CONFIG {
	bool bMute;										// 是否静音
	uint nVolume;									// 音量大小 [0,99]
}sAudioPlayConfig;

typedef struct S_SDK_AUDIO_PLAY_CONFIG_ALL {
	int nChlCount;
	sAudioPlayConfig playCfg[NET_MAX_CHANNUM];		// 音频输出
}sAudioPlayConfigAll;

typedef struct S_SDK_AUTO_MAINTAIN_CONFIG {
	int iAutoRebootDay;								// 自动重启设置日期,其中0：未知（错误配置），1：每天，2-8：周日-周六
	int iAutoRebootHour;							// 重启整点时间	[0, 23]（废弃）
	sTimeSection timeSection;						// 空闲时间段，其中sTimeSection::bEnable标志是否开启自动重启
}sAutoMaintainConfig;

typedef struct S_SDK_GENERAL_CONFIG {
	eLanguageList language;							// 语言
	eVideoStandard videoStandard;					// 视频制式 PAL,NTSC
	char szDeviceName[64];							// 设备名称
	char szLocation[64];							// 部署地点
}sGeneralConfig;

///////////////////智能算法相关结构体/////////////////////////////////
//智能算法类型
typedef enum {
	E_INTELLIGENCE_ALGORITHM_DISABLE = 0,			// 关闭算法
	E_INTELLIGENCE_ALGORITHM_CAPTURE_FACE = 1,		// 人脸抓怕（人脸属性）
	E_INTELLIGENCE_ALGORITHM_CAPTURE_BODY = 2,		// 脸人绑定	（人脸、人形属性）
	E_INTELLIGENCE_ALGORITHM_PVF = 3,				// 机非人算法（人形、汽车、车牌属性）
	E_INTELLIGENCE_ALGORITHM_IDENTIFY = 4,			// 识别算法
	E_INTELLIGENCE_ALGORITHM_CAP_VEHICLE = 5,		// 机动车抓拍+车牌识别+车辆属性(TtPvf)
	E_INTELLIGENCE_ALGORITHM_CAP_NONVEHICLE = 6,	// 非机动车抓拍+属性(TtPvf)
}eIntelligenceAlgType;

typedef struct {
	eIntelligenceAlgType algType;
}sIntelligenceAlgMode;

//
typedef enum {
	E_INTELLIGENCE_BOX_DISABLE = 0,					// 不画框
	E_INTELLIGENCE_BOX_STREAM = 1,					// 视频流画框
	E_INTELLIGENCE_BOX_FRONTEND = 2,				// 前端画框
}eIntelligenceBoxDrawMode;

typedef struct {
	eIntelligenceBoxDrawMode boxDrawType;			// 画框类型
}sIntelligenceGeneral;

//智能参数
// 3D pose				 		
typedef struct {
	float fRoll;									// 斜脸角[0,180]
	float fPitch;									// 俯仰角[0,180]
	float fYaw;										// 侧脸角[0,180]
}sIntelligenceAlgPose;

// 抓拍最小像素(相对于1080P)(人脸:宽高皆为[30, 500] 人形:宽:[40, 500] 高:[100, 800])
typedef struct {
	uint nWidth;
	uint nHeight;
}sAlgObjectMixSize;

typedef enum {
	E_INTELLIGENCE_BOX_COLOR_UNKNOWN = 0,
	E_INTELLIGENCE_BOX_COLOR_GREEN = 1,				// 绿色
	E_INTELLIGENCE_BOX_COLOR_RED = 2,				// 红色
	E_INTELLIGENCE_BOX_COLOR_BLUE = 3,				// 蓝色
	E_INTELLIGENCE_BOX_COLOR_PURPLE = 4,			// 紫色
	E_INTELLIGENCE_BOX_COLOR_DARKGREEN = 5,			// 暗绿色
	E_INTELLIGENCE_BOX_COLOR_YELLOW = 6,			// 黄色
	E_INTELLIGENCE_BOX_COLOR_LIGHTBLUE = 7,			// 亮蓝色
	E_INTELLIGENCE_BOX_COLOR_LIGHTPURPLE = 8,		// 亮紫
	E_INTELLIGENCE_BOX_COLOR_DARKBLACK = 9,			// 暗黑色
	E_INTELLIGENCE_BOX_COLOR_GRAY = 10,				// 灰色
	E_INTELLIGENCE_BOX_COLOR_WHITE = 11,			// 白色
}eIntelligenceBoxColorType;

// 画框类型
typedef enum {
	E_INTELLIGENCE_BOX_LINE_UNKNOWN = 0,
	E_INTELLIGENCE_BOX_LINE_DASH = 1,				// 线段
	E_INTELLIGENCE_BOX_LINE_FULL = 2,				// 完整框
}eIntelligenceBoxLineType;

typedef enum {
	E_PUSH_PICTURE_DISABLE = 0,						// 关闭推图
	E_PUSH_PICTURE_FAST = 1,						// 最快推图
	E_PUSH_PICTURE_BEST = 2,						// 最优推图
	E_PUSH_PICTURE_PERIOD = 3,						// 定时推图
	E_PUSH_PICTURE_RANGE = 4,						// 区间推图（预留）
}ePushPictureMode;

typedef enum {
	E_INTELLIGENCE_TRACK_FACE = 0,					// 追踪人脸
	E_INTELLIGENCE_TRACK_BODY = 1,					// 追踪人形
	E_INTELLIGENCE_TRACK_HYBRID = 2,				// 混合追踪
}eIntelligenceAlgTrackType;

// 抓拍普通参数
typedef struct {
	sAlgObjectMixSize minSize;						// 抓拍最小像素
	ePushPictureMode pushMode;						// 推图策略
	int nPushPeriod;								// 定时推图间隔[500, 3000],单位毫秒(依赖pushMode为E_PUSH_PICTURE_PERIOD)
	bool bAttribute;								// 是否带属性
	eIntelligenceBoxColorType boxColor;				// 目标框框颜色 (依赖draw_box_type)
	bool bBgImage;									// 是否生成背景图 (依赖pushMode不为E_PUSH_PICTURE_DISABLE)
	int nCapImageQuality;							// 抓拍图质量
	int nBgImageQuality;							// 背景图质量
	bool bCapStorage;								// 抓拍图存储
	bool bBgStorage;								// 背景图存储
	sPoint roi[8];									// 目标检测区域(暂只支持凸四边形)
	bool bEventRecord;								// 是否触发事件录像
	int nRecordDuration;							// 录像时长[1, 20],单位秒
	eIntelligenceBoxLineType lineType;				// 画框类型
	float fQualityThres;							// 质量阈值(0, 1)， 能力集 E_OTHER_ABILITY_ST
	float fConfidenceThreshold;						// 置信度阈值
	bool bObjectDetection;							// 目标检测开关
	char szReserve[16];
}sIntelligenceCapCommonCfg;

typedef struct {
	sIntelligenceCapCommonCfg comm;					// 通用参数
	sIntelligenceAlgPose detPoseThreshold;			// 抓拍人脸的角度约束(每个范围都是[0,180])	， 能力集 E_OTHER_ABILITY_Mgvl
	float fDetBlurThreshold;						// 抓拍人脸的模糊约束[0,1]				， 能力集 E_OTHER_ABILITY_Mgvl
	float fCropFaceScale;							// 截取人脸抓拍图的缩放参数[0,4]
	bool bIdentify;									// 是否做识别（预留）
	bool bMonoLiveness;								// 是否做单目活体（识别模式）
	int nIdPeriod;									// 二次识别间隔[1, 10],单位秒（识别模式）
}sIntelligenceFaceParam;

typedef struct {
	sIntelligenceCapCommonCfg comm;					// 通用参数
	bool bAction;									// 是否做动作识别(目前只有pvf)
}sIntelligenceHumanParam;

typedef struct {
	sIntelligenceCapCommonCfg comm;					// 通用参数
}sIntelligenceVehicleParam;

typedef struct {
	sIntelligenceCapCommonCfg comm;					// 通用参数
}sIntelligencePlateParam;

typedef struct {
	sIntelligenceCapCommonCfg comm;					// 通用参数
}sIntelligenceCycleParam;

typedef struct S_SDK_INTELLIGENCE_PARAM_CONFIG {
	sIntelligenceAlgMode algMode;
	sIntelligenceGeneral general;
	sIntelligenceFaceParam face;
	sIntelligenceHumanParam human;
	sIntelligenceVehicleParam vehicle;
	sIntelligencePlateParam plate;
	sIntelligenceCycleParam cycle;
	int nOnTemperature;								// 开启算法温度(0, 200)
	int nOffTemperature;							// 关闭算法温度(0, 200)
	eIntelligenceAlgTrackType trackMode;
}sIntelligenceConfig;

/*******************************门禁机相关配置****************************************/
// 激活状态
typedef enum E_SDK_ACTIVATY_STEP_TYPE {
	E_ACTIVATY_STEP_TYPE_UNKNOWN = 0,				// 未知
	E_ACTIVATY_STEP_TYPE_PWD = 1,					// 修改密码
	E_ACTIVATY_STEP_TYPE_NETWORK = 2,				// 网络配置
	E_ACTIVATY_STEP_TYPE_TAKEOVER = 3,				// 管理方式
	E_ACTIVATY_STEP_TYPE_USAGE_SCENE = 4,			// 使用场景
}eActivatyStepType;

typedef struct S_SDK_DOOR_ACTIVATY_STATE {
	bool bActivated;								// 是否已激活
	eActivatyStepType step;							// 激活进度
}sDoorActivatyState;

// 管理方式
typedef enum {
	E_DOOR_TAKEOVER_UNKNOWN = 0,
	E_DOOR_TAKEOVER_SERVER = 1,						// 服务器管理
	E_DOOR_TAKEOVER_MGVL_CLOUD = 2,					// 客户云管理
	E_DOOR_TAKEOVER_LOCAL = 3,						// 单机使用
	E_DOOR_TAKEOVER_ALI_CLOUD = 4,					// Ali云管理
	E_DOOR_TAKEOVER_PS_PUBLIC_CLOUD = 5,			// ps公有云
	E_DOOR_TAKEOVER_PS_PRIVATE_CLOUD = 6,			// ps私有云
	E_DOOR_TAKEOVER_WWX_CLOUD = 7,					// 企业微信
	E_DOOR_TAKEOVER_PSLAN = 8,						// ps局域网
	E_DOOR_TAKEOVER_PSWAN = 9,						// ps广域网
	E_DOOR_TAKEOVER_ONENET_CLOUD = 10,				// onenet云
}eDoorTakeoverMode;

typedef struct {
	sIpAddress address;
	char szUserName[NET_MAX_NAME_PSW_LEN];
	char szPassword[NET_MAX_NAME_PSW_LEN];
}sDoorTakeoverServerCfg;

typedef struct S_SDK_DOOR_TAKEOVER_MODE {
	eDoorTakeoverMode eType;
	sDoorTakeoverServerCfg sServer;					// 服务器管理配置项
}sDoorTakeoverMode;

// 使用场景
typedef enum {
	E_DOOR_SCENE_UNKNOWN = 0,
	E_DOOR_SCENE_SINGLE_PASS = 1,					// 快速通行场景，一次识别一人
	E_DOOR_SCENE_MULTIPLE_PASS = 2,					// 多人考勤场景，多人同时识别
}eDoorSceneType;

typedef struct S_SDK_DOOR_USAGE_SCENE {
	eDoorSceneType eType;
}sDoorUsageScene;

// 门禁参数
typedef enum {
	E_SENSOR_UNABLE = 0,							// 不使用
	E_SENSOR_NORMAL_OPEN = 1,						// 常开
	E_SENSOR_NORMAL_CLOSE = 2,						// 常闭
}eDoorSensorType;

typedef enum {
	E_DOOR_VT_UNKNOWN = 0,
	E_DOOR_VT_FACE = 1,								// 人脸
	E_DOOR_VT_FACE_OR_CARD = 2,						// 人脸或刷卡
	E_DOOR_VT_FACE_AND_CARD = 3,					// 人脸和刷卡
	E_DOOR_VT_FACE_AND_PWD = 4,						// 人脸和密码
	E_DOOR_VT_FACE_OR_OTHER = 6,					// 人脸或其它
	E_DOOR_VT_CARD_AND_FACE = 7,					// 刷卡和人脸
	E_DOOR_VT_ANY_FACE_AND_TEMP = 102,				// 快速测温(畅通模式的人脸和温度)
}eDoorVerificationType;

typedef enum {
	E_OPEN_MODE_EDGE = 0,							// 脉冲触发
	E_OPEN_MODE_LEVEL = 1,							// 电平触发
}eRelayOpeningMode;

typedef enum {
	E_RELAY_EDGE_FALLING = 0,						// 低触发
	E_RELAY_EDGE_RISING = 1,						// 高触发
}eRelayEdgeType;

typedef struct S_SDK_RELAY_EDGE {
	eRelayEdgeType type;
	int nDuty;										// 占空比(%) [1, 99]
	int nPeriod;									// 脉冲周期(ms) [1-1000]
	int nNum;										// 脉冲个数(个) [1,5]
}sRelayEdge;

typedef enum {
	E_RELAY_LEVEL_LOW = 0,							// 低电平
	E_RELAY_LEVEL_HIGH = 1,							// 高电平
}eRelayLevelType;

typedef struct S_SDK_RelayLevel {
	eRelayLevelType type;
	float fDuration;								// 门锁开门驱动持续时长(s) [0.1,60]
}sRelayLevel;

typedef struct S_SDK_DOOR_CTRL_PARAM {
	eDoorSensorType sensorType;						// 门磁类型，默认不使用
	float fTimeout;									// 开门超时时长(s) [0,50]
	float fDelayTime;								// 延迟门锁控制(s) [0,10]
	eDoorVerificationType VtType;					// 认证方式，默认人脸
	eRelayOpeningMode openMode;						// 继电器开门方式ps
	sRelayEdge edge;								// 脉冲触发ps
	sRelayLevel level;								// 电平触发ps/mgvl
}sDoorCtrlParam;

// 客户定制配置
typedef struct S_SDK_CUSTOMER_CLOUDDATA_CONFIG {
	int nDataSize;									// 数据长度
	char szData[1024];								// 
}sCustomerCloudDataConfig;

// 门禁机识别参数
typedef struct S_SDK_DOORCTRL_RECOGNITION_PARAM {
	bool bLivenessActivate;							// 活体开关 mgvl/ps
	bool bIrActivate;								// IR检测开关 mgvl
	float fIdentifyThres;							// 识别阈值 mgvl[0.0,100.0] ps[1,100)
	float fLivenessThres;							// 活体阈值 mgvl[0.0,100.0] ps[1,100)
	float fQualityThres;							// 人脸质量阈值 ps[1,100)
	uint nIdentifyInterval;							// 识别间隔(s) mgvl/ps[1,9]
	float fPitch;									// 垂直角(°) mgvl[0,90]
	float fRoll;									// 旋转角(°) mgvl[0,90]
	float fYaw;										// 水平角(°) mgvl[0,90]
	float fBlur;									// 模糊度 mgvl[0,1]
	float fTrackOverlapRatio;						// track 时边缘重合度阈值 ps[1,100)
	float fMaxIdentifyDistance;						// 最大识别距离 mgvl[1.0,2.0] ps[0.5,2.0]
	uint nLedLuminance;								// 补光灯亮度 mgvl[0, 8]
}sDoorCtrlRecognitionParam;

// 口罩设置参数
typedef struct S_SDK_DOORCTRL_MASK_PARAM {
	bool bDetectOpen;								// 口罩检测开关
	bool bNotify;									// 口罩提示开关
	float fIdentifyThres;							// 识别阈值 ps[1,100) 默认65
	float fLivenessThres;							// 活体阈值 ps[1,100) 默认50
	float fQualityThres;							// 质量阈值 ps[1,100) 默认60
}sDcPsMaskParam;

// 温度参数
typedef struct S_SDK_DOORCTRL_ONENET_TEMP_PARAM {
	bool bDetect;									// 是否开启检测，如果开启检测，检测到高温会有高温提示
	bool bForbidPass;								// 是否高温禁入
	float fHighTemp;								// 高温阈值
}sDcOneNetTempParam;

// 识别提示
typedef struct S_SDK_DOORCTRL_IDENTIFY_TIP {
	bool bShowPersonName;							// 是否显示人员名称
	uint nShowMask;									// 识别携带图片类型枚举，图片类型参考枚举 E_SDK_PERSON_SEARCH_PASSED_LOG_TYPE
}sDoorCtrlIdentifyTip;

typedef struct {
	char szPath[256];								// 固件路径
	char szVersion[64];
}sDcUsbUpgradePackage;

typedef struct {
	int nCount;
	sDcUsbUpgradePackage file[8];
}sDcUsbUpgradeCheckInfo;

typedef enum {
	E_WIEGAND_USAGE_MODE_IN = 0,					// 韦根输入
	E_WIEGAND_USAGE_MODE_OUT = 1,					// 韦根输出
}eWiegandUsageMode;

typedef enum {
	E_WIEGAND_FORMAT_TYPE_26 = 0,
	E_WIEGAND_FORMAT_TYPE_34 = 1,
	E_WIEGAND_FORMAT_TYPE_32 = 2,
}eWiegandFormatType;

typedef enum {
	E_WIEGAND_CONTENT_OUT_CARD = 0,					// 人员卡号
	E_WIEGAND_CONTENT_OUT_JOBNO = 1,				// 人员编号
}eWiegandContentOut;

typedef struct S_SDK_WIEGAND_PULSE_CONFIG {
	int nWidth;										// 脉冲宽度[20,200]us
	int nInterval;									// 脉冲间隔[200,20000]us
	bool bFlip;										// 脉冲是否翻转
}sWiegandPulseConfig;

typedef struct S_SDK_DOORCTRL_WIEGAND_CONFIG {
	bool bEnable;									// 使能
	eWiegandUsageMode usageMode;					// 使用模式
	eWiegandFormatType formatType;					// 韦根格式
	eWiegandContentOut contentOut;					// 输出内容
	sWiegandPulseConfig pulse;						// 脉冲参数
	char szCardNo[64];								// 手动开门，远程开门下的韦根输出卡号
}sDoorCtrlWiegandConfig;

typedef enum {
	E_DC_PASS_MODE_FACE = 0,						// 人脸
	E_DC_PASS_MODE_FACEAndTEMP = 1,					// 人脸加温度
	E_DC_PASS_MODE_ANYFACEAndTEMP = 2,				// 任意人脸加温度
}eDCPassMode;

typedef enum {
	E_DC_PASS_STANDARD_37 = 0,
	E_DC_PASS_STANDARD_37P1 = 1,
	E_DC_PASS_STANDARD_37P2 = 2,
	E_DC_PASS_STANDARD_37P3 = 3,
	E_DC_PASS_STANDARD_37P4 = 4,
	E_DC_PASS_STANDARD_37P5 = 5,
	E_DC_PASS_STANDARD_ANY = 6,
}eDCTempStandard;

typedef enum {
	E_DC_DETECTION_NOTEXIST = 0,
	E_DC_DETECTION_WRIST = 1,						// 测手腕模块
	E_DC_DETECTION_FOREHEAD = 2,					// 测额头模块
	E_DC_DETECTION_THERMOGRAPHY = 3,				// 红外模块
}eDCDetectionModule;

typedef struct S_SDK_DOORCTRL_PASSSETTING_CONFIG {
	eDCPassMode eMode;								// 通行模式
	//eDCTempDetectionLocation eLoc;
	eDCTempStandard eStandard;
	eDCDetectionModule eModule;						// 检测模块(只读)
	float fTempCompensated;							// 温度补偿 [-5.0,5.0]
	bool bTempOptimize;								// 温度算法优化
}sDoorCtrlPassSettingConfig;

typedef enum {
	E_DC_CHECK_STATUS_USB = 0,						// 检测是否插入U盘
	E_DC_CHECK_STATUS_PERSONINFO_DATA = 1,			// 检测是否有待导入的人员信息
	E_DC_CHECK_STATUS_DEVICE_CONFIG_DATA = 2,		// 检测是否有待导入的设备配置
	E_DC_CHECK_STATUS_DEVICE_ALLDATA = 3,			// 检测是否有待导入的整机数据
}eDCCheckStatusType;

typedef struct S_SDK_DOORCTRL_CHECK_STATUS {
	eDCCheckStatusType type;
}sDCCheckStatus;

typedef enum E_SDK_DOORCTRL_ALARM_IN_TYPE {
	E_DC_ALARM_IN_UNKNOWN = 0,
	E_DC_ALARM_IN_FIRE = 1,
	E_DC_ALARM_IN_TAMPER = 2,
	E_DC_ALARM_IN_DOORSENSOR = 3,
	E_DC_ALARM_IN_NR,
	E_DC_ALARM_IN_MAX = 8
}eDcAlarmInType;

typedef struct S_SDK_DOORCTRL_ALARM_IN {
	bool bEnable;
	eDcAlarmInType type;					//不可更改,传入什么就传回什么
	int nDoorTimeout;
}sDcAlarmInConfig;

typedef struct S_SDK_DOORCTRL_ALARM_PARAM {
	uint nCount;									//报警设置的条数
	sDcAlarmInConfig AlarmIn[E_DC_ALARM_IN_MAX];	//顺序不能更改，具体是哪项配置需要遍历去读 type
}sDcAlarmParamConfig;


typedef struct S_SDK_DOORCTRL_SCREENSAVER {
	bool bEnable;
	int nDelay;										// 延时时间(s) [3, 20]
	bool bCloudPush;								// 是否支持云推送
}sDcScreensaver;

typedef struct S_SDK_DC_CALIBRATION_MGVL {
	float x_k;										// x方向斜率
	float x_b;										// x方向截距
	float y_k;										// y方向斜率
	float y_b;										// y方向截距
}sDcCalibrationMgvl;

typedef struct S_SDK_DC_CALIBRATION_DM {
	int nDataLen;									// 标定数据长度
	char szData[64];								// 标定数据
	char szReserved[448];							// 保留字节
}sDcCalibrationDm;

// 记录清除请求
typedef enum E_SDK_DOORCTRL_LOG_CLEAR_MODE {
	E_DC_LOG_CLEAR_UNKNOWN = 0,
	E_DC_LOG_CLEAR_PASS_EVENT = 1,					// 通行事件记录
	E_DC_LOG_CLEAR_ALARM_EVENT = 2,					// 报警事件记录
	E_DC_LOG_CLEAR_END,
}eDcLogClearMode;

typedef struct S_SDK_DC_LOG_CLEAR_REQ {
	eDcLogClearMode type[E_DC_LOG_CLEAR_END];		// 需要清除的内容
}sDcLogClearReq;

/// 修改解锁密码请求
typedef struct S_SDK_UNLOCK_MODIFY_PSW {
	char szPassword[NET_MAX_NAME_PSW_LEN];
	char szNewPassword[NET_MAX_NAME_PSW_LEN];

	eEncryptType encryptType;
}sUnlockModifyPsw;

typedef struct S_SDK_DC_TRAVELTIME_PLAN {
	uint nDayMask;									// 星期掩码，从低位到高位依次为 Sunday, Monday, ...(最少为1个,最多为7个)
	int nCount;										// 通行时间段个数，最大为24
	sTimeSection timeSection[24];					// 一天的通行时段(最少为1，最多为24个)(其中sTimeSection::bEnable无效)
}sDcTravelTimePlan;

typedef struct S_SDK_DC_TRAVELTIME_PLAN_ALL {
	int nCount;										// 通行计划个数，最大为7
	sDcTravelTimePlan timePlan[7];					// 通行计划(最少为0个,最多为7个)
}sDcTravelTimePlanAll;

// 通行模式支持类型
enum E_SDK_DC_DETECT_TYPE {
	E_DC_DETECT_TEMP = 0,							// 是否支持温度检测
	E_DC_DETECT_MASK = 1,							// 是否支持口罩检测
};

typedef struct S_SDK_DC_PASS_SCHEME {
	eDoorVerificationType type;						// 验证方式
	uint detectTypeMask;							// 支持检测类型掩码，详情见E_SDK_DC_DETECT_TYPE
}sDcPassScheme;

// 获取设备支持的通行方案
typedef struct S_SDK_DC_PASS_SCHEME_ALL {
	int nCount;
	sDcPassScheme passScheme[8];
}sDcPassSchemeAll;

typedef enum {
	E_SCHEME_PERSON_TYPE_NORMAL = 0,				// 人员
	E_SCHEME_PERSON_TYPE_VISITOR = 1,				// 访客
	E_SCHEME_PERSON_TYPE_OTHER = 2,					// 其他上报人员
	E_SCHEME_PERSON_TYPE_NR,
}eSchemePersonType;

typedef struct S_SDK_DC_PS_CARD_SCHEME {
	bool bEnable;									// 是否启用
	bool bShowCard;									// 是否显示弹窗卡片
	bool bShowPersonName;							// 是否显示人员姓名
	uint nShowPicMask;								// 显示携带图片掩码，图片类型参考枚举 E_SDK_PERSON_SEARCH_PASSED_LOG_TYPE
	int nCardColor;									// 颜色
	bool bShowTip;									// 是否显示提示语
	char szTipContent[256];							// 提示语内容
	char szVoicePath[256];							// 声音路径
}sDcCardScheme;

typedef struct S_SDK_DC_PS_CARD_SCHEME_ALL {
	sDcCardScheme scheme[E_SCHEME_PERSON_TYPE_NR];	// 迎宾卡片方案(根据人员类型进行区分)
}sDcCardSchemeAll;

typedef struct S_SDK_DC_PS_FACE_BOX {
	bool bEnable;									// 是否画框
}sDcFaceBoxConfig;

typedef struct S_SDK_DC_ANTELOPE_SIGNATURE {
	char szSignature[1024];							// 验证码
	uint nDataLen;
}sAntelopeSignature;

typedef struct S_SDK_LINKKIT_REGISTER_CONFIG {
	char szProductKey[64];							// 产品密钥
	char szDeviceName[64];							// 设备名称
	char szDeviceSecret[64];						// 
}sLinkkitRegisterConfig;

typedef struct S_SDK_PSCLOUD_REGISTER_CONFIG {
	char szEncodePSn[64];
}sPsCloudRegisterConfig;

typedef struct S_SDK_WXCLOUD_REGISTER_CONFIG {
	char szSecretNo[64];
}sWxCloudRegisterConfig;

typedef struct S_SDK_360CLOUD_REGISTER_CONFIG {
	char szProductKey[64];
	char szDeviceName[64];
	char szDeviceSecret[64];
}s360CloudRegisterConfig;

typedef struct S_SDK_GD_SMARTEYE_REGISTER_CONFIG {
	char szModel[64];
}sGdSmarteyeRegisterConfig;

typedef struct S_SDK_TELECOM_VISION_SMART_LINK {
	char szCtei[256];								// 中国电信终端设备识别码（China Telecom Equipment Identity）
	char szDeviceName[NET_MAX_NAME_PSW_LEN];		// 国标设备名称
	char szServerId[NET_MAX_ADDRESS_LEN];			// 国标设备ID
	char szPasswd[NET_MAX_NAME_PSW_LEN];			// 国标注册密码
}sTelecomVisionSmartLink;

typedef struct S_SDK_ANDLINK_REGISTER {
	char szDeviceId[32];							// 一机一密 sn序列号
	char szCmei[32];								// 一机一密
	char szLoginSecret[32];							// 一机一密 平台接入密钥
	char szMediaSecret[32];							// 一机一密 视频加密密钥
	char szCmccAppProductKey[32];					// 一型一密 和家固话app key
	char szCmccAppProductSecret[32];				// 一型一密 和家固话app secret
	char szCmccProductId[32];						// 一型一密 和家固话分配产品id
	char szProductName[32];							// 一型一密 产品型号
	char szProductToken[32];						// 一型一密 产品验证码
	char szAndlinkToken[32];						// 一型一密 平台验证码
}sAndlinkRegister;

// 自研算法加密
typedef struct S_SDK_TT_ENCRYPT_INFO {
  char szEncrypt[1024];								// 自研算法软加密
}sTtEncryptInfo;

typedef struct E_SDK_AUDIO_TEST {
	uint nDataLen;
	char* szAudioData;								// 音频内容
}sAudioTestReq;

typedef enum AntennaState {
	E_GNSS_ANTRNNA_UNKNOWN = 0,						// 天线未知
	E_GNSS_ANTRNNA_OPEN = 1,						// 天线开路
	E_GNSS_ANTRNNA_SHORT = 2,						// 天线短路
	E_GNSS_ANTRNNA_OK = 3,							// 天线正常
}eGnssAntennaState;

typedef struct S_SDK_GNSSS_SIMPLE_DATA_CONFIG {
	bool bSupport;
	eGnssAntennaState antennaState;
	double longitude;								// 经度值
	double latitude;								// 纬度值
	int nLongitudeType;								// 东经0, 西经1
	int nLatitudeType;								// 南纬0, 北纬1
}sGnssSimpleDataCfg;

typedef enum E_SDK_VIDEO_ROTATION_TYPE {
	E_VIDEO_ROTATION_0 = 0,
	E_VIDEO_ROTATION_90 = 1,
	E_VIDEO_ROTATION_180 = 2,
	E_VIDEO_ROTATION_270 = 3,
}eVideoRotationType;

typedef struct S_SDK_VIDEO_ROTATION_CONFIG {
	bool bSupport;
	eVideoRotationType eType;
}sVideoRotationConfig;

typedef struct S_SDK_VIDEO_ROTATION_CONFIG_ALL {
	int nCount;
	sVideoRotationConfig rotation[NET_MAX_CHANNUM];
}sVideoRotationConfigAll;

// 视频输出参数
typedef struct S_SDK_VIDEO_OUTPARAM_CONFIG {
  bool bSupport;
  int nLuminance;									// 屏幕亮度,[0,100]
}sVideoOutparamConfig;

typedef struct S_SDK_VIDEO_OUTPARAM_CONFIG_ALL {
	int nCount;
	sVideoOutparamConfig out[NET_MAX_CHANNUM];
}sVideoOutparamConfigAll;

// AnRuan配置下发服务器
typedef struct S_SDK_ANRUAN_CONFIG_SERVER {
	bool bEnable;									// 使能
	sIpAddress serverUrl;							// 服务器地址
	int nCycle;										// 请求周期
}sAnruanConfigServer;

// Gui设备升级-立即更新
typedef struct S_SDK_GUI_UPGRADE_START {
	char szPath[256];
}sGuiUpgradeStart;

///////////////////能力集相关结构体/////////////////////////////////
//编码功能能力集
typedef enum E_SDK_ENCODE_ABILITY {
	E_ENCODE_ABILITY_Unknown = 0,
	E_ENCODE_ABILITY_NR,
	E_ENCODE_ABILITY_MAX = 64,
}eEncodeAbility;

//报警能力集
typedef enum E_SDK_ALARM_ABILITY {
	E_ALARM_ABILITY_Unknown = 0,
	E_ALARM_ABILITY_AlarmIn = 1,
	E_ALARM_ABILITY_Motion = 2,
	E_ALARM_ABILITY_Blind = 3,
	E_ALARM_ABILITY_NR,
	E_ALARM_ABILITY_MAX = 64,
}eAlarmAbility;

//网络服务能力集
typedef enum E_SDK_NETWORK_ABILITY {
	E_NETWORK_ABILITY_Unknown = 0,
	E_NETWORK_ABILITY_FTP = 1,
	E_NETWORK_ABILITY_NTP = 2,
	E_NETWORK_ABILITY_NetIPFilter = 3,
	E_NETWORK_ABILITY_CloudServer = 4,
	E_NETWORK_ABILITY_Smtp = 5,
	E_NETWORK_ABILITY_PsCloudServer = 6,
	E_NETWORK_ABILITY_PsFtp = 7,
	E_NETWORK_ABILITY_WEB = 8,
	E_NETWORK_ABILITY_RTSP = 9,
	E_NETWORK_ABILITY_OnvifServer = 10,
	E_NETWORK_ABILITY_Gb28181Client = 11,
	E_NETWORK_ABILITY_Pppoe = 12,
	E_NETWORK_ABILITY_WIFI = 13,
	E_NETWORK_ABILITY_INTELLIF_HTTP = 14,			// HTTP服务
	E_NETWORK_ABILITY_SAFESOFT_HTTP = 15,			//  
	E_NETWORK_ABILITY_CLOUD_UPGRADE = 16,			// 云升级
	E_NETWORK_ABILITY_WWAN = 17,
	E_NETWORK_ABILITY_GB35114 = 18,
	E_NETWORK_ABILITY_BCW_HTTP = 19,
	E_NETWORK_ABILITY_GA1400 = 20,
	E_NETWORK_ABILITY_WWANV2 = 21,
	E_NETWORK_ABILITY_NET_INTERFACE_ORDER = 22,
	E_NETWORK_ABILITY_Gb28181With4G = 23,
	E_NETWORK_ABILITY_360_SAAS = 24,
	E_NETWORK_ABILITY_PORT_MAPPING = 25,			// 端口映射
	E_NETWORK_ABILITY_GD_SMARTEYE = 26,				// gd慧眼
	E_NETWORK_ABILITY_BEITE = 27,					// 贝特
	E_NETWORK_ABILITY_TV_SMARTLINK = 28,			// TelecomVision
	E_NETWORK_ABILITY_XUZN = 29,					// 迅贞
	E_NETWORK_ABILITY_NR,
	E_NETWORK_ABILITY_MAX = 64,
}eNetworkAbility;

//其他能力集
typedef enum E_SDK_OTHER_ABILITY {
	E_OTHER_ABILITY_Unknown = 0,
	E_OTHER_ABILITY_Mgvl = 1,
	E_OTHER_ABILITY_Pensees = 2,
	E_OTHER_ABILITY_PTZ = 3,
	E_OTHER_ABILITY_PRODUCE = 4,					// 产测
	E_OTHER_ABILITY_PSDOOR = 5,						// 面板机
	E_OTHER_ABILITY_MGVLDOOR = 6,					// 面板机
	E_OTHER_ABILITY_MGVLID = 7,						// 识别机
	E_OTHER_ABILITY_VO = 8,							// 工装
	E_OTHER_ABILITY_PVF = 9,						// 机非人
	E_OTHER_ABILITY_STATISTIC = 10,					// 智能统计
	E_OTHER_ABILITY_PS_PVF = 11,					// pes机非人
	E_OTHER_ABILITY_STDOOR = 12,					// 面板机
	E_OTHER_ABILITY_ST = 13,						// ST算法机器
	E_OTHER_ABILITY_ALDOOR = 14,					// AL面板机
	E_OTHER_ABILITY_GNSS = 15,						// 北斗
	E_OTHER_ABILITY_INTER_STELL = 16,				// 温度控制算法开关
	E_OTHER_ABILITY_DMDOOR = 17,					// 面板机
	E_OTHER_ABILITY_MONITOR_BALL = 18,				// 布控球能力集
	E_OTHER_ABILITY_WXDOOR = 19,
	E_OTHER_ABILITY_AIPARK = 20,					// AiPark客户能力集
	E_OTHER_ABILITY_ST_PVF = 21,					// ST_PVF算法机器
	E_OTHER_ABILITY_SUPEREYE = 22,					// 千里眼推图
	E_OTHER_ABILITY_ONENET_DOOR = 23,				// 面板机
	E_OTHER_ABILITY_FSY_ELEVATOR_ACCESS = 24,		// 梯控
	E_OTHER_ABILITY_INTRUSION_DETECTION = 25,		// 区域入侵
	E_OTHER_ABILITY_SMART_INTRUSION_DETECTION = 26,	// 智能入侵
	E_OTHER_ABILITY_PRODUCEV2 = 27,					// 通用产测
	E_OTHER_ABILITY_SAFE_HELMET_DETECTION = 28,		// 安全帽检测
	E_OTHER_ABILITY_CAMERA_PARAM_V2 = 29,			// 摄像机参数V2版本
	E_OTHER_ABILITY_VANILLA_HUMAN_DETECTION = 30,	// 非智能人形检测
	E_OTHER_ABILITY_TALK = 31,						// 对讲
	E_OTHER_ABILITY_ILLEGAL_PARKING_DETECTION = 32,	// 车辆违停检测
	E_OTHER_ABILITY_360AICAM = 33,					// 360
	E_OTHER_ABILITY_AUDIO_DETECT = 34,				// 音频监测
	E_OTHER_ABILITY_RESPIRATOR_DETECTION = 35,		// 未佩戴口罩检测
	E_OTHER_ABILITY_TT_CAP = 36,					// 自研抓拍算法
	E_OTHER_ABILITY_TT_PVF = 37,					// 自研机非人算法
	E_OTHER_ABILITY_BURN_HELPER = 38,				// 升级进度返回
	E_OTHER_ABILITY_JPEG_ID = 39,					// 图片识别
	E_OTHER_ABILITY_NR,
	E_OTHER_ABILITY_MAX = 64,
}eOtherAbility;

//系统功能能力集
typedef struct S_SDK_SYSTEM_FUNC_ABILITY {
	bool bEncode[E_ENCODE_ABILITY_MAX];
	bool bAlarm[E_ALARM_ABILITY_MAX];
	bool bNetwork[E_NETWORK_ABILITY_MAX];
	bool bOther[E_OTHER_ABILITY_MAX];
}sSystemFuncAbility;

//语言能力集
typedef struct S_SDK_LANGUAGE_ABILITY {
	bool bLan[E_SDK_LANGUAGE_NR];
}sLanguageAbility;

//编码能力
typedef struct S_SDK_VIDEO_RESOLUTION {
	int nWidth;
	int nHeight;
	char sCustom[16];
	int nFps;										// 当前分辨率下最大帧率，等于0不限制
}sVideoResolution;

typedef struct S_SDK_VENC_ABILITY {
	bool bSupport;
	int nCount;										// 支持的有效载荷类型个数
	ePayloadType payloadType[16];					// 支持的有效载荷类型，即编码模式
	int nVRCount;									// 支持的分辨率个数
	sVideoResolution resolution[16];				// 建议值，底层不做严格校验
	int nVencFps;									// 编码最大帧率
}sVencAbility;

typedef struct S_SDK_VIDEO_ABILITY {
	int nVstdFps[16];								// 定义P制，N制对应的帧率,一般25/30
	sVencAbility vencAbility[4];					// 0:主码流 1:辅码流 2:图片码流
	int nTotalEncodePower;							// 总编码能力
}sVideoAbility;

typedef struct S_SDK_AUDIO_ABILITY {
	int nCount;										// 支持的有效载荷类型个数
	ePayloadType payloadType[16];					// 支持的有效载荷类型，即编码模式
	int nSRCount;									// 支持的采样率个数
	int nSampleRate[16];							// 支持的采样率，非零有效
	uint nMaskSoundMode;							// 0 bit: 单声道, 1 bit: 立体声
	uint nMaskWorkMode;								// 0 bit: 普通模式 1 bit: 对讲模式
	uint nMaskTalkPt;								// 对讲所支持的payload_type
	uint nMaskTalkSr;								// 对讲所支持的samplerate
	uint nNumPerFrm;								// 每帧采样点数
	uint nMaskTalkMode;								// 对讲模式，0 bit: 半双工，1 bit: 全双工, 全0默认半双工
}sAudioAbility;

//编码能力集
typedef struct S_SDK_ENCODE_ABILITY {
	sVideoAbility video;
	sAudioAbility audio;
}sEncodeAbility;

typedef struct S_SDK_ENCODE_ABILITY_ALL {
	sEncodeAbility encodeAbility[NET_MAX_CHANNUM];
}sEncodeAbilityAll;

//报警联动能力集
typedef struct S_SDK_EL_ABILITY_AUDIO {
	bool bSupport;
}sElAbilityAudio;

typedef struct S_SDK_EL_ABILITY_LIGHT {
	bool bSupport;
	uint nModeMask;									// 0:flicker 1:continuous
	bool bSupportLevel;
}sElAbilityLight;

typedef struct S_SDK_EVENT_LINK_ABILITY {
	sElAbilityAudio audio;
	sElAbilityLight light;
}sEventLinkAbility;

typedef struct S_SDK_EVENT_LINK_ABILITY_ALL {
	int nCount;
	sEventLinkAbility linkAbility[NET_MAX_CHANNUM];
}sEventLinkAbilityAll;

// 
typedef struct S_SDK_PLAY_DIR_ABILITY {
	char szDir[256];
	bool bSupportUpload;							// 是否支持上传文件
	int nMaxUploadFileNum;							// 支持上传文件个数
	int nMaxUploadFileSize;							// 支持上传文件总大小，单位Byte
}sPlayDirAbility;

typedef struct S_SDK_AUDIO_FILE_FORMAT {
	char szFormat[64];
}sAudioFileFormat;

typedef struct S_SDK_AUDIO_FILE_ABILITY {
	int nDirCount;
	sPlayDirAbility playDir[64];
	int nFmtCount;
	sAudioFileFormat format[64];					// 支持的文件格式
}sAudioFileAbility;

typedef struct S_SDK_AUDIO_FILE_ABILITY_ALL {
	int nCount;
	sAudioFileAbility ability[NET_MAX_CHANNUM];
}sAudioFileAbilityAll;

typedef struct S_SDK_AUTO_FOCUS_STATUS {
	bool bStable;
}sAutoFocusStatus;

// 设备文件管理
typedef enum {
	E_DFM_CMD_UNKNOWN = 0,
	E_DFM_CMD_FILE_GET_LIST = 1,					// 获取文件列表
	E_DFM_CMD_FILE_UPLOAD = 2,						// 上传文件
	E_DFM_CMD_FILE_DOWNLOAD = 3,					// 下载文件
	E_DFM_CMD_FILE_RENAME = 4,						// 重命名文件
	E_DFM_CMD_FILE_REMOVE = 5,						// 删除文件
	E_DFM_CMD_FILE_AUDIO_PLAY = 6,					// 播放音频文件
}eDeviceFileManagerCmd;

typedef struct S_SDK_PATH {
	char szPath[256];
}sPath;

typedef enum E_SDK_FILEMANAGER_TYPE {
	E_SDK_FILE_MANAGER_UNKNOW = 0,
	E_SDK_FILE_MANAGER_AUDIOFILE = 1,
}eFileManagerType;

typedef struct S_SDK_FILEMANAGER_LIST_SEARCH_REQ {
	eFileManagerType type;
	sPath dir;
}sFmListSearchReq;

typedef struct S_SDK_FILEMANAGER_FILE_INFO {
	sPath path;
	int nFileSize;
}sFmFileInfo;

typedef struct S_SDK_FILEMANAGER_LIST_SEARCH_RSP {
	eFileManagerType type;
	int nCount;
	sFmFileInfo file[32];
}sFmListSearchRsp;

typedef struct S_SDK_FILEMANAGER_UPLOAD_REQ{
	eFileManagerType type;
	sPath path;
	int nLength;
	char *pszContent;
}sFmUploadReq;

typedef struct S_SDK_FILEMANAGER_DOWNLOAD_REQ {
	eFileManagerType type;
	sPath path;
}sFmDownloadReq;

typedef struct S_SDK_FILEMANAGER_DOWNLOAD_RSP {
	eFileManagerType type;
	sPath path;
	int nLength;
	char *pszContent;
}sFmDownloadRsp;

typedef struct S_SDK_FILEMANAGER_RENAME_REQ {
	eFileManagerType type;
	sPath oldPath;
	sPath newPath;
}sFmRenameReq;

typedef struct S_SDK_FILEMANAGER_REMOVE_REQ {
	eFileManagerType type;
	int nCount;
	sPath path[10];
}sFmRemoveReq;

typedef struct S_SDK_FILEMANAGER_AUDIO_PLAY_REQ {
	sPath audioPath;
}sFmAudioPlayReq;

typedef struct s_SDK_JSON_DATA {
	char *pszJson;
	int nLength;
}sJsonData;

typedef struct S_SDK_FILEMANAGER_REQ {
	union {
		sFmListSearchReq get;
		sFmUploadReq upload;
		sFmDownloadReq download;
		sFmRenameReq rename;
		sFmRemoveReq remove;
		sFmAudioPlayReq audioPlay;
		sJsonData json;
	};
}sFileManagerReq;

typedef struct S_SDK_FILEMANAGER_RSP {
	union {
		sFmListSearchRsp get;
		sFmDownloadRsp download;
		sJsonData json;
	};
}sFileManagerRsp;

// 感兴趣区域
typedef struct S_SDK_ROI_PARAM {
	bool bSupport;									// 是否支持
	bool bEnable;									// 是否使能
	int nQuality;									// 相对于整幅图像编码质量,取值范围[-6,6]
	sRect rect;										// 这里使用相对坐标,相对8192 x[0, 8191], y[0, 8191], width[32, 8192], height[32, 8192]
}sRoiParam;

//每个通道参数，每个通道最多8个RIO
typedef struct S_SDK_ROI_PARAM_List {
	sRoiParam roiParam[8];
}sRoiParamList;

typedef struct S_SDK_ROI_PARAM_STREAM {
	sRoiParamList main;
	sRoiParamList second;
	sRoiParamList third;
}sRoiParamStream;

typedef struct S_SDK_ROI_PARAM_ALL {
	int nCount;
	sRoiParamStream channel[NET_MAX_CHANNUM];
}sRoiParamAll;

//网络摄像机配置
typedef enum E_SDK_DNC_MODE {
	E_SDK_DNC_MODE_AUTO = 0,               			// 根据ISO自动切换
	E_SDK_DNC_MODE_SYNC_INFRARED = 1,       		// 根据光敏电阻自动切换
	E_SDK_DNC_MODE_FORCE_DAY = 2,           		// 强制为白天模式，切成彩色
	E_SDK_DNC_MODE_FORCE_NIGHT = 3,         		// 强制为夜晚模式，不打开红外灯
	E_SDK_DNC_MODE_FORCE_NIGHT_INFRARED = 4, 		// 强制为夜晚模式，打开红外灯(此项已移除)
	E_SDK_DNC_MODE_LED_WHITE = 5,					// 自动白光灯模式，保持彩色
	E_SDK_DNC_MODE_NR,
}eDncMode;

typedef enum E_SDK_CAMERA_ANTIFLICKER {
	E_CAMERA_ANTIFLICKER_DISABLE = 0,
	E_CAMERA_ANTIFLICKER_50Hz = 1,
	E_CAMERA_ANTIFLICKER_60Hz = 2,
}eCameraAntiflicker;

typedef enum E_SDK_CAMERA_WB_MODE {
	E_CAMERA_WB_MODE_AUTO = 0,						// 自动模式
	E_CAMERA_WB_MODE_MANUAL = 1,					// 手动模式
	E_CAMERA_WB_MODE_TUNGSTENLAMP = 2,				// 钨丝灯模式
	E_CAMERA_WB_MODE_SUNLIGHT = 3,					// 日光模式
	E_CAMERA_WB_MODE_CLOUDY = 4,					// 晴天模式
	E_CAMERA_WB_MODE_OVERCAST = 5,					// 阴天模式
	E_CAMERA_WB_MODE_SHADE = 6,						// 阴影模式
}eCameraWbMode;

typedef struct E_SDK_CAMERA_WHITE_BALANCE_CONFIG {
	eCameraWbMode eMode;							// 白平衡模式
	uint nRGain;									// 手动模式下的r分量增益 [0,65535]
	uint nBGain;									// 手动模式下的b分量增益 [0,65535]
	char szReserve[32];
}sCameraWhiteBalanceConfig;

// 日夜模式切换功能能力集类型
typedef enum E_SDK_CAMERA_DNC_CFG_ABILITY_MODE {
	E_CMAERA_DNC_CFG_THRESHOLD = 0,					// 阈值设置
	E_CMAERA_DNC_CFG_TIMING = 1,					// 定时设置
	E_CMAERA_DNC_CFG_PWM = 2,						// 方波调节, 对应补光灯亮度值
}eCameraDncCfgAbilityMode;

typedef struct S_SDK_CAMERA_DNC_ABILITY {
	uint nMaskType;									// dnc类型, 见枚举eDncMode
	uint nMaskCfg[E_SDK_DNC_MODE_NR];				// dnc操作能力,见枚举eCameraDncCfgAbilityMode
	int nLedNum;									// 可软件控制补光灯数(暂无该功能)
}sCameraDncAbility;

typedef struct S_SDK_CAMERA_DNC {
	eDncMode mode;
	int nLevel;										// 自动切换时的阈值等级[0,5]
	sCameraDncAbility ability;						// 能力集合
	sTimeSection timing;							// 定时
	int nBrightness;								// 补光亮度值[0,100]
	char szReserve[32];
}sCameraDnc;

typedef struct S_SDK_CAMERA_EXPOSURE {
	bool bSlowShutter;								// 是否自动降帧，暂不配置
	int nSpeed;										// 自动曝光速度，[0x0,0xFF]
	int nCompensation;								// 自动曝光调整时的目标亮度，[0x0,0xFF]
	bool bManual;									// 手动曝光使能
	uint nExpvalue;									// 手动曝光时间，（0x0,0xFFFFFFFF]
	eCameraAntiflicker flicker;						// 抗闪烁, 自动曝光开启有效
	int nAgain;										// 手动曝光增益，[0x400,0xFFFFFFFF]
	uint nExpTimeMax;								// 自动曝光最大时间，(0x0,0xFFFFFFFF]
	char szReserve[32];
}sCameraExposure;

typedef struct S_SDK_CAMERA_IMAGE {
	int nHue;										// 色度 [0,100] 默认50
	int nLuma;										// 亮度 [0,100] 默认50
	int nContr;										// 对比度 [0,100] 默认50
	int nSatu;										// 饱和度 [0,100] 默认50
	int nSharpenMode;								// 锐化工作模式 0: 自动，detailCtrl无效 1:手动，detailCtrl生效
	int nDetailCtrl;								// 锐化的细节纹理强度，[0,0xFF]
	char szReserve[32];
}sCameraImage;

typedef struct S_SDK_CAMERA_DEH{
	bool bEnable;									// 去雾使能
	int  nOptype;									// 0自动 1手动
	int  nManualValue;								// 手动模式下去雾强度 [0, 255]
	int  nAutoValue;								// 自动模式下去雾强度 [0, 255]
	char szReserve[32];
}sCameraDeh;

typedef struct S_SDK_AREA_ROI{
	bool  bEnable;
	int   nWeight;									// ROI区域的权重 [0,15],一般取较大值
	int   nX;										// ROI, x坐标 [0,8191]
	int   nY;										// ROI, y坐标 [0,8191]
	int   nWidth;									// ROI, 宽度 [1,8192]
	int   nHeight;									// ROI, 高度 [1,8192]
	char szReserve[32];
}sAreaRoi;

typedef struct S_SDK_AREA_ROI_V2 {
	bool bEnable;
	int nWeight;									// ROI区域的权重 [0,15],一般取较大值
	sPoint point[4];								// 凸四边形，顺时针四个顶点
	char reserve[32];
}sAreaRoiV2;

typedef enum E_SDK_BACKLIGHT_MODETYPE {
	E_SDK_BACKLIGHT_AUTOMATIC = 0,					// 自动
	E_SDK_BACKLIGHT_MANUAL = 1,						// 手动
}eBackLightModeType;

typedef struct S_SDK_CAMERA_BACKLIGHT {
	bool bEnable;									// 背光使能
	eBackLightModeType eMode;						// 0为自动，1为自定义区域
	sAreaRoi areaRoi;								// 已废弃
	sAreaRoiV2 areaRoiV2;							// 背光范围
	char szReserve[32];
}sCameraBackLight;

typedef enum {
	E_CAMERA_MODE_LINEAR = 0,						// linear模式
	E_CAMERA_MODE_WDR = 1,							// wdr模式
	E_CAMERA_MODE_AUTO = 2,							// 自动模式
}eCameraWdrMode;

typedef struct S_SDK_CAMERA_WDR {
	bool bSupport;
	eCameraWdrMode mode;
	int nBvThreshold;								// 阈值，自动模式下显示有效[0,100]
	char szReserve[32];
}sCameraWdr;

typedef enum E_SDK_CAMERA_NOISEREDUCE_MODE {
	E_NOISE_REDUCE_DISABLE = 0,						// 关闭
	E_NOISE_REDUCE_2D = 1,							// 2D降噪
	E_NOISE_REDUCE_3D = 2,							// 3D降噪
}eNoiseReduceMode;

typedef struct S_SDK_CAMERA_3DNR_PARAM {
  int nLevel;										// 默认值0,取值范围[0,8]
  char szReserve[32];
}sCamera3DnrParam;

typedef struct S_SDK_CAMERA_NOISEREDUCE {
	eNoiseReduceMode mode;
	sCamera3DnrParam param;							// 3D降噪参数
	char szReserve[32];
}sCameraNoiseReduce;

typedef struct S_SDK_CAMERA_PARAM_CONFIG {
	bool bMirror;									// 水平镜像
	bool bFlip;										// 上下翻转
	bool bIrcut;									// ircut是否反序
	sCameraDnc dnc;
	sCameraExposure exposure;
	sCameraImage image;
	sCameraWhiteBalanceConfig wbMode;				// 白平衡
	sCameraDeh deh;									// 去雾
	sCameraBackLight backLight;						// 背光
	bool bIsEis;									// 电子防抖
	sCameraWdr wdr;									// 宽动态
	sCameraNoiseReduce noiseReduce;					// 数字降噪
	char szReserve[128];
}sCameraParamConfig;

typedef struct S_SDK_CAMERA_PARAM_CONFIG_All {
	int nCount;
	sCameraParamConfig param[NET_MAX_CHANNUM];
}sCameraParamConfigAll;

//************************摄像机参数V2************************//
// 参数管理 CPM(Camera param manager)
typedef enum E_SDK_CPM_SCENE_TYPE {
	E_CPM_SCENE_DAY = 0,							// 白天
	E_CPM_SCENE_NIGHT = 1,							// 夜晚
	E_CPM_SCENE_IN_DOOR = 2,						// 室内
	E_CPM_SCENE_OUT_DOOR = 3,						// 室外
	E_CPM_SCENE_NIGHTFALL = 4,						// 傍晚
	E_CPM_SCENE_STREET = 5,							// 道路
	E_CPM_SCENE_LOW_ILLUMINATION = 6,				// 低照度
	E_CPM_SCENE_FACE = 7,							// 人脸
	E_CPM_SCENE_CUSTOM1 = 8,						// 自定义1
	E_CPM_SCENE_CUSTOM2 = 9,						// 自定义2
	E_CPM_SCENE_NR,
	E_CPM_SCENE_MAX = 16,							// 预留用
}eCpmSceneType;

typedef struct S_SDK_CPM_PERIOD {
	eCpmSceneType linkScene;						// 对应场景
	sTimeSection timing;							// 定时
}sCpmPeriod;

typedef struct S_SDK_CPM_PERIOD_LIST {
	bool bEnable;									// 开启定时切换（开启后摄像机参数不支持修改）
	int nCount;										// 时间段个数，由设备给出，不支持修改
	sCpmPeriod period[E_CPM_SCENE_MAX];
}sCpmPeriodList;

typedef struct S_SDK_CAMERA_PARAM_MANAGER {
	eCpmSceneType curScene;							// 当前场景
	sCpmPeriodList periodList;
	uint nSceneMask;								// 展示场景掩码，详见eCpmSceneType
}sCameraCfgManager;

typedef struct S_SDK_CAMERA_PARAM_MANAGER_ALL {
	int nCount;
	sCameraCfgManager manager[NET_MAX_CHANNUM];
}sCameraCfgManagerAll;

// 电子防抖配置
typedef struct S_SDK_CAMERA_PARAM_EIS {
	bool bEnable;
}sCameraParamEis;

typedef struct S_SDK_CAMERA_PARAM_EIS_LIST{
	sCameraParamEis eis[E_CPM_SCENE_MAX];
}sCameraParamEisList;

typedef struct S_SDK_CAMERA_PARAM_EIS_ALL {
	int nCount;
	sCameraParamEisList list[NET_MAX_CHANNUM];
}sCameraCfgEisAll;

// 白平衡配置 CPW(Camera param wb) wb(White balance)
typedef enum E_SDK_CAMERA_PARAM_AWB_MODE {
	E_CPW_MODE_AUTO = 0,							// 自动模式
	E_CPW_MODE_MANUAL = 1,							// 手动模式
	E_CPW_MODE_TUNGSTENLAMP = 2,					// 钨丝灯模式
	E_CPW_MODE_SUNLIGHT = 3,						// 日光模式
	E_CPW_MODE_CLOUDY = 4,							// 晴天模式
	E_CPW_MODE_OVERCAST = 5,						// 阴天模式
	E_CPW_MODE_SHADE = 6,							// 阴影模式
}eCameraParamAwbMode;

typedef struct E_SDK_CAMERA_PARAM_AWB_CONFIG {
	eCameraParamAwbMode eMode;						// 白平衡模式
	uint nRGain;									// 手动模式下的r分量增益 [0,65535]
	uint nBGain;									// 手动模式下的b分量增益 [0,65535]
}sCameraParamAwbConfig;

typedef struct S_SDK_CAMERA_PARAM_AWB_LIST {
	sCameraParamAwbConfig awb[E_CPM_SCENE_MAX];
}sCameraParamAwbList;

typedef struct S_SDK_CAMERA_PARAM_AWB_ALL {
	int nCount;
	sCameraParamAwbList list[NET_MAX_CHANNUM];
}sCameraCfgAwbAll;

// 日夜转换配置
typedef enum E_SDK_CAMERA_PARAM_DNC_MODE_V2 {
	E_CPD_DNC_V2_AUTO = 0,							// 自动切换
	E_CPD_DNC_V2_COLOR = 1,							// 强制为彩色
	E_CPD_DNC_V2_BLACKWHITE = 2,					// 强制为黑白
}eCpdMode;

typedef struct S_SDK_CAMERA_PARAM_DNC_V2 {
	eCpdMode mode;									// 日夜切换的模式，参考EDncModeV2
	int nLevel;										// 自动切换时的灵敏度[0,5]
}sCameraParamDncV2;

typedef struct S_SDK_CAMERA_PARAM_DNC_LIST {
	sCameraParamDncV2 dnc[E_CPM_SCENE_MAX];
}sCameraParamDncList;

typedef struct S_SDK_CAMERA_PARAM_DNC_ALL {
	int nCount;
	sCameraParamDncList list[NET_MAX_CHANNUM];
}sCameraCfgDncAll;

// 补光灯配置 CPL(Camera param light)
typedef enum E_SDK_CPL_MODE {
	E_CPL_MODE_DISABLE = 0,							// 关闭
	E_CPL_MODE_AUTO = 1,							// 自动
	E_CPL_MODE_MANUAL = 2,							// 手动
	E_CPL_MODE_SMART = 3,							// 智能双光模式(仅在双光设备和智能算法下存在,仅在只能双光是能下才展示)
}eCplMode;

typedef struct S_SDK_CPL_PARAM {
	bool bSupport;									// 是否支持
	uint nModeMask;									// 支持的模式掩码，详细查看ELightModeType
	eCplMode mode;									// 补光灯模式
	bool bSupportLevel;								// 手动模式下是否支持调节亮度
	int nLevel;										// 手动模式下补光灯的强度
}sCplParam;

typedef struct S_SDK_CPL_SMART_DUAL_LIGHT {
	bool bSupport;									// 是否支持
	bool bEnable;									// 使能
}sCplSmartDualLight;

typedef struct S_SDK_CAMERA_PARAM_LIGHT {
	sCplParam infrared;								// 红外参数
	sCplParam white;								// 白光参数
	sCplSmartDualLight smart;						// 智能双光(仅在双光设备和智能算法下存在)
}sCameraCfgLight;

typedef struct S_SDK_CAMERA_PARAM_LIGHT_LIST {
	sCameraCfgLight light[E_CPM_SCENE_MAX];
}sCameraLightList;

typedef struct S_SDK_CAMERA_PARAM_LIGHT_ALL {
	int nCount;
	sCameraLightList list[NET_MAX_CHANNUM];
}sCameraCfgLightAll;

// 曝光配置 CPE(Camera param exposure)
typedef enum E_SDK_CAMERA_PARAM_EXPOSURE_MODE {
	E_CPE_MODE_AUTO = 0,							// 自动模式
	E_CPE_MODE_MANUAL = 1,							// 手动模式
}eCpeMode;

// auto
typedef struct S_SDK_CPE_AUTO_PARAM {
	bool bSlowShutter;								// 是否自动降帧
	int nSpeed;										// 自动曝光速度,[0x0,0xFF]
	int nCompensation;								// 自动曝光调整时的目标亮度,[0x0,0xFF]
	uint nExptimemax;								// 自动曝光时间,(0x0,0xFFFFFFFF]
	eCameraAntiflicker flicker;						// 抗闪烁
	uint nSysgainmax;								// 系统增益上限,(0x0,0xFFFFFFFF]
}sCpeAutoParam;

// manual
typedef struct S_SDK_CPE_MANUAL_PARAM {
	int nGain;										// 手动曝光增益,[0x400,0xFFFFFFFF]
	uint nExpvalue;									// 手动曝光时间,(0x0,0xFFFFFFFF]
}sCpeManualParam;

typedef struct S_SDK_CAMERA_PARAM_EXPOSURE_V2 {
	eCpeMode mode;									// 曝光模式模式
	sCpeAutoParam autoParam;						// 自动曝光参数
	sCpeManualParam manualParam;					// 手动曝光参数
}sCameraParamExposureV2;

typedef struct S_SDK_CAMERA_PARAM_EXPOSURE_LIST {
	sCameraParamExposureV2 exposure[E_CPM_SCENE_MAX];
}sCameraExposureList;

typedef struct S_SDK_CAMERA_PARAM_EXPOSURE_ALL {
	int nCount;
	sCameraExposureList list[NET_MAX_CHANNUM];
}sCameraCfgExposureAll;

// 图像配置
typedef struct S_SDK_CAMERA_PARAM_IMAGE {
	int nHue;										// 色度 [0,100] 默认50
	int nLuma;										// 亮度 [0,100] 默认50
	int nContr;										// 对比度 [0,100] 默认50
	int nSatu;										// 饱和度 [0,100] 默认50
	int nSharpenMode;								// 锐化工作模式 0: 自动，detailCtrl无效 1:手动，detailCtrl生效
	int nDetailCtrl;								// 锐化的细节纹理强度，[0,0xFF]
}sCameraParamImage;

typedef struct S_SDK_CAMERA_PARAM_IMAGE_LIST {
	sCameraParamImage image[E_CPM_SCENE_MAX];
}sCameraParamImageList;

typedef struct S_SDK_CAMERA_PARAM_IMAGE_ALL {
	int nCount;
	sCameraParamImageList list[NET_MAX_CHANNUM];
}sCameraCfgImageAll;

// 去雾配置
typedef struct S_SDK_CAMERA_PARAM_DEH {
	bool bEnable;									// 去雾使能
	int  nOptype;									// 0自动 1手动
	int  nManualValue;								// 手动模式下去雾强度 [0, 255]
	int  nAutoValue;								// 自动模式下去雾强度 [0, 255]
}sCameraParamDeh;

typedef struct S_SDK_CAMERA_PARAM_DEH_List {
	sCameraParamDeh deh[E_CPM_SCENE_MAX];
}sCameraParamDehList;

typedef struct S_SDK_CAMERA_PARAM_DEH_ALL {
	int nCount;
	sCameraParamDehList list[NET_MAX_CHANNUM];
}sCameraCfgDehAll;

// 背光配置
typedef struct S_SDK_CAMERA_PARAM_BACKLIGHT {
	bool bEnable;									// 背光使能
	eBackLightModeType eMode;						// 0为自动，1为自定义区域
	sAreaRoiV2 areaRoi;								// 背光范围
}sCameraParamBackLight;

typedef struct S_SDK_CAMERA_PARAM_BACKLIGHT_List {
	sCameraParamBackLight backlight[E_CPM_SCENE_MAX];
}sCameraParamBackLightList;

typedef struct S_SDK_CAMERA_PARAM_BACKLIGHT_ALL {
	int nCount;
	sCameraParamBackLightList list[NET_MAX_CHANNUM];
}sCameraCfgBacklightAll;

// 宽动态配置
typedef struct S_SDK_CAMERA_PARAM_WDR {
	eCameraWdrMode mode;
}sCameraParamWdr;

typedef struct S_SDK_CAMERA_PARAM_WDR_List {
	sCameraParamWdr wdr[E_CPM_SCENE_MAX];
}sCameraParamWdrList;

typedef struct S_SDK_CAMERA_PARAM_WDR_ALL {
	int nCount;
	sCameraParamWdrList list[NET_MAX_CHANNUM];
}sCameraCfgWdrAll;

// 降噪配置 CPNR(Camera param noise reduce)
typedef enum E_SDK_CPNR_MODE_TYPE {
	E_CPNR_MODE_DISABLE = 0,						// 关闭
	E_CPNR_MODE_AUTO = 1,							// 自动
	E_CPNR_MODE_MANUAL = 2,							// 手动
}eCpnrModeType;

typedef struct S_SDK_CPNR_PARAM {
	eCpnrModeType mode;								// 降噪模式
	int nLevel;										// 降噪级别,范围[0,100]
}sCpnrParam;

typedef struct S_SDK_CAMERA_PARAM_NOISE_REDUCE {
	sCpnrParam nr2d;								// 2D降噪
	sCpnrParam nr3d;								// 3D降噪
}sCameraParamNoiseReduce;

typedef struct S_SDK_CAMERA_PARAM_NOISE_REDUCE_List {
	sCameraParamNoiseReduce noiseReduce[E_CPM_SCENE_MAX];
}sCameraParamNoiseReduceList;

typedef struct S_SDK_CAMERA_PARAM_NOISE_REDUCE_ALL {
	int nCount;
	sCameraParamNoiseReduceList list[NET_MAX_CHANNUM];
}sCameraCfgNoiseReduceAll;

// 图像翻转配置 CPI(Camera image flip)
typedef enum E_SDK_CPI_FLIP_TYPE {
	E_CPI_FLIP_DISABLE = 0,							// 关闭
	E_CPI_FLIP_UPDOWN = 1,							// 上下
	E_CPI_FLIP_LEFTRIGHT = 2,						// 左右
	E_CPI_FLIP_CENTER = 3,							// 中心
}eCpiFlipType;

typedef struct S_SDK_CAMERA_PARAM_IMAGE_FLIP {
	eCpiFlipType mode;
}sCameraImageFlip;

typedef struct S_SDK_CAMERA_PARAM_IMAGE_FLIP_ALL {
	int nCount;
	sCameraImageFlip imageFlip[NET_MAX_CHANNUM];
}sCameraCfgImageFlipAll;

// ircut反序
typedef struct S_SDK_CAMERA_PARAM_IRCUT {
	bool bEnable;
}sCameraParamIrcut;

typedef struct S_SDK_CAMERA_PARAM_IRCUT_ALL {
	int nCount;
	sCameraParamIrcut ircut[NET_MAX_CHANNUM];
}sCameraCfgIrcutAll;

//************************相机能力集 begin************************//
enum E_SDK_CAMERA_ABILITY_TYPE {
	K_CAMERA_ABILITY_MIRROR = 0,								// 水平镜像
	K_CAMERA_ABILITY_FLIP = 1,									// 上下翻转
	K_CAMERA_ABILITY_INVIRCUT = 2,								// IR镜片反序
	K_CAMERA_ABILITY_DNC = 3,									// 日夜切换
	K_CAMERA_ABILITY_EXP = 4,									// 曝光参数
	K_CAMERA_ABILITY_IMG = 5,									// 图像调节
	K_CAMERA_ABILITY_DEH = 6,									// 去雾
	K_CAMERA_ABILITY_BLC = 7,									// 背光
	K_CAMERA_ABILITY_AWB = 8,									// 白平衡
	K_CAMERA_ABILITY_WDR = 9,									// 宽动态
	K_CAMERA_ABILITY_NOISEREDUCE = 10,							// 数字降噪
	K_CAMERA_ABILITY_EIS = 11,									// 电子防抖
};

typedef struct E_SDK_CAMERA_ABILITY {
	uint nTypeMask;												// camera类型，见枚举E_SDK_CAMERA_ABILITY_TYPE
}sCameraAbility;

typedef struct E_SDK_CAMERA_ABILITY_ALL {
	sCameraAbility ability[NET_MAX_CHANNUM];
}sCameraAbilityAll;

///////////////////报警相关结构体/////////////////////////////////
typedef struct E_SDK_EVENT_LINK_AUDIO {
	bool bEnable;
	int nCount;													// 报警次数[1,3]
	char szPath[256];											// 声音路径
}sEventLinkAudio;

typedef enum E_SDK_EL_LIGHT_MODE {
	E_EL_LIGHT_MODE_FLICKER = 0,								// 闪烁
	E_EL_LIGHT_MODE_CONTINUOUS = 1,								// 常亮
}eElLightMode;

typedef enum E_SDK_EL_FREQUENCY_TYPE {
	E_EL_FREQUENCY_TYPE_LOW = 0,
	E_EL_FREQUENCY_TYPE_MIDDLE = 1,
	E_EL_FREQUENCY_TYPE_HIGH = 2,
}eElLightFrequencyType;

typedef struct E_SDK_EVENT_LINK_LIGHT {
	bool bEenable;
	eElLightMode mode;
	eElLightFrequencyType frequency;							// 闪烁频率
	int nDuration;												// 报警时长[5,30]
	int nLevel;													// 亮度等级[0,100]
}sEventLinkLight;

typedef struct S_SDK_EVENT_HANDLER {
	sWorkSheetConfig wcWorkSheet;
	bool bRecord;
	uint unRecordMask;
	int nRecordDelay;								// 录像延时(s)

	bool bSnap;
	uint unSnapMask;

	bool bAlarmout;
	uint unAlarmoutMask;
	int nAlarmoutDelay;								// 报警输出延时(s)

	bool bEmail;
	bool bBeep;
	bool bFtp;
	bool bLog;

	sEventLinkAudio audio;
	sEventLinkLight light;
}sEventHandler;

typedef struct S_SDK_ALARM_INPUTCONFIG {
	bool bEnable;
	bool bSensor;									// 传感器类型 false:常闭 true:常开
	sEventHandler event;
}sAlarmInputConfig;

typedef struct S_SDK_ALARM_INPUTCONFIG_ALL {
	int nCount;
	sAlarmInputConfig inConfigAll[NET_MAX_CHANNUM];
}sAlarmInputConfigAll;

typedef struct S_SDK_ALARM_BLIND_DETECT {
	bool bEnable;
	int  nLevel;
	sEventHandler event;
}sBlindDetectConfig;

typedef struct S_SDK_ALARM_BLIND_DETECT_ALL {
	int nCount;
	sBlindDetectConfig configAll[NET_MAX_CHANNUM];
}sBlindDetectConfigAll;

typedef struct S_SDK_ALARM_MOTION_DETECT {
	bool bEnable;
	int  nLevel;
	uint unRectMask[18];
	sEventHandler event;
}sMotionDetectConfig;

typedef struct S_SDK_ALARM_MOTION_DETECT_ALL {
	int nCount;
	sMotionDetectConfig configAll[NET_MAX_CHANNUM];
}sMotionDetectConfigAll;

///////////////////////////////////////////////////////////////////////////////
// 入侵检测，非智能入侵检测只支持一种规则同时存在，越界侦测支持4个，区域入侵支持一个
///////////////////////////////////////////////////////////////////////////////
typedef enum {
	E_ID_RULE_CROSS_LINE = 0,						// 越界侦测
	E_ID_RULE_CROSS_REGION = 1,						// 区域入侵
	E_ID_RULE_SAFE_HELMET = 2,						// 安全帽监测
	E_ID_RULE_ILLEGAL_PARKING = 3,					// 车辆违停
	E_ID_RULE_RESPIRATOR = 4,						// 未戴口罩
}eIDRuleType;

// 如果规则类型为绊线, 则A代表左B代表右
// 如果规则类型为区域, 则A代表内B代表外
typedef enum E_SDK_INTRUSION_DETECT_DIRECTION_TYPE {
	E_ID_DIRECTION_B2A = 0,
	E_ID_DIRECTION_A2B = 1,
	E_ID_DIRECTION_AB = 2,
}eIDDirectionType;

enum E_SDK_INTRUSION_DETECT_ACTION {
	E_IM_ACTION_UNKNOWN = 0x0,
	E_IM_ACTION_APPEAR = 0x1,						// 出现
	E_IM_ACTION_PASS = 0x2,							// 通过
};

enum E_SDK_INTRUSION_DETECT_ALARM_OBJECT {
	E_IM_ALARM_OBJECT_UNKNOWN = 0x0,
	E_IM_ALARM_OBJECT_HUMAN = 0x1,					// 人
	E_IM_ALARM_OBJECT_VEHICLE = 0x2,				// 机动车
	E_IM_ALARM_OBJECT_CYCLE = 0x4,					// 非机动车
	E_IM_ALARM_OBJECT_FACE = 0x8,					// 脸
	E_IM_ALARM_OBJECT_PLATE = 0x10,					// 车牌
};

typedef struct S_SDK_INTRUSION_DETECT_RULE {
	bool bEnable;
	char szRuleName[64];
	eIDRuleType type;
	sPoint detectPts[8];							// 需要按照描点顺序给出(线段或者凸四边形)
	sSize2i maxSize;								// 0*0~8191*8191, 且大于minSize
	sSize2i minSize;								// 0*0~8191*8191, 且小于maxSize
	int nAction;									// 事件类型掩码，详见E_SDK_INTRUSION_DETECT_ACTION
	eIDDirectionType direction;
	int nObjectMask;								// 目标类型掩码，详见E_SDK_INTRUSION_DETECT_ALARM_OBJECT
	sEventHandler event;
	int nLevel;										// 非智能人形检测:[1~4]，1-4分别对应 高、中、低、极低，默认2; 车辆违停:[1~100]，默认80
	bool bIndoor;									// 是否是室内，默认false（目前仅用于非智能入侵检测）
	int nTimeThreshold;								// 时间阈值:[3-300]，默认10
}sIntrusionDetectRule;

typedef struct S_SDK_INTRUSION_DETECT_CFG {
	int nRuleCount;
	sIntrusionDetectRule rule[10];
}sIntrusionDetect;

typedef struct S_SDK_INTRUSION_DETECT_CFG_ALL {
	int nCount;
	sIntrusionDetect detect[NET_MAX_CHANNUM];
}sIntrusionDetectAll;

typedef enum E_SDK_ALARMOUT_TYPE {
	E_SDK_ALARMOUT_TYPE_CLOSE = 0,
	E_SDK_ALARMOUT_TYPE_AUTO = 1,
	E_SDK_ALARMOUT_TYPE_MANUAL = 2,
}eAlarmOutType;

typedef struct S_SDK_ALARM_OUTPUTCONFIG {
	eAlarmOutType type;
	bool bState;									// true代表打开 false代表关闭
}sAlarmOutputConfig;

typedef struct S_SDK_ALARM_OUTPUTCONFIG_ALL {
	int nCount;
	sAlarmOutputConfig outConfigAll[NET_MAX_CHANNUM];
}sAlarmOutputConfigAll;

// 硬盘满
typedef struct S_SDK_ALARM_DISKFULL_CONFIG {
	bool bEnable;
	sEventHandler event;							// 仅且仅需配置邮件、报警输出联动
}sAlarmDiskFullConfig;

// 硬盘错误
typedef struct S_SDK_ALARM_DISKERROR_CONFIG {
	bool bEnable;
	sEventHandler event;							// 仅且仅需配置邮件、报警输出联动
}sAlarmDiskErrorConfig;

// 网络断开
typedef struct S_SDK_ALARM_NIC_BROKEN_CONFIG {
	bool bEnable;
	sEventHandler event;							// 仅且仅需配置报警输出、录像联动
}sAlarmNicBrokenConfig;

// IP冲突
typedef struct S_SDK_ALARM_IP_CONFLICT_CONFIG {
	bool bEnable;
	sEventHandler event;							// 仅且仅需配置报警输出、录像联动
}sAlarmIpConflictConfig;

// 非法访问
typedef struct S_SDK_ALARM_ILLEGAL_LOGIN_CONFIG {
	bool bEnable;
	sEventHandler event;							// 仅且仅需配置报警输出、发送邮件
}sAlarmIllegalLoginConfig;

// 音频监测
///////////////////////////////////////////////////////////////////////////////
// AAD = Alaram audio detect
// 输入异常
typedef struct S_SDK_AAD_ANOMALY_DETECT {
	bool bEnable;
}sAadAnomalyDetect;

// 声强突变
typedef struct S_SDK_AAD_MUTATION_DETECT {
	bool bEnable;
	int nThreshold;									// 阈值 [1, 100]
	int nLevel;										// 灵敏度 [1, 100]
}sAadMutationDetect;

typedef struct S_SDK_AAD_CONFIG {
	sAadAnomalyDetect anomalyDetect;
	sAadMutationDetect mutationDetect;
	sEventHandler event;
}sAaDetectConfig;

typedef struct S_SDK_AAD_CONFIG_ALL {
	int nCount;
	sAaDetectConfig detect[NET_MAX_CHANNUM];
}sAaDetectConfigAll;

///////////////////////////////////////////////////////////////////////////////
// 人形侦测
///////////////////////////////////////////////////////////////////////////////
typedef struct S_SDK_ALARM_HUMAN_DETECT {
	bool bEnable;
	int nLevel;										// [1,5]
	sRect2i rect;									// x[0,8191] y[0,8191] w[1,8192] h[1,8192]
	sEventHandler event;
}sAlarmHumanDetect;

typedef struct S_SDK_ALARM_HUMAN_DETECT_ALL {
	int nCount;
	sAlarmHumanDetect detect[NET_MAX_CHANNUM];
}sAlarmHumanDetectAll;

//区域遮挡设置
///////////////////////////////////////////////////////////////////////////////
//每个区域参数
typedef struct S_SDK_VIDEOCOVER_PARAM {
	bool bEnable;									// 使能
	bool bShow;										// 是否显示
	int nLayer;										// 区域层次[0, 7],暂为0
	uint unColor;									// 格式为PIXEL_FORMAT_RGB_888 比如0xff0000 0x00ff00
	sRect rect;										// 这里使用相对坐标,相对8192 x[0, 8191], y[0, 8191], width[1, 8192], height[1, 8192]
}sVideoCoverParam;

typedef struct S_SDK_VIDEOCOVER_CONFIG {
	int nSupportCount;								// 遮挡区域支持个数，不可修改
	sVideoCoverParam coverParam[8];					// 每个通道参数，每个通道最多8个遮挡区域
}sVideoCoverConfig;

typedef struct S_SDK_VIDEOCOVER_CONFIG_ALL {
	int nCount;
	sVideoCoverConfig coverCfg[NET_MAX_CHANNUM];
}sVideoCoverConfigAll;

// OSD设置
///////////////////////////////////////////////////////////////////////////////
//单个OSD区域参数
typedef enum E_SDK_OSD_MODE_TYPE {
	E_SDK_OSD_OUTLINE_MODE = 0,						// 勾边
	E_SDK_OSD_INVERTCOLOR_MODE = 1,					// 反色
}eOsdModeType;

// 额外OSD类型
typedef enum E_SDK_OSD_EXTRA_TYPE {
	E_OSD_EXTRA_PTZ_ZOOM = 0,
	E_OSD_EXTRA_PTZ_MENU_PRESET = 1,
	E_OSD_EXTRA_GNSS = 2,
	E_OSD_EXTRA_WATERMARK = 3,
}eOsdExtraType;

typedef enum E_SDK_OSD_ALIGN_TYPE {
	E_OSD_ALIGN_LEFT = 0,
	E_OSD_ALIGN_RIGHT = 1,
}eOsdAlignType;

typedef struct S_SDK_OSD_PARAM {
	bool bShow;
	char szText[64];								// 显示内容（仅通道标题和自定义OSD有效）
	sRect rect;										// 这里使用相对坐标,相对8192 x[0, 8191], y[0, 8191], width[1,8192], height[1, 8192]
	int nFGAlpha;									// 前景透明度，[0,128],取值越小越透明
	int nBGAlpha;									// 背景透明度，[0,128],取值越小越透明
	int nBGColor;									// 背景色，格式为rgb555
	int nFontSize;									// 字体大小
	eOsdModeType eMode;								// 显示模式
	eOsdExtraType extraType;						// 额外OSD类型(仅额外OSD有效)
	bool bSupport;									// 是否支持，仅自定义osd和额外osd有效，实际生效的数量和为6个(能力集，只读)
	bool bShowWeek;									// 是否显示星期，仅时间标题有效
	uint nStreamHideMask;							// 是否隐藏各个码流的osd掩码，从低到高位分别对应第1、2、3码流
	eOsdAlignType alignType;						// 对齐方式
	char szReserve[16];
}sOsdParam;

//所有通道的标题
typedef struct S_SDK_CHANNEL_TITLE_CONFIG_ALL {
	int nCount;
	sOsdParam param[NET_MAX_CHANNUM];
}sChannelTitleConfigAll;

typedef struct S_SDK_TIME_TITLE_CONFIG_ALL {
	int nCount;
	sOsdParam param[NET_MAX_CHANNUM];
}sTimeTitleConfigAll;

//每个通道的自定义OSD，固定6个，由sOsdParam::bSupport决定是否支持
typedef struct S_SDK_CUSTOM_OSD_CONFIG {
	sOsdParam param[6];
}sOsdCustomConfig;

//所有通道的自定义OSD
typedef struct  S_SDK_CUSTOM_OSD_CONFIG_ALL {
	int nCount;
	sOsdCustomConfig osd[NET_MAX_CHANNUM];
}sCustomOSDInfoConfigAll;

//每个通道的额外OSD，固定6个，由sOsdParam::bSupport决定是否支持
typedef struct S_SDK_EXTRA_OSD_CONFIG {
	sOsdParam param[6];
}sExtraOsdConfig;

//所有通道的额外OSD
typedef struct  S_SDK_EXTRA_OSD_CONFIG_ALL {
	int nCount;
	sExtraOsdConfig osd[NET_MAX_CHANNUM];
}sExtraOsdInfoConfigAll;

///////////////////存储相关结构体/////////////////////////////////
typedef enum E_SDK_STORAGE_FILE_TYPE {		// 废弃
	E_SDK_UnKnown = 0,
	E_SDK_RECORD_ALL = 1,
	E_SDK_PIC_ALL = 100,
	E_SDK_TYPE_NUM
}eStorageFileType;

typedef enum E_SDK_STORE_FILE_TYPE {
	E_STORE_FILE_UNKNOWN = 0,						// 未定义

	//单独搜索录像类型，保持与录像内部值一致
	E_STORE_VIDEO_SCHEDULE = 1,						// 定时录像
	E_STORE_VIDEO_MANUAL = 2,						// 手动录像
	E_STORE_VIDEO_MOTION = 4,						// 移动侦测
	E_STORE_VIDEO_IO_ALARM = 8,						// 报警录像
	E_STORE_VIDEO_EVENT = 9,						// 事件录像
	
	//单独搜索图片类型，保持与存储内部值+300
	E_STORE_PIC_SCHEDULE = 301,						// 定时抓图
	E_STORE_PIC_MANUAL = 302,						// 手动抓图
	E_STORE_PIC_MOTION = 303,						// 移动侦测抓图
	E_STORE_PIC_ALARMIN = 304,						// 报警输入抓图
	E_STORE_PIC_VIDEO_BLOCK = 305,					// 视频遮挡抓图
	E_STORE_PIC_ANR = 306,							// 断网续传图片
	E_STORE_PIC_NORMAL = 316,						// 普通图片（老接口使用，考虑兼容保留）
	E_STORE_PIC_INTER_FACE = 331,					// 智能图片，人脸小图
	E_STORE_PIC_INTER_FACE_BG = 332,				// 智能图片，背景图
	E_STORE_PIC_INTER_BODY = 333,					// 智能图片，人形小图
	E_STORE_PIC_INTER_BODY_BG = 334,				// 智能图片，背景图
	E_STORE_PIC_INTER_CAR = 335,					// 智能图片，汽车小图
	E_STORE_PIC_INTER_CAR_BG = 336,					// 智能图片，背景图
	E_STORE_PIC_INTER_PLATE = 337,					// 智能图片，车牌小图
	E_STORE_PIC_INTER_PLATE_BG = 338,				// 智能图片，背景图
	E_STORE_PIC_INTER_CYCLE = 339,					// 智能图片，非机动车小图
	E_STORE_PIC_INTER_CYCLE_BG = 340,				// 智能图片，背景图

	//组合搜索类型
	E_STORE_VIDEO_ALL = 900,						// 代表所有录像类型
	E_STORE_PIC_ALL = 901,							// 代表所有图片类型
}eStoreFileType;

/// 录像模式种类
typedef enum E_SDK_RecordModeTypes {
	E_SDK_RECORD_MODE_CLOSED,						// 关闭录像
	E_SDK_RECORD_MODE_MANUAL,						// 手动录像
	E_SDK_RECORD_MODE_CONFIG,						// 按配置录像
	E_SDK_RECORD_MODE_NR,
}eRecordModeTypes;

/// 磁盘信息
typedef enum E_SDK_FILESYSTEM_TYPE {
	E_SDK_FILESYSTEM_TYPE_None = 0,					// 未知文件系统
	E_SDK_FILESYSTEM_TYPE_Fat32 = 1,				// FAT32
	E_SDK_FILESYSTEM_TYPE_Ntfs = 2,					// NTFS
	E_SDK_FILESYSTEM_TYPE_Stfs = 3,					// STFS
}eFileSysType;

typedef enum E_SDK_DISKBUS_TYPE {
	E_SDK_DISKBUS_TYPE_SATA = 0,					// 本地磁盘
	E_SDK_DISKBUS_TYPE_ESATA = 1,					// 可以支持热插拨的SATA接口
	E_SDK_DISKBUS_TYPE_USB = 2,						// USB接口
	E_SDK_DISKBUS_TYPE_SDCARD = 3,					// SDCard接口
}eDiskBusType;

typedef enum E_SDK_DISKFUNC_TYPE {
	E_SDK_DISKFUNC_TYPE_UnFormat = 0,				// 未格式化
	E_SDK_DISKFUNC_TYPE_Record = 1,					// 录像
	E_SDK_DISKFUNC_TYPE_Backup = 2,					// 备份
}eDiskFuncType;

typedef struct S_SDK_DISK_PARTITION_INFO {
	eFileSysType type;								// 文件系统类型
	char szLabel[64];								// 标签
	char szMntDir[256];								// 挂载路径
}sDiskPartitionInfo;

typedef struct S_SDK_DISK_INFORMATION {
	eDiskBusType busType;							// 磁盘类型
	eDiskFuncType funcType;							// 磁盘用途
	int nBusId;
	int nDiskIndex;									// 磁盘编号
	bool bFormated;									// 是否已经格式化
	bool bFormatStfs;								// 是否能格式化成STFS
	bool bStfs;
	bool bBusy;										// 是否忙碌
	char szDiskName[64];							// 磁盘名字
	uint nFreeSpace;								// 剩余空间(MB)
	uint nTotalSpace;								// 总空间(MB)（异常情况下大小为0）
	sDiskPartitionInfo partitions[SDK_MAX_DRIVER_PER_DISK]; // 分区信息
	uint nImageSpace;								// 图片使用空间(MB)（录像使用空间 = nTotalSpace - nFreeSpace - nImageSpace）
	uint nImgPartRatio;								// 图片空间比例(弃用)
}sDiskInformation;

typedef struct S_SDK_DISK_INFORMATION_ALL {
	int iDiskNumber;
	sDiskInformation vDiskInfo[SDK_MAX_DISK_PER_MACHINE];
}sDiskInformationAll;

typedef struct S_SDK_DISK_MANAGER_CONTROL {
	int nDiskIndex;									// 硬盘ID， 暂只支持格式化磁盘操作
}sDiskManagerControl;

///< 录像设置（废弃）
///////////////////////////////////////////////////////////////////////////////
//     每天可配置最小时间为半小时，用48个bit表示
//     bit#0   00:00:00 - 00:29:59
//     bit#1   00:29:59 - 00:59:59
//     bit#2   01:00:00 - 01:29:59
//     ...
//     bit#47  23:30:00 - 23:59:59
///////////////////////////////////////////////////////////////////////////////
typedef struct S_SDK_DAY_SCHEDULE {
	uint64 timeSection;
}sDaySchedule;

typedef struct S_SDK_RECORD_SCHEDULE {
	sDaySchedule dayScheduler[7];					// 工作时间段，固定7个工作表 周一，...周日
}sRecordSchedule;

typedef struct S_SDK_RECORDCONFIG {
	eRecordModeTypes recordMode;					// 录像模式
	sRecordSchedule workSheet;						// 录像时间段
}sRecordConfig;

//录像设置结构体
typedef struct S_SDK_RECORDCONFIG_ALL {
	int nCount;
	sRecordConfig vRecordConfigAll[NET_MAX_CHANNUM];
}sRecordConfigALL;

// 录像配置V2
typedef struct S_SDK_RECORDCONFIG_V2{
	eRecordModeTypes recordMode;
	sWorkSheetConfig workSheet;						// 录像时间段
}sRecordConfigV2;

typedef struct S_SDK_RECORDCONFIG_ALL_V2 {
	int nCount;
	sRecordConfigV2 mainChannel[NET_MAX_CHANNUM];
	sRecordConfigV2 subChannel[NET_MAX_CHANNUM];
}sRecordConfigAllV2;

///< 抓图设置
typedef struct S_SDK_SNAPCONFIG {
	bool bStorage;									// 存在sd卡,默认打开
	bool bFtp;										// 传送ftp，默认关闭
	bool bEmail;									// 传送email，默认关闭
	int nInterval;									// 时间间隔，取值范围5-9999s，默认5s
	eRecordModeTypes recordMode;					// 抓图模式
	sWorkSheetConfig wcWorkSheet;					// 抓图时间段
}sSnapConfig;

//抓图设置结构体
typedef struct S_SDK_SNAPSHOT_CONFIG_ALL {
	int nCount;
	sSnapConfig vSnapConfigAll[NET_MAX_CHANNUM];
}sSnapShotConfigALL;

//存储策略
typedef struct S_SDK_STORAGE_POLICY_CONFIG {
	bool bCoverage;									// 覆盖策略，默认覆盖
	uint nImgPartRatio;								// 图片容量比例   配额范围(0~100]  >100未配额
	uint nMRecPartRatio;							// 主码流容量比例 配额范围(0~100]  >100未配额
	uint nSRecPartRatio;							// 子码流容量比例 配额范围(0~100]  >100未配额
}sStoragePolicyConfig;

//录像查询条件
typedef struct S_SDK_RECODE_CONDITION {
	int nYear;										// 形如2019
	int nMonth;										// 1-12 对应1到12月
	uint64 nChannelMask;							// 通道掩码
	eStoreFileType fileType;						// 文件类型
	eStreamType stream;
}sRecordCondition;

//哪些天有符合要求的录像或图片
typedef struct S_SDK_RECODE_SEARCH_EXIST {
	int mask;										// 每位代表一天从低位开始，1:有录像, 0:无录像
}sRecordSearchExist;

typedef struct S_SDK_DATE_TIME {
	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMinute;
	int nSecond;
}sDateTime;

// 事件类型，保持与存储内部值+1
typedef enum {
	E_RECORD_EVENT_TYPE_UNKNOWN = 0,				// 未定义
	E_RECORD_EVENT_TYPE_FACE = 1,					// 人脸
	E_RECORD_EVENT_TYPE_BODY = 2,					// 人体
	E_RECORD_EVENT_TYPE_VEHICLS = 3,				// 机动车
	E_RECORD_EVENT_TYPE_CYCLE = 4,					// 非机动车
	E_RECORD_EVENT_TYPE_PLATE = 5,					// 车牌
}eRecordEventType;

// 人脸参数
typedef struct {
	uint nAgeBegin;									// 年龄 起始
	uint nAgeEnd;									// 年龄 结束
	uint nGenderMask;								// 性别掩码 0未知 1男性 2女性
	uint nEyeMask;									// 眼睛掩码 0未知 1闭眼 2睁眼
	uint nNoseMask;									// 鼻子掩码 0未知 1有 2没有
	uint nMouthMask;								// 嘴巴掩码 0未知 1闭嘴 2张嘴
	uint nBeardMask;								// 胡子掩码 0未知 1没有 2小胡子 3腮须 4其他类型
	uint nSkinColorMask;							// 肤色掩码 0未知 1黄 2白 3黑 4深色
	uint nGlassMask;								// 眼镜掩码 0未知 1不戴  2戴 3深色透明 4普通透明 5太阳墨镜
	uint nRespiratorMask;							// 口罩掩码 0未知 1不戴 2戴 3医用口罩 4雾霾口罩 5普通口罩 6厨房透明口罩
	uint nMaskMask;									// 面具掩码 0未知 1有面具 2无面具
	uint nHairMask;									// 头发掩码 0未知 1光头 2很少，包含秃顶 3短头发 4长头发 5其他发型
	uint nHatColorMask;								// 帽子颜色掩码 0未知 1白色 2其他颜色
	uint nHatStyleMask;								// 帽子类型掩码 0未知 1戴帽子 2不戴帽子 3安全帽 4厨师帽 5学生帽 6头盔 7头巾 8其他帽子
}sRecordEventFaceParam;

// 人体参数
typedef struct {
	uint nClothesColor;								// 上衣颜色 0未知 1黑色 2白色 3灰色 4红色 5橙色 6黄色 7绿色 8深蓝色 9浅蓝色 10紫色 11粉红色 12棕色 13彩色
	uint nClothesStyle;								// 上衣款式 0未知 1长袖 2短袖
	uint nPantsColor;								// 裤子颜色 同上衣颜色
	uint nPantsStyle;								// 裤子款式 0未知 1长裤 2短裤 3裙子
	uint nBags;										// 包 0未知 1背包 2不背包 3双肩背包 4单肩包斜挎包 5手提包 6拉杆箱
	uint nRidebke;									// 骑车 0未知 1骑车 2不骑车 
	uint nUmbrella;									// 雨伞 0未知 1打伞 2不打伞
	uint ngender;									// 性别 0未知 1男性 2女性
	uint nHair;										// 头发 0未知 1光头 2很少头发包含秃顶 3短头发 4长头发 5其他发型
	uint nHatColor;									// 帽子颜色 0未知 1白色 2其他颜色
	uint nHatStyle;									// 帽子种类 0未知 1戴帽子 2不戴帽子 3安全帽 4厨师帽 5学生帽 6头盔 7头巾 8其他帽子
	uint nActionTumble;								// 跌倒动作 0未知 1跌倒 2未跌倒
	uint nActionSmoke;								// 抽烟动作 0未知 1抽烟 2未抽烟
	uint nActionRun;								// 奔跑动作 0未知 1奔跑  2未奔跑
	uint nActionCalling;							// 打电话动作 0未知 1打电话 2未打电话
	uint nActionWatchphone;							// 看手机动作 0未知 1看手机 2未看手机
}sRecordEventBodyParam;

// 机动车参数
typedef struct {
	uint nType;										// 机动车类型 0未知 1小轿车 2suv 3面包车 4中巴车和大巴车 5皮卡车 6卡车 7其他
	uint nColor;									// 机动车颜色 0未知 1黑色 2白色 3银灰 4棕色 5红色 6蓝色 7黄色 8绿色 9花色
	uint nOrientation;								// 机动车朝向 0未知 1正向 2背向 3其他
	uint nBrand;									// 机动车品牌  按值传递 按值传递 大众、宝马...
	uint nModel;									// 机动车型号  按值映射 高尔夫2009款...
}sRecordEventVehiclesParam;

// 非机动车参数
typedef struct {
	uint nType;										// 非机动车类型 0未知 1自行车 2电动车 3摩托车 4三轮车 5其他
}sRecordEventCycleParam;

// 车牌参数
typedef struct {
	uint nType;										// 车牌类型 0单行 1双行
	uint nColor;									// 车牌颜色 0蓝色 1黄色 2黑色 3白色 4绿色 5小型新能源 6大型新能源 7缺省
	int nCount;
	uchar plateCode[32];							// 车牌字符 省份、字母、数字按值映射
}sRecordEventPlateParam;

// 事件搜索参数
typedef struct {
	eRecordEventType eType;							// 搜索类型
	sRecordEventFaceParam face;						// 人脸参数
	sRecordEventBodyParam body;						// 人体参数
	sRecordEventVehiclesParam vehicle;				// 机动车参数
	sRecordEventCycleParam cycle;					// 非机动车参数
	sRecordEventPlateParam plate;					// 车牌参数
}sRecordEventSearchParam;

// 异步搜索
typedef enum {
	E_RECORD_SEARCH_ASYNC_UNKNOWN = 0,				// 未定义
	E_RECORD_SEARCH_ASYNC_START = 1,				// 开始异步搜索
	E_RECORD_SEARCH_ASYNC_STOP = 2,					// 结束异步搜索
}eRecordSearchAsyncType;

//查询录像条件
typedef struct S_SDK_RECODE_SEARCH_CONDITION {
	uint64 nChannelMask;							// 通道掩码
	sDateTime startTime;
	sDateTime endTime;
	eStoreFileType fileType;						// 搜索录像/图片类型
	uint nMaxNum;									// 请求个数 不超过64
	uint nRecordCnt;								// 已经收到结果的数量
	eStreamType stream;
	sRecordEventSearchParam eventParam;				// 搜索事件参数
	eRecordSearchAsyncType searchAyncAction;		// 异步搜索启停（值为E_RECORD_SEARCH_ASYNC_UNKNOWN时为同步搜索，事件搜索必须是异步搜索）
}sRecordSearchCondition;

//查询录像结果
typedef struct S_SDK_RECORD_FILEINFO {
	sDateTime startTime;
	sDateTime endTime;
	char szRecordName[64];
	uint nLen;
	uint nRecordSn;									// 用于图片读，全局唯一
	eStoreFileType fileType;
	sRecordEventSearchParam eventData;				// 录像、图片对应的结构化信息
	uint nBgRecordSn;								// 用于背景图片读，全局唯一
}sRecordFileInfo;

// 每个通道录像文件信息
typedef struct S_SDK_RECORD_CHANNEL_FILEINFO {
	int nChannel;
	int nCount;
	sRecordFileInfo fileInfo[64];
}sRecordChannelFileInfo;

typedef struct S_SDK_RECODE_LIST {
	sRecordChannelFileInfo recordInfo[NET_MAX_CHANNUM];	// 查询结果
	int nTotalFiles;								// 搜索总数
	int nPageFiles;									// 返回数
}sRecordList;

typedef enum E_SDK_PLAYBACK_CONTROL {
	E_SDK_PLAYBACK_CONTROL_START = 1,				// 回放开始
	E_SDK_PLAYBACK_CONTROL_STOP = 2,				// 回放结束
	E_SDK_PLAYBACK_CONTROL_PAUSE = 3,				// 暂停回放
	E_SDK_PLAYBACK_CONTROL_CONTINUR = 4,			// 继续回放
	E_SDK_PLAYBACK_CONTROL_LOCATE = 5,				// 回放定位
	E_SDK_PLAYBACK_CONTROL_FAST = 6,				// 快放
	E_SDK_PLAYBACK_CONTROL_SLOW = 7,				// 慢放
	E_SDK_PLAYBACK_CONTROL_BACK = 8,				// 倒放
	E_SDK_PLAYBACK_CONTROL_NORMAL = 9,				// 正常播放
	E_SDK_PLAYBACK_CONTROL_DOWNLOAD_START = 10,		// 下载开始
	E_SDK_PLAYBACK_CONTROL_DOWNLOAD_STOP = 11,		// 下载结束
	E_SDK_PLAYBACK_CONTROL_STEP = 12,				// 单帧回放
}ePlayBackControl;

// 回放控制
typedef struct S_SDK_PLAYBACK_CONTROL {
	int nChannel;
	eStreamType stream;
	char szFileName[64];
	uint nFileSize;
	uint nRecordSn;									// 用于图片读，全局唯一
	sDateTime startTime;
	sDateTime endTime;
}sPlayBackControl;

// 下载存储图片参数
typedef struct S_SDK_PB_DL_PICTURE_PARAM {
	ePushPictureType eType;							// 图片类型
	char *pBuffer;									// 图片数据
	uint nBufLen;									// 数据大小
	char *pszAIDataAttr;							// 智能数据，Json字符串（具体内容含义请查阅文档）
}sDownloadStoredPicParam;

/// 默认配置种类
typedef enum E_SDK_DEFAULT_CONFIG_KINDS {
	E_SDK_DEFAULT_CONFIG_KINDS_Unknown = 0,			// 未知保留
	E_SDK_DEFAULT_CONFIG_KINDS_All = 1,				// 所有配置
	E_SDK_DEFAULT_CONFIG_KINDS_GENERAL = 2,			// 普通配置
	E_SDK_DEFAULT_CONFIG_KINDS_MEDIA,				// 摄像机参数，编码配置
	E_SDK_DEFAULT_CONFIG_KINDS_STORAGE,				// 录像配置
	E_SDK_DEFAULT_CONFIG_KINDS_ALARM,				// 报警
	E_SDK_DEFAULT_CONFIG_KINDS_NET_COMMON,			// 通用网络
	E_SDK_DEFAULT_CONFIG_KINDS_NET_SERVICE,			// 网络服务
	E_SDK_DEFAULT_CONFIG_KINDS_USERMANAGER,			// 用户管理
	E_SDK_DEFAULT_CONFIG_KINDS_INTELLIGENT,			// 智能
	E_SDK_DEFAULT_CONFIG_KINDS_USERDATA = 10,		// 用户数据，包括人员底库和通行记录	E_OTHER_ABILITY_PSDOOR
	E_SDK_DEFAULT_CONFIG_KINDS_END,
}eDefaultConfigKinds;

/// 恢复默认
typedef struct S_SDK_DEFAULT_CONFIG_TYPES {
	bool vTypes[E_SDK_DEFAULT_CONFIG_KINDS_END];
}sDefaultConfigTypes;

///////////////////烧写硬件信息相关结构体/////////////////////////////////
typedef struct S_SDK_HARDWARE_INFO{
	uchar szBuffer[256];
	int nBufLen;
	char szName[64];
	int nType;										// 0:烧MAC 1:烧SN
}sHardwareInfo;

///////////////////设备抓图相关结构体/////////////////////////////////
typedef struct S_SDK_CATCH_PICTURE_PARAM {
	//int
	char reserve[16];
	char *sFileName;								// 保存文件路径（不需要保存文件传“null”即可）
	//in out
	char *pBuffer;									// 接收数据缓存（不需要可传null）
	uint nBufLen;									// 缓存大小/数据大小
}sCatchPictureParam;

///////////////////日志信息相关结构体/////////////////////////////////
typedef enum E_SDK_LOG_TYPE {
	E_SDK_LOG_TYPE_Unknown = 0,
	E_SDK_LOG_TYPE_All = 1,							// 所有日志
	E_SDK_LOG_TYPE_System = 2,						// 系统日志
	E_SDK_LOG_TYPE_Config = 3,						// 配置日志
	E_SDK_LOG_TYPE_Alarm = 4,						// 报警日志
	E_SDK_LOG_TYPE_UserManager = 5,					// 用户管理日志
	E_SDK_LOG_TYPE_Warn = 6,						// 警告日志
}eLogType;

/// 日志查询条件
typedef struct S_SDK_LOG_SEARCH_CONDITION {
	eLogType eType;									// 日志类型
	int iLogPosition;								// 从上次查询的结束时的日志指针
	sSystemTime stBeginTime;						// 查询日志开始时间
	sSystemTime stEndTime;							// 查询日志结束时间
}sLogSearchCondition;

typedef struct S_SDK_LOG_INFO {
	char szType[32];								// 日志类型
	char szUser[32];								// 日志用户
	char szData[256];								// 日志数据
	sSystemTime stLogTime;							// 日志时间
	eLogType eType;									// 日志类型
	int iLogPosition;								// 日志索引
}sLogInfo;

//日志返回信息
typedef struct S_SDK_LOG_LIST {
	int iNumLog;
	sLogInfo logs[NET_MAX_RETURNED_LOGLIST];
}sLogList;

/*********************************统计信息****************************************/
// 搜索目标物类型
typedef enum {
	E_ALG_TARGET_TYPE_ALL = 0,
	E_ALG_TARGET_TYPE_FACE = 1,						// 人脸
	E_ALG_TARGET_TYPE_HUMAN = 2,					// 人形
	E_ALG_TARGET_TYPE_VEHICLE = 3,					// 机动车
	E_ALG_TARGET_TYPE_CYCLE = 4,					// 非机动车 
}eAlgorithmTargetType;

typedef enum {
	E_STATISTICAL_TYPE_UNKNOWN = 0,
	E_STATISTICAL_TYPE_YEARLY = 1,					// 一年每个月统计数量
	E_STATISTICAL_TYPE_MONTHLY = 2,					// 一个月每天统计数量
	E_STATISTICAL_TYPE_WEEKLY = 3,					// 一周中每天统计数量
	E_STATISTICAL_TYPE_DAILY = 4,					// 一天每小时统计数量
}eStatisticalType;

// 搜索track统计信息
typedef struct S_SDK_SEARCH_TARGET_STAT_REQ {
	eStatisticalType statType;						// 搜索类型
	eAlgorithmTargetType trackType;					// 目标类型
	sSystemTime startTime;							// 开始时间
	sSystemTime endTime;							// 结束时间
}sSearchTargetStatReq;

typedef struct S_SDK_SEARCH_TARGET_STAT_RSP {
	uint size[32];									// 数组长度根据搜索类型判断
}sSearchTargetStatRsp;

// 获取当前统计信息
enum E_SDK_CURRENT_STAT_TYPE {
	E_CURRENT_STAT_UNKNOWN = 0,
	E_CURRENT_STAT_COUNT = 0x0001,					// 目标计数，废弃
	E_CURRENT_ALG_STATUS = 0x0002,					// 算法状态获取
};

typedef struct S_SDK_SEARCH_CURRENT_STAT_REQ {
	int nStatMask;									// 请求类型掩码（见枚举 E_SDK_CURRENT_STAT_TYPE）
}sSearchCurrentStatReq;

typedef enum E_SDK_STAT_OBJECT_TYPE {
	E_STAT_OBJECT_UNKNOWN = 0,
	E_STAT_OBJECT_FACE = 1,							// 人脸
	E_STAT_OBJECT_HUMAN = 2,						// 人形
	E_STAT_OBJECT_VEHICLE = 3,						// 机动车
	E_STAT_OBJECT_CYCLE = 4,						// 非机动车
	E_STAT_OBJECT_PLATE = 5,						// 车牌
	E_STAT_OBJECT_NR,
}eStatObjectType;

typedef enum E_SDK_ALG_STATUS {
	E_ALG_STATUS_UNKNOWN = 0,
	E_ALG_STATUS_NORMAL = 1,
	E_ALG_STATUS_STOP = 2,
}eAlgStatus;

typedef struct S_SDK_CURRENT_STAT_DATA {
	eStatObjectType objType;						// 目标类型
	int nObjCount;									// 目标计数
	eAlgStatus algStatus;							// 算法状态
	int nTemperature;								// cpu温度
}sCurrentStatData;

// 返回消息
typedef struct S_SDK_SEARCH_CURRENT_STAT_RSP {
	int nCount;
	sCurrentStatData data[E_STAT_OBJECT_NR];
}sSearchCurrentStatRsp;

///////////////////工装相关结构体/////////////////////////////////
// 产测通用回复
typedef enum E_RESULT_TYPE {
	E_PRODUCE_RESULT_TYPE_UNKNOWN = 0,				// 未知错误
	E_PRODUCE_RESULT_TYPE_OK = 1,					// 成功
	E_PRODUCE_RESULT_TYPE_DOUBLEOK = 2,				// 需要人工二次确认的成功
	E_PRODUCE_RESULT_TYPE_FAILED = 3,				// 失败
	E_PRODUCE_RESULT_TYPE_UNSUPPORTED = 4,			// 不支持
	E_PRODUCE_RESULT_TYPE_UNINITIALIZED = 5,		// 产测模式未初始化
}ePrduceResultType;

typedef struct S_SDK_PRODUCE_TEST_RSP {
	ePrduceResultType eRet;							// 产测返回码
	char szLog[102400];
}sPrduceTestRsp;

typedef struct S_SDK_PRODUCE_STATUS {
	bool bPcb;										// PCB测试
	bool bIntegrated;								// 整机测试
	sPrduceTestRsp sRsp;							// 保存时不用赋值
}sProduceStatus;

typedef enum {
	E_VO_TYPE_RGB = 0,
	E_VO_TYPE_GBR = 1,
	E_VO_TYPE_BRG = 2,
	E_VO_TYPE_CLEAR_FB = 3,							//按0、1、2、3顺序发送
	E_VO_TYPE_ALL_SENSOR = 4,						//整机时测试
}sProduceVoType;

typedef struct S_SDK_PRODUCE_VO_REQ {
	sProduceVoType vo;
}sProduceVoReq;

typedef struct S_SDK_NETWORKSPEED_TEST_REQ {
	sIpAddress address;								// wifi:ip地址 4G:外网url
}sTestNetworkSpeedReq;

typedef struct S_SDK_NETWORKSPEED_TEST_RSP {
	sPrduceTestRsp sRsp;
	float fSpeed;									// wifi:带宽值 4G:下载速度
}sTestNetworkSpeedRsp;

typedef struct S_SDK_TEST_GPIO_REQ {
	bool bPress;									// 是否按下按钮, 先发false再发true
}sTestGpioReq;

///////////////////通用产测相关结构体/////////////////////////////////
typedef enum {
	E_GPT_TYPE_UNKNOWN = 0,
	E_GPT_TYPE_BUTTON = 1,							// 按钮测试，硬件触发.主动上传 被按下的按钮
	E_GPT_TYPE_ALARM_TAMPER = 2,					// 防拆报警，硬件触发.主动上传 开始与结束
	E_GPT_TYPE_ALARM_DOOR_SENSOR = 3,				// 门磁报警，硬件触发.主动上传 开始与结束
	E_GPT_TYPE_ALARM_FIRE = 4,						// 消防报警，硬件触发.主动上传 开始与结束
	E_GPT_TYPE_WIEGAND = 5,							// 韦根测试，即时返回结果
	E_GPT_TYPE_LAMP_BOARD_TOP = 6,					// 上灯板测试，即时返回结果
	E_GPT_TYPE_LAMP_BOARD_BOTTOM = 7,				// 下灯板测试, 即时返回结果
	E_GPT_TYPE_USB_TEST = 8,						// USB测试，即时返回结果
} eGeneralProduceTestType;


// 上灯板测试
typedef struct S_SDK_GPT_LAMP_BOARD_TOP_REQ {
	bool bOpen;
}sGPTLampBoardTopReq;

//下灯板测试
typedef enum {
	E_BLB_COLOR_UNKNOWN = 0,
	E_BLB_COLOR_ALL = 1,
	E_BLB_COLOR_RED = 2,
	E_BLB_COLOR_GREEN = 3,
	E_BLB_COLOR_BLUE = 4,
	E_BLB_COLOR_WHITE = 5,
}eBottomLBColorType;

typedef struct S_SDK_GPT_LAMP_BOARD_BOTTOM_REQ {
	eBottomLBColorType color;
	bool bOpen;
}sGPTLampBoardBottomReq;

//通用产测-请求
typedef struct S_SDK_GENERAL_PRODUCE_TEST_REQ {
	eGeneralProduceTestType eType;					// 根据type找相应类型的结构体

	union {											
		sGPTLampBoardTopReq sLampBoardTop;
		sGPTLampBoardBottomReq sLampBoardBottom;
	};				
}sGeneralProduceTestReq;

// RS485写入数据
typedef struct S_SDK_GPT_RS485_WRITE_REQ {
	int nLen;
	char szBuffer[512];
}sGPTRS485WriteReq;


//通用产测-回复
typedef enum{
	E_GPT_RESULT_UNKNOWN = 0,						// 未知错误
	E_GPT_RESULT_OK = 1,							// 成功
	E_GPT_RESULT_DOUBLE_OK = 2,						// 需要人工二次确认的成功
	E_GPT_RESULT_FAILED = 3,						// 失败
	E_GPT_RESULT_UNSUPPOETED = 4,					// 不支持
	E_GPT_RESULT_UNSTART = 5,						// 产测模式未开始
}eGPTestResultType;

//报警测试 返回结构体
typedef enum {
	E_GPT_ALARM_EVENT_UNKNOWN = 0,
	E_GPT_ALARM_EVENT_START = 1,					// 事件开始
	E_GPT_ALARM_EVENT_STOP = 2,						// 事件结束
}eGPTAlarmEventAction;

typedef struct S_SDK_GPT_ALARM_EVENT_RSP {
	eGPTAlarmEventAction eTestType;
}sGPTAlarmEventRsp;

//按钮测试 返回结构体
typedef struct S_SDK_GPT_BUTTON_RSP {
	int nType; //0:恢复出厂设置 4: 开门 5:重启
}sGPTButtonRsp;

typedef struct S_SDK_GENERAL_PRODUCE_TEST_RSP {
	eGeneralProduceTestType eTestType;				//测试项
	eGPTestResultType eTestResultType;				//测试结果

	union {
		sGPTAlarmEventRsp sAlarmEvent;
		sGPTButtonRsp sButton;
	};
}sGeneralProduceTestRsp;

// RS485读取数据
typedef struct S_SDK_GPT_RS485_READ_REQ {
	int nLen;
	char szBuffer[512];
}sGPTRS485ReadRsp;

///////////////////推图相关结构体/////////////////////////////////
typedef struct S_SDK_PUSH_DATA {
	ePushPictureType eType;							//上传图片类型
	char *pszAIDataAttr;							//推送的智能数据，Json字符串（具体内容含义请查阅文档）
	int nChannel;									//通道号
	int nLenSize;									//图片大小
	uchar* pBuffer;									//图片数据
}sPushData;

///////////////////人脸识别相关结构体/////////////////////////////////
typedef enum E_SDK_GENDER_TYPE {
	E_GENDER_TYPE_UNKNOW = 0,
	E_GENDER_TYPE_MALE = 1,
	E_GENDER_TYPE_FEMALE = 2,
}eGenderType;

typedef enum E_SDK_FACE_RECOGNITION_OPT_RET {
	E_FR_RESULT_OK = 0,								// 通用成功
	E_FR_RESULT_ERROR = 1,							// 通用错误
	E_FR_RESULT_VERIFY_FAILED = 2,					// 参数校验失败
	E_FR_RESULT_ROW_LIMIT = 3,						// 行数超出限制
	E_FR_RESULT_NAME_USED = 4,						// 名字被占用
	E_FR_RESULT_NOT_EXIST = 5,						// 此项不存在
	E_FR_RESULT_DEFAULT_ITEM = 6,					// 默认配置不可操作
	E_FR_RESULT_QUALITY_LOW = 7,					// 人脸入库图片质量低
	E_FR_RESULT_OVER_SIZE = 8,						// 人脸入库图片过大
	E_FR_RESULT_FULL = 9,							// 人脸库已满
	E_FR_RESULT_GROUP_FULL = 10,					// 人脸分组已满
	E_FR_RESULT_GROUP_NOT_EMPTY = 11,				// 组内人员不为空
}eFRPersonOptRet;

// 人脸信息
typedef enum {
	E_FR_CREDENTIAL_TYPE_UNKNOW = 0,
	E_FR_CREDENTIAL_TYPE_IDENTITY_CARD = 1,			// 身份证
	E_FR_CREDENTIAL_TYPE_PASSPORT = 2,				// 护照
	E_FR_CREDENTIAL_TYPE_OFFICER = 3,				// 军官证
}eFRCredentialType;

typedef struct S_SDK_FACE_RECOGNITION_PERSON_INFO {
	uint nFaceId;									// face id
	uint nGroupId;									// group id
	char szPersonName[64];							// 人员姓名
	eGenderType eGender;							// 性别
	uint nEthnicity;								// 民族
	sSystemTime birthday;							// 生日
	uint nProvincev;								// 省份
	uint nCity;										// 城市
	eFRCredentialType cdt;							// 证件类型
	char szCdtNo[64];								// 证件号
	char *pszFacePicture;							// 人脸图片二进制数据
	uint nPicSize;									// 人脸图片大小
}sFRPersonInfo;

// 增、删、改
// 操作人员信息
typedef struct {
	sFRPersonInfo info;
}sFRPersonContent;

typedef struct S_SDK_FACE_RECOGNITION_PERSONINFO_OPT_REQ {
	uint nCount;
	sFRPersonContent content[NET_MAX_OPT_PERSONS_ONCES];
}sFRPersonInfoOptReq;

typedef struct {
	uint nId;
	eFRPersonOptRet eRet;
}sFRPersonInfoOptResult;

typedef struct S_SDK_FACE_RECOGNITION_PERSONINFO_OPT_RSP {
	uint nCount;
	sFRPersonInfoOptResult result[NET_MAX_OPT_PERSONS_ONCES];
}sFRPersonInfoOptRsp;

// 搜索人员信息
typedef enum E_SDK_PERSON_SEARCH_TYPE {
	E_PERSON_SEARCH_WITHOUT_PICTURE = 0x00,			// 不要图片,
	E_PERSON_SEARCH_WITH_PICTURE = 0x01,			// 要图片,带图片搜索建议一次少于20条
	E_PERSON_SEARCH_WITH_FEATURE = 0x02,			// 带特征值（不需要）
}ePersonSearchType;

typedef struct S_SDK_FACE_RECOGNITION_SEARCH_PERSON_REQ {
	uint nSchMask;									// 搜索类型，具体见ePersonSearchType
	sFRPersonInfo sCondition;						// 具体搜索条件
	sSystemTime birthBegin;							// 生日开始时间
	sSystemTime birthEnd;							// 生日结束时间
	uint nNumber;									// 请求条数
	uint nPosition;									// 分段搜索定位 即第从几条人脸信息开始搜索
}sFRSearchPersonReq;

typedef struct {
	sFRPersonInfo personInfo;
}sFRSearchPersonResult;

typedef struct S_SDK_FACE_RECOGNITION_SEARCH_PERSON_RSP {
	uint nCount;									// 搜索到的人脸条数
	sFRSearchPersonResult *pResults;				// 搜索到的人脸信息
	int nFaceCount;									// 人脸总条数
}sFRSearchPersonRsp;

/***********************分组信息**********************/
typedef enum {
	E_FR_GROUP_TYPE_UNKNOW = 0,
	E_FR_GROUP_TYPE_GUARD = 1,
	E_FR_GROUP_TYPE_NOTGUARD = 2,
	E_FR_GROUP_TYPE_WHITE_LIST = 3,
	E_FR_GROUP_TYPE_BLACK_LIST = 4,
}eFRGroupType;

typedef struct S_SDK_FACE_RECOGNITION_GROUP_INFO {
	uint nGroupId;
	char szGroupName[64];							// 组名，不重复
	eFRGroupType type;
	uint nSimilarity;								// 相似度，即识别阈值
	uint nLiveness;									// 活体阈值
}sFRGroupInfo;

// 增、删、改
// 操作人员组
typedef struct S_SDK_FACE_RECOGNITION_GROUP_OPT_REQ {
	uint nGroupNum;
	sFRGroupInfo group[NET_MAX_OPT_PERSONS_ONCES];
}sFRGroupOptReq;

typedef struct {
	uint nId;
	eFRPersonOptRet eRet;
}sFRGroupOptResult;

typedef struct S_SDK_FACE_RECOGNITION_GROUP_OPT_RSP {
	uint nRetCount;
	sFRGroupOptResult rt[NET_MAX_OPT_PERSONS_ONCES];
}sFRGroupOptRsp;

// 搜索人员组
typedef struct S_SDK_FACE_RECOGNITION_GROUP_SEARCH_REQ {
	sFRGroupInfo condition;							// 具体搜索条件
	uint nNumber;									// 请求条数
	uint nPosition;									// 分段搜索定位
}sFRGroupSearchReq;

typedef struct {
	sFRGroupInfo group;
	uint nPersonNum;
}sFRGroupSearchResult;

typedef struct S_SDK_FACE_RECOGNITION_GROUP_SEARCH_RSP {
	uint nRetCount;
	sFRGroupSearchResult *pResult;					// 搜索到的分组信息
	uint nGroupCount;								// 分组总条数
}sFRGroupSearchRsp;

/*******************************识别结果****************************************/
// 人脸识别返回信息
typedef enum {
	E_FACE_ID_RESULT_UNKNOWN = 0,
	E_FACE_ID_RESULT_SUCCESS = 1,					// 识别成功
	E_FACE_ID_RESULT_STRANGER = 2,					// 陌生人
	E_FACE_ID_RESULT_NOT_LIVING = 3,				// 非活体
}eFRResultType;

typedef struct S_SDK_FACE_RECOGNITION_EVENT_LOG {
	uint nEventId;
	sFRPersonInfo personInfo;						// 人员信息
	eFRResultType eventType;						// 事件类型
	float fLivenessScore;							// 活体分数
	float fRecognitionScore;						// 识别分数
	char *pszSnapPic;								// 人脸抓拍图
	uint nSnapPicSize;
	char *pszBgPic;									// 背景图
	uint nBgPicSize;
	sSystemTime sTimeSnap;							// 抓拍时间
}sFREventLog;

// 识别记录搜索请求
enum E_SDK_FR_EVENT_SEARCH_TYPE {
	E_FR_EVENT_SEARCH_WITHOUT_PIC = 0x00,				// 不要图片
	E_FR_EVENT_SEARCH_WITH_SNAP = 0x01,					// 要抓拍图
	E_FR_EVENT_SEARCH_WITH_BGM = 0x02,					// 要背景图
	E_FR_EVENT_SEARCH_WITH_PERSON = 0x04,				// 要底库图
};

typedef struct S_SDK_FACE_RECOGNITION_SEARCH_EVENTLOG_REQ {
	uint nSearchTypeMask;							// 搜索携带图片掩码,参看枚举E_SDK_FR_EVENT_SEARCH_TYPE
	sFREventLog condition;							// 具体搜索条件
	sSystemTime sStartTime;							// 搜索开始时间。为0时忽略时间条件
	sSystemTime sEndTime;							// 搜索结束时间。为0时忽略时间条件
	int nNumber;									// 请求条数
	int nPosition;									// 搜索位置
	bool bTimeDesc;									// 搜索结果是否按照时间倒序
}sFRSearchEventLogReq;

typedef struct S_SDK_FACE_RECOGNITION_SEARCH_EVENTLOG_RSP{
	uint nRetCount;
	sFREventLog *pEventInfo;						// 搜索到的通行记录
	uint nTotalSize;								// 搜索到的总记录条数
}sFRSearchEventLogRsp;

/*****识别事件上传*****/
typedef struct S_SDK_FACE_RECOGNITION_EVENT {
	sFREventLog log;								// 事件具体内容
}sFaceRecognitionEvent;

/*******************************报警事件相关*******************************/
typedef enum {
	E_ALARM_TYPE_UNKNOWN = 0,
	E_ALARM_TYPE_FIREALARM  = 1,			// 消防报警 
	E_ALARM_TYPE_TAMPER = 2,				// 防拆报警
	E_ALARM_TYPE_DOORSENSOR = 3,			// 门磁报警
	E_ALARM_TYPE_UNLOCKPWDCRACK = 4,		// 解锁密码破解报警
	E_ALARM_TYPE_UNONLIVINGATTACK = 5,		// 非活体攻击报警
}eDCAlarmEventType;

typedef enum {
	E_ALARM_ACTION_UNKNOWN = 0,
	E_ALARM_ACTION_START = 1,		// 事件开始
	E_ALARM_ACTION_STOP = 2,		// 事件结束
}eDCAlarmEventAction;

typedef struct S_SDK_ALARM_EVENT_LOG {
	eDCAlarmEventType   alarmType;
	eDCAlarmEventAction alarmAction;

	int nEventId;
	char *pszPic;									// 抓拍图
	uint nPicSize;
	//sSystemTime sTimeSnap;							// 抓拍时间
	sSystemTime sStartTime;							// 开始时间
	sSystemTime sEndTime;							// 结束时间
}sDCAlarmEventLog;

// 报警记录搜索请求
enum E_SDK_ALARM_EVENT_SEARCH_TYPE {
	E_ALARM_EVENT_SEARCH_WITHOUT_PIC = 0x00,				// 不要图片
	//E_ALARM_EVENT_SEARCH_WITH_SNAP = 0x01,				// 要抓拍图
	E_ALARM_EVENT_SEARCH_WITH_BGM = 0x02,					// 要背景图
	//E_ALARM_EVENT_SEARCH_WITH_PERSON = 0x04,				// 要底库图
};
/*请求*/
typedef struct S_SDK_ALARM_SEARCH_EVENTLOG_REQ {
	uint nSearchTypeMask;							// 搜索携带图片掩码,参看枚举E_SDK_ALARM_EVENT_SEARCH_TYPE
	sDCAlarmEventLog condition;						// 具体搜索条件
	sSystemTime sStartTime;							// 搜索开始时间。为0时忽略时间条件
	sSystemTime sEndTime;							// 搜索结束时间。为0时忽略时间条件
	int nNumber;									// 请求条数
	int nPosition;									// 搜索位置
	bool bTimeDesc;									// 搜索结果是否按照时间倒序
}sDCAlarmSearchEventLogReq;
/*结果*/
typedef struct S_SDK_ALARM_SEARCH_EVENTLOG_RSP {
	uint nRetCount;
	sDCAlarmEventLog *pEventInfo;					// 搜索到的报警记录
	uint nTotalSize;								// 搜索到的总报警记录条数
}sDCAlarmSearchEventLogRsp;
/*************报警事件上传************************/
typedef struct S_SDK_ALARM_EVENT {
	sDCAlarmEventLog log;								// 事件具体内容
}sDCAlarmEvent;

///////////////////门禁机相关结构体/////////////////////////////////
typedef enum {
	E_SDK_DOOR_OPT_RESULT_OK = 0,					// 通用成功
	E_SDK_DOOR_OPT_RESULT_ERROR = 1,				// 通用错误
	E_SDK_DOOR_OPT_RESULT_VERIFY_FAILED = 2,		// 参数校验失败
	E_SDK_DOOR_OPT_RESULT_ROW_OUT_LIMIT = 3,		// 行数超出限制
	E_SDK_DOOR_OPT_RESULT_NAME_USED = 4,			// 名字被占用
	E_SDK_DOOR_OPT_RESULT_NOTEXIST = 5,				// 此项不存在
	E_SDK_DOOR_OPT_RESULT_DEFAULT_FAILED = 6,		// 默认配置不可操作
	E_SDK_DOOR_OPT_RESULT_JOBNO_USED = 7,			// 工号被占用
	E_SDK_DOOR_OPT_RESULT_NO_SPACE = 8,				// 剩余空间不足
	E_SDK_DOOR_OPT_RESULT_GROUP_NOT_EXIST = 9,		// 人员组不存在
	E_SDK_DOOR_OPT_RESULT_SCHEDULE_NOT_EXIST = 10,	// 时间计划不存在
	E_SDK_DOOR_OPT_RESULT_CARD_NO_INUSE = 11,		// 卡号被占用
	E_SDK_DOOR_OPT_RESULT_EF_ERROR = 101,			// 抽取特征通用错误
	E_SDK_DOOR_OPT_RESULT_EF_PARAM_ERROR = 102,		// 抽取特征参数错误
	E_SDK_DOOR_OPT_RESULT_EF_INNER_ERROR = 103,		// 抽取特征算法内部错误
	E_SDK_DOOR_OPT_RESULT_EF_OVER_BLUR = 104,		// 抽取特征模糊度超过阈值
	E_SDK_DOOR_OPT_RESULT_EF_OVER_POSE = 105,		// 抽取特征pose超过阈值
	E_SDK_DOOR_OPT_RESULT_EF_IMAGE_ERROR = 106,		// 抽取特征图片错误
}eDoorOptResult;

/*********************************人员信息****************************************/
typedef enum E_SDK_PERSON_EXTRA_INFO_TYPE {
	E_PERSON_EXTRA_UNKNOWN = 0,
	E_PERSON_EXTRA_FSY_ELEVATOR_ACCESS = 1,			// 梯控信息  elevInfo
}ePersonExtraInfoType;

// kEitFsyElevatorAccess
typedef struct S_SDK_FSY_FLOOR_INFO {
	char szFloor[8];
}sFsyFloorInfo;

typedef struct S_SDK_FSY_ELEVATOR_ACCESS_INFO {
	uint nCount;
	sFsyFloorInfo floor[256];
}sFsyElevatorAccessInfo;

typedef struct S_SDK_PERSON_EXTRA_INFO {
	ePersonExtraInfoType type;						// 额外信息类型（人员属性，不支持修改）
	union {											// 根据type找相应类型的结构体
		sFsyElevatorAccessInfo elevInfo;			// 梯控楼层信息, E_PERSON_EXTRA_FSY_ELEVATOR_ACCESS
		char sz[4096];
	};
}sPersonExtraInfo;

// 人员信息
typedef enum {
	E_PERSON_TYPE_UNKNOWN = 0,
	E_PERSON_TYPE_NORMAL = 1,						// 普通人员
	E_PERSON_TYPE_VISITOR = 2,						// 访客
	E_PERSON_TYPE_BLACK_LIST = 3,					// 黑名单
	E_PERSON_TYPE_STRANGER = 4,						// 陌生人
	E_PERSON_TYPE_VISITOR_VIP = 100,				// ps Vip访客
}ePersonType;

typedef struct S_SDK_PERSON_INFO {
	sIdentifier id;									// 人员ID
	char szPersonName[301];							// 人员名字
	char szJobNo[64];								// 人员编号，唯一
	char szCardNo[64];								// 卡号
	char szVirtualCardNo[64];						// 虚拟卡号 ps用(客户端无需使用，修改人员时只需把获取到的数据原样保存即可)
	char szPersonPwd[NET_MAX_NAME_PSW_LEN];			// 人员密码
	bool bPwdChanged;								// 人员密码是否发生变化
	bool bAdmin;									// 是否为管理员
	ePersonType ePerType;							// 人员类型
	char szVisitTime[32];							// 访客允许通行时间，仅E_PERSON_VISITOR类型 时间格式：20200311000000-20200311235959
	char szVisitTarget[NET_MAX_NAME_PSW_LEN];		// 受访人，仅E_PERSON_VISITOR类型
	char *pszFacePicture;							// 人员照片，人脸图片二进制数据
	uint nPicSize;									// 人脸图片大小
	eGenderType eGender;							// 性别
	char szPhone[16];								// 手机号
	char szEmail[32];								// 邮箱
	char szInstitution[64];							// 机构
	char szImageUri[256];							// 图片链接
	char *pszFeature;								// 人脸特征
	uint nFeatureLen;								// 人脸特征数据长度
	char *pszMaskFeature;							// 口罩特征
	uint nMaskFeatureLen;							// 口罩特征数据长度
	uint64 nUpdateTime;								// 更新时间
	sIdentifier personGroupId[128];					// 人员组
	uint nGroupNum;									// 人员组个数
	char szQrCode[256];								// 二维码
	char *pszUserData;								//
	uint nUserDataSize;
	sPersonExtraInfo extraInfo;						// 人员额外信息
}sPersonInfo;

// 增、删、改人员信息
// 增加时，person_id自动生成的，所以这个值和添加的会不一致。添加时一次最好不要超过四条
// 删除时，以person_id为删除依据
// 修改时，以person_id为修改依据，如果face_picture为空，代表不修改图片
typedef struct {
	sPersonInfo content;
}sPersonInfoOptRequired;

typedef struct S_SDK_PERSONINFO_OPT_REQ {
	int nCount;
	sPersonInfoOptRequired required[NET_MAX_OPT_PERSONS_ONCES];
}sPersonInfoOptReq;

typedef struct {
	sIdentifier id;
	eDoorOptResult eRet;
}sPersonInfoOptResult;

typedef struct S_SDK_PERSONINFO_OPT_RSP {
	int nCount;
	sPersonInfoOptResult result[NET_MAX_OPT_PERSONS_ONCES];
}sPersonInfoOptRsp;

// 搜索人员请求
typedef struct S_SDK_SEARCH_PERSON_REQ {
	uint nSchMask;									// 搜索类型，具体见ePersonSearchType
	sPersonInfo sCondition;							// 具体搜索条件
	uint nNumber;									// 请求条数
	uint nPosition;									// 分段搜索定位 即第从几条人脸信息开始搜索
}sSearchPersonReq;

typedef struct {
	sPersonInfo personInfo;
}sSearchPersonResult;

typedef struct S_SDK_SEARCH_PERSON_RSP {
	uint nCount;									// 搜索到的人脸条数
	sSearchPersonResult *pResults;					// 搜索到的人脸信息
	int nFaceCount;									// 人脸总条数
}sSearchPersonRsp;

/*********************************时间计划信息****************************************/
typedef struct S_SDK_DOOR_SCHEDULE {
	sIdentifier id;
	char szName[NET_MAX_NAME_PSW_LEN];
	sWorkSheetConfig week;							// 周计划 总计7 * 3个时间段（7天，一天3个时间段）
	sDaySheet holiday[32];							// 假日计划 总计32 * 3个时间段(一天3个时间段)
	sSystemTime time[32];							// 假日计划 总计32个天数
	uint64 nUpdateTime;								// 更新时间
	char *pszUserData;								//
	uint nUserDataSize;
}sDoorSchedule;

// 增、删、改时间计划
typedef struct S_SDK_DOOR_SCHEDULE_OPT_REQ {
	uint nSchNum;
	sDoorSchedule schedule[16];
}sDoorScheduleOptReq;

typedef struct {
	sIdentifier id;
	eDoorOptResult ret;
}sDoorScheduleOptRsp_Result;

typedef struct S_SDK_DOOR_SCHEDULE_OPT_RSP {
	uint nRetCount;
	sDoorScheduleOptRsp_Result rt[16];
}sDoorScheduleOptRsp;

// 搜索时间计划
typedef struct S_SDK_DOOR_SCHEDULE_SEARCH_REQ {
	sDoorSchedule condition;						// 具体搜索条件
	uint nNumber;									// 请求条数
	uint nPosition;									// 分段搜索定位
}sDoorScheduleSearchReq;

typedef struct {
	sDoorSchedule scheduleInfo;
}sDoorSchSearchResult;

typedef struct S_SDK_DOOR_SCHEDULE_SEARCH_RSP {
	uint nRetCount;
	sDoorSchSearchResult *pSchInfo;					// 搜索到的时间计划
	uint nSchCount;									// 时间计划总条数
}sDoorScheduleSearchRsp;

/*********************************人员组信息****************************************/
// 人员组信息，用于单个人员组的增加，删除，修改，查找
typedef struct S_SDK_PERSONGROUP_INFO {
	sIdentifier groupId;
	char szGroupName[NET_MAX_NAME_PSW_LEN];			// 组名（唯一）
	sIdentifier planId;								// 时间计划
	int nType;										// 组类型，云使用
	bool bAll;										// 是否为全员组，云使用
	uint64 nUpdateTime;
	char *pszUserData;								//
	uint nUserDataSize;
}sPersonGroupInfo;

// 增、删、改人员组
typedef struct S_SDK_DOOR_GROUP_OPT_REQ {
	uint nGroupNum;
	sPersonGroupInfo group[16];
}sDoorGroupOptReq;

typedef struct {
	sIdentifier id;
	eDoorOptResult ret;
}sDoorGroupOptRsp_Result;

typedef struct S_SDK_DOOR_GROUP_OPT_RSP {
	uint nRetCount;
	sDoorGroupOptRsp_Result rt[16];
}sDoorGroupOptRsp;

// 搜索人员组
typedef struct S_SDK_DOOR_GROUP_SEARCH_REQ {
	sPersonGroupInfo condition;						// 具体搜索条件
	uint nNumber;									// 请求条数
	uint nPosition;									// 分段搜索定位
}sDoorGroupSearchReq;

typedef struct {
	sPersonGroupInfo group;
	uint nPersonNum;
}sDoorGroupSearchRsp_Result;

typedef struct S_SDK_DOOR_GROUP_SEARCH_RSP {
	uint nRetCount;
	sDoorGroupSearchRsp_Result *pGroupInfo;			// 搜索到的分组信息
	uint nGroupCount;								// 分组总条数
}sDoorGroupSearchRsp;

/*******************************通行记录****************************************/
// 单条通行记录
	// 活体类型
typedef enum E_LIVENESS_TYPE {
	E_LIVENESS_UNKNOWN = 0,
	E_LIVENESS_NOTLIVING = 1,						// 非活体攻击
	E_LIVENESS_LIVING = 2,							// 活体
}sPassedEventLog_eLivenessType;

// 元通行事件类型
typedef enum {
	E_DC_META_PASSTYPE_UNKNOWN = 0,
	E_DC_META_PASSTYPE_FACE = 1,					// 人脸
	E_DC_META_PASSTYPE_CARD = 2,					// 刷卡
	E_DC_META_PASSTYPE_FACEAndCARD = 3,				// 人脸和刷卡
	E_DC_META_PASSTYPE_FACEAndPWD = 4,				// 人脸和密码
	E_DC_META_PASSTYPE_QRCODE = 5,					// 二维码
	E_DC_META_PASSTYPE_UNLOCK_PWD = 6,				// 解锁密码
	E_DC_META_PASSTYPE_REMOTE_OPEN = 7,				// 远程开门
	E_DC_META_PASSTYPE_MANUAL_OPEN = 8,				// 手动开门
	E_DC_META_PASSTYPE_CARD_AND_FACE = 9,			// 刷卡和人脸
	E_DC_META_PASSTYPE_FACEAndTEMP = 101,			// 比对模式的人脸和温度
	E_DC_META_PASSTYPE_UNIMPED_FACEAndTEMP = 102,	// 畅通模式的人脸和温度
}eDcMetaPassType;

// 通行类型
typedef enum E_PASS_TYPE {
	E_PASS_TYPE_UNKNOWN = 0,
	E_PASS_TYPE_FACE_SUCCESS = 1,					// 人脸识别成功
	E_PASS_TYPE_CARD_SUCCESS = 2,					// 刷卡识别成功
	E_PASS_TYPE_FACEAndCARD_SUCCESS = 3,			// 人脸加刷卡识别成功
	E_PASS_TYPE_FACEAndPWD_SUCCESS = 4,				// 人脸加密码识别成功
	E_PASS_TYPE_QR_SUCCESS = 5,						// 二维码识别成功
	E_PASS_TYPE_FACEAndTEMP_SUCCESS = 6,			// 人脸加温度，温度正常
	E_PASS_TYPE_REMOTE_OPEN = 7,					// 远程开门
	E_PASS_TYPE_MANUAL_OPEN = 8,					// 手动开门
	E_PASS_TYPE_UNLOCK_PWD = 9,						// 解锁密码开门
	E_PASS_TYPE_CARD_AND_FACE = 10,					// 刷卡和人脸成功

	E_PASS_TYPE_BLACK_LIST = 101,					// 黑名单
	E_PASS_TYPE_DEV_NOTPERMIT_TIME = 102,			// 设备当前时段无效

	E_PASS_TYPE_FACE_FAIL = 111,					// 人脸识别失败
	E_PASS_TYPE_FACE_NOTPERMIT_TIME = 112,			// 人脸识别当前时段无效
	E_PASS_TYPE_FACE_WITHOUT_MASK = 113,			// 未佩戴口罩

	E_PASS_TYPE_CARD_INVALID = 121,					// 卡片无效
	E_PASS_TYPE_CARD_NOTPERMIT_TIME = 122,			// 刷卡当前时段无效

	E_PASS_TYPE_FACEAndCARD_ERROR = 131,			// 人脸和卡片不匹配，卡片错误
	E_PASS_TYPE_FACEAndCARD_NOTPERMIT_TIME = 132,	// 人脸加刷卡当前时段无效 此索引包含在人脸识别当前时段无效
	E_PASS_TYPE_FACEAndCARD_TIMEOUT = 133,			// 刷卡超时
	E_PASS_TYPE_FACEAndCARD_QUIT_SWIPECARD = 134,	// 退出输入卡片

	E_PASS_TYPE_FACEAndPWD_ERROR = 141,				// 人脸和密码不匹配，密码错误
	E_PASS_TYPE_FACEAndPWD_NOTPERMIT_TIME = 142,	// 人脸加密码当前时段无效 此索引包含在人脸识别当前时段无效
	E_PASS_TYPE_FACEAndPWD_TIMEOUT = 143,			// 输入密码超时
	E_PASS_TYPE_FACEAndPWD_QUIT_INPUTPWD = 144,		// 退出输入密码

	E_PASS_TYPE_QR_NOT_EFFECT = 151,				// 二维码未生效
	E_PASS_TYPE_QR_EXPIRED = 152,					// 二维码已过期
	E_PASS_TYPE_QR_NOT_EXIST = 153,					// 二维码不存在
	E_PASS_TYPE_QR_USED_UP = 154,					// 二维码次数用尽

	E_PASS_TYPE_TEMP_TIMEOUT = 161,					// 测温超时
	E_PASS_TYPE_TEMP_HIGH = 162,					// 疑似高温
	E_PASS_TYPE_TEMP_TOO_HIGH = 163,				// 温度过高

	E_PASS_TYPE_UNLOCK_PWD_ERROR = 171,				// 解锁密码错误
	E_PASS_TYPE_UNLOCK_PWD_TIMEOUT = 172,			// 解锁密码输入超时
	E_PASS_TYPE_UNLOCK_PWD_QUIT = 173,				// 解锁密码退出
	E_PASS_TYPE_UNLOCK_PWD_LOCK = 174,				// 解锁密码密码错误次数达到最大次数,锁定

	E_PASS_TYPE_CARD_AND_FACE_ERROR = 181,			// 刷卡和人脸不匹配
}sPassedEventLog_ePassType;

// 通行结果
typedef enum {
	E_PASS_RESULT_UNKNOWN = 0,
	E_PASS_RESULT_SUCCESS = 1,
	E_PASS_RESULT_FAILURE = 2,
}sPassedEventLog_ePassResult;

typedef struct S_SDK_PASSED_EVENTLOG {
	uint nEventId;
	sPersonInfo personInfo;
	sPassedEventLog_eLivenessType livenessType;		// 活体类型
	float fLScore;									// 活体分数
	float fRScore;									// 识别分数
	sPassedEventLog_eVerificationType verType;		// 验证类型
	sPassedEventLog_ePassType passType;				// 通行事件类型
	char szPassType[64];							// 通行事件类型翻译
	uint nSnapSize;
	char *pszSnapPic;								// 人脸抓拍图
	uint nBgmPicSize;
	char *pszBgmPic;								// 抓拍图的背景图
	uint nRedPicSize;
	char *pszRedPic;								// 抓拍图的红外图
	sSystemTime sTimeSnap;							// 抓拍时间
	//char szSnapUri[64];							// mgvl_cloud 抓拍图上传后返回的uri
	float fTemperature;								// ps 温度
	sPassedEventLog_ePassResult passResult;			// 通行结果
	eDcMetaPassType metaPassType;					// 元通行事件类型
}sPassedEventLog;

// 通行记录搜索请求
enum E_SDK_PERSON_SEARCH_PASSED_LOG_TYPE {
	E_SEARCH_TYPE_WITHOUT_PIC = 0x00,				// 不要图片
	E_SEARCH_TYPE_WITH_SNAP = 0x01,					// 要抓拍图
	E_SEARCH_TYPE_WITH_BGM = 0x02,					// 要抓拍图对应背景图
	E_SEARCH_TYPE_WITH_RED = 0x04,					// 要红外图
	E_SEARCH_TYPE_WITH_PERSON = 0x08,				// 要数据库里的底图
};

typedef struct S_SDK_SEARCH_PASSED_LOG_REQ {
	uint nTypeMask;									// 搜索携带图片掩码 E_SDK_PERSON_SEARCH_PASSED_LOG_TYPE
	sPassedEventLog sCondition;						// 具体搜索条件
	sSystemTime sStartTime;							// 搜索开始时间。为0时忽略时间条件
	sSystemTime sEndTime;							// 搜索结束时间。为0时忽略时间条件
	uint nNumber;									// 请求条数。带图片搜索建议一次少于20条（一张图），多张图建议一次搜索1条
	uint nPosition;									// 搜索位置
	bool bPassTimeDesc;								// 搜索结果是否按照通行时间倒序
}sSearchPassedLogReq;

typedef struct S_SDK_SEARCH_PASSED_LOG_RSP {
	int nCount;
	sPassedEventLog *pLog;							// 搜索到的通行记录
	uint nTotalSize;								// 搜索到的总记录条数
}sSearchPassedLogRsp;

/*******************************门禁事件****************************************/
typedef enum {
	E_EVENT_TIP_NO = 0,								// 不提示
	E_EVENT_TIP_GOOD_MORNING = 1,					// 上午好
	E_EVENT_TIP_GOOD_NOON = 2,						// 中午好
	E_EVENT_TIP_GOOD_AFTERNOON = 3,					// 下午好
	E_EVENT_TIP_GOOD_EVENING = 4,					// 晚上好
	E_EVENT_TIP_GOOD_JOB = 5,						// 辛苦了
	E_EVENT_TIP_NOT_PERMIT_TIME = 6,				// 当前时段无权限，请联系管理员
	E_EVENT_TIP_WELCOME = 7,						// 欢迎光临
	E_EVENT_TIP_NOT_PERMIT_USER = 8,				// 此用户无权限，请联系管理员
	E_EVENT_TIP_INPUTPWD = 9,						// 请输入密码
	E_EVENT_TIP_PWD_ERROR = 10,						// 密码错误，认证失败
	E_EVENT_TIP_PWD_LOCK = 11,						// 密码错误次数达到最大次数，锁定
	E_EVENT_TIP_SWIPE_CARD = 13,					// 请刷卡
	E_EVENT_TIP_CARD_EEEOR = 14,					// 卡片不正确，认证失败
	E_EVENT_TIP_CARD_LOCK = 15,						// 卡片错误次数达到最大次数，锁定
	E_EVENT_TIP_CARD_TIMEOUT = 16,					// 刷卡超时
	E_EVENT_TIP_UNLOCK_PWD_ERROR = 17,				// 解锁密码错误，认证失败
	E_EVENT_TIP_UNLOCK_PWD_LOCK = 18,				// 解锁密码错误次数达到最大次数，锁定
	E_EVENT_TIP_INVALID_QRCODE = 19,				// 无效二维码
	E_EVENT_TIP_WRIST = 101,						// 手腕靠近测温点
	E_EVENT_TIP_WRIST_TIMEOUT = 102,				// 一定时间内没有有效温度，退出
	E_EVENT_TIP_TEMP_NORMAL = 103,					// 体温正常
	E_EVENT_TIP_TEMP_HIGH = 104,					// 疑似高温
	E_EVENT_TIP_TEMP_TOOHIGH = 105,					// 温度过高
	E_EVENT_TIP_TEMP_PAGE_QUIT = 106,				// 展示温度页面退出
	E_EVENT_TIP_FACE_WITHOUT_MASK = 107,			// 未佩戴口罩

	E_EVENT_TIP_SWIPE_FACE = 108,					// 请刷脸
	E_EVENT_TIP_CARD_AND_FACE_ERROR = 109,			// 人证不匹配
}eDoorCtrlEventTip;

typedef struct S_SDK_DOORCTRL_UPLOAD_EVENT {
	sPassedEventLog log;							// 事件具体内容
	eDoorCtrlEventTip tip;							// 事件提示内容（用于UI显示和声音播放）
	sDoorCtrlIdentifyTip idTip;						// 识别提示配置（用于UI确定显示什么内容）
	int nLockTime;									// 锁定时间，单位s
}sDoorCtrlEventInfo;

// 资源信息
typedef struct {
	uint64 nTotalSize;								// 总容量 单位 Byte
	uint64 nUsedSize;								// 已用容量 单位 Byte
	int nTotalCount;								// 总条数
	int nUsedCount;									// 已用条数
}sResourceInfoDetail;

typedef struct S_SDK_RESOURCE_INFO {
	sResourceInfoDetail person;						// 人员信息
	sResourceInfoDetail event;						// 通行记录
}sResourceInformation;

/*******************************界面操作请求 GUI->DEVICE*************************/
typedef enum {
	E_INTERACTIVE_G2D_UNKNOWN = 0,
	E_INTERACTIVE_G2D_UI_INITED = 1,				// GUI已初始化
	// 开机向导的界面请求

	// 检测模式的界面请求
	E_INTERACTIVE_G2D_DETECT_QUIT_SWIPECARD = 101,	// 组合验证退出刷卡
	E_INTERACTIVE_G2D_DETECT_SWIPECARD_TMOUT = 102,	// 组合验证刷卡超时
	E_INTERACTIVE_G2D_DETECT_INPUTPWD = 103,		// 组合验证输入密码					sCheckPassword
	E_INTERACTIVE_G2D_DETECT_QUIT_INPUTPWD = 104,	// 组合验证退出输入密码
	E_INTERACTIVE_G2D_DETECT_INPUTPWD_TMOUT = 105,	// 组合验证输入密码超时

	// 解锁密码
	E_INTERACTIVE_G2D_DETECT_ENTER_UNLOCK_PWD = 106,// 进入解锁界面
	E_INTERACTIVE_G2D_DETECT_INPUT_UNLOCK_PWD = 107,// 输入解锁密码						sCheckPassword
	E_INTERACTIVE_G2D_DETECT_QUIT_UNLOCK_PWD = 108,	// 退出解锁界面
	E_INTERACTIVE_G2D_DETECT_UNLOCK_PWD_TMOUT = 109,// 输入密码超时

	// 门铃
	E_INTERACTIVE_G2D_DETECT_DOORBELL = 110,		// 按门铃
	E_INTERACTIVE_G2D_DETECT_QUIT = 111,			// 组合验证退出，恢复初始状态
	E_INTERACTIVE_G2D_DETECT_TYPE_CHANGED = 112,	// 验证类型发生改变,检测更新模式

	// 二维码检测
	E_INTERACTIVE_G2D_ENTER_QRCODE = 131,			// 界面通知进入二维码检测模式
	E_INTERACTIVE_G2D_QUIT_QRCODE = 132,			// 界面通知退出二维码检测模式

	// 报警模式的界面请求
	E_INTERACTIVE_G2D_ALARM_VERIFY_ENTER = 141,		// 界面通知进入报警解除状态
	E_INTERACTIVE_G2D_ALARM_ADMINPWD = 142,			// 界面输入管理员密码解除报警				sCheckPassword
	E_INTERACTIVE_G2D_ALARM_QUIT = 143,				// 界面取消输入密码，退出报警解除状态到检测状态
	E_INTERACTIVE_G2D_ALARM_EM_ENTER = 144,			// 校验通过后界面进入工程模式请求

	// 显示二维码
	E_INTERACTIVE_G2D_ENTER_SHOW_QRCODE_WX = 151,  // 界面通知进入显示二维码模式,企业微信定制 sWXShowQRCodeReq
	E_INTERACTIVE_G2D_QUIT_SHOW_QRCODE_WX = 152,  // 界面通知退出显示二维码模式,企业微信定制

	// 人脸入库界面
	E_INTERACTIVE_G2D_ENTER_INPUT_FACE_WX = 161,	// 界面通知进入人脸入库模式,企业微信定制 
	E_INTERACTIVE_G2D_QUIT_INPUT_FACE_WX = 162,		// 界面通知退出人脸入库模式,企业微信定制
	E_INTERACTIVE_G2D_FINISH_INPUT_FACE_WX = 163,   // 完成采集人脸,企业微信定制	sWXPersonPicReq

	// 管理员校验模式的界面请求
	E_INTERACTIVE_G2D_ADMINVERIFY_ENTER = 201,		// 界面通知进入管理员校验模式
	E_INTERACTIVE_G2D_ENTER_ADMINPWD = 202,			// 界面输入管理员密码校验				sCheckPassword
	E_INTERACTIVE_G2D_ADMINVERIFY_QUIT = 203,		// 界面取消输入密码，退出到检测模式
	E_INTERACTIVE_G2D_EM_ENTER = 204,				// 校验通过后界面进入工程模式请求
	E_INTERACTIVE_G2D_INPUT_OTP = 205,				// 输入一次性密码						sD2GPsInputOtpReq
	E_INTERACTIVE_G2D_OTP_MODIFY_PWD = 206,			// 一次性密码修改密码				  sD2GPsForceModifyPwdReq

	// 工程模式界面请求
	E_INTERACTIVE_G2D_EM_QUIT = 301,				// 界面通知退出工程模式到检测模式
	E_INTERACTIVE_G2D_SWIPE_CARD_BG = 302,			// 人员入库时开始检测卡片
	E_INTERACTIVE_G2D_SWIPE_CARD_ED = 303,			// 人员入库时结束检测卡片
	E_INTERACTIVE_G2D_SNAP_FACE_BG = 304,			// 人员入库时开始采集人脸
	E_INTERACTIVE_G2D_SNAP_FACE_ED = 305,			// 人员入库时结束采集人脸
	E_INTERACTIVE_G2D_BEGIN_CLOUD_TEST = 306,		// 开始云服务测试						sD2GPsCloudTestReq
	E_INTERACTIVE_G2D_END_CLOUD_TEST = 307,			// 结束云服务测试
	E_INTERACTIVE_G2D_CHECK_CLOUD_FIRMWARE = 308,	// 检测云固件版本						sPsCloudFirmwareCheckReq
	E_INTERACTIVE_G2D_CLOUD_UPGRADE = 309,			// 开始云升级						sPsCloudUpgradeReq
	E_INTERACTIVE_G2D_CLOUD_UPGRADE_STATE = 310,	// 获取云升级状态

	// 数据管理界面
	E_INTERACTIVE_G2D_IMEXPORT_END = 401,			// 结束导入导出
	E_INTERACTIVE_G2D_IP_PERSON_BG = 402,			// 开始人员导入						sD2GImportPersonReq
	E_INTERACTIVE_G2D_EP_PERSON_BG = 403,			// 开始人员导出
	E_INTERACTIVE_G2D_IP_CONFIG_BG = 404,			// 开始导入设备参数
	E_INTERACTIVE_G2D_EP_CONFIG_BG = 405,			// 开始导出设备参数
	E_INTERACTIVE_G2D_IP_ALLDATA_BG = 406,			// 开始导入整机数据
	E_INTERACTIVE_G2D_EP_ALLDATA_BG = 407,			// 开始导出整机数据
	E_INTERACTIVE_G2D_EP_EVENTLOG_BG = 408,			// 开始通行记录导出
	E_INTERACTIVE_G2D_EP_SYSTEMLOG_BG = 409,		// 开始导出系统日志
}eInteractiveActionOpt;

// 人员检测输入密码
typedef struct S_SDK_CHECK_PASSWORD {
	char szPassword[NET_MAX_NAME_PSW_LEN];
}sCheckPassword;

//输入OTP密码
typedef struct S_SDK_G2D_PS_INPUT_OTP_REQ {
	sSystemTime time;
	char szSN[64];				//序列号
	char szOTP[64];				//一次性密码
}sD2GPsInputOtpReq;

//强制修改密码
typedef struct S_SDK_G2D_PS_FORCE_MODIFY_PWD_REQ {
	char szName[64];						
	char szOldPwd[64];						//本地使用为空 云端使用传入超级密码
	char szNewPwd[64];

	eEncryptType encryptType;
}sD2GPsForceModifyPwdReq;

typedef struct S_SDK_G2D_PS_CLOUD_TEST_REQ {
	sIpAddress addr;
	int nTimeout;
	char szUuid[64];
}sD2GPsCloudTestReq;

typedef struct {
	int nTimeout;
	char szUuid[64];
}sPsCloudFirmwareCheckReq;

typedef struct {
	char szFirmwareInfo[64];
}sPsCloudUpgradeReq;

typedef enum {
	E_IMPORT_PERSON_RULE_NAME = 0,
	E_IMPORT_PERSON_RULE_JOBNO = 1,
}eD2GImportRuleType;

typedef struct S_SDK_G2D_IMPORT_PERSON_REQ {
	eD2GImportRuleType rule;
}sD2GImportPersonReq;

//企业微信 界面请求二维码数据
typedef enum {
	E_QRCODE_UNKNOW = 0,
	E_QRCODE_BIND_DEVICE = 1,
	E_QRCODE_LOGIN_DEVICE = 2,
}eWXQrCodeType;

typedef struct {
	eWXQrCodeType type;
}sWXShowQRCodeReq;

//企业微信 退出人脸录入
typedef struct {
	bool bIsExit;
	char szUuid[64];
	char szOperId[64];
	int nFaceLen;						// 图片数据大小
	char* pszFacePicture;				// 图片数据
}sWXPersonPicReq;

typedef struct S_SDK_INTERACTIVE_G2D {
	eInteractiveActionOpt type;
	union {											// 发送信息,根据type找相应类型的结构体
		sCheckPassword pwd;
		sD2GPsCloudTestReq cloudTest;
		sPsCloudFirmwareCheckReq firmware;
		sPsCloudUpgradeReq upgrade;
		sD2GImportPersonReq import;
		sWXShowQRCodeReq qrcode_wx;
		sWXPersonPicReq	pic_wx;
		sD2GPsInputOtpReq	inputOtp;
		sD2GPsForceModifyPwdReq forceModifyPwd;
	};
}sDoorInteractiveG2D;

/********************************界面操作设备主动上传 DEVICE->GUI*****************************/
// 人员入库,刷卡后返回卡号
typedef struct S_SDK_INTERACTIVE_CARD_NUMBER {
	char szCardNo[64];
}sInteractiveCardNumber;

// 人员入库,返回采集人脸图片
typedef enum {
	E_SNAP_RESULT_UNKNOWN = 0,
	E_SNAP_RESULT_SUCCESS = 1,
}sInteractiveSnapFace_eRet;

typedef struct S_SDK_INTERACTIVE_SNAP_FACE {
	sInteractiveSnapFace_eRet ret;
	int nFaceLen;									// 人脸图片数据大小
	char *pszFacePicture;							// 人脸图片数据

	int nFeatureLen;								// 人脸特征数据大小
	char *pszFeature;								// 人脸特征数据

	uint nMaskFeatureLen;							// 口罩特征数据长度
	char *pszMaskFeature;							// 口罩特征
}sInteractiveSnapFace;


typedef struct S_SDK_INTERACTIVE_IMEXPORT_PROGRESS {
	int nProgress;
}sInteractiveImExportProgress;

typedef enum {
	E_D2G_IMPORT_PERSON_OK = 0,
	E_D2G_IMPORT_PERSON_FAILURE = 1,
	E_D2G_IMPORT_PERSON_SPACE = 2,					// 空间不足
	E_D2G_IMPORT_PERSON_FILE_ERROR = 3,				// 文件损坏
	E_D2G_IMPORT_PERSON_USB_NOT_EXIST = 4,			// U盘不存在
}eInteractiveImExportResult;

typedef struct S_SDK_INTERACTIVE_IMEXPORT_RESULT {
	eInteractiveImExportResult ret;
	int nSuccess;									// 成功量
	int nFailure;									// 失败量
}sInteractiveImExportResult;

typedef enum {
	E_PS_CLOUD_TEST_UNKNOWN = 0,
	E_PS_CLOUD_TEST_CONNECTED = 1,
	E_PS_CLOUD_TEST_DEVICE_NOT_EXIST = 2,
	E_PS_CLOUD_TEST_REFUSE_DEVICE = 3,
	E_PS_CLOUD_TEST_SERVER_ERROR = 4,
}ePsCloudTestResult;

typedef struct {
	ePsCloudTestResult ret;
	char szUuid[64];
}sInteractivePsCloudTestResult;

typedef struct {
	bool bNew;
	char szFirmwareInfo[64];
	char szUuid[64];
}sPsCloudFirmwareResultRsp;

typedef enum {
	E_PS_CLOUD_UPGRADE_STATE_UNKNOWN = 0,
	E_PS_CLOUD_UPGRADE_STATE_STABLE = 1,			// 无新版本
	E_PS_CLOUD_UPGRADE_STATE_UNSTABLE = 2,			// 有新版本未下载
	E_PS_CLOUD_UPGRADE_STATE_DOWNLOADING = 3,		// 下载中
	E_PS_CLOUD_UPGRADE_STATE_DOWNLOADED = 4,		// 下载完成
	E_PS_CLOUD_UPGRADE_STATE_UPGRADING = 5,			// 升级中
}ePsCloudUpgradeType;

typedef struct {
	ePsCloudUpgradeType state;
	int nProgress;									// 下载或升级进度
}sPsCloudUpgradeStateRsp;

typedef struct {
	char *pszFeature;								// 人脸特征
	uint nFeatureLen;								// 人脸特征数据长度
}sDmyUploadFaceFeature;

typedef struct {
	eWXQrCodeType eQRCodeType;
	char szData[256];
}sWXQRCodeDataRsp;

typedef enum {
	E_WX_INPUT_FACE_START = 0,
	E_WX_INPUT_FACE_END = 1,
}eWXInputFaceDataType;

typedef struct {
	eWXInputFaceDataType type;
	char szUuid[64];
	char szOperId[64];
}sWXInputFaceDataRsp;

typedef struct {
	bool bIsBind;
}sWXBindResultRsp;

typedef enum {
	E_INTERACTIVE_D2G_UNKNOWN = 0,
	E_INTERACTIVE_D2G_IDENTIFY_ADMIN = 1,			// 识别结果是管理员			收到消息即是管理员
	E_INTERACTIVE_D2G_CARD = 2,						// 刷卡后返回卡号			sInteractiveCardNumber
	E_INTERACTIVE_D2G_SNAP_FACE = 3,				// 入库返回采集人脸图片		sInteractiveSnapFace
	E_INTERACTIVE_D2G_PROGRESS = 4,					// 导入导出信息进度			sInteractiveImExportProgress
	E_INTERACTIVE_D2G_RESULT = 5,					// 导入导出信息结果			sInteractiveImExportResult
	E_INTERACTIVE_D2G_PS_CLOUD_TEST_RESULT = 6,		// ps云状态测试结果返回		sInteractivePsCloudTestResult
	E_INTERACTIVE_D2G_PS_CLOUD_FIRMWARE_RESULT = 7,	// ps云固件版本信息			sPsCloudFirmwareResultRsp
	E_INTERACTIVE_D2G_PS_CLOUD_UPGRADE_STATE = 8,	// 获取云升级状态			sPsCloudUpgradeStateRsp
	E_INTERACTIVE_D2G_DM_SNAP_FACEFEATURE = 9,		// DMY实时入库特征上报		sDmyUploadFaceFeature
	E_INTERACTIVE_D2G_WEIXIN_QRCODE_DATA = 10,		// 上传二维码数据			sWXQRCodeDataRsp
	E_INTERACTIVE_D2G_WEIXIN_INPUT_FACE_DATE = 11,  // 企业微信本地人脸入库		sWXInputFaceDataRsp
	E_INTERACTIVE_D2G_WEIXIN_BIND_RESULT = 12,		// 若企微绑定成功则返回此结果		sWXBindResultRsp
}sDoorInteractiveD2G_eActionType;

typedef struct S_SDK_DOOR_INTERACTIVE_D2G {
	sDoorInteractiveD2G_eActionType type;			// 消息类型
	union {											// 上传信息,根据type找相应类型的结构体
		sInteractiveCardNumber card;
		sInteractiveSnapFace snap;
		sInteractiveImExportProgress progress;
		sInteractiveImExportResult imExResult;
		sInteractivePsCloudTestResult testResult;
		sPsCloudFirmwareResultRsp firmware;
		sPsCloudUpgradeStateRsp state;
		sDmyUploadFaceFeature dmFeature;
		sWXQRCodeDataRsp qrcode_wx;
		sWXInputFaceDataRsp face_wx;
		sWXBindResultRsp bindResult_wx;
	};
}sDoorInteractiveD2G;

/*******************************Cloud操作请求 Cloud->Device*************************/
typedef enum {
	E_PS_CLOUD_INIT = 0,
	E_PS_CLOUD_OFFLINE = 1,
	E_PS_CLOUD_ONLINE = 2,
}ePsCloudState;

typedef struct S_SDK_C2D_UPDATE_PSCLOUD_STATE {
	ePsCloudState state;
}sC2DUpdatePsCloudState;

typedef enum {
	E_C2D_ACTION_UNKNOWN = 0,
	E_C2D_ACTION_PS_CLOUD_STATE = 1,				// 云状态更新---请求结构体: sC2DUpdatePsCloudState, 返回结构体: 无
	E_C2D_ACTION_PS_CLOUD_TEST_RESULT = 2,			// ps云测试回复---请求结构体: sInteractivePsCloudTestResult, 返回结构体: 无
	E_C2D_ACTION_PS_CLOUD_FIRMWARE_RESULT = 3,		// ps云固件版本信息 sPsCloudFirmwareResultRsp
	E_C2D_ACTION_PS_CLOUD_UPGRADE_STATE = 4,		// 获取云升级状态 sPsCloudUpgradeStateRsp
	E_C2D_ACTION_PS_CLOUD_FORCE_MODIFY_PWD = 5,		// 修改管理员密码 sD2GPsForceModifyPwdReq
}eC2DActionType;

 typedef struct S_SDK_CLOUD_TO_DEVICE_REQ {
	eC2DActionType type;
	// 根据eL2DActionType对应相应结构体
	union {
		sC2DUpdatePsCloudState cloudState;
		sInteractivePsCloudTestResult result;
		sPsCloudFirmwareResultRsp firmware;
		sPsCloudUpgradeStateRsp state;
		sD2GPsForceModifyPwdReq forceModifyPwd;
	};
}sCloudToDeviceReq;

// LocalSdk操作请求返回结果
typedef struct S_SDK_CLOUD_TO_DEVICE_RSP {
	eC2DActionType type;
	// 根据eL2DActionType对应相应结构体
}sCloudToDeviceRsp;

/*******************************Device上传事件 Device->Cloud*************************/
//
typedef enum {
	E_OPT_PERSON_INFO_ADD = 0,						// 人员信息增加
	E_OPT_PERSON_INFO_DELETE = 1,					// 人员信息删除
	E_OPT_PERSON_INFO_MODIFY = 2,					// 人员信息修改
	E_OPT_PERSON_GROUP_ADD = 3,						// 人员分组增加
	E_OPT_PERSON_GROUP_DELETE = 4,					// 人员分组删除
	E_OPT_PERSON_GROUP_MODIFY = 5,					// 人员分组修改
	E_OPT_SCEDULR_ADD = 6,							// 时间计划增加
	E_OPT_SCEDULR_DELETE = 7,						// 时间计划删除
	E_OPT_SCEDULR_MODIFY = 8,						// 时间计划修改
	E_OPT_EVENT_PASSLOG = 9,						// 通行事件上报
	E_OPT_ALARM_LOG = 10,							// 门铃报警上报
}sChangedEventLog_eOptType;

typedef struct {
	sChangedEventLog_eOptType type;
	sIdentifier id;
	uint64 nTimeStamp;
} sChangedEventLogResult;

typedef struct {
	int nCount;
	sChangedEventLogResult rt[NET_MAX_OPT_PERSONS_ONCES];
}sChangedEventLog;

typedef struct {
	eConfigCmdType cfgType;							// 配置改变
}sD2CConfigChangedReq;

typedef enum {
	E_D2C_ACTION_UNKNOWN = 0,
	E_D2C_ACTION_DATA_CHANGED = 1,					// 数据库发生改变 sChangedEventLog
	E_D2C_ACTION_CONFIG_CHANGED = 2,				// 配置发生改变 sD2CConfigChangedReq
	E_D2C_ACTION_PS_START_CLOUD_TEST = 3,			// ps开始云测试请求 sD2GPsCloudTestReq
	E_D2C_ACTION_PS_STOP_CLOUD_TEST = 4,			// ps结束云测试请求
	E_D2C_ACTION_PS_CHECK_CLOUD_FIRMWARE = 5,		// 检测云固件版本 sPsCloudFirmwareCheckReq
	E_D2C_ACTION_PS_CLOUD_UPGRADE = 6,				// 开始云升级 sPsCloudUpgradeReq
	E_D2C_ACTION_PS_CLOUD_UPGRADE_STATE = 7,		// 获取云升级状态
	E_D2C_ACTION_PS_DOOR_DETECT_DOORBELL = 8,		// 门铃信号
}eD2CActionType;

typedef struct S_SDK_DEVICE_TO_CLOUD_REQ {
	eD2CActionType type;
	union {
		sChangedEventLog log;
		sD2CConfigChangedReq changed;
		sD2GPsCloudTestReq test;
		sPsCloudFirmwareCheckReq firm;
		sPsCloudUpgradeReq upgrade;
	};
}sDeviceToCloudReq;

typedef struct S_SDK_CONFIG_CHANGE_OBSERVER {
	eConfigCmdType cfgType;							// 改变配置枚举
}sConfigChangeObserver;

typedef struct S_SDK_AUDIO_STRENGTH_UPLOAD {
	int nAudioStrength;								// 音频强度[0~100]
}sAudioStrengthUpload;

typedef struct S_SDK_SERIAL_DATA_UPLOAD {
	int nSerialId;									// 串口Id
	int nDataLen;									// 上传数据长度
	uchar *pszData;									// 上传数据
}sSerialDataUpload;

// Gui测试，设备端透传
typedef enum {
	E_S2S_RESULT_UNKNOWN = 0,						// 未知错误
	E_S2S_RESULT_OK = 1,							// 开始、成功
	E_S2S_RESULT_FAILED = 2,						// 结束、失败
	E_S2S_RESULT_UNSUPPORTED = 3,					// 不支持
}eS2SResultType;

typedef struct S_SDK_S2S_SCREENTEST_RSP {
	eS2SResultType result;
}sS2SScreenTestRsp;

typedef enum {
	E_S2S_INTERACTIVE_SCREEN_TEST = 0,				// 屏幕测试，对应sS2SScreenTestRsp
}eS2SInteractiveType;

typedef struct S_SDK_S2S_INTERACTIVE_REQ {
	eS2SInteractiveType type;
	char szSender[16];								// 发送者标识，回调中确认是否为自己发送的请求
	char reserve[32];								// 预留字节
	union {
		sS2SScreenTestRsp rsp;
	};
	char reserve2[32];								// 预留字节
}sS2SInteractiveReq;

typedef struct S_SDK_RESTORE_TEMPORARYCONFIG_PARAM {
	int nCount;
	eConfigCmdType cmd[16];
}sRestoreTempConfigParam;

typedef struct S_SDK_FRAME_HEAD_INFO {
	unsigned int nFrameType;
	unsigned int dateTime;
	unsigned short nWidth;
	unsigned short nHeight;
	unsigned short nFps;
	unsigned short reserved1;
	unsigned int nDataLength;
	unsigned short nInfoLength;
	unsigned short reserved2;
	//unsigned char data[0];
}sFrameHeadInfo;

typedef struct S_SDK_AUDIO_HEAD_INFO {
	unsigned int nFrameType;
	unsigned int dateTime;
	unsigned int sampleRate;
	unsigned int nDataLength;
	unsigned short nInfoLength;
	unsigned short reserved;
}sAudioHeadInfo;

typedef struct S_SDK_FRAME_BODY_DATA {
	union {
		sFrameHeadInfo frameInfo;
		sAudioHeadInfo audioInfo;
	};
	eSubFrameType eType;
	size_t nFramePosInFile;							// 当前帧在文件中的位置，仅本地回放有效
	unsigned char *pBuf;							// 码流信息
	unsigned char *pExtInfo;						// 扩展信息
}sFrameBodyData;

// 数据上报通道建立、关闭参数
typedef struct {
	int nChannel;									//通道号, 固定填"0"
	eIntelPicturePushType picType;					//需要关注的图片类型
	int nTypeMsk;									//推送图片类型掩码--见枚举E_SDK_INTEL_PUSH_IMG_TYPE
}sPicPushChannelParam;

typedef struct {
	int nSerialId;									//通道号, 固定填"0"
}sSerialUploadChannelParam;

typedef struct {
	bool bClose;									// 是否关闭通达，为true时可不用填其他参数
	union {
		sPicPushChannelParam picPush;				// 对应枚举E_SDK_ALARM_TYPE_PUSH
		sSerialUploadChannelParam serialUpload;		// 对应枚举E_SDK_ALARM_TYPE_SERIAL_UPLOAD
		char reserve[128];							// 预留字节（联合体大小128个字节）
	};
	char reserve2[32];								// 预留字节
}sUploadInfoChannelParam;

/************************************************************************
** 名称: fDisconnectedCallback
** 功能: 设备断线回调函数
************************************************************************/
typedef void (CALL_METHOD *fDisconnectedCallback) (long lLogin, char *pszIp, long lPort, puint dwUser);

/************************************************************************
** 名称: fSubDisConnectCallBack
** 功能: 子连接断线回调
注：不包含eSubConnType::conn_main主链接
************************************************************************/
typedef void (CALL_METHOD *fSubDisConnectCallBack)(long lLoginID, eSubConnType type, long nChannel, puint dwUser);

/************************************************************************
** 名称: fRealDataCallBack
** 功能: 码流数据回调函数
	dwDataType：帧类型 详情见eSubFrameType
************************************************************************/
typedef int (CALL_METHOD *fRealDataCallBack) (long lRealHandle, long dwDataType, uchar *pBuffer, long lbufsize, puint dwUser);

/************************************************************************
** 名称: fRealDataCallBackV2
** 功能: 码流数据回调函数
************************************************************************/
typedef int (CALL_METHOD *fRealDataCallBackV2) (long lRealHandle, const sFrameBodyData *pFrameData, puint dwUser);

/************************************************************************
** 名称: fDownLoadPosCallBack
** 功能: 回放录像进度回调函数、搜索进度回调（此时lPlayHandle参数无效）
************************************************************************/
typedef void(CALL_METHOD *fDownLoadPosCallBack) (long lPlayHandle, long lTotalSize, long lDownLoadSize, puint dwUser);

/************************************************************************
** 名称: fUpgradeCallBack
** 功能: 升级设备回调函数
** 说明: nTotalSize >  0时, nSendSize >  0 发送进度
		 nTotalSize =  0时, nSendSize = -1 说明升级完成
							nSendSize = -2 说明升级出错
							nSendSize = E_SDK_ERROR_NOENOUGH_MEMORY --- E_SDK_ERROR_INVALID_CRC 升级错误原因
		 nTotalSize = -1时, nSendSize:1-99返回升级进度
		 nTotalSize = -2时, nSendSize:1-99云升级下载进度
************************************************************************/
typedef void(CALL_METHOD *fUpgradeCallBack) (long lLoginID, puint lUpgradeHandle, int nTotalSize, int nSendSize, puint dwUser);

/************************************************************************
** 名称: pfSearchDeviceCallBack
** 功能: 搜索设备回调函数
************************************************************************/
typedef  void (CALL_METHOD *pfSearchDeviceCallBack)(sSearchDeviceConfig *pDevInfo, puint userData);

/************************************************************************
** 名称: fMessCallBack
** 功能: 消息（报警等）回调函数
** 说明: pBuf数据按eType对应不同结构体
************************************************************************/
typedef bool (CALL_METHOD *fMessCallBack)(long lLoginID, char *pBuf, ulong dwBufLen, puint dwUser, eAlarmType eType);


/************************************************************************
** 名称: F_SDK_Init
** 功能: 初始化环境
** 参数: [in]fDisconnect			设备断开用户回调函数指针
**       [in]dwUser				设备断开用户回调参数
** 返回: 1 成功, <0 失败,返回值对应错误号
************************************************************************/
DLL_EXPORT long F_SDK_Init(fDisconnectedCallback cbDisconnect, puint dwUser);

/************************************************************************
** 名称: F_SDK_Uninit
** 功能: 清除环境
** 参数: 无
** 返回: 1 成功, <0 失败,返回值对应错误号
************************************************************************/
DLL_EXPORT long F_SDK_Uninit(puint dwUser DEF_PARAM(NULL));

/************************************************************************
** 名称: F_SDK_SetSubDisconnectCallBack
** 功能: 设置子连接异常断开回调函数
** 参数: [in]cbSubDisconnect		子连接断开回调
**       [in]dwUser				回调函数参数
** 返回: =1 成功, =0 失败
************************************************************************/
DLL_EXPORT long F_SDK_SetSubDisconnectCallBack(fSubDisConnectCallBack cbSubDisconnect, puint dwUser);

/************************************************************************
** 名称: F_SDK_SetConnectTime
** 功能: 设置登录设备超时时间和尝试次数
** 参数: [in]nWaitTime			超时时间，单位ms，默认3000ms,
**       [in]nTryTimes			次数,默认1次
** 返回: true 成功, false 失败
************************************************************************/
DLL_EXPORT bool F_SDK_SetConnectTime(long nWaitTime, long nTryTimes);

/************************************************************************
** 名称: F_SDK_SetLocalCfg
** 功能: 设置本地配置
** 参数: [in]eType				配置类型
**       [in]lpInBuff			发送缓冲
** 返回: >0 成功, <0 失败,返回值对应错误号
************************************************************************/
DLL_EXPORT long F_SDK_SetLocalCfg(eLocalCfgType eType, const void *lpInBuff);

/************************************************************************
** 名称: F_SDK_GetLastError
** 功能: 获取错误信息
** 参数: 无
** 返回: 错误码
************************************************************************/
DLL_EXPORT long F_SDK_GetLastError();

/************************************************************************
** 名称: F_SDK_Login
** 功能: 登录设备
** 参数: [in]sLoginInfo			登录信息，包括设备IP、端口、用户名、密码等
**       [out]lpDeviceInfo		设备信息
**       [out]pnError			登录错误码
** 返回: >0 成功, <=0 失败, pnError值对应错误号
************************************************************************/
DLL_EXPORT long F_SDK_Login(const sLoginInfo loginInfo, sDeviceInfo *lpDeviceInfo, int *pnError);

/************************************************************************
** 名称: F_SDK_LocalLogin
** 功能: 本地登录设备（LocalNetSdk）
** 参数: [out]lpDeviceInfo		设备信息
**       [out]pnError			登录错误码
** 说明: 需要等待应用主程序启动之后调用此接口
** 返回: >0 成功, <=0 失败, pnError值对应错误号
************************************************************************/
DLL_EXPORT long F_SDK_LocalLogin(sDeviceInfo *lpDeviceInfo, int *pnError);

/************************************************************************
** 名称: F_SDK_Logout
** 功能: 登出设备
** 参数: [in]lLoginID			设备登录句柄
** 返回: 1 成功, 0 失败,
************************************************************************/
DLL_EXPORT long F_SDK_Logout(long lLoginID);

/************************************************************************
** 名称: F_SDK_SearchDeviceInfo
** 功能: 搜索设备信息，是否存在录像，录像列表，日志信息等
** 参数: [in]lLoginID			设备登录句柄
**       [in]dwCommand:			控制命令,支持且只支持下面列出的命令
**       [in]nChannelNO:		-1代表全通道,0-n代表单个通道
**       [in]lpInBuffer:		发送缓冲
**       [in]dwInBufferSize:	发送缓冲大小
**       [out]lpOutBuffer:		接收缓冲
**       [in out]pnOutSize		接收缓冲大小,返回的数据大小
**		 [in]bGetJson:			结果是否以Json字符串的形式返回
**       [in]waittime:			等待时间
** 说明:  bGetJson: true:返回结果是Json字符串
                    false:返回结果是结构体二进制数据

		 dwCommand支持的命令						lpInBuffer对应结构体				lpOutBuffer对应结构体
		 E_SDK_CMD_SEARCH_RECORD_EXIST			sRecordCondit					sRecordSearchExist			//有无录像
		 E_SDK_CMD_SEARCH_RECORD_LIST			sRecordSearchCondition			sRecordList					//查询录像
		 E_SDK_CMD_SEARCH_LOG_LIST				sLogSearchCondition				sLogList					//查询日志
		 E_SDK_CMD_SEARCH_ALGORITHM_STATISTIC	sSearchTargetStatReq			sSearchTargetStatRsp		//智能统计
		 E_SDK_CMD_SEARCH_CURRENT_STATISTIC		sSearchCurrentStatReq			sSearchCurrentStatRsp		//当前统计
** 返回: =1:成功,=0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SearchDevInfo(long lLoginID, ulong dwCommand, int nChannelNO, char *lpInBuffer, ulong nInSize, char *lpOutBuffer, ulong *pnOutSize, bool bGetJson DEF_PARAM(false), int nWaittime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_SetSearchPosCallBack
** 功能: 设置搜索进度回调函数
** 参数: [in]cbProgress			搜索进度回调函数
**       [in]dwUser				回调函数参数
** 返回: =1 成功, =0 失败
************************************************************************/
DLL_EXPORT long F_SDK_SetSearchPosCallBack(fDownLoadPosCallBack cbProgress, puint dwUser);

/************************************************************************
** 名称: F_SDK_GetDevConfig
** 功能: 获取远程配置参数
** 参数: [in]lLoginID			设备登录句柄
**       [in]dwCommand:			控制命令,见enum SDK_COMMAND_TYPE
**       [in]nChannelNO:		-1代表全通道,0-n代表单个通道
**       [out]lpOutBuffer:		接收缓冲
**       [in out]pnOutSize		接收缓冲大小,返回的数据大小
**		 [in]bDefaultCfg:		是否获取默认配置
**		 [in]bGetJson:			结果是否以Json字符串的形式返回
**       [in]nWaittime:			等待时间
** 说明: bGetJson: true:返回结果是Json字符串
                   false:返回结果是结构体二进制数据
** 返回: 1 成功, <0 失败,
************************************************************************/
DLL_EXPORT long F_SDK_GetDevConfig(long lLoginID, ulong dwCommand, int nChannelNO, char *lpOutBuffer, ulong *pnOutSize, bool bDefaultCfg DEF_PARAM(false), bool bGetJson DEF_PARAM(false), int nWaittime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_SetDevConfig
** 功能: 保存远程配置参数
** 参数: [in]lLoginID			设备登录句柄
**       [in]dwCommand			控制命令,见enum SDK_COMMAND_TYPE
**       [in]nChannelNO			-1代表全通道,0-n代表单个通道
**       [in]lpInBuffer			发送缓冲
**       [in]dwInSize			发送缓冲大小
**		 [in]bSetJson			数据是否以Json字符串的形式发送
**       [in]nWaittime			等待时间
** 说明: bSetJson: true:lpInBuffer是Json字符串
                   false:lpInBuffer是结构体二进制数据
** 返回: 1 成功, <0 失败,
************************************************************************/
DLL_EXPORT long F_SDK_SetDevConfig(long lLoginID, ulong dwCommand, int nChannelNO, char *lpInBuffer, ulong dwInSize, bool bSetJson DEF_PARAM(false), int nWaittime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_OpenRealPreview
** 功能: 打开实时预览
** 参数: [in]lLoginID			设备登录句柄
**       [in]lpPlayInfo:		播放信息
** 返回: >0:成功，预览播放句柄,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_OpenRealPreview(long lLoginID, lpsPlayInfo lpPlayInfo);

/************************************************************************
** 名称: F_SDK_StopRealPreview
** 功能: 停止实时预览
** 参数: [in]lPlayHandle			预览播放句柄
** 返回: >0:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_StopRealPreview(long lPlayHandle);

/************************************************************************
** 名称: F_SDK_SetRealDataCallBack
** 功能: 设置预览码流回调函数
** 参数: [in]lPlayHandle			预览播放句柄
**       [in]cbRealData			回调函数
**       [in]dwUser				回调函数参数
** 返回: =1:成功,=0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SetRealDataCallBack(long lPlayHandle, fRealDataCallBack cbRealData, puint dwUser);

/************************************************************************
** 名称: F_SDK_DelRealDataCallBack
** 功能: 清除回调函数
** 参数: [in]lPlayHandle			预览播放句柄
**       [in]cbRealData			回调函数
**       [in]dwUser				回调函数参数
** 说明: 该函数需要在F_SDK_StopRealPreview前调用
** 返回: =1:成功,=0:失败
************************************************************************/
DLL_EXPORT long F_SDK_DelRealDataCallBack(long lPlayHandle, fRealDataCallBack cbRealData, puint dwUser);

/************************************************************************
** 名称: F_SDK_SetRealDataCallBackV2
** 功能: 设置预览码流回调函数
** 参数: [in]lPlayHandle			预览播放句柄
**       [in]cbRealData			回调函数
**       [in]dwUser				回调函数参数
** 说明: 数据经过码流分析过，带有帧的具体信息
** 返回: =1:成功,=0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SetRealDataCallBackV2(long lPlayHandle, fRealDataCallBackV2 cbRealData, puint dwUser);

/************************************************************************
** 名称: F_SDK_DelRealDataCallBackV2
** 功能: 清除回调函数
** 参数: [in]lPlayHandle			预览播放句柄
**       [in]cbRealData			回调函数
**       [in]dwUser				回调函数参数
** 说明: 该函数需要在F_SDK_StopRealPreview前调用
** 返回: =1:成功,=0:失败
************************************************************************/
DLL_EXPORT long F_SDK_DelRealDataCallBackV2(long lPlayHandle, fRealDataCallBackV2 cbRealData, puint dwUser);

/************************************************************************
** 名称: F_SDK_StartTalk
** 功能: 开始对讲
** 参数: [in]lLoginID			设备登录句柄
**       [in]cbAudioData		音频回调函数(目前无)
**       [in]dwUser				回调函数参数
** 返回: > 0:成功,<=0:失败
************************************************************************/
DLL_EXPORT long F_SDK_StartTalk(long lLoginID, const sStartTalkInfo *pInfo, fRealDataCallBack cbAudioData, puint dwUser);

/************************************************************************
** 名称: F_SDK_StopTalk
** 功能: 关闭对讲
** 参数: [in]lVoiceHandle		对讲句柄
** 返回: > 0:成功,<=0:失败
************************************************************************/
DLL_EXPORT long F_SDK_StopTalk(long lVoiceHandle);

/************************************************************************
** 名称: F_SDK_TalkSendData
** 功能: 发送对讲数据
** 参数: [in]lVoiceHandle		对讲句柄
**       [in]pSendBuf			对讲数据
**       [in]lBufSize			对讲数据大小
**       [in]pFormat			对讲数据编码信息
** 返回: > 0:成功,<=0:失败
************************************************************************/
DLL_EXPORT long F_SDK_TalkSendData(long lVoiceHandle, const char *pSendBuf, long lBufSize, const sAudioFormat *pFormat);

/************************************************************************
** 名称: F_SDK_PlayBackByName
** 功能: 按文件名回放录像
** 参数: [in]lLoginID			设备登录句柄
**       [in]lpControl			播放信息
**       [in]cbDownLoadPos		回放进度回调函数，这里只通知是否发送结束
**       [in]cbPlackBackData	回放数据回调函数
**       [in]dwDataUser			回调函数参数
** 返回: >0:成功，回放句柄,=0:失败, F_SDK_GetLastError获取错误信息
************************************************************************/
DLL_EXPORT long F_SDK_PlayBackByName(long lLoginID, sPlayBackControl *lpControl, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack cbPlackBackData, puint dwDataUser);

/************************************************************************
** 名称: F_SDK_DownLoadRecordFileByName
** 功能: 按文件名下载录像文件
** 参数: [in]lLoginID			设备登录句柄
**       [in]pFileInfo			下载的录像信息
**       [in]pszSavedPath		保存的文件路径
**       [in]cbDownLoadPos		下载进度回调
**       [in]dwDataUser			回调函数参数
** 返回: >0:成功，下载句柄,=0:失败, F_SDK_GetLastError获取错误信息
************************************************************************/
DLL_EXPORT long F_SDK_DownLoadRecordFileByName(long lLoginID, sPlayBackControl *pFileInfo, char *pszSavedPath, fDownLoadPosCallBack cbDownLoadPos, puint dwDataUser);

/************************************************************************
** 名称: F_SDK_DownloadStoredPicture
** 功能: 下载存储图片
** 参数: [in]lLoginID			设备登录句柄
**       [in]pFileInfo			下载的抓图信息
**       [out]pRecvInfo			获取文件参数
** 返回: >0:成功, <0:失败
************************************************************************/
DLL_EXPORT long F_SDK_DownloadStoredPicture(long lLoginID, sPlayBackControl *pFileInfo, sDownloadStoredPicParam *pRecvInfo);

/************************************************************************
** 名称: F_SDK_PlayBackControl
** 功能: 回放控制
** 参数: [in]lPlayHandle			回放句柄
**       [in]lControlCode		控制命令,见enum ePlayBackControl
**       [in]pCtl				控制参数
** 说明: pCtl 仅当lControlCode为E_SDK_PLAYBACK_CONTROL_LOCATE时有效，其余情况置NULL即可
** 返回: =1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_PlayBackControl(long lPlayHandle, long lControlCode, sPlayBackControl *pCtl DEF_PARAM(NULL));

/************************************************************************
** 名称: F_SDK_SetKeepLifeTime
** 功能: 设置保活时间
** 参数: [in]lLoginID			设备登录句柄
**       [in]nKeeplifeTime		心跳间隔,默认10s
**       [in]nDetectDisconTime	断线检测时间，默认30s
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SetKeepLifeTime(long lLoginID, uint nKeeplifeTime, uint nDetectDisconTime);

/************************************************************************
** 名称: F_SDK_DeviceUpgrade
** 功能: 系统升级
** 参数: [in]lLoginID			登录句柄
**       [in]pszFileName		升级文件路径
**       [in]nType				升级类型
**       [in]cbUpgrade			升级进度回调
**       [in]dwUser				回调函数参数
**       [in]nTotalLen			升级文件大小
** 说明:
**       升级类型: 0-全分区升级（本地升级）
                  1-云升级（pszFileName传NULL即可）
         
		 升级文件路径: 本地升级: 如果pszFileName置NULL则需要发送升级文件长度 nTotalLen，
		                       用户调用F_SDK_SendUpgradeData分包发送数据。否则nTotalLen置0即可
                      云升级: pszFileName置NULL、nTotalLen 置0即可
** 返回: >=1:成功,=0:失败
************************************************************************/
DLL_EXPORT puint F_SDK_DeviceUpgrade(long lLoginID, char *pszFileName, int nType, fUpgradeCallBack cbUpgrade, puint dwUser, int nTotalLen DEF_PARAM(0));

/************************************************************************
** 名称: F_SDK_SendUpgradeData
** 功能: 发送升级数据（配合本地升级使用）
** 参数: [in]lUpgradeHandle		升级句柄
**       [in]pszData			升级文件数据
**       [in]nDataLen			数据大小
** 说明: 设备老程序（2019年12月17日之前）nDataLen 不应大于102400
         设备新程序（2019年12月17日之后）nDataLen 不应大于512000
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_UpgradeSendData(puint lUpgradeHandle, const char *pszData, int nDataLen);

/************************************************************************
** 名称: F_SDK_GuiDeviceUpgrade
** 功能: Gui系统升级
** 参数: [in]lLoginID			登录句柄
**       [in]upParam			升级参数
**       [in]cbUpgrade			升级进度回调
**       [in]dwUser				回调函数参数
** 说明:
         升级前先把 “E_SDK_ALARM_TYPE_UPLOAD_INFO”状态信息上传通道打开，否则会没有升级进度返回
** 返回: >=1:成功,=0:失败
************************************************************************/
DLL_EXPORT puint F_SDK_GuiDeviceUpgrade(long lLoginID, sGuiUpgradeStart upParam, fUpgradeCallBack cbUpgrade, puint dwUser);

/************************************************************************
** 名称: F_SDK_CloseUpgradeHandle
** 功能: 释放升级句柄
** 参数: [in]lUpgradeHandle		升级句柄
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_CloseUpgradeHandle(puint lUpgradeHandle);

/************************************************************************
** 名称: F_SDK_SearchDevice
** 功能: 搜索局域网内的设备
** 参数: [out]pCfgArray			接收缓冲,sSearchDeviceConfig数组
**       [in out]pnArrayLen		传入缓冲长度，接收设备数量
**       [in]nSearchTime		等待时间
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SearchDevice(sSearchDeviceConfig *pCfgArray, int *pnArrayLen, int nSearchTime);

/************************************************************************
** 名称: F_SDK_SetConfigOverNet
** 功能: 跨网段设置设备配置
** 参数: [in]dwCommand			控制命令,见enum E_SDK_OVERNET_CMD_TYPE
**       [in]nChannelNO
**       [in]lpInBuffer
**       [in]dwInSize
**       [in]nWaitTime			等待时间
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SetConfigOverNet(ulong dwCommand, int nChannelNO, char *lpInBuffer, ulong dwInSize, int nWaitTime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_SetDevMessCallBack
** 功能: 设置接收设备信息回调, 例如报警信息,以ID号区分
** 参数: [in]cbAlarm				回调函数
**       [in]lUser				回调函数参数
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SetDevMessCallBack(fMessCallBack cbAlarm, puint lUser);

/************************************************************************
** 名称: F_SDK_SetupPushChan
** 功能: 建立图片上传通道
** 参数: [in]lLoginID			登录句柄
**       [in]nChannelNo			通道号,固定填"0"
**       [in]picType			需要关注的图片类型
**       [in]nTypeMsk			推送图片类型掩码--见枚举E_SDK_INTEL_PUSH_IMG_TYPE
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SetupPushChan(long lLoginID, int nChannel, eIntelPicturePushType picType, int nTypeMsk);

/************************************************************************
** 名称: F_SDK_ClosePushChan
** 功能: 关闭图片上报
** 参数: [in]lLoginID			登录句柄
**       [in]nChannelNo			通道号,固定填"0"
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_ClosePushChan(long lLoginID, int nChannel);

/************************************************************************
** 名称: F_SDK_SetupUploadInfoChan
** 功能: 建立、关闭信息上传通道
** 参数: [in]lLoginID			登录句柄
**       [in]uploadType			通道类型
**       [in]bClose				是否关闭
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SetupUploadInfoChan(long lLoginID, eAlarmType uploadType, bool bClose DEF_PARAM(false));


/************************************************************************
** 名称: F_SDK_SetupUploadInfoChanV2
** 功能: 建立、关闭信息上传通道V2
** 参数: [in]lLoginID			登录句柄
**       [in]uploadType			通道类型
**       [in]bClose				是否关闭
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_SetupUploadInfoChanV2(long lLoginID, eAlarmType uploadType, sUploadInfoChannelParam *pParam);

/************************************************************************
** 名称: F_SDK_DeviceControl
** 功能: 设备控制
** 参数: [in]lLoginID			登录句柄
**       [in]nType				控制类型
**       [in]nWaitTime			等待时间
** 说明: nType 0:重启设备
               1:清除日志
               2:门禁机远程开门
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_DeviceControl(long lLoginID, int nType, int nWaitTime DEF_PARAM(2000));

/************************************************************************
** 名称: F_SDK_PTZControl
** 功能: 云台控制
** 参数: [in]lLoginID			登录句柄
**       [in]sParam				云台控制参数
**       [in]nWaitTime			等待时间
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_PTZControl(long lLoginID, sPTZControlParam sParam, int nWaitTime DEF_PARAM(2000));

/************************************************************************
** 名称: F_SDK_WriteHardwareInfo
** 功能: 烧写硬件信息
** 参数: [in]lLoginID			登录句柄
**       [in]info				硬件信息
**       [in]nWaittime			超时时间
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_WriteHardwareInfo(long lLoginID, const sHardwareInfo info, int nWaittime DEF_PARAM(5000));

/************************************************************************
** 名称: F_SDK_OperFaceLibrary
** 功能: 操作设备人脸库
** 参数: [in]lLoginID			登录句柄
**       [in]eCmd				控制命令,见enum E_SDK_FACELIBRARY_CMDTYPE
**       [in]lpInBuffer			发送缓冲
**       [in]nInSize			发送缓冲大小
**       [out]lpOutBuffer		接收缓冲
**       [in out]nOutSize		接收缓冲大小,返回的数据大小
**       [in]bJson				数据是否以Json字符串的形式发送、接收（lpInBuffer、lpOutBuffer）
**       [in]nWaitTime			等待时间
** 返回: >=1:成功, <0:失败
************************************************************************/
DLL_EXPORT long F_SDK_OperFaceLibrary(long lLoginID, eFaceLibCmd eCmd, char *lpInBuffer, uint nInSize, char *lpOutBuffer, uint *pnOutSize, bool bJson DEF_PARAM(false), uint nWaitTime DEF_PARAM(5000));

/************************************************************************
** 名称: F_SDK_FreeBuffer
** 功能: 释放内存
** 参数: [in]lpBuffer			待释放内存指针
** 说明: 本接口只用来释放F_SDK_OperFaceLibrary接口的搜索结果
** 返回: >=1:成功, <0:失败
************************************************************************/
DLL_EXPORT long F_SDK_FreeBuffer(char *lpBuffer);

/************************************************************************
** 名称: F_SDK_DCInteractiveOperation
** 功能: 门禁机交互操作（GUI -> Device）
** 参数: [in]lLoginID			登录句柄
**       [in]ctl				操作参数
**       [in]nWaitTime			等待时间
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_DCInteractiveOperation(long lLoginID, sDoorInteractiveG2D ctl, int nWaitTime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_L2DOperation
** 功能: 本地SDK操作（LocalSdk -> Device）
** 参数: [in]lLoginID			登录句柄
**       [in]ctl				操作参数
**       [in]nWaitTime			等待时间
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_C2DOperation(long lLoginID, const sCloudToDeviceReq *pReq, sCloudToDeviceRsp *pRsp, int nWaitTime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_S2SOperation
** 功能: SDK交互操作（Sdk -> Sdk）
** 参数: [in]lLoginID			登录句柄
**       [in]ctl				操作参数
**       [in]nWaitTime			等待时间
** 返回: >=1:成功,<0:失败
************************************************************************/
DLL_EXPORT long F_SDK_S2SOperation(long lLoginID, const sS2SInteractiveReq *pReq, int nWaitTime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_ProduceTest
** 功能: 工装测试
** 参数: [in]lLoginID			登录句柄
**       [in]eCmd				控制命令
**       [in]lpInBuffer			发送缓冲
**       [in]nInSize			发送缓冲大小
**       [out]lpOutBuffer		接收缓冲
**       [in out]pnOutSize		接收缓冲大小,返回的数据大小
**       [in]nWaitTime			等待时间
** 返回: >=1:成功, <0:失败
************************************************************************/
DLL_EXPORT long F_SDK_ProduceTest(long lLoginID, eProduceTestCmd eCmd, char *lpInBuffer DEF_PARAM(NULL), uint nInSize DEF_PARAM(0), char *lpOutBuffer DEF_PARAM(NULL), uint *pnOutSize DEF_PARAM(NULL), uint nWaitTime DEF_PARAM(5000));

/************************************************************************
** 名称: F_SDK_CatchPicture
** 功能: 设备抓图
** 参数: [in]lLoginID			登录句柄
**       [in]nChannelNo			通道号
**       [in out]pParam			抓图数据
** 返回: >=1:成功, <0:失败
************************************************************************/
DLL_EXPORT long F_SDK_CatchPicture(long lLoginID, int nChannel, sCatchPictureParam *pParam);

/************************************************************************
** 名称: F_SDK_Log
** 功能: 日志打印
** 参数: [in]level				此条日志等级
**       [in]pszMsg				日志内容
** 返回: >=1:成功, <0:失败
************************************************************************/
DLL_EXPORT long F_SDK_Log(eLoggerLevelType level, const char *pszMsg);

/************************************************************************
** 名称: F_SDK_ConfigChangeObserver
** 功能: 配置修改监察
** 参数: [in]lLoginID			登录句柄
**       [in]eCmd				命令枚举
**       [in]bClose				是否关闭观察
** 返回: >=1:成功, <0:失败
************************************************************************/
DLL_EXPORT long F_SDK_ConfigChangeObserver(long lLoginID, eConfigCmdType eCmd, bool bClose DEF_PARAM(false));

/************************************************************************
** 名称: F_SDK_DeviceFileManager
** 功能: 文件管理
** 参数: [in]lLoginID			登录句柄
**       [in]eCmd				控制命令
**       [in]pReq				发送缓冲
**       [in]pRsp				接收缓冲
**       [in]bJson				是否以Json字符串的形式传输
**       [in]nWaitTime			等待时间
** 返回: >=1:成功, <0:失败
************************************************************************/
DLL_EXPORT long F_SDK_DeviceFileManager(long lLoginID, eDeviceFileManagerCmd eCmd, const sFileManagerReq *pReq, sFileManagerRsp *pRsp, bool bJson DEF_PARAM(false), uint nWaitTime DEF_PARAM(5000));

/************************************************************************
** 名称: F_SDK_SetDevTemporaryConfig
** 功能: 保存远程临时配置参数
** 参数: [in]lLoginID			设备登录句柄
**       [in]dwCommand			控制命令,见enum SDK_COMMAND_TYPE
**       [in]nChannelNO			-1代表全通道,0-n代表单个通道
**       [in]lpInBuffer			发送缓冲
**       [in]dwInSize			发送缓冲大小
**		 [in]bSetJson			数据是否以Json字符串的形式发送
**       [in]nWaittime			等待时间
** 说明: bSetJson: true:lpInBuffer是Json字符串
				false:lpInBuffer是结构体二进制数据
** 返回: 1 成功, <0 失败
************************************************************************/
DLL_EXPORT long F_SDK_SetDevTemporaryConfig(long lLoginID, eConfigCmdType eCmd, int nChannelNO, char *lpInBuffer, ulong dwInSize, bool bSetJson DEF_PARAM(false), int nWaittime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_RestoreTemporaryConfig
** 功能: 恢复临时配置
** 参数: [in]lLoginID			设备登录句柄
**       [in]dwCommand			控制命令,见enum SDK_COMMAND_TYPE
**       [in]nChannelNO			-1代表全通道,0-n代表单个通道
**       [in]nWaittime			等待时间
** 返回: 1 成功, <0 失败
************************************************************************/
DLL_EXPORT long F_SDK_RestoreTemporaryConfig(long lLoginID, int nChannelNO, sRestoreTempConfigParam param, int nWaittime DEF_PARAM(1000));

/************************************************************************
** 名称: F_SDK_SerialWrite
** 功能: 通过串口向设备写数据
** 参数: [in]lLoginID			设备登录句柄
**       [in]nPortId			串口Id
**       [in]pBuffer			数据
**       [in]nBufLen			数据长度
** 返回: 1 成功, <0 失败
************************************************************************/
DLL_EXPORT long F_SDK_SerialWrite(long lLoginID, int nPortId, char *pBuffer, int nBufLen);
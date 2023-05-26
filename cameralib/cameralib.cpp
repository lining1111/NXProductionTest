//
// Created by lining on 5/17/22.
//

#include <iostream>
#include <cstring>
#include <vector>
#include "cameralib.h"

#define x64

#ifdef x64

#include <jsoncpp/json/json.h>

#else

#include <json/json.h>

#endif

puint g_pUpgradeHandle = nullptr;
//HANDLE hEvent = NULL;
bool g_bExit = false;
bool g_bConnect = false;
long g_lLogin = 0;
sLoginInfo g_loginInfo{};
S_SDK_DEVICEINFO g_devInfo{};
static int g_nFeatureLen = 0;
static char *g_pszFeatureData = nullptr;

vector<sSearchDeviceConfig> vector_DeviceConfig;

std::string FormatCurrDatetime() {
    time_t tmt;
    time(&tmt);
    tm *t = localtime(&tmt);
    char szTemp[32]{};
    sprintf(szTemp, "%04d%02d%02d_%02d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min,
            t->tm_sec);
    return szTemp;
}

void SaveFile(void *pData, int nSize, char *pszPath) {
    std::cout << "Save data len: " << nSize << endl;
    if (!pData || nSize <= 0) {
        return;
    }
    char *pPath = nullptr;
    char strname1[200]{};
    if (pszPath) {
        pPath = pszPath;
    } else {
        sprintf(strname1, "./pic/%s_%d.jpg", FormatCurrDatetime().c_str(), nSize);
        pPath = strname1;
    }
    FILE *pfile1 = NULL;
    pfile1 = fopen(pPath, "wb+");
    if (pfile1) {
        fwrite(pData, 1, nSize, pfile1);
        fclose(pfile1);
    }
}

void CALL_METHOD DisconnectedCallback(long lLogin, char *pszIp, long lPort, puint dwUser) {
    USER_UNREFERENCED_PARAMETER(lLogin);
    USER_UNREFERENCED_PARAMETER(dwUser);
    std::cout << "Device Disconnected, IP:" << pszIp << ", Port:" << lPort << endl;
    g_bConnect = false;
}

bool CALL_METHOD MessCallBack(long lLoginID, char *pBuf, unsigned long dwBufLen, puint dwUser, eAlarmType eType) {
    USER_UNREFERENCED_PARAMETER(lLoginID);
    USER_UNREFERENCED_PARAMETER(dwBufLen);
    USER_UNREFERENCED_PARAMETER(dwUser);
    if (eType == E_SDK_ALARM_TYPE_PUSH) {
        sPushData *pInfo = (sPushData *) pBuf;
//        SaveFile(pInfo->pBuffer, pInfo->nLenSize);
        std::cout << "face pic recived, type: " << pInfo->eType << " picture ai attr: " << pInfo->pszAIDataAttr
                  << std::endl;
    } else if (eType == E_SDK_ALARM_TYPE_ALARM) {
        sAlarmInfo info;
        memcpy(&info, pBuf, sizeof(sAlarmInfo));
        std::cout << "Alarm upload action:" << info.action << " event:" << info.event << " channel:" << info.nChannel
                  << " time:"
                  << info.time.year << info.time.month << info.time.day << "_" << info.time.hour << info.time.minute
                  << info.time.second << endl;
    } else if (eType == E_SDK_ALARM_TYPE_UPLOAD_INFO) {
        sUploadInfo *info = (sUploadInfo *) pBuf;
        std::cout << "upload info type:" << info->type;
        if (info->type == E_TYPE_PERSON_COUNT) {
            std::cout << " Person Count:" << info->nPersonCount << endl;
        } else if (info->type == E_TYPE_WIFI_SIGNAL) {
            std::cout << " Wifi Signal:" << info->nWifiSignal << endl;
        } else if (info->type == E_TYPE_COMPANY) {
            std::cout << " Company name:" << info->szCompanyName << endl;
        } else if (info->type == E_TYPE_PLACE) {
            std::cout << " Local place:" << info->szLocation << endl;
        } else if (info->type == E_TYPE_TIME_ZONE) {
            std::cout << " Time zone:" << info->nMinutesWest << endl;
        } else if (info->type == E_TYPE_CLOSE_ALGORITHM) {
            std::cout << " is close algorithm:" << info->bCloseAlgorithm << endl;
        } else if (info->type == E_TYPE_SCREENSAVER) {
            std::cout << " Screensaver:" << info->bScreensaver << endl;
        } else if (info->type == E_TYPE_WWAN_SIGNAL) {
            std::cout << " Wwan Signal:" << info->nWwanSignal << endl;
        } else if (info->type == E_TYPE_WIRED_NETWORK) {
            std::cout << " wired network:" << info->wiredNetwork << endl;
        } else if (info->type == E_TYPE_CONFIG_CHANGED) {
            std::cout << " config change:" << info->cfgType << endl;
        } else if (info->type == E_TYPE_WIFI_CONN_STATUS) {
            std::cout << "E_TYPE_WIFI_CONN_STATUS config change:" << info->wifiStatus << endl;
        } else if (info->type == E_TYPE_IMPORT_FAIL_COUNT) {
            std::cout << "import fail count:" << info->nImportFailCount << endl;
        } else if (info->type == E_TYPE_INTERNET) {
            std::cout << "internet  change:" << info->bInternet << endl;
        } else if (info->type == E_TYPE_STATE_CLOUD) {
            std::cout << "cloud config change:" << info->bCloudLinked << endl;
        } else if (info->type == E_TYPE_IS_UPGRADING) {
            std::cout << "Upgrading change:" << info->bUpgrading << endl;
        } else {
            std::cout << " type error!!!" << endl;
        }
    } else if (eType == E_SDK_ALARM_TYPE_PASSED_EVENT_INFO) {
        sDoorCtrlEventInfo *info = (sDoorCtrlEventInfo *) pBuf;
        //memcpy(&info, pBuf, sizeof(sPassedEventLog));
        std::cout << "event info type:" << info->tip << " pass type:" << info->log.szPassType << " type:"
                  << info->log.passType
                  << " vertify type:" << info->log.verType << " person name:" << info->log.personInfo.szPersonName
                  << endl;
    } else if (eType == E_SDK_ALARM_TYPE_INTERACTIVE_D2G) {
        sDoorInteractiveD2G *info = (sDoorInteractiveD2G *) pBuf;
        std::cout << "D2G info type:" << info->type;
        if (info->type == E_INTERACTIVE_D2G_SNAP_FACE) {
            sInteractiveSnapFace &face = info->snap;
            std::cout << " upload face ret:" << face.ret
                      << " face len:" << face.nFaceLen
                      << " Feature len:" << face.nFeatureLen << endl;
            if (!g_pszFeatureData) {
                g_pszFeatureData = new char[1024 * 1024]{};
            }
            memcpy(g_pszFeatureData, face.pszFacePicture, face.nFaceLen);
            g_nFeatureLen = face.nFaceLen;
        } else if (info->type == E_INTERACTIVE_D2G_CARD) {
            sInteractiveCardNumber &card = info->card;
            std::cout << " upload Card number:" << card.szCardNo << endl;
        } else if (info->type == E_INTERACTIVE_D2G_PROGRESS) {
            sInteractiveImExportProgress &pro = info->progress;
            std::cout << "\r";
            std::cout << "D2G info type:" << info->type;
            std::cout << " ImExport Progress:" << pro.nProgress << "\t" << flush;
        } else if (info->type == E_INTERACTIVE_D2G_WEIXIN_QRCODE_DATA) {
            sWXQRCodeDataRsp &Rsp = info->qrcode_wx;
            std::cout << "\r";
            std::cout << "QRCode type:" << Rsp.eQRCodeType;
            std::cout << " QRCode szData:" << Rsp.szData << endl;
        } else if (info->type == E_INTERACTIVE_D2G_WEIXIN_INPUT_FACE_DATE) {
            sWXInputFaceDataRsp &pro = info->face_wx;
            std::cout << "\r";
            std::cout << "pro.szOperId:" << pro.szOperId;
            std::cout << "pro.szUuid:" << pro.szUuid;
            std::cout << "pro.type:" << pro.type << endl;
        } else if (info->type == E_INTERACTIVE_D2G_RESULT) {
            sInteractiveImExportResult &ret = info->imExResult;
            std::cout << " ImExport ret:" << ret.ret << " Success:" << ret.nSuccess << " Failure:" << ret.nFailure
                      << endl;
        } else if (info->type == E_INTERACTIVE_D2G_PS_CLOUD_FIRMWARE_RESULT) {
            sPsCloudFirmwareResultRsp &firm = info->firmware;
            std::cout << " firmware is new:" << firm.bNew << " Firmware Info:" << firm.szFirmwareInfo << " uuid:"
                      << firm.szUuid << endl;
        } else if (info->type == E_INTERACTIVE_D2G_PS_CLOUD_UPGRADE_STATE) {
            sPsCloudUpgradeStateRsp &state = info->state;
            std::cout << endl;
            std::cout << "D2G info type:" << info->type;
            std::cout << " upgrade state:" << state.state << " progress:" << state.nProgress << endl;
        } else if (info->type == E_INTERACTIVE_D2G_DM_SNAP_FACEFEATURE) {
            sDmyUploadFaceFeature &dmFeature = info->dmFeature;
            std::cout << " dm snap face feature len: " << dmFeature.nFeatureLen << endl;
            if (!g_pszFeatureData) {
                g_pszFeatureData = new char[1024 * 1024]{};
            }
            memcpy(g_pszFeatureData, dmFeature.pszFeature, dmFeature.nFeatureLen);
            //std::cout << Base64Encode((uchar*)dmFeature.pszFeature, dmFeature.nFeatureLen) << endl;
            g_nFeatureLen = dmFeature.nFeatureLen;
        } else {
            std::cout << endl;
        }
    } else if (eType == E_SDK_ALARM_TYPE_INTERACTIVE_D2C) {
        sDeviceToCloudReq *req = (sDeviceToCloudReq *) pBuf;
        switch (req->type) {
            case E_D2C_ACTION_DATA_CHANGED:
                for (int i = 0; i < req->log.nCount; i++) {
                    std::cout << "changed info type:" << req->log.rt[i].type << " changed Id:" << req->log.rt[i].id.nId
                              << " changed timestamp:" << req->log.rt[i].nTimeStamp << endl;
                }
                break;
            case E_D2C_ACTION_CONFIG_CHANGED:
                std::cout << "config changed id : " << req->changed.cfgType << endl;
                break;
            case E_D2C_ACTION_PS_START_CLOUD_TEST:
                std::cout << "ps cloud test address : " << req->test.addr.szIp << " timeout : " << req->test.nTimeout
                          << "  uuid: " << req->test.szUuid << endl;
                break;
            case E_D2C_ACTION_PS_STOP_CLOUD_TEST:
                std::cout << "ps cloud test stop" << endl;
                break;
            case E_D2C_ACTION_PS_CHECK_CLOUD_FIRMWARE:
                std::cout << "ps cloud check firmware, uuid:" << req->firm.szUuid << " timeout:" << req->firm.nTimeout
                          << endl;
                break;
            default:
                break;
        }
    } else if (eType == E_SDK_ALARM_TYPE_FR_EVENT_INFO) {
        sFaceRecognitionEvent *info = (sFaceRecognitionEvent *) pBuf;
        std::cout << " vertify type:" << info->log.eventType << " person name:" << info->log.personInfo.szPersonName
                  << endl;
//        SaveFile(info->log.pszBgPic, info->log.nBgPicSize);
//        SaveFile(info->log.pszSnapPic, info->log.nSnapPicSize);
//        SaveFile(info->log.personInfo.pszFacePicture, info->log.personInfo.nPicSize);
    } else if (eType == E_SDK_ALARM_TYPE_INTERACTIVE_S2S) {
        sS2SInteractiveReq *info = (sS2SInteractiveReq *) pBuf;
        std::cout << " sender:" << info->szSender << " type:" << info->type << endl;
        if (info->type == E_S2S_INTERACTIVE_SCREEN_TEST) {
            std::cout << "Screen test result:" << info->rsp.result << std::endl;
        }
    } else if (eType == E_SDK_ALARM_TYPE_INTERACTIVE_GPT) {
        sGeneralProduceTestRsp *sGPTInfo = (sGeneralProduceTestRsp *) pBuf;
        std::cout << " TestType:" << sGPTInfo->eTestType << " ResultType:" << sGPTInfo->eTestResultType << endl;
        switch (sGPTInfo->eTestType) {
            case E_GPT_TYPE_ALARM_TAMPER:
            case E_GPT_TYPE_ALARM_DOOR_SENSOR:
            case E_GPT_TYPE_ALARM_FIRE: {
                sGPTAlarmEventRsp sAlarmEvent = sGPTInfo->sAlarmEvent;
                std::cout << " sAlarmEvent.eTestType:" << sAlarmEvent.eTestType << endl;
            }
                break;
            case E_GPT_TYPE_BUTTON: {
                sGPTButtonRsp sButton = sGPTInfo->sButton;
                std::cout << " Button.nType:" << sButton.nType << endl;
            }
                break;
            default:
                break;
        }
    } else if (eType == E_SDK_ALARM_TYPE_CONFIG_OBSERVER) {
        sConfigChangeObserver *pInfo = (sConfigChangeObserver *) pBuf;
        std::cout << "Config changed, cmd Type:" << pInfo->cfgType << endl;
    } else if (eType == E_SDK_ALARM_TYPE_AUDIO_STRENGTH) {
        sAudioStrengthUpload *pInfo = (sAudioStrengthUpload *) pBuf;
        std::cout << "Audio strength: " << pInfo->nAudioStrength << endl;
    } else if (eType == E_SDK_ALARM_TYPE_SERIAL_UPLOAD) {
        sSerialDataUpload *pInfo = (sSerialDataUpload *) pBuf;
        std::cout << "Serial id: " << pInfo->nSerialId << " data: " << pInfo->pszData << " length: " << pInfo->nDataLen
                  << std::endl;
    }
    return true;
}


int Open() {
    F_SDK_Init(DisconnectedCallback, nullptr);
    F_SDK_SetDevMessCallBack(MessCallBack, nullptr);
    sAVPrivateHeadConfig cfg;
    //cfg.bNeedPrivateHead = false;		// 不需要私有头
    F_SDK_SetLocalCfg(eLocalCfgType::E_SDK_LOCAL_CFG_AV_PRIVATEHEAD, &cfg);
    F_SDK_Log(E_LOGGER_LEVEL_INFO, "will print this message");
    sLoggerConfig logCfg{};
    logCfg.level = E_LOGGER_LEVEL_WARN;                        // 等级超过WARN的日志打印,默认等级INFO
    // 开启日志文件存储
    //logCfg.bSaveToFile = true;
    //strcpy_s(logCfg.file.szFilePath, "./logs/log.log");
    //logCfg.file.bCoverage = true;							// 日志循环覆盖
    //logCfg.file.covCfg.nFileMaxSize = 1024 * 1024 * 4;	// 单个日志文件最大4MB
    //logCfg.file.covCfg.nMaxFiles = 3;						// 最多3个日志文件
    F_SDK_SetLocalCfg(E_SDK_LOCAL_CFG_LOGGER, &logCfg);
    F_SDK_Log(E_LOGGER_LEVEL_INFO, "will not print this message");

    //登录
    int error = 0;
    g_loginInfo.encryptType = E_SDK_ENCRYPT_TYPE_MD5;
    g_loginInfo.loginType = E_SDK_LOGIN_TYPE_CONSOLE;
    g_loginInfo.connectType = E_SDK_CONNECT_TYPE_TCP;
    g_loginInfo.nPort = 51666;
    //g_loginInfo.bGb35114 = true;			//GB35114鉴权登录
    strcpy(g_loginInfo.szName, "admin");

    g_lLogin = F_SDK_LocalLogin(&g_devInfo, &error);

    if (g_lLogin > 0) {
        g_bConnect = true;
    } else {
        return -1;
    }

    return 0;
}

int GetDeviceInfo() {

    int count = 64;
    sSearchDeviceConfig *device = new sSearchDeviceConfig[count]{};
    long lRet = F_SDK_SearchDevice(device, &count, 1000);
    std::cout << "Search device ret:" << lRet << "  count: " << count << endl;
    vector_DeviceConfig.clear();
    for (int i = 0; i < count; i++) {
        vector_DeviceConfig.push_back(device[i]);
    }
    delete[] device;

    return 0;
}

string FormatDeviceInfo(vector<sSearchDeviceConfig> vector_deviceConfig) {
    Json::FastWriter fastWriter;
    Json::Value root;

    if (vector_deviceConfig.empty()) {
        root["deviceInfo"].resize(0);
    } else {
        Json::Value arrayDeviceConfig;
        for (auto iter:vector_deviceConfig) {
            Json::Value item;
            item["softWareVersion"] = string(iter.szSoftWareVersion);
            item["hardWareVersion"] = string(iter.szHardWareVersion);
            item["aiVersion"] = string(iter.szAiVersion);
            arrayDeviceConfig.append(item);
        }
        root["deviceInfo"] = arrayDeviceConfig;
    }

    string out = fastWriter.write(root);

    return out;
}

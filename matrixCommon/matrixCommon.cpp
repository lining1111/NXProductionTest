#include "matrixCommon.h"

#include <iostream>
#include <cstring>
#include <map>

uint16_t reverse16(uint16_t value) {
    return __bswap_constant_16(value);
}

uint32_t reverse32(uint32_t value) {
    return __bswap_constant_32(value);
}

uint64_t reverse64(uint64_t value) {
    return __bswap_constant_64(value);
}

uint8_t crcSum(uint8_t *data, uint32_t len) {
    uint8_t sum = 0;


    for (int i = 0; i < len; i++) {
        sum += data[i];
    }

    return sum;
}

int packStructHead(uint8_t *out, uint32_t *len, Head head) {
    int index = 0;
    out[index] = head.start;
    index++;
    out[index] = head.cmd;
    index++;
    out[index] = head.len;
    index++;

    *len += index;
    return 0;
}

int packStructCrc(uint8_t *out, uint32_t *len, Crc crc) {
    int index = 0;
    out[index] = crc.data;
    index++;

    *len += index;
    return 0;
}


int packStructHeart(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Heart *sHeart = (S_Heart *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value16B = reverse16(sHeart->angleRoll);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sHeart->anglePitch);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sHeart->anglePos);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sHeart->temperature);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sHeart->humidity);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sHeart->switchVoltage);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sHeart->alarmStatus);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sHeart->version);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    *len += index;
    return 0;
}

int packStructReq_SetSwitch(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_SetSwitch *sReqSetSwitch = (S_Req_SetSwitch *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sReqSetSwitch->heat1;
    index++;
    out[index] = sReqSetSwitch->heat2;
    index++;
    out[index] = sReqSetSwitch->reboot;
    index++;
    out[index] = sReqSetSwitch->enterBootloader;
    index++;
    out[index] = sReqSetSwitch->resetAngle;
    index++;

    *len += index;
    return 0;
}

int packStructReq_SetFun(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_SetFun *sReqSetFun = (S_Req_SetFun *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sReqSetFun->on;
    index++;

    *len += index;
    return 0;
}

int packStructReq_SetIp(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_SetIp *sReqSetIp = (S_Req_SetIp *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value32B = reverse32(sReqSetIp->ip);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    *len += index;
    return 0;
}

int packStructReq_SetNet(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_SetNet *sReqSetNet = (S_Req_SetNet *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value32B = reverse32(sReqSetNet->gateway);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    value32B = reverse32(sReqSetNet->mask);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    value32B = reverse32(sReqSetNet->ip);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    *len += index;
    return 0;
}

int packStructReq_SetSn(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_SetSn *sReqSetSn = (S_Req_SetSn *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    for (int i = 0; i < ARRAY_SIZE(sReqSetSn->sn); i++) {
        out[index] = sReqSetSn->sn[i];
        index++;
    }

    *len += index;
    return 0;
}

int packStructReq_GetNetSn(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_GetNetSn *sReqGetNetSn = (S_Req_GetNetSn *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sReqGetNetSn->data;
    index++;

    *len += index;
    return 0;
}

int packStructRsp_GetNetSn(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_GetNetSn *sRspGetNetSn = (S_Rsp_GetNetSn *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value32B = reverse32(sRspGetNetSn->gateway);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    value32B = reverse32(sRspGetNetSn->mask);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    value32B = reverse32(sRspGetNetSn->ip);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    for (int i = 0; i < ARRAY_SIZE(sRspGetNetSn->sn); i++) {
        out[index] = sRspGetNetSn->sn[i];
        index++;
    }

    *len += index;
    return 0;
}

int packStructReq_GetNet(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_GetNet *sReqGetNet = (S_Req_GetNet *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sReqGetNet->data;
    index++;

    *len += index;
    return 0;
}

int packStructRsp_GetNet(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_GetNet *sRspGetNet = (S_Rsp_GetNet *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value32B = reverse32(sRspGetNet->gateway);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    value32B = reverse32(sRspGetNet->mask);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    value32B = reverse32(sRspGetNet->ip);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    for (int i = 0; i < ARRAY_SIZE(sRspGetNet->mac); i++) {
        out[index] = sRspGetNet->mac[i];
        index++;
    }

    value32B = reverse32(sRspGetNet->remoteIp);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    *len += index;
    return 0;
}

int packStructReq_SetLightThreshold(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_SetLightThreshold *sReqSetLightThreshold = (S_Req_SetLightThreshold *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value16B = reverse16(sReqSetLightThreshold->thresholdOn);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sReqSetLightThreshold->thresholdOff);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    *len += index;
    return 0;
}

int packStructRsp_SetLightThreshold(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_SetLightThreshold *sRspSetLightThreshold = (S_Rsp_SetLightThreshold *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sRspSetLightThreshold->farBrightness;
    index++;
    out[index] = sRspSetLightThreshold->midBrightness;
    index++;
    out[index] = sRspSetLightThreshold->nearBrightness;
    index++;

    value16B = reverse16(sRspSetLightThreshold->thresholdOn);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sRspSetLightThreshold->thresholdOff);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    out[index] = sRspSetLightThreshold->deviceType;
    index++;

    out[index] = sRspSetLightThreshold->lightStatus;
    index++;

    *len += index;
    return 0;
}

int packStructReq_SetLightOn(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_SetLightOn *sReqSetLightOn = (S_Req_SetLightOn *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sReqSetLightOn->status;
    index++;

    *len += index;
    return 0;
}

int packStructRsp_SetLightOn(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_SetLightOn *sRspSetLightOn = (S_Rsp_SetLightOn *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sRspSetLightOn->status;
    index++;

    *len += index;
    return 0;
}

int packStructReq_SetLightBrightness(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_SetLightBrightness *sReqSetLightBrightness = (S_Req_SetLightBrightness *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sReqSetLightBrightness->farBrightness;
    index++;
    out[index] = sReqSetLightBrightness->midBrightness;
    index++;
    out[index] = sReqSetLightBrightness->nearBrightness;
    index++;

    *len += index;
    return 0;
}

int packStructRsp_SetLightBrightness(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_SetLightBrightness *sRspSetLightBrightness = (S_Rsp_SetLightBrightness *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sRspSetLightBrightness->farBrightness;
    index++;
    out[index] = sRspSetLightBrightness->midBrightness;
    index++;
    out[index] = sRspSetLightBrightness->nearBrightness;
    index++;

    value16B = reverse16(sRspSetLightBrightness->thresholdOn);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sRspSetLightBrightness->thresholdOff);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    out[index] = sRspSetLightBrightness->deviceType;
    index++;

    out[index] = sRspSetLightBrightness->lightStatus;
    index++;

    *len += index;
    return 0;
}

int packStructReq_GetLightPara(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_GetLightPara *sReqGetLightPara = (S_Req_GetLightPara *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sReqGetLightPara->data;
    index++;

    *len += index;
    return 0;
}

int packStructRsp_GetLightPara(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_GetLightPara *sRspGetLightPara = (S_Rsp_GetLightPara *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    out[index] = sRspGetLightPara->farLightBrightness;
    index++;
    out[index] = sRspGetLightPara->farLightOn;
    index++;

    out[index] = sRspGetLightPara->midLightBrightness;
    index++;
    out[index] = sRspGetLightPara->midLightOn;
    index++;

    out[index] = sRspGetLightPara->nearLightBrightness;
    index++;
    out[index] = sRspGetLightPara->nearLightOn;
    index++;

    out[index] = sRspGetLightPara->deviceType;
    index++;

    value16B = reverse16(sRspGetLightPara->thresholdOn);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    value16B = reverse16(sRspGetLightPara->thresholdOff);
    memcpy(out + index, &value16B, sizeof(value16B));
    index += sizeof(value16B);

    *len += index;
    return 0;
}

int packStructReq_UpdateDataSize(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_UpdateDataSize *sReqUpdateDataSize = (S_Req_UpdateDataSize *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value32B = reverse32(sReqUpdateDataSize->totalLen);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    *len += index;
    return 0;
}

int packStructRsp_UpdateDataSize(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_UpdateDataSize *sRspUpdateDataSize = (S_Rsp_UpdateDataSize *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value32B = reverse32(sRspUpdateDataSize->totalLen);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    *len += index;
    return 0;
}

int packStructReq_UpdateData(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Req_UpdateData *sReqUpdateData = (S_Req_UpdateData *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;
    for (auto iter:sReqUpdateData->data) {
        out[index] = iter;
        index++;
    }

    *len += index;
    return 0;
}

int packStructRsp_UpdateData(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_UpdateData *sRspUpdateData = (S_Rsp_UpdateData *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value32B = reverse32(sRspUpdateData->eachLen);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    *len += index;
    return 0;
}


int packStructRsp_UpdateStatus(uint8_t *out, uint32_t *len, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    if (sIn == nullptr) {
        return -1;
    }
    S_Rsp_UpdateStatus *sRspUpdateStatus = (S_Rsp_UpdateStatus *) sIn;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    value32B = reverse32(sRspUpdateStatus->status);
    memcpy(out + index, &value32B, sizeof(value32B));
    index += sizeof(value32B);

    *len += index;
    return 0;
}

int packSendUpdate(uint8_t *out, uint32_t *len) {
    *out = Req_UpdateStart;
    *len++;
    return 0;
}

bool unpackIsCanUpdate(uint8_t *in, uint32_t len) {
    if (in == nullptr || len < 2) {
        return false;
    }
    std::string str;
    str.clear();

    for (int i = 0; i < len; i++) {
        str.append(1, (char) in[i]);
    }

    if (str.find_first_of("##") != std::string::npos) {
        return true;
    }

    return false;
}

int unpackSawHead(Head *head, uint8_t *in, uint32_t len) {
    if (head == nullptr || in == nullptr || len < sizeof(Head)) {
        return -1;
    }

    int index = 0;
    head->start = in[index];
    index++;
    head->cmd = in[index];
    index++;
    head->len = in[index];
    index++;

    return 0;
}

int unpackSawCrc(Crc *crc, uint8_t *in, uint32_t len) {
    if (crc == nullptr || in == nullptr || len < sizeof(Head)) {
        return -1;
    }

    int index = 0;
    crc->data = in[index];
    index++;
    return 0;
}


int unpackSawHeart(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Heart *sHeart = (S_Heart *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sHeart->angleRoll = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sHeart->anglePitch = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sHeart->anglePos = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sHeart->temperature = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sHeart->humidity = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sHeart->switchVoltage = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sHeart->alarmStatus = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sHeart->version = reverse16(value16B);

    return 0;
}

int unpackSawReq_SetSwitch(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_SetSwitch *sReqSetSwitch = (S_Req_SetSwitch *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sReqSetSwitch->heat1 = in[index];
    index++;

    sReqSetSwitch->heat2 = in[index];
    index++;

    sReqSetSwitch->reboot = in[index];
    index++;

    sReqSetSwitch->enterBootloader = in[index];
    index++;

    sReqSetSwitch->resetAngle = in[index];
    index++;

    return 0;
}

int unpackSawReq_SetFun(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_SetFun *sReqSetFun = (S_Req_SetFun *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sReqSetFun->on = in[index];
    index++;

    return 0;
}

int unpackSawReq_SetIp(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_SetIp *sReqSetIp = (S_Req_SetIp *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sReqSetIp->ip = reverse32(value32B);

    return 0;
}

int unpackSawReq_SetNet(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_SetNet *sReqSetNet = (S_Req_SetNet *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sReqSetNet->gateway = reverse32(value32B);

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sReqSetNet->mask = reverse32(value32B);

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sReqSetNet->ip = reverse32(value32B);

    return 0;
}

int unpackSawReq_SetSn(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_SetSn *sReqSetSn = (S_Req_SetSn *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    for (int i = 0; i < ARRAY_SIZE(sReqSetSn->sn); i++) {
        sReqSetSn->sn[i] = in[index];
        index++;
    }

    return 0;
}

int unpackSawReq_GetNetSn(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_GetNetSn *sReqGetNetSn = (S_Req_GetNetSn *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sReqGetNetSn->data = in[index];
    index++;

    return 0;
}

int unpackSawRsp_GetNetSn(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_GetNetSn *sRspGetNetSn = (S_Rsp_GetNetSn *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspGetNetSn->gateway = reverse32(value32B);

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspGetNetSn->mask = reverse32(value32B);

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspGetNetSn->ip = reverse32(value32B);

    for (int i = 0; i < ARRAY_SIZE(sRspGetNetSn->sn); i++) {
        sRspGetNetSn->sn[i] = in[index];
        index++;
    }

    return 0;
}

int unpackSawReq_GetNet(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_GetNet *sReqGetNet = (S_Req_GetNet *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sReqGetNet->data = in[index];
    index++;

    return 0;
}

int unpackSawRsp_GetNet(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_GetNet *sRspGetNet = (S_Rsp_GetNet *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspGetNet->gateway = reverse32(value32B);

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspGetNet->mask = reverse32(value32B);

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspGetNet->ip = reverse32(value32B);

    for (int i = 0; i < ARRAY_SIZE(sRspGetNet->mac); i++) {
        sRspGetNet->mac[i] = in[index];
        index++;
    }

    return 0;
}

int unpackSawReq_SetLightThreshold(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_SetLightThreshold *sReqSetLightThreshold = (S_Req_SetLightThreshold *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sReqSetLightThreshold->thresholdOn = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sReqSetLightThreshold->thresholdOff = reverse16(value16B);

    return 0;
}

int unpackSawRsp_SetLightThreshold(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_SetLightThreshold *sRspSetLightThreshold = (S_Rsp_SetLightThreshold *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sRspSetLightThreshold->farBrightness = in[index];
    index++;
    sRspSetLightThreshold->midBrightness = in[index];
    index++;
    sRspSetLightThreshold->nearBrightness = in[index];
    index++;

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sRspSetLightThreshold->thresholdOn = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sRspSetLightThreshold->thresholdOff = reverse16(value16B);

    sRspSetLightThreshold->deviceType = in[index];
    index++;

    sRspSetLightThreshold->lightStatus = in[index];
    index++;

    return 0;
}

int unpackSawReq_SetLightOn(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_SetLightOn *sReqSetLightOn = (S_Req_SetLightOn *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sReqSetLightOn->status = in[index];
    index++;

    return 0;
}

int unpackSawRsp_SetLightOn(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_SetLightOn *sRspSetLightOn = (S_Rsp_SetLightOn *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sRspSetLightOn->status = in[index];
    index++;

    return 0;
}

int unpackSawReq_SetLightBrightness(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_SetLightBrightness *sReqSetLightBrightness = (S_Req_SetLightBrightness *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sReqSetLightBrightness->farBrightness = in[index];
    index++;
    sReqSetLightBrightness->midBrightness = in[index];
    index++;
    sReqSetLightBrightness->nearBrightness = in[index];
    index++;

    return 0;
}

int unpackSawRsp_SetLightBrightness(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_SetLightBrightness *sRspSetLightBrightness = (S_Rsp_SetLightBrightness *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sRspSetLightBrightness->farBrightness = in[index];
    index++;
    sRspSetLightBrightness->midBrightness = in[index];
    index++;
    sRspSetLightBrightness->nearBrightness = in[index];
    index++;

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sRspSetLightBrightness->thresholdOn = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sRspSetLightBrightness->thresholdOff = reverse16(value16B);

    sRspSetLightBrightness->deviceType = in[index];
    index++;

    sRspSetLightBrightness->lightStatus = in[index];
    index++;

    return 0;
}

int unpackSawReq_GetLightPara(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_GetLightPara *sReqGetLightPara = (S_Req_GetLightPara *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sReqGetLightPara->data = in[index];
    index++;

    return 0;
}

int unpackSawRsp_GetLightPara(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_GetLightPara *sRspGetLightPara = (S_Rsp_GetLightPara *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    sRspGetLightPara->farLightBrightness = in[index];
    index++;
    sRspGetLightPara->farLightOn = in[index];
    index++;
    sRspGetLightPara->midLightBrightness = in[index];
    index++;
    sRspGetLightPara->midLightOn = in[index];
    index++;
    sRspGetLightPara->nearLightBrightness = in[index];
    index++;
    sRspGetLightPara->nearLightOn = in[index];
    index++;
    sRspGetLightPara->deviceType = in[index];
    index++;

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sRspGetLightPara->thresholdOn = reverse16(value16B);

    memcpy(&value16B, in + index, sizeof(value16B));
    index += sizeof(value16B);
    sRspGetLightPara->thresholdOff = reverse16(value16B);

    return 0;
}

int unpackSawReq_UpdateDataSize(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_UpdateDataSize *sReqUpdateDataSize = (S_Req_UpdateDataSize *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sReqUpdateDataSize->totalLen = reverse32(value32B);

    return 0;
}

int unpackSawRsp_UpdateDataSize(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_UpdateDataSize *sRspUpdateDataSize = (S_Rsp_UpdateDataSize *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspUpdateDataSize->totalLen = reverse32(value32B);

    return 0;
}

int unpackSawReq_UpdateData(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Req_UpdateData *sReqUpdateData = (S_Req_UpdateData *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    for (int i = 0; i < len; i++) {
        sReqUpdateData->data.push_back(in[index]);
        index++;
    }

    return 0;
}

int unpackSawRsp_UpdateData(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_UpdateData *sRspUpdateData = (S_Rsp_UpdateData *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspUpdateData->eachLen = reverse32(value32B);

    return 0;
}

int unpackSawRsp_UpdateStatus(void *sOut, uint8_t *in, uint32_t len) {
    if (sOut == nullptr || in == nullptr) {
        return -1;
    }
    S_Rsp_UpdateStatus *sRspUpdateStatus = (S_Rsp_UpdateStatus *) sOut;
    uint32_t value32B;//大端字节
    uint16_t value16B;//大端字节
    uint64_t value64B;//大端字节

    int index = 0;

    memcpy(&value32B, in + index, sizeof(value32B));
    index += sizeof(value32B);
    sRspUpdateStatus->status = reverse32(value32B);

    return 0;
}


std::map<Cmd, packStruct> mapPack{
        {Heart,                  packStructHeart},
        {Req_SetSwitch,          packStructReq_SetSwitch},
        {Req_SetFun,             packStructReq_SetFun},
        {Req_SetIp,              packStructReq_SetIp},
        {Req_SetNet,             packStructReq_SetNet},
        {Req_SetSn,              packStructReq_SetSn},
        {Req_GetNetSn,           packStructReq_GetNetSn},
        {Rsp_GetNetSn,           packStructRsp_GetNetSn},
        {Req_GetNet,             packStructReq_GetNet},
        {Rsp_GetNet,             packStructRsp_GetNet},
        {Req_SetLightThreshold,  packStructReq_SetLightThreshold},
        {Rsp_SetLightThreshold,  packStructRsp_SetLightThreshold},
        {Req_SetLightOn,         packStructReq_SetLightOn},
        {Rsp_SetLightOn,         packStructRsp_SetLightOn},
        {Req_SetLightBrightness, packStructReq_SetLightBrightness},
        {Rsp_SetLightBrightness, packStructRsp_SetLightBrightness},
        {Req_GetLightPara,       packStructReq_GetLightPara},
        {Rsp_GetLightPara,       packStructRsp_GetLightPara},
        {Req_UpdateDataSize,     packStructReq_UpdateDataSize},
        {Rsp_UpdateDataSize,     packStructRsp_UpdateDataSize},
        {Req_UpdateData,         packStructReq_UpdateData},
        {Rsp_UpdateData,         packStructRsp_UpdateData},
        {Rsp_UpdateStatus,       packStructRsp_UpdateStatus},
        {Heart,                  packStructHeart},
        {Heart,                  packStructHeart},
        {Heart,                  packStructHeart},
        {Heart,                  packStructHeart},
        {Heart,                  packStructHeart},
};

std::map<Cmd, unpackSaw> mapUnpack{
        {Heart,                  unpackSawHeart},
        {Req_SetSwitch,          unpackSawReq_SetSwitch},
        {Req_SetFun,             unpackSawReq_SetFun},
        {Req_SetIp,              unpackSawReq_SetIp},
        {Req_SetNet,             unpackSawReq_SetNet},
        {Req_SetSn,              unpackSawReq_SetSn},
        {Req_GetNetSn,           unpackSawReq_GetNetSn},
        {Rsp_GetNetSn,           unpackSawRsp_GetNetSn},
        {Req_GetNet,             unpackSawReq_GetNet},
        {Rsp_GetNet,             unpackSawRsp_GetNet},
        {Req_SetLightThreshold,  unpackSawReq_SetLightThreshold},
        {Rsp_SetLightThreshold,  unpackSawRsp_SetLightThreshold},
        {Req_SetLightOn,         unpackSawReq_SetLightOn},
        {Rsp_SetLightOn,         unpackSawRsp_SetLightOn},
        {Req_SetLightBrightness, unpackSawReq_SetLightBrightness},
        {Rsp_SetLightBrightness, unpackSawRsp_SetLightBrightness},
        {Req_GetLightPara,       unpackSawReq_GetLightPara},
        {Rsp_GetLightPara,       unpackSawRsp_GetLightPara},
        {Req_UpdateDataSize,     unpackSawReq_UpdateDataSize},
        {Rsp_UpdateDataSize,     unpackSawRsp_UpdateDataSize},
        {Req_UpdateData,         unpackSawReq_UpdateData},
        {Rsp_UpdateData,         unpackSawRsp_UpdateData},
        {Rsp_UpdateStatus,       unpackSawRsp_UpdateStatus},
};


int Pack(uint8_t *out, uint32_t *len, enum Cmd cmd, void *sIn) {
    if (out == nullptr || len == nullptr) {
        return -1;
    }
    int ret = 0;

    uint32_t index = 0;
    //1.组头
    Head head;
    head.cmd = cmd;
    packStructHead(out, &index, head);

    //2.组内容
    //按照命令类型进行不同的组包
    auto iter = mapPack.find(cmd);

    if (iter != mapPack.end()) {
        //find
        ret = iter->second(out + index, &index, sIn);
    } else {
        printf("cmd:%d not find\n", cmd);
        ret = -1;
    }
    //设置长度
    out[OFFSET(Head, len)] = (index - sizeof(Head));
    //组验证
    Crc crc;
    crc.data = crcSum(out, index);
    packStructCrc(out + index, &index, crc);


    *len = index;

    return ret;
}

int Unpack(void *sOut, enum Cmd *cmd, uint8_t *in, uint32_t len) {
    if (in == nullptr || len == 0) {
        return -1;
    }
    int ret = 0;

    int index = 0;
    //寻找cmd类型
    Head head;
    unpackSawHead(&head, in, len);
    index += sizeof(head);

    *cmd = (Cmd) head.cmd;

    //按照命令类型进行不同的组包
    auto iter = mapUnpack.find(*cmd);

    if (iter != mapUnpack.end()) {
        //find
        ret = iter->second(sOut, (in + index), (len - index));
    } else {
        printf("cmd:%d not find\n", *cmd);
        ret = -1;
    }
    //得到校验
    Crc crc;
    unpackSawCrc(&crc, (in + index), (len - index));
    index += sizeof(crc);

    return ret;
}

//
// Created by lining on 5/17/22.
//

#ifndef _CAMERALIB_H
#define _CAMERALIB_H

#include "NetSdk.h"
#include <vector>
#include <string>
using namespace std;

#define USER_UNREFERENCED_PARAMETER(P) { (P) = (P); }

extern vector<sSearchDeviceConfig> vector_DeviceConfig;

std::string FormatCurrDatetime();

void SaveFile(void *pData, int nSize, char *pszPath = nullptr);

void DisconnectedCallback(long lLogin, char *pszIp, long lPort, puint dwUser);

bool MessCallBack(long lLoginID, char *pBuf, unsigned long dwBufLen, puint dwUser, eAlarmType eType);


int Open();

int GetDeviceInfo();

string FormatDeviceInfo(vector<sSearchDeviceConfig> vector_deviceConfig);

#endif //_CAMERALIB_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This library is part of CL NUI SDK
// It allows the use of Microsoft Kinect cameras in your own applications
//
// For updates and file downloads go to: http://codelaboratories.com/get/kinect
//
// Copyright 2010 (c) Code Laboratories, Inc.  All rights reserved.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <windows.h>

 extern "C" {




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NUIDevice  API
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Device enumeration
__declspec(dllimport) int __cdecl GetNUIDeviceCount();
__declspec(dllimport) PCHAR __cdecl GetNUIDeviceSerial(int index);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLNUIMotor  API
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Motor instance type
typedef void *CLNUIMotor;

// Library initialization
__declspec(dllimport) CLNUIMotor __cdecl CreateNUIMotor(PCHAR serial);
__declspec(dllimport) bool __cdecl DestroyNUIMotor(CLNUIMotor mot);

// Motor control
__declspec(dllimport) bool __cdecl SetNUIMotorPosition(CLNUIMotor mot, SHORT position);

// Get accelerometer data
__declspec(dllimport) bool __cdecl GetNUIMotorAccelerometer(CLNUIMotor mot, SHORT &x, SHORT &y, SHORT &z);

__declspec(dllimport) bool __cdecl SetNUIMotorLED(CLNUIMotor mot, BYTE value);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLNUICamera API
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera instance type
typedef void *CLNUICamera;

// Library initialization
__declspec(dllimport) CLNUICamera __cdecl CreateNUICamera(PCHAR serial);
__declspec(dllimport) bool __cdecl DestroyNUICamera(CLNUICamera cam);

// Camera capture control
__declspec(dllimport) bool __cdecl StartNUICamera(CLNUICamera cam);
__declspec(dllimport) bool __cdecl StopNUICamera(CLNUICamera cam);

// Camera video frame image data retrieval
__declspec(dllimport) bool __cdecl GetNUICameraColorFrameRAW(CLNUICamera cam, PBYTE pData, int waitTimeout = 2000);
__declspec(dllimport) bool __cdecl GetNUICameraColorFrameRGB24(CLNUICamera cam, PBYTE pData, int waitTimeout = 2000);
__declspec(dllimport) bool __cdecl GetNUICameraColorFrameRGB32(CLNUICamera cam, PDWORD pData, int waitTimeout = 2000);

// Camera depth frame image data retrieval
__declspec(dllimport) bool __cdecl GetNUICameraDepthFrameRAW(CLNUICamera cam, PUSHORT pData, int waitTimeout = 2000);
__declspec(dllimport) bool __cdecl GetNUICameraDepthFrameCorrected12(CLNUICamera cam, PUSHORT pData, int waitTimeout = 2000);
__declspec(dllimport) bool __cdecl GetNUICameraDepthFrameCorrected8(CLNUICamera cam, PBYTE pData, int waitTimeout = 2000);
__declspec(dllimport) bool __cdecl GetNUICameraDepthFrameRGB32(CLNUICamera cam, PDWORD pData, int waitTimeout = 2000);
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

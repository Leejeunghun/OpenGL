/****************************************************************************/
/*																			*/
/* @file	CubeEyeDef.h													*/
/*																			*/
/* @brief	Define & Type Header file for CubeEye Camera					*/
/*                                                                          */
/* @date    Jan 19, 2021                                                    */
/*                                                                          */
/* Copyright(c) Meerecompany, Inc.											*/
/*																			*/
/****************************************************************************/

//#pragma once
#ifndef _CUBEEYEDEF_H_
#define _CUBEEYEDEF_H_

#ifndef Linux
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define CRTDBG_MAP_ALLOC
#include "targetver.h"
#include <windows.h>
#include <strmif.h>
#include <crtdbg.h>
#include <conio.h>
#include <uuids.h>
#include <Windows.h>
#include <dshow.h>
#include <chrono>
#include <strsafe.h>
#include <omp.h>
#endif

#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <time.h>
#include <bitset>
#include <string.h>
#include <fstream>
#include <cerrno>
#include <stdio.h>
#include <vector>
#include <list>


//#ifdef PTF_SDK
#define STRING2 string
//#else
//#define STRING2 System::String^
//#endif

#define LENS_FX 0
#define LENS_CX 2
#define LENS_FY 4
#define LENS_CY 5

#define LENS_K1 0
#define LENS_K2 1
#define LENS_K3 2
#define LENS_P1 3
#define LENS_P2 4

#define LENS_R11 0
#define LENS_R12 1
#define LENS_R13 2
#define LENS_TX  3
#define LENS_R21 4
#define LENS_R22 5
#define LENS_R23 6
#define LENS_TY  7
#define LENS_R31 8
#define LENS_R32 9
#define LENS_R33 10
#define LENS_TZ  11

#define MR1000_PRODUCT_ID 0x08776U				//Cube Eye Camera PID
//#define MR1000_PRODUCT_ID 0x08776U				//Cube Eye Camera PID

#ifndef Linux

#ifdef CUBEEYE_EXPORTS
#define CUBEEYE_EXPORT __declspec(dllexport) 
#else
#define CUBEEYE_EXPORT __declspec(dllimport) 
#endif

#else

#ifdef QTapp 
#include <QtCore/qglobal.h>
#endif
#ifdef CUBEEYE_TOF_LIBRARY
#  define CUBEEYE_TOFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CUBEEYE_TOFSHARED_EXPORT Q_DECL_IMPORT
#endif
#endif

///Output Data Fromat
enum data_format {
	///x,y,z,i output mode(frame size = W:1922 x H:800 x 2byte) - default
	Format_XYZI = 0,
	///z,i output mode(frame size = W:1922 x H:400 x 2byte)
	Format_ZI = 1,
	///z output mode(frame size = W:1922 x H:200 x 2byte)
	Format_Z = 2,
};

///Depth Output Mode
enum depth_mode {
	///raw depth(uint:mm)
	DEPTH_IR,
	///z data(unit:m)
	POINT_CLOUD,
	///not support
	RAW_PHASE,
	///not support
	RAW_DATA,
};

///IR Output Mode
enum ir_mode {
	///amplitude data
	AMPLITUDE,
	///intensity data
	INTENSITY,
};

///Operation Mode - To stream start the camera, it is possible in retention mode.
enum operation_mode {
	///Sleep Mode(Default at power on)
	Mode_Sleep = 2,
	///Retention Mode(initial value when calling 'Connect' function in SDK)
	Mode_Retention = 1,
	///Active Mode(illumination on status)
	Mode_Active = 0,
};

///Frame Rate Control
enum  {
	///30 fps(default)
	FPS_30 = 30,
	///15 fps
	FPS_15 = 15,
	///7.5 fps
	FPS_8 = 8,
};

///Error Code
typedef enum _ceError
{
	CE_QUEQUED = 2,
	CE_WARNING = 1,
	CE_SUCCESS = 0,
	CE_FAILED = -1,
	CE_NOT_FOUND = -2,
	CE_OPEN_FAILED = -3,
	CE_GETFRAME_FAILED = -4,
	CE_WRITE_FAILED = -5,
	CE_READ_FAILED = -6,
	CE_UNSUPPORTED = -7,
	CE_OUTOFRANGE = -8,
	CE_NOT_OPENED = -9,
	CE_INVALID_PARAM = -10,
	CE_CONFIG_LOADING_FAILED = -11
} ceError;

#ifdef _WIN32
typedef uint32_t uint;
#endif

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using List = std::list<T>;

typedef uint8_t ByteType;

/* define unsigned integer types */
typedef char int8;
typedef short int16;
typedef int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef uint64_t TimeStampType;

///Device Path
typedef struct _ceDevicePath
{
	///Device Nummber
	unsigned char szDevNum;
	///Product Name
	char szProductName[16];
	///Device Path
	char szDevPath[256];
	///Format-1(X,Y,Z,A mode - defulat), 2(Z,A mode), 3(Z mode)
	uint8 data_format;

} ceDevicePath;

///Device Infomation
typedef struct _ceDeviceInfo
{
	///Vendor Name
	char szVendorName[16];
	///Device Name
	char szDevName[16];
	///Product Name
	char szProductName[8];
	///Sereial Number
	char szSerialNumber[16];
	///Firmware Version
	uint8 unFWVersion[5];
	///Vendor ID
	unsigned short nVendorId;
	///Product ID
	unsigned short nProductId;
	///Device Type(0:Only Depth, 1:Depth+RGB)
	unsigned short nDeviceType;
	///Device Framae Width
	unsigned short nWidth;
	///Device Frmae Height
	unsigned short nHeight;

} ceDeviceInfo;


///PointCloud XYZ Coordinates
typedef struct _cePointCloud
{
	///X Coordinates (unit: m)
	float fX;
	///Y Coordinates (unit: m)
	float fY;
	///Z Coordinates (unit: m)
	float fZ;
	///Intensity value
	float fI;

} cePointCloud;

///Frame Infomation
typedef struct _ceFrameInfo
{
	///0:DEPTH_IR, 1:PCL, 2:RGB Color
	int nFrameType;
	///Image Width
	int nWidth;
	///Image Height
	int nHeight;
	///Frmae ID
	long nFrameID;
	///Frame Timestamp
	TimeStampType nTimeStamp;
	///Sensor Temperature(ºC)
	float fSensorTemp;
	///LD Temperature(ºC)
	float fLDTemp;
	///Integration Time(ms)
	float fIntegrationTime;
	///Embedded Line Information
	uint8 nEmbeddedLine[80];

} ceFrameInfo;

///Camera Distortion Prameters
typedef struct _ceDistortionParam
{
	///coeff. K1
	float fK1;
	///coeff. K2
	float fK2;
	///coeff. K3
	float fK3;
	///coeff. P1
	float fP1;
	///coeff. P2
	float fP2;
	///coeff. skew
	float fSkew;

} ceDistortionParam;

///Camera Intrinsic Prameters
typedef struct _ceIntrinsicParam
{
	///Focal Length X
	float fFx;
	///Focal Length Y
	float fFy;
	///Principal Point X
	float fCx;
	///Principal Point Y
	float fCy;

} ceIntrinsicParam;

///Depth - Color Camera Extrinsic Prameters
typedef struct _ceExtrinsicParam
{
	///Rotation Parameter 1-1
	float fR11;
	///Rotation Parameter 1-2
	float fR12;
	///Rotation Parameter 1-3
	float fR13;
	///Rotation Parameter 2-1
	float fR21;
	///Rotation Parameter 2-2
	float fR22;
	///Rotation Parameter 2-3
	float fR23;
	///Rotation Parameter 3-1
	float fR31;
	///Rotation Parameter 3-2
	float fR32;
	///Rotation Parameter 3-3
	float fR33;
	///Translation X Parameter
	float fTx;
	///Translation Y Parameter
	float fTy;
	///Translation Z Parameter
	float fTz;

} ceExtrinsicParam;

class Point
{
public:
	float x, y, z;

	Point() : x(0), y(0), z(0) {}
	Point(float x, float y) : x(x), y(y), z(0) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
};


#endif

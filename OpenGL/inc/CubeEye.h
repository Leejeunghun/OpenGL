/**

*@mainpage			Meerecompany CubeEye SDK Introduction
*@section intro		Introduce
					- DLL's default header file. CubeEye ToF Camera SDK(Windows Standard DLL Version)
*@section Program	File name
					- CubeEye.h
*@section Version	Version
					- 1.0.0 beta
*@section ModifyInfo
					- author : Support@cube-eye.co.kr
					- date : Jan 19, 2021
@section Common
					- Copyright(c) Meerecompany, 2019 All rights reserved.
*
*/

#pragma once
#include"CubeEyeDef.h"


namespace CUBE_EYE
{
/**
*
*@CUBE_EYE
*@brief Meerecompany CubeEye SDK function description
*@details CUBE_EYE SDK provides a programatic interface to the CubeEye camera.
Through its set of APIs the camera can be configured and Depth/IR and Point Cloud images
are returned with various levels of processing performed.
*
*/

//#ifndef Linux
class CUBEEYE_EXPORT CCubeEye {
	//#else
	//#ifdef QTApp
	//class CUBEEYE_SHARED_EXPORT CCUBEEYE {
	//#else
	//class CCUBEEYE {
	//#endif

private:
	class CData;
	CData *m_pData;

public:

	ceDeviceInfo		pDevInfo;			//Device Infomation
	ceIntrinsicParam	pIntrinsicParam;	//Depth Camera Intrinsic Param
	ceDistortionParam	pDistortionParam;	//Depth Camera Distortion Param

	/*************************************************************************************
	* \defgroup Initialization
	* @{
	*/

	/**
	*
	* @date		Aug 06, 2019
	* @brief	Construction
	* @details	Frame Buffer & Variable Initialize.
	*
	*/
	CCubeEye();

	/**
	*
	* @date		Aug 06, 2019
	* @brief	Destruction
	* @details	Frame Buffer UnInitialize.
	*
	*/
	~CCubeEye();

	/**
	*
	* @date		Oct 19, 2020
	* @brief	Set Log Status
	* @details	This method is used to enable / disable logging and console printing.
	* @param	bConsolePrintEnable - Set console print log status.
	* @param	bLogEnable - Set log file write status.
	* @return	void
	*
	*/
	void SetLogStatus(bool bConsolePrintEnable = true, bool bLogEnable = false);

	/**
	*
	* @date		Oct 22, 2019
	* @brief	Search Camera.
	* @details	This method search the Cube Eye Camera(Checking VID, PID)
	* @return	searched camera info(path, vid, pid, size(total number))
	*
	*/
	Vector<ceDevicePath> DeviceSearch();

	/**
	*
	* @date		Aug 28, 2019
	* @brief	Connect Camera.
	* @details	This method connects the Cube Eye Camera(Checking VID, PID) and initialize the Parameter.
	* @param	cameraNum - Select camera number to be connected.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int Connect(ceDevicePath pDevPath);

	/**
	*
	* @date		Aug 28, 2019
	* @brief	Disconnect Camera
	* @details	This method disconnects the Cube Eye Camera.
	* @return	void
	*
	*/
	void Disconnect();

	/**@}*/

	/*************************************************************************************
	* \defgroup Start/Stop Frame
	* @{
	*/

	/**
	*
	* @date		Aug 06, 2019
	* @brief	start stream
	* @details	This method sets the start of frame acquisition.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int Start();

	/**
	*
	* @date		Aug 06, 2019
	* @brief	stop stream
	* @details	This method sets the stop of frame acquisition.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int Stop();

	/**@}*/

	/*************************************************************************************
	* \defgroup Read ToF Frame
	* @{
	*/

	/**
	*
	* @date		Aug 06, 2019
	* @brief	Read Depth/IR Frame.
	* @details	This method reads the Depth/IR frames & copies them into the output buffer(pDepth, pIR).
	* @param	punDepth - Pointer to the output detph image.
	* @param	pIR - Pointer to the output IR image.
	* @param	pFrameInfo - Pointer to the Frame Info. buffer
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int ReadDepthIRFrame(uint16 *pDepth, uint16 *pIR, ceFrameInfo &pFrameInfo);

	/**
	*
	* @date		Aug 06, 2019
	* @brief	Read Depth/IR Frame.
	* @details	This method reads the PCL(Ppoint Cloud) frames & copies them into the output buffer(pPCLFrame)
	* @param	pPCLFrame - Pointer to the output point cloud image
	* @param	pFrameInfo - Pointer to the Frame Info. buffer
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int ReadPCLFrame(cePointCloud *pPCLFrame, ceFrameInfo &pFrameInfo);

	/**@}*/
	
	/*************************************************************************************
	* \defgroup Set/Get ToF Parameters
	* @{
	*/
	
	/**
	*
	* @date		Sep 27, 2019
	* @brief	get depth camera's lens parameters.
	* @details	This method gets depth camera's lens intrinsic & distortion parameters.
	* @param	pfIntrinsics - Intrinsic parameter.
	* @param	pDistortionCoeff - Distortion parameter.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getDepthCameraLensParameter(ceIntrinsicParam &pfIntrinsics, ceDistortionParam &pDistortionCoeff);

	/**
	*
	* @date		Sep 24, 2020
	* @brief	get color camera's lens parameters.(only with color camera model)
	* @details	This method gets color camera's lens intrinsic & distortion parameters.
	* @param	pfIntrinsics - Intrinsic parameter.
	* @param	pDistortionCoeff - Distortion parameter.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getColorCameraLensParameter(ceIntrinsicParam &pfIntrinsics, ceDistortionParam &pDistortionCoeff);
	
	/**
	*
	* @date		Feb 24, 2020
	* @brief	get depth + color camera's extrinsic parameters.(only with color camera model)
	* @details	This method gets depth + color camera's extrinsic parameters.
	* @param	pfExtrinsics - extrinsic parameter.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getDepthColorExtrinsicParameter(ceExtrinsicParam &pfExtrinsics);


	/**
	*
	* @date		Sep 27, 2019
	* @brief	get camera's max/min depth range
	* @details	This method gets the current camera's depth range.
	* @param	nMaxDepth - maximum depth range.
	* @param	nMinDepth -  minimum depth range.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getDepthRange(uint16 &nMaxDepth, uint16 &nMinDepth);

	/**
	*
	* @date		Sep 27, 2019
	* @brief	set depth offset
	* @details	This method sets depth global offset.
	* @param	nDepthOfst(0~4095) - depth offset(unit; mm).
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setDepthOffset(int16 nDepthOfst);

	/**
	*
	* @date		Sep 27, 2019
	* @brief	get depth offset
	* @details	This method gets depth global offset.
	* @param	nDepthOfst - current depth offset(unit; mm).
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getDepthOffset(int16 &nDepthOfst);

	/**
	*
	* @date		Aug 06, 2019
	* @brief	set amplitude((IR) strength check threshold
	* @details	This method sets amplitude(IR) threshold for removing pixels with low amplitude(IR) strength.
	* @param	nThreshold(0~4095) - amplitude((IR) check threshold.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setAmplitudeCheckThreshold(uint16 nThreshold = 5);

	/**
	*
	* @date		Aug 06, 2019
	* @brief	get amplitude((IR) strength check threshold
	* @details	This method gets the current amplitude((IR) strength check threshold.
	* @param	nThreshold - current amplitude(IR) threshold value
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getAmplitudeCheckThreshold(uint16 &nThreshold);

	/**
	*
	* @date		Aug 06, 2019
	* @brief	set scattering pixel check threshold
	* @details	This method sets scattering check threshold for removing scattering pixels.
	* @param	nScatteringCheckTh(0~4095) - scattering check threshold.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setScatteringCheckThreshold(uint16 nThreshold = 100);

	/**
	*
	* @date		Aug 06, 2019
	* @brief	get scattering pixel check threshold
	* @details	This method gets the current scattering check threshold.
	* @param	nThreshold - current scattering pixel check threshold value
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getScatteringCheckThreshold(uint16 &nThreshold);

	/**
	*
	* @date		Nov 25, 2020
	* @brief	enable guided filter
	* @details	This method enables a guided filter to remove the spatial noise in the depth frame.
	* @param	nEpsilon(1~8000) - filter coeff(epsilon).
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setGuidedFilter(uint16 nEpsilon = 0x8000);

	/**
	*
	* @date		Mar 03, 2020
	* @brief	disable guided filter
	* @details	This method disables a guided filter in the depth frame.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int clearGuidedFilter();

	/**
	*
	* @date		Aug 06, 2019
	* @brief	enable median filter
	* @details	This method enables the 3x3 median filter to remove the spatial noise in the depth frame.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setMedianFilter();

	/**
	*
	* @date		Aug 06, 2019
	* @brief	disable median filter
	* @details	This method disables the 3x3 median filter in the depth frame.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int clearMedianFilter();

	/**
	*
	* @date		Aug 06, 2019
	* @brief	enable flying pixel removal filter
	* @details	This method enables the flying pixel removal filtering in the depth frame.
				If the depth map's gap value of the pixel is higher than this value, the pixel's depth value is changed to 0.

	* @param	nIRThrs - Flying Pixel check ir threshold, the filter applies only if the ir value is higher than this value.
	* @param	nDepthThrs - Flying Pixel check depth map's gap threshold,
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setFlyPxlFilter(uint16 nEdgeChkTh = 300);

	/**
	*
	* @date		Aug 06, 2019
	* @brief	disable flying pixel removal filter
	* @details	This method disables the flying pixel removal filter in the depth frame.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int clearFlyPxlFilter();

	/**
	*
	* @date		Feb 12, 2020
	* @brief	enable TNR(Temporal Noise Reduction) filter
	* @details	This method enables a TNR filter to remove the temporal noise in the depth frame.
				(In f/w ver4 or more, it is only supported in depth/ir mode.)
	* @param	fRatio(0 ~ 1) - ratio of n frame & (n-1) frame.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setTNRFilter(float fRatio = 0.5f);

	/**
	*
	* @date		Feb 12, 2020
	* @brief	disable TNR(Tempoal Noise Reduction) filter
	* @details	This method disables the TNR filter in the depth frame.
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int clearTNRFilter();

	/**
	*
	* @date		Mar 20, 2020
	* @brief	enable/disable Auto Exposure Function
	* @details	This method enables or disable a the auto exposure function
	* @param	bEanble - true:enable, false:disable
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setAutoExposureOnOff(bool bEanble);

	/**
	*
	* @date		Mar 20, 2020
	* @brief	set Sleep Mode Function
	* @details	This method sets the sleep mode function
	* @param	mode - 0:active(illumination on status), 1:retention (initial value when calling 'Connect' function in SDK), 2:sleep mode(Default at power on)
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setSleepMode(operation_mode mode);

	/**
	*
	* @date		Mar 20, 2020
	* @brief	Illumination on/off control
	* @details	This method sets the Illumination on/off status
	* @param	bEanble - true:on, false:off
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setIlluminationOnOff(bool bEnable);

	/**
	*
	* @date		Mar 20, 2020
	* @brief	Illumination on/off status
	* @details	This method gets the Illumination on/off status
	* @param	bEanble - true:on, false:off
	* @return	Success(0)|Error Code(< 0)
	*
	*/

	int getIlluminationOnOff(bool &bEnable);

	/**
	*
	* @date		Jun 25, 2020
	* @brief	Set Motion Blur Remove Parameter
	* @details	This method sets the motion blur remove parameter
	* @param	nBlurCheckThrs(0~255) - blur check & remove parameter
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setMotionBlurRemove(uint16 nBlurCheckThrs);

	/**
	*
	* @date		Jun 25, 2020
	* @brief	Get Motion Blur Remove Parameter
	* @details	This method gets the current motion blur remove parameter
	* @param	nBlurCheckThrs - current blur check & remove parameter
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getMotionBlurRemove(uint16 &nBlurCheckThrs);

	/**
	*
	* @date		May 28, 2020
	* @brief	Set Point Cloud Mode
	* @details	This method sets the Point Cloud Output Mode(x,y,z,i)
				(depth/ir output mode disable)
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setDepthToPointCloud();

	/**
	*
	* @date		May 28, 2020
	* @brief	Clear Point Cloud Mode
	* @details	This method clears the Point Cloud Output Mode(x,y,z,i)
				(depth/ir output mode enable)
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int clearDepthToPointCloud();

	/**
	*
	* @date		Aug 21, 2020
	* @brief	Set IR Output Mode
	* @details	This method sets the current camera's ir output mode
	* @param	nIROutMode - 0: Amplitude(default), 1:Intensity
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setIROutputMode(uint8 nIROutMode);

	/**
	*
	* @date		Jun 25, 2020
	* @brief	Set Frame Rate
	* @details	This method sets the current camera's frame rate(f/w ver5 or more)
	* @param	nFrameRate - 30(fps), 15(fps), 8(fps)
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int setFrameRate(uint8 nFrameRate);

	/**
	*
	* @date		Jun 25, 2020
	* @brief	Get Frame Rate
	* @details	This method gets the current camera's frame rate(f/w ver5 or more)
	* @param	nFrameRate - 30(fps), 15(fps), 8(fps)
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getFrameRate(uint8 &nFrameRate);

	/**
	*
	* @date		Sep 15, 2020
	* @brief	Get firmware version
	* @details	This method gets the current camera's f/w version
	* @param	unFWVersion - f/w version infor. buffer(size = 5 byte)
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getFWVersion(uint8 *unFWVersion);

	/**
	*
	* @date		Nov 30, 2020
	* @brief	Get Serial Number
	* @details	This method gets the current camera's serial number
	* @param	szSerialNumber - serial number buffer(length = 16 byte)
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getSerialNumber(char *szSerialNumber);

	/**
	*
	* @date		Nov 30, 2020
	* @brief	Get Product Name
	* @details	This method gets the current camera's name
	* @param	szProductName - product name buffer(length = 8 byte)
	* @return	Success(0)|Error Code(< 0)
	*
	*/
	int getProductName(char *szProductName);
};

}
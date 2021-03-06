/********************************************************************
	modified:	2013/12/20
	created:	2013/03/25
	filename: 	RF625Device.h
	maintainer:	Pavel Filipchik [RIFTEK, LLC]
	
	purpose:	Interface to the RF625 Series LASER SCANNER



	>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	>>>  INTERNAL VERSION!!!																				    <<<
	>>>  Any protected/private members and RFDEVICE_FACTORY_API scoped code must be removed before this header  <<<
	>>>  file will be included into customer redistributable API package										<<<
	>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



*********************************************************************/

/*

	RF625 result packet format (RAW)
	==================================================================
	Offs(DEC)	|	Type		| Value
	------------+-------------+-----------------------------------------
	00			|	UINT16		| Measure counter
	02			| UINT16		| Packet counter
	04			| UINT32		| Timestamp
	08			| UINT16		| Number of points (0...1280)
	10			| INT32			| Point 1 - X value
	14			| INT32			| Point 1 - Z value
	18			| INT32			| Point 2 - X value
	22			| INT32			| Point 2 - Z value
	...			|	...			| ...
	Total packet size is (10 + Number_of_points * sizeof(INT32)*2). Max packet size is 10250.

	User can call ConvertResultToPoints function to convert RAW packet data to array of float values in millimeters.
	Float array pointer is passed to store converted values, it's size must be at least Number_of_points*sizeof(float)*2.

	Normalized float values in millimeters may be obtained directly by calling GetNormalizedResult/UDPGetNormalizedResult
	function based on connection protocol (TCP or UDP respectively).

*/

#ifndef RF625DEVICE_INCLUDE
#define RF625DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFLanDevice.h"
#include "RFDeviceDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF625Device : public RFLanDevice
	{
	public:
		// Size of raw profile buffer in bytes
		static const size_t ProfileBufferSize = (10 + 1280*8);
		// Size of raw image buffer in bytes
		static const size_t ImageBufferSize = (512 * 640);
		// Number of items in single profile
		static const size_t ProfileValuesCount = (2 * 1280);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::RF625Device
		/// \brief    Default constructor of RF625Device object. RF625Device::Connect(UDP_DEVINFOBLOCK_PC * lpDevBlock) must be used to connect to the device over TCP.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF625Device();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::RF625Device
		/// \brief    Construct RF625Device object assigned to device specified with lpDevBlock structure. RF625Device::Connect() may be used to connect to this device over TCP.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF625Device(LPUDP_DEVINFOBLOCK_PC lpDevBlock);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::RF625Device
		/// \brief    Default destructor of RF625Device object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RF625Device();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::Connect
		/// \brief    Connect to the device via TCP. RF625Device object must be initialized via RF625Device(LPUDP_DEVINFOBLOCK_PC lpDevBlock)
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL Connect();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::Connect
		/// \brief    Connect to the device specified with lpDevBlock via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL Connect(LPUDP_DEVINFOBLOCK_PC lpDevBlock );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::Disconnect
		/// \brief    Disconnect from device when connected via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL Disconnect();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetResult
		/// \brief    Get raw profile buffer from device when connected via TCP. lpBuffer is a pointer to a buffer RF625Device::ProfileBufferSize bytes long.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL GetResult(void* lpBuffer, BOOL bOldMode = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetImage
		/// \brief    Get raw image buffer from device's camera  when connected via TCP. lpBuffer is a pointer to a buffer RF625Device::ImageBufferSize bytes long.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL GetImage(void* lpBuffer);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetResultInclinationAngle
		/// \brief    Get result inclination angle value. Device must be connected via TCP.
		///           
		/// \return   short : Angle value (-32767 through 32767) which corresponds to [-60:60] degrees.
		//-----------------------------------------------------------------------------
		short GetResultInclinationAngle();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::ReadParams
		/// \brief    Read internal device parameters. Device must be connected via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL ReadParams();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::WriteParams
		/// \brief    Write internal device parameters. Device must be connected via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL WriteParams();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::FlushParams
		/// \brief    If bDefault is FALSE (by default), function stores current internal device parameters to the EEPROM. If bDefault is set to TRUE, default parameters will be restored. Device must be connected via TCP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL FlushParams(BOOL bDefault = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::UDPConnect
		/// \brief    Connect to the device by UDP. usUDPPort value must be set to valid UDP port number. UDP port number may be obtained with GetHostPortNumber() function. Specific network adapter may be specified with szLocalIPAddress. Otherwise function will bind to 0.0.0.0 (INADDR_ANY).
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPConnect (USHORT usUDPPort, LPCSTR szLocalIPAddress = NULL);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::UDPDisconnect
		/// \brief    Disconnect from device when connected via UDP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPDisconnect();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::UDPGetResult
		/// \brief    Get raw profile buffer from device when connected via UDP. lpBuffer is a pointer to a buffer RF625Device::ProfileBufferSize bytes long.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPGetResult(void* lpBuffer, BOOL bOldMode = FALSE);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::PingTest
		/// \brief    Test if device is available over network by issuing a PING command via TCP.
		///           
		/// \return   BOOL : TRUE if PING reply received, FALSE otherwise.
		//-----------------------------------------------------------------------------
		BOOL PingTest();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::UDPPacketCounter
		/// \brief    Static helper function to extract UDP packet counter from raw packet buffer.
		///           
		/// \return   WORD : UDP packet counter.
		//-----------------------------------------------------------------------------
		static WORD UDPPacketCounter(void* lpBuffer);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::UDPGetNormalizedResult
		/// \brief    An UCP helper function to get profile data directly to array of DWORD values in microns. See RF625Device::ConvertResultToPoints. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value). Will be 0xFFFF on UDPGetResult failure.
		//-----------------------------------------------------------------------------
		USHORT UDPGetNormalizedResult(DWORD OUT *lpPointsBuffer, USHORT OUT *lpCount);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::ConvertResultToPoints
		/// \brief    Converts raw profile buffer data specified with lpResultBuffer to the array of float values (lpPointsBuffer). Output values are representations of profile's points in millimeters. Each odd value of lpPointsBuffer is a X value, and next (even) value is appropriate Z value. lpPointsBuffer must be a pointer to float[RF625Device::ProfileValuesCount]. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value)
		//-----------------------------------------------------------------------------
		USHORT ConvertResultToPoints(void IN *lpResultBuffer, float OUT *lpPointsBuffer, USHORT OUT *lpCount);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetNormalizedResult
		/// \brief    A TCP helper function to get profile data directly to array of float values in millimeters. See RF625Device::ConvertResultToPoints. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value). Will be 0xFFFF on GetResult failure.
		//-----------------------------------------------------------------------------
		USHORT GetNormalizedResult(float OUT *lpPointsBuffer, USHORT OUT *lpCount);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetNormalizedResult
		/// \brief    An UDP helper function to get profile data directly to array of float values in millimeters. See RF625Device::ConvertResultToPoints. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value). Will be 0xFFFF on GetResult failure.
		//-----------------------------------------------------------------------------
		USHORT UDPGetNormalizedResult(float OUT *lpPointsBuffer, USHORT OUT *lpCount);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetSerialNumber
		/// \brief    Get serial number of RF620 device.
		///           
		/// \return   DWORD: Device's serial number.
		//-----------------------------------------------------------------------------
		DWORD GetSerialNumber();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetCapsExternalResultSync
		/// \brief    Check if device is capable of external result synchronization.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsExternalResultSync();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetCapsExternalMeasurementSync
		/// \brief    Check if device is capable of external measurement synchronization.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsExternalMeasurementSync();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetCapsAnalogueOutputByCurrent
		/// \brief    Check if device is capable of analogue output synchronization by current.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsAnalogueOutputByCurrent();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetCapsAnalogueOutputByVoltage
		/// \brief    Check if device is capable of analogue output synchronization by voltage.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsAnalogueOutputByVoltage();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetCapsLaserModulation
		/// \brief    Check if device is capable of laser modulation.
		///           
		/// \return   BOOL: TRUE or FALSE
		//-----------------------------------------------------------------------------
		BOOL GetCapsLaserModulation();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetBaseDistance
		/// \brief    Returns device base distance in mm.
		///           
		/// \return   WORD: Base distance in mm.
		//-----------------------------------------------------------------------------
		WORD GetBaseDistance();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetMeasurementRangeZ
		/// \brief    Returns measurement range along Z in mm.
		///           
		/// \return   WORD: Range in mm.
		//-----------------------------------------------------------------------------
		WORD GetMeasurementRangeZ();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetMeasurementRangeXSMR
		/// \brief    Returns measurement range along X(SMR) in mm.
		///           
		/// \return   WORD: Range in mm.
		//-----------------------------------------------------------------------------
		WORD GetMeasurementRangeXSMR();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetMeasurementRangeXEMR
		/// \brief    Returns measurement range along X(EMR) in mm.
		///           
		/// \return   WORD: Range in mm.
		//-----------------------------------------------------------------------------
		WORD GetMeasurementRangeXEMR();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetFirmwareVersion
		/// \brief    Returns device firmware version.
		///           
		/// \return   DWORD: Firmware version number.
		//-----------------------------------------------------------------------------
		DWORD GetFirmwareVersion();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetLaserLevel
		/// \brief    Returns laser emission intensity in the range from 0 (OFF) to 31(maximum power - default).
		///           
		/// \return   BYTE: Laser level.
		//-----------------------------------------------------------------------------
		BYTE GetLaserLevel();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetExposureTime
		/// \brief    Returns exposure time (0 through 65535) which corresponds to 1-65536 microseconds.
		///           
		/// \return   WORD: Exposure time.
		//-----------------------------------------------------------------------------
		WORD GetExposureTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetSignalProcessingTime
		/// \brief    Returns signal processing time (0 through 65535) which corresponds to 1-65536 microseconds.
		///           
		/// \return   WORD: Signal processing time.
		//-----------------------------------------------------------------------------
		WORD GetSignalProcessingTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetLeftBoundary
		/// \brief    Returns left boundary of window dimensions ROI (0 through 224).
		///           
		/// \return   BYTE: Left boundary.
		//-----------------------------------------------------------------------------
		BYTE GetLeftBoundary();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetWindowWidth
		/// \brief    Returns window width (31 through 255).
		///           
		/// \return   BYTE: Window width.
		//-----------------------------------------------------------------------------
		BYTE GetWindowWidth();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetUpperBoundary
		/// \brief    Returns upper boundary window dimensions ROI (0 through 224).
		///           
		/// \return   BYTE: Upper boundary.
		//-----------------------------------------------------------------------------
		BYTE GetUpperBoundary();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetWindowHeight
		/// \brief    Returns window height (31 through 255).
		///           
		/// \return   BYTE: Window height.
		//-----------------------------------------------------------------------------
		BYTE GetWindowHeight();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetExternalResultSyncEnabled
		/// \brief    Checks if external synchronization of result is turned on. Applicable only when RF625Device::GetCapsExternalResultSync() is TRUE.
		///           
		/// \return   BOOL: TRUE if enabled or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetExternalResultSyncEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetExternalResultSyncEdge
		/// \brief    Returns FALSE if there is leading edge used or TRUE if trailing edge used. Applicable only when RF625Device::GetCapsExternalResultSync() is TRUE.
		///           
		/// \return   BOOL: TRUE or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetExternalResultSyncEdge();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetExternalMeasurementSyncEnabled
		/// \brief    Checks if external synchronization of measurement is turned on. Applicable only when RF625Device::GetCapsExternalMeasurementSync() is TRUE.
		///           
		/// \return   BOOL: TRUE if enabled or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetExternalMeasurementSyncEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetExternalMeasurementSyncEdge
		/// \brief    Returns FALSE if there is leading edge used or TRUE if trailing edge used. Applicable only when RF625Device::GetCapsExternalMeasurementSync() is TRUE.
		///           
		/// \return   BOOL: TRUE or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetExternalMeasurementSyncEdge();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetAnalogueOutputSyncEnabled
		/// \brief    Checks if synchronization of analogue output is turned on. Applicable only when one of RF625Device::GetCapsAnalogueOutputByCurrent() or RF625Device::GetCapsAnalogueOutputByVoltage() is TRUE.
		///           
		/// \return   BOOL: TRUE if enabled or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetAnalogueOutputSyncEnabled();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetAnalogueOutputSyncEdge
		/// \brief    Returns FALSE if there is leading edge used or TRUE if trailing edge used. Applicable only when one of RF625Device::GetCapsAnalogueOutputByCurrent() or RF625Device::GetCapsAnalogueOutputByVoltage() is TRUE.
		///           
		/// \return   BOOL: TRUE or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetAnalogueOutputSyncEdge();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetAnalogueOutputSyncEdge
		/// \brief    Returns TRUE if level of TTL_OUT0 signal of valid data at the analog output.
		///           
		/// \return   BOOL: TRUE or FALSE.
		//-----------------------------------------------------------------------------
		BOOL GetAnalogueOutputTTL_OUT0Level();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetExternalSignalDivisor
		/// \brief    Returns parameter of external signal divisor (0 through 255) which corresponds to 1-256 divisor.
		///           
		/// \return   BYTE: Divisor value.
		//-----------------------------------------------------------------------------
		BYTE GetExternalSignalDivisor();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetMeasurementDelay
		/// \brief    Returns measurement delay time (0 through 255) which corresponds to 0-255 microseconds.
		///           
		/// \return   BYTE: Measurement delay time.
		//-----------------------------------------------------------------------------
		BYTE GetMeasurementDelay();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetAnalogueOutputNumberOfPoints
		/// \brief    Returns a byte value that specifies the number of points at analogue output: 0 - disabled; 1 - 128 points; 2 - 256 points; 3 - 512 points; 4 - 1024 points.
		///           
		/// \return   BYTE: Value in range of 0 through 4.
		//-----------------------------------------------------------------------------
		BYTE GetAnalogueOutputNumberOfPoints();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetAnalogueOutputPointHoldupTime
		/// \brief    Returns point holdup time at the analog output (0 through 255) which corresponds to 1-256 microseconds.
		///           
		/// \return   BYTE: Holdup time.
		//-----------------------------------------------------------------------------
		BYTE GetAnalogueOutputPointHoldupTime();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetDeviceIPAddress
		/// \brief    Returns device IPv4 address.
		///           
		/// \return   BYTE*: Array of 4 bytes of IPv4 address.
		//-----------------------------------------------------------------------------
		const BYTE *GetDeviceIPAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetHostIPAddress
		/// \brief    Returns IPv4 address of the receiver of UDP package.
		///           
		/// \return   BYTE*: Array of 4 bytes of IPv4 address.
		//-----------------------------------------------------------------------------
		const BYTE *GetHostIPAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetNetworkMask
		/// \brief    Returns Ethernet mask.
		///           
		/// \return   BYTE*: Array of 4 bytes of Ethernet mask.
		//-----------------------------------------------------------------------------
		const BYTE *GetNetworkMask();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetHumanReadableDeviceIPAddress
		/// \brief    Returns device IPv4 address human readable string.
		///           
		/// \return   char*: IPv4 address string. NOTE: String buffer must be deleted by user (use delete[])
		//-----------------------------------------------------------------------------
		char *GetHumanReadableDeviceIPAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetHumanReadableHostIPAddress
		/// \brief    Returns IPv4 address human readable string for UDP package receiver.
		///           
		/// \return   char*: IPv4 address string. NOTE: String buffer must be deleted by user (use delete[])
		//-----------------------------------------------------------------------------
		char *GetHumanReadableHostIPAddress();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetHumanReadableNetworkMask
		/// \brief    Returns human readable string for Ethernet mask.
		///           
		/// \return   char*: Ethernet mask string. NOTE: String buffer must be deleted by user (use delete[])
		//-----------------------------------------------------------------------------
		char *GetHumanReadableNetworkMask();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetHostPortNumber
		/// \brief    Returns port of the receiver of UDP package.
		///           
		/// \return   WORD: UDP port number.
		//-----------------------------------------------------------------------------
		WORD GetHostPortNumber();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetUDPFrequency
		/// \brief    Returns UDP package repetition frequency (0 through 255) which corresponds to 0-255 Hz.
		///           
		/// \return   BYTE: Frequency. If 0 the function is disabled and UDP packages are not transmitted.
		//-----------------------------------------------------------------------------
		BYTE GetUDPFrequency();

		// Deprecated, for compatibility
		short GetRotationAngle();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetLaserLevel
		/// \brief    Sets laser emission intensity in the range from 0 (OFF) to 31(maximum power - default).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetLaserLevel(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetExposureTime
		/// \brief    Sets exposure time (0 through 65535) which corresponds to 1-65536 microseconds.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExposureTime(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetSignalProcessingTime
		/// \brief    Sets signal processing time (0 through 65535) which corresponds to 1-65536 microseconds.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetSignalProcessingTime(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetLeftBoundary
		/// \brief    Sets left boundary of window dimensions ROI (0 through 224).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetLeftBoundary(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetWindowWidth
		/// \brief    Sets window width (31 through 255).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetWindowWidth(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetUpperBoundary
		/// \brief    Sets upper boundary window dimensions ROI (0 through 224).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetUpperBoundary(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetWindowHeight
		/// \brief    Sets window height (31 through 255).
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetWindowHeight(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetExternalResultSyncEnabled
		/// \brief    Turns on/off external synchronization of result. Applicable only when RF625Device::GetCapsExternalResultSync() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalResultSyncEnabled(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetExternalResultSyncEdge
		/// \brief    Sets synchronization of result by leading edge if bValue is TRUE, otherwise by trailing edge. Applicable only when RF625Device::GetCapsExternalResultSync() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalResultSyncEdge(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetExternalMeasurementSyncEnabled
		/// \brief    Turns on/off external synchronization of measurement. Applicable only when RF625Device::GetCapsExternalMeasurementSync() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalMeasurementSyncEnabled(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetExternalResultSyncEdge
		/// \brief    Sets synchronization of measurement by leading edge if bValue is TRUE, otherwise by trailing edge. Applicable only when RF625Device::GetCapsExternalMeasurementSync() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalMeasurementSyncEdge(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetAnalogueOutputSyncEnabled
		/// \brief    Turns on/off external synchronization of analogue output. Applicable only when one of RF625Device::GetCapsAnalogueOutputByCurrent() or RF625Device::GetCapsAnalogueOutputByVoltage() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputSyncEnabled(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetAnalogueOutputSyncEdge
		/// \brief    Sets synchronization of analogue output by leading edge if bValue is TRUE, otherwise by trailing edge. Applicable only when one of RF625Device::GetCapsAnalogueOutputByCurrent() or RF625Device::GetCapsAnalogueOutputByVoltage() is TRUE.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputSyncEdge(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetAnalogueOutputTTL_OUT0Level
		/// \brief    Sets the level of TTL_OUT0 signal of valid data at the analog output.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputTTL_OUT0Level(BOOL bValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetExternalSignalDivisor
		/// \brief    Sets parameter of external signal divisor (0 through 255) which corresponds to 1-256 divisor.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetExternalSignalDivisor(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetMeasurementDelay
		/// \brief    Sets measurement delay time (0 through 255) which corresponds to 0-255 microseconds.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetMeasurementDelay(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetAnalogueOutputNumberOfPoints
		/// \brief    Sets a byte value that specifies the number of points at analogue output: 0 - disabled; 1 - 128 points; 2 - 256 points; 3 - 512 points; 4 - 1024 points.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputNumberOfPoints(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetAnalogueOutputPointHoldupTime
		/// \brief    Sets point holdup time at the analog output (0 through 255) which corresponds to 1-256 microseconds.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetAnalogueOutputPointHoldupTime(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetDeviceIPAddress
		/// \brief    Sets device IPv4 address.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetDeviceIPAddress(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetHostIPAddress
		/// \brief    Sets IPv4 address of the receiver of UDP package.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetHostIPAddress(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetNetworkMask
		/// \brief    Sets Ethernet mask.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetNetworkMask(BYTE ucValue[4]);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetHostPortNumber
		/// \brief    Sets the port of the receiver of UDP package. To avoid conflicts, do not specify values 6000, 6001 and 6002.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetHostPortNumber(WORD wValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetUDPFrequency
		/// \brief    Sets UDP package repetition frequency (0 through 255) which corresponds to 0-255 Hz.
		///           
		/// \return   BOOL: TRUE on success. NOTE: You must call WriteParams() to make setting to take effect.
		//-----------------------------------------------------------------------------
		BOOL SetUDPFrequency(BYTE ucValue);

		// Deprecated, for compatibility
		BOOL SetRotationAngle(short sValue);

		// Returns pointer to UDP_DEVINFOBLOCK_PC structure associated with RF625Device instance
		const LPUDP_DEVINFOBLOCK_PC GetDevBlock();

		// Copy device parameters from another RF625Device instance
		void CloneParameters(RF625Device* lpDev);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::Reboot
		/// \brief    Initiate device reboot
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL Reboot();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::PowerOff
		/// \brief    Initiate device power off
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL PowerOff();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetDevicePortNumber
		/// \brief    Update device TCP port number. Has no effect until FlushParams called and device is rebooted.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetDevicePortNumber(WORD usPort);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetDevicePortNumber
		/// \brief    Get device TCP port number
		///           
		/// \return   WORD : TCP port number
		//-----------------------------------------------------------------------------
		WORD GetDevicePortNumber();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetPixelBrightnessThreshold
		/// \brief    Update pixel brightness threshold. Has no effect until UpdateParams called.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetPixelBrightnessThreshold(BYTE ucValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetPixelBrightnessThreshold
		/// \brief    Get pixel brightness threshold
		///           
		/// \return   BYTE : pixel brightness threshold value
		//-----------------------------------------------------------------------------
		BYTE GetPixelBrightnessThreshold();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetAutoExposureMode
		/// \brief    Enable or disable auto exposure mode. Has no effect until UpdateParams called.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetAutoExposureMode(BYTE ucMode);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetAutoExposureMode
		/// \brief    Return the state of auto exposure mode trigger.
		///           
		/// \return   BOOL : TRUE if enabled, FALSE if disabled.
		//-----------------------------------------------------------------------------
		BYTE GetAutoExposureMode();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetEnableLegacyMode
		/// \brief    Enable or disable UDP legacy data mode. Has no effect until UpdateParams called.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetEnableLegacyMode(BOOL bEnable);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetEnabledLegacyMode
		/// \brief    Return the state of UDP legacy data mode trigger.
		///           
		/// \return   BOOL : TRUE if enabled, FALSE if disabled.
		//-----------------------------------------------------------------------------
		BOOL GetEnabledLegacyMode();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetEnableRawImageMode
		/// \brief    Enables raw image mode and turns off image processor if bEnable is TRUE. Turns image processor back on if bEnable is FALSE.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetEnableRawImageMode(BOOL bEnable);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetEnabledLegacyMode
		/// \brief    Returns state of raw image mode trigger.
		///           
		/// \return   BOOL : TRUE if enabled, FALSE if disabled.
		//-----------------------------------------------------------------------------
		BOOL GetEnabledRawImageMode();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetEnableInterpolation
		/// \brief    Enable or disable hardware profile interpolation
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetEnableInterpolation(BOOL bEnable);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetEnabledInterpolation
		/// \brief    Check if hardware interpolation enabled.
		///           
		/// \return   BOOL : TRUE if enabled, FALSE if disabled.
		//-----------------------------------------------------------------------------
		BOOL GetEnabledInterpolation();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetAutoExposure
		/// \brief    Read exposure value when device is in auto-exposure mode. Exposure value written to unsigned short pointed by lpusValue.
		///           
		/// \return   BOOL : TRUE on success.
		//-----------------------------------------------------------------------------
		BOOL GetAutoExposure(LPWORD lpusValue);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::SetEnableModbusTcp
		/// \brief    Switch device to Profibus mode if bEnable is TRUE, back to normal mode if FALSE.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL SetEnableModbusTcp(BOOL bEnable);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF625Device::GetEnabledModbusTcp
		/// \brief    Check if device switched to Profibus mode.
		///           
		/// \return   BOOL : TRUE if enabled, FALSE if disabled.
		//-----------------------------------------------------------------------------
		BOOL GetEnabledModbusTcp();

		BOOL SetModbusTcpAddress(BYTE ucAddress[4]);
		const BYTE *GetModbusTcpAddress();
		char *GetHumanReadableModbusTcpAddress();
		BOOL SetModbusTcpPort(WORD wPort);
		WORD GetModbusTcpPort();

#ifdef RFDEVICE_FACTORY_API
		BOOL SetCalibrationMode(BOOL bEnable);
		BOOL GetPixels(void* lpBuffer);
		BOOL ReadFactoryParams(void* lpBuffer);
		BOOL WriteFactoryParams(void* lpBuffer);
		BOOL FlushFactoryParams();
		BOOL ReadFactoryTables(void* lpBuffer);
		BOOL WriteFactoryTables(void* lpBuffer);
		BOOL FlushFactoryTables(UCHAR uBlock64k);
		BOOL ReadFirmware(void* lpBuffer);
		BOOL WriteFirmware(void* lpBuffer);
		BOOL FlushFirmware(UCHAR uBlock64k);
		BOOL SetAnalogOutNormal();
		BOOL SetAnalogOutDbgMin();
		BOOL SetAnalogOutDbgMax();
		BOOL SendSPI(BYTE ucCmd, BYTE ucNumParams, BYTE* lpucValues);
#endif

#ifdef RFDEVICE_FACTORY_API
		BOOL UpgradeFirmware(LPCSTR szFileName);	// Not sure - is it factory or customer function?
#endif

		BOOL ReadParams(void * lpBuffer);
		BOOL WriteParams(void* lpBuffer);
		BOOL CalcAngle(void* lpBuffer);


//////////////////////////////////////////////////////////////////////////
	protected:
		RF620HS_INFO m_DevInfo;
		RF620HS_PARAMETERS m_params;
		UDP_DEVINFOBLOCK_PC m_DevBlock;

		BOOL PopulateParams();
		void UDPPopulateParams();


	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF625Device_INCLUDE

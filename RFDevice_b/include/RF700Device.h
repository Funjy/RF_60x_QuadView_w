/********************************************************************
	modified:	2013/08/16
	created:	2013/08/16
	filename: 	RF700Device.h
	author:		RIFTEK, LLC
	
	purpose:	Interface to the RF700 Series 

	>>>>>>>>>>>><<<<<<<<<<<<<<
	>>>  INTERNAL VERSION  <<<
	>>>>>>>>>>>><<<<<<<<<<<<<<

*********************************************************************/

#ifndef RF700DEVICE_INCLUDE
#define RF700DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFLanDevice.h"
#include "RFDeviceDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF700Device : public RFLanDevice
	{
	public:
		// Size of raw measurements buffer in bytes
		static const size_t measurePacket = (12);
		// Number of items in single profile
		static const size_t measureValueCount = (12);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::RF700Device
		/// \brief    Default constructor of RF700Device object. RF700Device::Connect(UDP_DEVINFOBLOCK_PC * lpDevBlock) must be used to connect to the device over TCP.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF700Device();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::RF700Device
		/// \brief    Construct RF700Device object assigned to device specified with lpDevBlock structure. RF700Device::Connect() may be used to connect to this device over TCP.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RF700Device(LPRF700_PARAMETERS lpDevBlock);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::RF700Device
		/// \brief    Default destructor of RF700Device object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RF700Device();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::UDPConnect
		/// \brief    Connect to the device by UDP. usUDPPort value must be set to valid UDP port number. UDP port number may be obtained with GetHostPortNumber() function. Specific network adapter may be specified with szLocalIPAddress. Otherwise function will bind to 0.0.0.0 (INADDR_ANY).
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPConnect(USHORT usListenUDPPort, USHORT usSendUDPPort, LPCSTR szLocalIPAddress = NULL );

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::UDPDisconnect
		/// \brief    Disconnect from device when connected via UDP.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPDisconnect();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::UDPGetResult
		/// \brief    Get raw profile buffer from device when connected via UDP. lpBuffer is a pointer to a buffer RF700Device::ProfileBufferSize bytes long.
		///           
		/// \return   BOOL : TRUE on success, FALSE on error.
		//-----------------------------------------------------------------------------
		BOOL UDPGetResultFromFlow(void* lpBuffer);

		BOOL UDPGetSingleResult( void* lpBuffer);


// 		//-----------------------------------------------------------------------------
// 		//  FUNCTION  RF700Device::UDPPacketCounter
// 		/// \brief    Static helper function to extract UDP packet counter from raw packet buffer.
// 		///           
// 		/// \return   WORD : UDP packet counter.
// 		//-----------------------------------------------------------------------------
// 		static WORD UDPPacketCounter(void* lpBuffer);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::ConvertResultToPoints
		/// \brief    Converts raw profile buffer data specified with lpResultBuffer to the array of DWORD values (lpPointsBuffer). Output values are representations of profile's points in microns. Each odd value of lpPointsBuffer is a X value, and next (even) value is appropriate Z value. lpPointsBuffer must be a pointer to DWORD[RF700Device::ProfileValuesCount]. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value)
		//-----------------------------------------------------------------------------
		USHORT ConvertResultToPoints(void IN *lpResultBuffer, DWORD OUT *lpPointsBuffer, USHORT OUT *lpCount);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::ConvertResultToPoints
		/// \brief    Converts raw profile buffer data specified with lpResultBuffer to the array of float values (lpPointsBuffer). Output values are representations of profile's points in millimeters. Each odd value of lpPointsBuffer is a X value, and next (even) value is appropriate Z value. lpPointsBuffer must be a pointer to float[RF700Device::ProfileValuesCount]. lpCount is a pointer to number of points in profile.
		///           
		/// \return   USHORT: number of profile points (same as lpCount value)
		//-----------------------------------------------------------------------------
		USHORT ConvertResultToPoints(void IN *lpResultBuffer, float OUT *lpPointsBuffer, USHORT OUT *lpCount);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RF700Device::GetSerialNumber
		/// \brief    Get serial number of RF700 device.
		///           
		/// \return   DWORD: Device's serial number.
		//-----------------------------------------------------------------------------
		BOOL UDPGet603SerialNumberS( void* lpBuffer );

		BOOL UDPSendHello( void* lpBuffer, int* err_code = NULL );

		BOOL UDPSendTermoHello( void* lpBuffer );

		BOOL UDPGetTermoMeasure( void* lpBuffer );

		BOOL UDPReadPortsState( void* lpBuffer );

		BOOL UDPWritePortsState( void* lpBuffer );

		BOOL UDPReadParams( void* lpBuffer );

		BOOL UDPWriteParams( void* lpBuffer );

		BOOL UDPWriteParam(BYTE ucAddress, BYTE ucLength, LPBYTE lpucValue);

		BOOL UDPStartStream();

		BOOL UDPStopStream();

		unsigned short getRF603Serial(int);

		BOOL UDPGetNormalizedMeasures( void *lpBuffer );		

	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF700DEVICE_INCLUDE

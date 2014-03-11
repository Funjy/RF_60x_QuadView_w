#ifndef RFCOMDEVICE_INCLUDE
#define RFCOMDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFDeviceDefs.h"

namespace RFDevice {

	class RFDEVICE_API RFComDevice : public RFDeviceObject
	{
	public:
		RFComDevice();
		~RFComDevice();

		/************************************************************************/
		/* RS-232 functions                                                     */
		/************************************************************************/
		BOOL	OpenPort(LPCSTR lpPort_Name, DWORD dwSpeed);
		BOOL	ClosePort();
		BOOL    fn_con_DEBUG_REGISTERS(BYTE bAddress, LPcon_DEBUG_REGISTERS con_DEBUG_REGISTERS);
		BOOL	ReadParameter(BYTE bAddress, WORD wParameter, DWORD* lpdwValue);
		BOOL	WriteParameter(BYTE bAddress, WORD wParameter, DWORD dwValue);
		BOOL	ReadCustomParameter(BYTE bAddress, BYTE bParameterAddress, BYTE bParameterSize, void* lpValue);
		BOOL	WriteCustomParameter(BYTE bAddress, BYTE bParameterAddress, BYTE bParameterSize, void* lpValue);
		BOOL	FlushToFlash(BYTE bAddress);
		BOOL	RestoreFromFlash(BYTE bAddress);
		BOOL	LockResult(BYTE bAddress);
		BOOL	Measure(BYTE bAddress, USHORT* lpusValue);
		BOOL	StartStream(BYTE bAddress);
		BOOL	StopStream(BYTE bAddress);
		BOOL	GetStreamMeasure(USHORT* lpusValue);
		BOOL	CustomCmd(char * pcInData, DWORD dwInSize, char * pcOutData, DWORD * pdwOutSize);
		HANDLE	GetPortHandle();
		static BOOL	ValidateData(LPBYTE lpucData, const int nDataLength);

		/************************************************************************/
		/* Ethernet functions		                                            */
		/************************************************************************/
		BOOL	EthernetOpenPort();
		BOOL	EthernetSetTimeout(DWORD dwTimeout);
		BOOL	EthernetClosePort();

	};

}

#if defined(__cplusplus)
}
#endif

#endif //RFCOMDEVICE_INCLUDE

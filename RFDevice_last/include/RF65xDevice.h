#ifndef RF65XDEVICE_INCLUDE
#define RF65XDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFComDevice.h"

namespace RFDevice {

	class RFDEVICE_API RF65xDevice : public RFComDevice
	{
	public:	
		RF65xDevice(void);
		~RF65xDevice(void);
	
		LPRF65xUDPPACKET pack;		

		BOOL OpenPort(LPCSTR lpPort_Name, DWORD dwSpeed);
		void BindNetworkAddress(BYTE ucAddress);
		BOOL HelloCmd(BYTE bAddress, LPRF65xHELLOANSWER lprfHelloAnswer);
		BOOL HelloCmd();

		BOOL GetSingleMeasure(USHORT* lpusValue);
		BOOL GetStreamMeasure(USHORT* lpusValue);
		BOOL GetSingleDualMeasure8( BYTE* lpbValue  );
		BOOL GetStreamDualMeasure8( BYTE* lpbValue  );
		BOOL StartStream();
		BOOL StopStream();

		BOOL EthernetOpenPort();
		BOOL EthernetGetStreamMeasure();//(LPRF65xUDPPACKET lp65xUDPPacket);

		BOOL EnableSensor(BOOL bEnable = TRUE);
		BOOL SetPriority(BYTE ucValue);
		BOOL SetNetworkAddress(BYTE ucValue);
		BOOL SetBaundRate(DWORD dwValue);
		BOOL SetAverageCount(DWORD dwValue);
		BOOL SetSamplingPeriod(DWORD dwValue);
		BOOL SetNominalValue(DWORD dwValue);

		BOOL GetPowerState();
		BYTE GetPriority();
		BYTE GetNetworkAddress();
		DWORD GetBaundRate();
		DWORD GetAverageCount();
		DWORD GetSamplingPeriod();
		DWORD GetNominalValue();

		LPRF65xPARAMS GetParams();
		
		BYTE	GetDeviceType();
		BYTE	GetDeviceModificaton();
		WORD	GetDeviceSerial();
		WORD	GetDeviceMaxDistance();
		WORD	GetDeviceRange();

	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF65XDEVICE_INCLUDE

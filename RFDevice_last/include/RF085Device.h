#ifndef RF085DEVICE_INCLUDE
#define RF085DEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFLanDevice.h"
#include "RFDeviceDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF085Device : public RFLanDevice
	{
	public:
		RF085Device();
		RF085Device(LPCSTR szDeviceIPAddress);
		RF085Device(LPCSTR szDeviceIPAddress, LPCSTR szLocalIPAddress);
		~RF085Device();

		BOOL Connect();
		BOOL Connect(LPCSTR szDeviceIPAddress);
		BOOL Disconnect();

		BOOL GetStateOUT1(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT2(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT3(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT4(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT5(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateOUT6(BOOL bReadHardwareValue = FALSE);

		BOOL GetStateLED1(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateLED2(BOOL bReadHardwareValue = FALSE);
		BOOL GetStateLED3(BOOL bReadHardwareValue = FALSE);

		BOOL SetStateOUT1(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT2(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT3(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT4(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT5(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateOUT6(BOOL state, BOOL bWriteHardwareValue = FALSE);

		BOOL SetStateLED1(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateLED2(BOOL state, BOOL bWriteHardwareValue = FALSE);
		BOOL SetStateLED3(BOOL state, BOOL bWriteHardwareValue = FALSE);

		BOOL ReadParamsOUT();
		BOOL ReadParamsLED();
		BOOL WriteParamsOUT();
		BOOL WriteParamsLED();

		BOOL MotorEnable(BOOL bEnable);
		BOOL MotorMove(int nDistance);
		BOOL MotorStop();
		BOOL MotorReadStatus();
		BOOL MotorIsMoving(BOOL bReadHardwareStatus = FALSE);
		BOOL MotorAtHome(BOOL bReadHardwareStatus = FALSE);

		BOOL MotorReadParam(BYTE ucCmd, BYTE ucAddr, BYTE* lpucResult);
		BOOL MotorReadParams();
		BOOL MotorWriteParam(BYTE ucCmd, BYTE ucAddr, BYTE ucValue);
		BOOL MotorWriteParams();
		BOOL MotorRestoreParams();
		BOOL MotorFlushParams();

		WORD MotorGetSpeed(BOOL bReadHardwareValue = FALSE);
		WORD MotorGetACC(BOOL bReadHardwareValue = FALSE);
		WORD MotorGetDCC(BOOL bReadHardwareValue = FALSE);
		WORD MotorGetAlarm(BOOL bReadHardwareValue = FALSE);
		WORD MotorGetFSS(BOOL bReadHardwareValue = FALSE);

		BOOL MotorSetSpeed(WORD wSpeed, BOOL bWriteHardwareValue = FALSE);
		BOOL MotorSetACC(WORD wACC, BOOL bWriteHardwareValue = FALSE);
		BOOL MotorSetDCC(WORD wDCC, BOOL bWriteHardwareValue = FALSE);
		BOOL MotorSetAlarm(WORD wAlarm, BOOL bWriteHardwareValue = FALSE);
		BOOL MotorSetFSS(WORD wFSS, BOOL bWriteHardwareValue = FALSE);

	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF085DEVICE_INCLUDE

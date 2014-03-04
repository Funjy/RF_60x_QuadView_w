#ifndef RF603BDEVICE_INCLUDE
#define RF603BDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF605Device.h"
#include "RFDeviceDefs.h"

namespace RFDevice {

	class RFDEVICE_API RF603BDevice : public RF605Device
	{
	public:
		RF603BDevice();
		~RF603BDevice();

		BOOL EthernetGetStreamMeasure( LPRF60xBUDPPACKET );	
		BOOL EthernetGetNormalisedStreamMeasure(float* OUT lpValues);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF603DEVICE_INCLUDE

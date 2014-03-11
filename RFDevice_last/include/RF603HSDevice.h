#ifndef RF603HSDEVICE_INCLUDE
#define RF603HSDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RF605Device.h"
#include "RFDeviceDefs.h"
#include "RFString.h"

namespace RFDevice {

	class RFDEVICE_API RF603HSDevice : public RF605Device
	{
	public:
		RF603HSDevice();
		~RF603HSDevice();

		BOOL EthernetOpenPort();
		BOOL EthernetGetStreamMeasure( LPRF60xHSMEASUREPACKET );
		BOOL EthernetGetNormalisedStreamMeasure(float* OUT lpValues);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RF603HSDEVICE_INCLUDE

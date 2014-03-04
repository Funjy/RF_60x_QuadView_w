#ifndef RFLANDEVICE_INCLUDE
#define RFLANDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"

namespace RFDevice {

	class RFDEVICE_API RFLanDevice : public RFDeviceObject
	{
	public:
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDevice::RFLanDevice
		/// \brief    This is constructor of generic RFLanDevice object
		///           
		/// \return   none
		//-----------------------------------------------------------------------------
		RFLanDevice();
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDevice::~RFLanDevice
		/// \brief    This is destructor of generic RFLanDevice object
		///           
		/// \return   none
		//-----------------------------------------------------------------------------
		~RFLanDevice();

		SOCKET GetSocket();

	protected:
		SOCKET m_sock;
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RFLANDEVICE_INCLUDE

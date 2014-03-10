/********************************************************************
	modified:	2013/04/16
	created:	2013/03/25
	filename: 	RFLanDetector.h
	author:		RIFTEK, LLC
	
	purpose:	Ethernet device detector class

	>>>>>>>>>>>><<<<<<<<<<<<<<
	>>>  INTERNAL VERSION  <<<
	>>>>>>>>>>>><<<<<<<<<<<<<<

*********************************************************************/

#ifndef RFLANDETECTOR_INCLUDE
#define RFLANDETECTOR_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFDeviceDefs.h"

namespace RFDevice {

	class RFDEVICE_API RFLanDetector
	{
	public:
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDetector::RFLanDetector
		/// \brief    Default constructor of RFLanDetector object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RFLanDetector(void);
		
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDetector::~RFLanDetector
		/// \brief    Destructor of RFLanDetector object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RFLanDetector(void);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDetector::Search
		/// \brief    Performs device search for timeout (seconds) period. Device type is specified with type argument (e.g., 620 for RF620 Series).
		///           
		/// \return   int : Number of detected devices.
		//-----------------------------------------------------------------------------
		int Search(USHORT type, int timeout);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDetector::Clear
		/// \brief    Clears detected devices list. NOTE: Memory cleanup is done via destructor, you don't need to call Clear for this purpose.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		void Clear();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDetector::GetSize
		/// \brief    Returns the number of items in detected devices list.
		///           
		/// \return   int : number of items.
		//-----------------------------------------------------------------------------
		int GetSize();

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDetector::GetDevBlock
		/// \brief    Returns a pointer to UDP_DEVINFOBLOCK_PC structure of device of specified index.
		///           
		/// \return   LPUDP_DEVINFOBLOCK_PC : a pointer.
		//-----------------------------------------------------------------------------
		LPUDP_DEVINFOBLOCK_PC GetDevBlock (const int index);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFLanDetector::operator []
		/// \brief    The same as GetDevBlock.
		///           
		/// \return   LPUDP_DEVINFOBLOCK_PC : a pointer.
		//-----------------------------------------------------------------------------
		LPUDP_DEVINFOBLOCK_PC operator[](const int index);


}

#if defined(__cplusplus)
}
#endif

#endif //RFLANDETECTOR_INCLUDE

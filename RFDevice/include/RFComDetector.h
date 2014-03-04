/********************************************************************
	modified:	2013/06/17
	created:	2013/03/25
	filename: 	RFLanDetector.h
	author:		RIFTEK, LLC
	
	purpose:	Ethernet device detector class

	>>>>>>>>>>>><<<<<<<<<<<<<<
	>>>  INTERNAL VERSION  <<<
	>>>>>>>>>>>><<<<<<<<<<<<<<

	>>> EXPERIMENTAL <<<

*********************************************************************/

#ifndef RFCOMDETECTOR_INCLUDE
#define RFCOMDETECTOR_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "RFDevice.h"
#include "RFDeviceDefs.h"

namespace RFDevice {

	class RFDEVICE_API RFComDetector
	{
	public:
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFComDetector::RFComDetector
		/// \brief    Default constructor of RFComDetector object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		RFComDetector(void);
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFComDetector::~RFComDetector
		/// \brief    Destructor of RFComDetector object.
		///           
		/// \return   void : N/A
		//-----------------------------------------------------------------------------
		~RFComDetector(void);

		//-----------------------------------------------------------------------------
		//  FUNCTION  RFComDetector::Search
		/// \brief    Performs scan for COM devices, address from 1 to ucMaxAddress=1..127, lpdwBaudRatesList is pointer to array of DWORD values of baud rates of nBaudRatesListLength length.
		///           
		/// \return   int : Number of detected devices.
		//-----------------------------------------------------------------------------
		int Search(BYTE ucMaxAddress, LPDWORD lpdwBaudRatesList, int nBaudRatesListLength);
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFComDetector::GetSize
		/// \brief    Returns the number of items in detected devices list.
		///           
		/// \return   int : number of items.
		//-----------------------------------------------------------------------------
		int GetSize();
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFComDetector::GetComDescriptor
		/// \brief    Returns a pointer to COM_DESCRIPTOR structure of device of specified index.
		///           
		/// \return   LPCOM_DESCRIPTOR : a pointer.
		//-----------------------------------------------------------------------------
		LPCOM_DESCRIPTOR GetComDescriptor (const int index);
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFComDetector::operator []
		/// \brief    The same as GetComDescriptor.
		///           
		/// \return   LPCOM_DESCRIPTOR : a pointer.
		//-----------------------------------------------------------------------------
		LPCOM_DESCRIPTOR operator[](const int index);

	protected:
		LPCOM_DESCRIPTOR m_existingPorts;
		LPCOM_DESCRIPTOR m_foundDevices;
		int m_nFoundDevices;

		int EnumSerialPorts();
		void ClearList(LPCOM_DESCRIPTOR p);
		BOOL TryDevice(LPCOM_DESCRIPTOR p, BYTE ucNetAddress, DWORD dwSpeed, LPBYTE lpucDeviceType);
		HANDLE OpenPort( LPCSTR lpPort_Name, DWORD dwSpeed );
		BOOL HelloCmd( HANDLE hCOM, BYTE bAddress, LPVOID lpHelloAnswer );
		BOOL ClosePort(HANDLE hCOM);
	};

}

#if defined(__cplusplus)
}
#endif

#endif //RFCOMDETECTOR_INCLUDE

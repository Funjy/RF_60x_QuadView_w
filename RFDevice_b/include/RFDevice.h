#ifndef RFDEVICE_INCLUDE
#define RFDEVICE_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#define RFDEVICE_API __declspec(dllexport)

#if defined _WIN32
#include <Windows.h>
#include <WinSock.h>
#elif defined __linux__
#include <pthread.h>
#include <sys/socket.h>
#else
#error "Unsupported platform"
#endif

namespace RFDevice {
	/************************************************************************/
	/* Initialize/Cleanup functions                                         */
	/************************************************************************/
	//-----------------------------------------------------------------------------
	//  FUNCTION  RFDevice::Initialize
	/// \brief    Global library initializations. Must be called once before using of most of library functions.
	///           
	/// \return   BOOL : TRUE on success, FALSE on error.
	//-----------------------------------------------------------------------------
	BOOL RFDEVICE_API Initialize(void);
	//-----------------------------------------------------------------------------
	//  FUNCTION  RFDevice::Cleanup
	/// \brief    Must be called once before application exit.
	///           
	/// \return   void
	//-----------------------------------------------------------------------------
	void RFDEVICE_API Cleanup(void);

	/************************************************************************/
	/* Return library version string										*/
	/************************************************************************/
	//-----------------------------------------------------------------------------
	//  FUNCTION  RFDevice::GetVersionString
	/// \brief    Returns library version string.
	///           
	/// \return   const char *
	//-----------------------------------------------------------------------------
	const char RFDEVICE_API *RFDevice_GetVersionString();

	/************************************************************************/
	/* RFDevice Base class                                                  */
	/************************************************************************/
	class RFDEVICE_API RFDeviceObject
	{
	public:
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFDeviceObject::RFDeviceObject
		/// \brief    This is constructor of base RFDeviceObject object
		///           
		/// \return   none
		//-----------------------------------------------------------------------------
		RFDeviceObject();
		//-----------------------------------------------------------------------------
		//  FUNCTION  RFDeviceObject::~RFDeviceObject
		/// \brief    This is destructor of base RFDeviceObject object
		///           
		/// \return   none
		//-----------------------------------------------------------------------------
		~RFDeviceObject();
	};

#if defined __linux__
	void InitializeCriticalSection(pthread_mutex_t* m);
	void EnterCriticalSection(pthread_mutex_t* m);
	void LeaveCriticalSection(pthread_mutex_t* m);
	void DeleteCriticalSection(pthread_mutex_t* m);
	#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
	int WSAStartup(WORD versionRequested, void* wsaData);
	void WSACleanup();
	#define SOCKET int
	#define closesocket close
#endif
}

#if defined(__cplusplus)
}
#endif

#endif //RFDEVICE_INCLUDE

#ifndef RFDEVICEDEFS_INCLUDE
#define RFDEVICEDEFS_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

namespace RFDevice {


	/************************************************************************/
	/* LAN Structures                                                       */
	/************************************************************************/
	//-----------------------------------------------------------------------------
	//  STRUCT  UDP_DEVINFOBLOCK_PC
	/// \brief    Structure to store LAN device related data collected during search.
	///           
	/// \return   none
	//-----------------------------------------------------------------------------
#pragma pack(push, 1)
	typedef struct _UDP_DEVINFOBLOCK_PC {
		WORD				usDeviceType;
		BYTE				ucIP[4];
		BYTE				ucMAC[6];
		BYTE				ucInfo[256];
		_UDP_DEVINFOBLOCK_PC  *		pNext;
	}  UDP_DEVINFOBLOCK_PC, *LPUDP_DEVINFOBLOCK_PC;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _UDP_DEVINFOBLOCK { 
		WORD				usDeviceType; 
		BYTE				ucIP[4]; 
		BYTE				ucMAC[6]; 
		BYTE				ucInfo[256]; 
	}  UDP_DEVINFOBLOCK, *LPUDP_DEVINFOBLOCK; 
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF_COMMAND_PACKET { 
		DWORD				ulCommand; 
		DWORD				ulAttachSize;
		DWORD				ulOffset;
		DWORD				ulSize;
	}  RF_COMMAND_PACKET, *LPRF_COMMAND_PACKET; 
#pragma pack(pop)

	/************************************************************************/
	/* RF620HS Structures                                                   */
	/************************************************************************/
#pragma pack(push, 1)
	typedef struct _RF620HS_INFO_
	{
		BYTE	ucCaps;					//	0
		BYTE	ucSerial[3];			//	3-1
		WORD	wBaseDistance;			//	5-4
		WORD	wMeasurementRange_Z;	//	7-6
		WORD	wMeasurementRange_X_SMR;//	9-8
		WORD	wMeasurementRange_X_EMR;//	11-10
		WORD	wDiscreteValue;			//	13-12
		WORD	wErrorValue;			//	15-14
		DWORD	dwFirmwareVersion;		//	19-16
		BYTE	ucLaserColor;			//  20
		BYTE	ucReserved[235];		//	255-21
		// additional params
		//DWORD	dwSerial;			<-- removed, must be 256 bytes long
	} RF620HS_INFO, *LPRF620HS_INFO;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF620HS_PARAMETERS_
	{
		BYTE	ucLaserLevel;			//	0
		WORD	wExposureTime;			//	2-1
		WORD	wProcessingTime;		//	4-3
		BYTE	ucWindowLeft;			//	5
		BYTE	ucWindowWidth;			//	6
		BYTE	ucWindowTop;			//	7
		BYTE	ucWindowHeight;			//	8
		BYTE	ucReserved1;			//	9
		short	sRotationAngle;			//	11-10
		WORD	wExtSyncSignal;			//	13-12
		BYTE	ucExtSyncDivider;		//	14
		BYTE	ucExtSyncDelay;			//	15
		BYTE	ucAnalogDotCount;		//	16
		BYTE	ucAnalogDotHold;		//	17
		BYTE	ucTCPAddress[4];			//	21-18
		BYTE	ucTCPSubnetMask[4];		//	25-22
		BYTE	ucUDPAddress[4];			//	29-26
		WORD	wUDPPort;				//	31-30
		BYTE	ucUDPFrequency;			//	32
		WORD	wTCPPort;				//	34-33
		BYTE	ucDHCP;					//	35
		BYTE	ucSyncInOutLine;		//	36
		BYTE	ucAutoExposure;			//	37
		BYTE	ucPixelBrightnessThres;	//	38
		BYTE	ucLegacyMode;			//	39
		BYTE	ucRawImageMode;			//	40
		BYTE	ucInterpolation;		//	41
		BYTE	ucModbusTcpEnabled;			//	42
		BYTE	ucModbusTcpAddr[4];		//	43
		WORD	wModbusTcpPort;			// 46
		BYTE	ucReserved2[463];		//	511-47
	} RF620HS_PARAMETERS, *LPRF620HS_PARAMETERS;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _con_DEBUG_REGISTERS_
	{
		unsigned short	PULSE[128];
		unsigned short  NUMBER_PIXEL;
		unsigned short  EXPOSURE;
	} con_DEBUG_REGISTERS, *LPcon_DEBUG_REGISTERS;                                            
#pragma pack(pop)

	//-----------------------------------------------------------------------------
	//  STRUCT  COM_DESCRIPTOR
	/// \brief    Structure to store COM device related data.
	///           
	/// \return   none
	//-----------------------------------------------------------------------------
	typedef struct _COM_DESCRIPTOR
	{
		char				szPort_Name[16];
		DWORD				dwSpeed;
		HANDLE				hCOM;
		BYTE				ucDeviceType;
		BYTE				ucNetAddress;
		_COM_DESCRIPTOR *	pNext;
	} COM_DESCRIPTOR, *LPCOM_DESCRIPTOR;

	typedef struct _RF60x_HANDLE_CONTEXT_
	{
		SOCKET 		sSendSocket;
		SOCKET 		sRecvSocket;
		sockaddr_in siRecvAddr;
		sockaddr_in siSendAddr;
		int			iSenderAddrSize;
	} RF60X_HANDLE_CONTEXT, *LPRF60X_HANDLE_CONTEXT;

#pragma pack(push, 1)
	typedef struct _RF60x_HELLO_ANSWER_
	{
		BYTE	bDeviceType;
		BYTE	bDeviceModificaton;
		WORD	wDeviceSerial;
		WORD	wDeviceMaxDistance;
		WORD	wDeviceRange;
	} RF60xHELLOANSWER, *LPRF60xHELLOANSWER;
#pragma pack(pop)

	typedef struct _RF60x_PARAMS_
	{
		BOOL	LaserIsOn;
		BOOL	AnalogOutIsOn;
		BYTE	SampleAveragingControlByte;
		BYTE	NetAddress;
		DWORD	BaundRate;
		DWORD	AverageCount;
		DWORD	SamplingPeriod;
		DWORD	AccumulationTime;
		DWORD	ResultDelayTime;
		DWORD	ZeroPoint;
		DWORD	CanSpeed;
		DWORD	CanStdID;
		DWORD	CanExtID;
		BOOL	CanIdIsExt;
		BOOL	CanIsOn;
		BYTE	DestinationIP[4];
		BYTE	GateWayIP[4];
		BYTE	SubnetMask[4];
		BYTE	SourceIP[4];
		BOOL	EthIsOn;
		DWORD	BeginAnalogRange;
		DWORD	EndAnalogRange;
	} RF60xPARAMS, *LPRF60xPARAMS;

	typedef struct _RF60x_STREAM_VALUE_
	{
		WORD	wMeasure;
		BYTE	bStatus;
	} RF60xSTREAMVALUE, *LPRF60xSTREAMVALUE;

#pragma pack(push, 1)
	typedef struct _RF60x_UDP_VALUE_
	{
		WORD	wMeasure;
		BYTE	bStatus;
	} RF60xUDPVALUE, *LPRF60xUDPVALUE;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60x_UDP_PACKET_
	{
		RF60xUDPVALUE	rf60xValArray[168];
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPackCount;
		BYTE	bPacketControlSumm;
	} RF60xUDPPACKET, *LPRF60xUDPPACKET;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60xB_UDP_VALUE_
	{
		WORD	wMeasure;
		WORD	wExposition;
		BYTE	bStatus;
	} RF60xBUDPVALUE, *LPRF60xBUDPVALUE;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF60xB_UDP_PACKET_
	{
		RF60xBUDPVALUE	rf60xBValArray[100];
		WORD	wReserved;
		WORD	wReserved2;
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPackCount;
		BYTE	bPacketControlSumm;
	} RF60xBUDPPACKET, *LPRF60xBUDPPACKET;
#pragma pack(pop)

	typedef struct _RF60xHS_MEASURE_BLOCK_
	{
		DWORD	dwMeasure;
		BYTE	bStatus;
	} RF60xHSMEASUREBLOCK, *LPRF60xHSMEASUREBLOCK;

#pragma pack(push, 1)
	typedef struct _RF60xHS_MEASURE_PACKET_
	{
		RF60xHSMEASUREBLOCK	rfbValues[100];
		WORD	wBlocksCount;
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPacketCount;
		BYTE	bPacketControlSumm;
		WORD	wServiceInfo;

	} RF60xHSMEASUREPACKET, *LPRF60xHSMEASUREPACKET;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF65x_HELLO_ANSWER_
	{
		BYTE	bDeviceType;
		BYTE	bDeviceModificaton;
		WORD	wDeviceSerial;
		WORD	wDeviceMaxDistance;
		WORD	wDeviceRange;
	} RF65xHELLOANSWER, *LPRF65xHELLOANSWER;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF65x_UDP_VALUE_
	{
		BYTE	bMeasure1;
		BYTE	bMeasure2;
		BYTE	bMeasure3;
		BYTE	bMeasure4;	
		//unsigned long	dwMeasure;
		BYTE	bStatus;
	} RF65xUDPVALUE, *LPRF65xUDPVALUE;
#pragma pack(pop)

#pragma pack(push, 1)
	typedef struct _RF65x_UDP_PACKET_
	{

		BYTE	bDeviceType;
		BYTE	bPOVersion;
		WORD	wDeviceSerial;
		WORD	wDeviceBaseDistance;
		WORD	wDeviceMeasureRange;
		BYTE	bPacketMeasureQuantity;
		BYTE	bPackCount;
		RF65xUDPVALUE	rf65xValArray[5];	

	} RF65xUDPPACKET, *LPRF65xUDPPACKET;
#pragma pack(pop)

	typedef struct _RF65x_PARAMS_
	{
		BOOL	MicrometerIsOn;
		BYTE	PriorityAndSyncroniseControlByte;	
		BYTE	NetAddress;
		DWORD	BaundRate;
		DWORD	AverageCount;
		DWORD	SamplingPeriod;
		DWORD	BeginAnalogRange;
		DWORD	EndAnalogRange;
		DWORD	NominalValue;
		BYTE	ResultAndBoundaryControlByte;
		DWORD	ControlledBoundariesNumbers;
		BYTE	LowLimitByte;
		BYTE	UpLimitByte;
		BYTE	OutLogicControllByte;	
		BYTE	SynchType;
		DWORD	RSSynch;
		DWORD	AveragingType;
		DWORD   ResultType;
		DWORD	ABoundaryNumber;
		DWORD	BBoundaryNumber;
		BOOL	AnalogSynch;
		DWORD    AnalogSynchNew;
		DWORD	ZeroPoint;
		DWORD	MinTolerance;
		DWORD	MaxTolerance;
		DWORD	EthSynch;
		DWORD	EthPackType;
		DWORD	EthPackMeasureQuantity;
		BYTE	EthDestinationtMAC[6];
		DWORD	SourceIP;
		DWORD   DestIP;
		DWORD	SubnetMask;
		DWORD	AnalogCalibrateLow;
		DWORD	AnalogCalibrateHigh;
		BYTE	Type;
		BYTE	Release;
		DWORD	BaseDist;
		DWORD	MeasureRange;


	} RF65xPARAMS, *LPRF65xPARAMS;

#pragma pack(push, 1)
	typedef struct _RF25x_HELLO_ANSWER_
	{
		BYTE	bDeviceType;
		BYTE	bDeviceModificaton;
		WORD	wDeviceSerial;
		WORD	wDeviceMaxDistance;
		WORD	wDeviceRange;
	} RF25xHELLOANSWER, *LPRF25xHELLOANSWER;
#pragma pack(pop)

	typedef struct _RF25x_PARAMS_
	{
		BOOL	SensorIsOn;	
		BYTE	SampleControlByte;
		BYTE	NetAddress;
		DWORD	BaundRate;
		DWORD	CoordStartPoint;
		DWORD	SamplingPeriod;
		DWORD	BeginAnalogRange;
		DWORD	EndAnalogRange;
		DWORD	AnalogOutScaling;
		DWORD	LowLimitOC;
		DWORD	UpLimitOC;
		DWORD	LogicOutPolarity;	
	} RF25XPARAMS, *LPRF25XPARAMS;

#pragma pack(push, 1)
	typedef struct _RFQDPMOTOR_HELLO_ANSWER_
	{
		BYTE	bDeviceType;
		WORD	wDeviceSerial;
	} RFQDPMOTORHELLOANSWER, *LPRFQDPMOTORHELLOANSWER;
#pragma pack(pop)

	typedef struct _RFQDPMOTOR_PARAMS_
	{
		BYTE	NetAddress;
		BYTE	SysSW;
		DWORD	dwBaundRate;
		WORD	wMaxSpeed;
		DWORD	dwSpeed;
		BYTE	ucAccel;
		WORD	wAlarmFlags;
		WORD	wACC;
		WORD	wDCC;
		WORD	wFullStepSpeed;
		BYTE	ucStepMode;
		DWORD	dwConfig;
		BOOL	bHold;
	} RFQDPMOTORPARAMS, *LPRFQDPMOTORPARAMS;

	typedef struct _RF085_PARAMETERS_
	{
		BYTE	OUT1;
		BYTE	OUT2;
		BYTE	OUT3;
		BYTE	OUT4;
		BYTE	OUT5;
		BYTE	OUT6;
		BYTE	LED1;
		BYTE	LED2;
		BYTE	LED3;
		BOOL	bIsMoving;
		BOOL	bAtHome;
		// params
		WORD	wSpeed;
		WORD	wACC;
		WORD	wDCC;
		WORD	wAlarm;
		WORD	wFSS;
	} RF085_PARAMETERS, *LPRF085_PARAMETERS;

#pragma pack(push,1)
	typedef struct _RF700_603PARAMS
	{
		unsigned short SerialNumber;
		unsigned short RangeValue;
	} RF700_603PARAMS, *LPRF700_603PARAMS;
#pragma pack(pop)
#pragma pack(push,1)
	typedef struct _RF700_PARAMETERS_
	{
		RF700_603PARAMS inner603Sensors[12];
		unsigned short innerTermoSN;
	} RF700_PARAMETERS, *LPRF700_PARAMETERS;
#pragma pack(pop)
#pragma pack(push,1)
	typedef struct _RF700_MEASURE_UDP_PACKET_
	{
		unsigned short measures[12];
	}	RF700MeasureUdpPacket, *LPRF700MeasureUdpPacket;
#pragma pack(pop)
}

#if defined(__cplusplus)
}
#endif

#endif //RFDEVICEDEFS_INCLUDE

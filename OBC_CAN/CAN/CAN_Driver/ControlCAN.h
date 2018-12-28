#ifndef CONTROLCAN_H
#define CONTROLCAN_H

////�ļ��汾��v2.00 20150920
//#include <cvidef.h>   //ʹ��CVIƽ̨��������ʹ�ø���䡣
#include <vcl.h>
/* ERROR Type */
#define DEVICE_INIT_OK  0
#define DLL_NOT_EXIST  1
#define DEVICE_OPEN_FAIL  2     /* Device not correct */
#define DEVICE_INITIAL_FAIL  3  /* Device correct, but channel not ok */
#define DEVICE_START_FAIL  4  /* Device correct, but channel not ok */

//�ӿڿ����Ͷ���

#define ZLG_DEVICE      0
#define ZHCX_DEVICE     1

#define VCI_USBCAN1     3
#define VCI_USBCAN2     4
#define VCI_USBCAN2A        4

#define VCI_USBCAN_E_U      20
#define VCI_USBCAN_2E_U     21



//�������÷���״ֵ̬
#define STATUS_OK                   1
#define STATUS_ERR                  0
    
/*------------------------------------------------����ZLG�ĺ�������������------------------------------------------------*/
//1.ZLGCANϵ�нӿڿ���Ϣ���������͡�
typedef  struct  _VCI_BOARD_INFO{
        USHORT  hw_Version;
        USHORT  fw_Version;
        USHORT  dr_Version;
        USHORT  in_Version;
        USHORT  irq_Num;
        BYTE    can_Num;
        CHAR    str_Serial_Num[20];
        CHAR    str_hw_Type[40];
        USHORT  Reserved[4];
} VCI_BOARD_INFO,*PVCI_BOARD_INFO; 

//2.����CAN��Ϣ֡���������͡�
typedef  struct  _VCI_CAN_OBJ{
    UINT    ID;
    UINT    TimeStamp;
    BYTE    TimeFlag;
    BYTE    SendType;
    BYTE    RemoteFlag;//�Ƿ���Զ��֡
    BYTE    ExternFlag;//�Ƿ�����չ֡
    BYTE    DataLen;
    BYTE    Data[8];
    BYTE    Reserved[3];
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

//3.�����ʼ��CAN����������
typedef struct _VCI_INIT_CONFIG{
    DWORD   AccCode;
    DWORD   AccMask;
    DWORD   Reserved;
    UCHAR   Filter;
    UCHAR   Timing0;    
    UCHAR   Timing1;    
    UCHAR   Mode;
}VCI_INIT_CONFIG,*PVCI_INIT_CONFIG;

///////// new add struct for filter /////////
typedef struct _VCI_FILTER_RECORD{
    DWORD ExtFrame; //�Ƿ�Ϊ��չ֡
    DWORD Start;
    DWORD End;
}VCI_FILTER_RECORD,*PVCI_FILTER_RECORD;

//#if 0
//#define EXTERNC     extern "C"
//
//EXTERNC DWORD __stdcall VCI_OpenDevice(DWORD DeviceType,DWORD DeviceInd,DWORD Reserved);
//EXTERNC DWORD __stdcall VCI_CloseDevice(DWORD DeviceType,DWORD DeviceInd);
//EXTERNC DWORD __stdcall VCI_InitCAN(DWORD DeviceType, DWORD DeviceInd, DWORD CANInd, PVCI_INIT_CONFIG pInitConfig);
//
//EXTERNC DWORD __stdcall VCI_ReadBoardInfo(DWORD DeviceType,DWORD DeviceInd,PVCI_BOARD_INFO pInfo);
//
//EXTERNC DWORD __stdcall VCI_SetReference(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,DWORD RefType,PVOID pData);
//
//EXTERNC ULONG __stdcall VCI_GetReceiveNum(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);
//EXTERNC DWORD __stdcall VCI_ClearBuffer(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);
//
//EXTERNC DWORD __stdcall VCI_StartCAN(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);
//EXTERNC DWORD __stdcall VCI_ResetCAN(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd);
//
//EXTERNC ULONG __stdcall VCI_Transmit(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_CAN_OBJ pSend,ULONG Len);
//EXTERNC ULONG __stdcall VCI_Receive(DWORD DeviceType,DWORD DeviceInd,DWORD CANInd,PVCI_CAN_OBJ pReceive,ULONG Len,INT WaitTime);
//#endif

/*------------------------------------------------�������亯�������ݽṹ����------------------------------------------------*/

//USB-CAN�����������忨��Ϣ����������1��������ΪVCI_FindUsbDevice�����ķ��ز�����
typedef  struct  _VCI_BOARD_INFO1{
    USHORT  hw_Version;
    USHORT  fw_Version;
    USHORT  dr_Version;
    USHORT  in_Version;
    USHORT  irq_Num;
    BYTE    can_Num;
    BYTE    Reserved;
    CHAR    str_Serial_Num[8];
    CHAR    str_hw_Type[16];
    CHAR    str_Usb_Serial[4][4];
} VCI_BOARD_INFO1,*PVCI_BOARD_INFO1;

//USB-CAN�����������忨��Ϣ����������2��������ΪVCI_FindUsbDevice�����ķ��ز�����Ϊ��չ������豸
typedef  struct  _VCI_BOARD_INFO2{
    USHORT  hw_Version;
    USHORT  fw_Version;
    USHORT  dr_Version;
    USHORT  in_Version;
    USHORT  irq_Num;
    BYTE    can_Num;
    BYTE    Reserved;
    CHAR    str_Serial_Num[8];
    CHAR    str_hw_Type[16];
    CHAR    str_Usb_Serial[10][4];
} VCI_BOARD_INFO2,*PVCI_BOARD_INFO2;

//���������Ϣ���������͡�    
typedef struct _ERR_INFO{     
    UINT	ErrCode;             //#if 0
    BYTE	Passive_ErrData[3];  //#define EXTERNC     extern "C"
    BYTE	ArLost_ErrData;      //
} VCI_ERR_INFO,*PVCI_ERR_INFO;

//����CAN������״̬���������͡�
typedef struct _VCI_CAN_STATUS{
    UCHAR	ErrInterrupt;
    UCHAR	regMode;
    UCHAR	regStatus;
    UCHAR	regALCapture;
    UCHAR	regECCapture;
    UCHAR	regEWLimit;
    UCHAR	regRECounter;
    UCHAR	regTECounter;
    DWORD	Reserved;
}VCI_CAN_STATUS,*PVCI_CAN_STATUS;

//���峣���������
typedef struct _REF_NORMAL{
    BYTE Mode;		 //����ģʽ
    BYTE Filter;		 //�˲���ʽ
    DWORD AccCode;		//�����˲�������
    DWORD AccMask;		//�����˲�������
    BYTE kBaudRate;		//�����������ţ�0-SelfDefine,1-5Kbps(δ��),2-18����Ϊ��10kbps,20kbps,40kbps,50kbps,80kbps,100kbps,125kbps,200kbps,250kbps,400kbps,500kbps,666kbps,800kbps,1000kbps,33.33kbps,66.66kbps,83.33kbps
    BYTE Timing0;
    BYTE Timing1;
    BYTE CANRX_EN;		//������δ��
    BYTE UARTBAUD;		//������δ��
}VCI_REF_NORMAL,*PVCI_REF_NORMAL;

//���岨�������ò�������
typedef struct _BAUD_TYPE{
    DWORD Baud;		//�洢������ʵ��ֵ
    BYTE SJW;		//ͬ����ת��ȣ�ȡֵ1-4
    BYTE BRP;		//Ԥ��Ƶֵ��ȡֵ1-64
    BYTE SAM;		//�����㣬ȡֵ0=����һ�Σ�1=��������
    BYTE PHSEG2_SEL;	//��λ�����2ѡ��λ��ȡֵ0=����λ�����1ʱ�����,1=�ɱ��
    BYTE PRSEG;		//����ʱ��Σ�ȡֵ1-8
    BYTE PHSEG1;		//��λ�����1��ȡֵ1-8
    BYTE PHSEG2;		//��λ�����2��ȡֵ1-8
}VCI_BAUD_TYPE,*PVCI_BAUD_TYPE;

//����Reference��������
typedef struct _REF_STRUCT{
    VCI_REF_NORMAL RefNormal;
    BYTE Reserved;
    VCI_BAUD_TYPE BaudType;
}VCI_REF_STRUCT,*PVCI_REF_STRUCT;

//EXTERNC DWORD __stdcall VCI_GetReference2(DWORD DevType,DWORD DevIndex,DWORD CANIndex,DWORD Reserved,BYTE *pData);
//EXTERNC DWORD __stdcall VCI_SetReference2(DWORD DevType,DWORD DevIndex,DWORD CANIndex,DWORD RefType,BYTE *pData);
//
//
//EXTERNC DWORD __stdcall VCI_ConnectDevice(DWORD DevType,DWORD DevIndex);
//EXTERNC DWORD __stdcall VCI_UsbDeviceReset(DWORD DevType,DWORD DevIndex,DWORD Reserved);
//EXTERNC DWORD __stdcall VCI_FindUsbDevice(PVCI_BOARD_INFO1 pInfo);
//EXTERNC DWORD __stdcall VCI_FindUsbDevice2(PVCI_BOARD_INFO2 pInfo);
//#endif

/* typedef CAN driver API function call */
typedef DWORD (CALLBACK*  LPVCI_OpenDevice)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_CloseDevice)(DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_InitCan)(DWORD,DWORD,DWORD,PVCI_INIT_CONFIG);

typedef DWORD (CALLBACK*  LPVCI_ReadBoardInfo)(DWORD,DWORD,PVCI_BOARD_INFO);
typedef DWORD (CALLBACK*  LPVCI_ReadErrInfo)(DWORD,DWORD,DWORD,PVCI_ERR_INFO);
typedef DWORD (CALLBACK*  LPVCI_ReadCanStatus)(DWORD,DWORD,DWORD,PVCI_CAN_STATUS);

typedef DWORD (CALLBACK*  LPVCI_GetReference)(DWORD,DWORD,DWORD,DWORD,PVOID);
typedef DWORD (CALLBACK*  LPVCI_SetReference)(DWORD,DWORD,DWORD,DWORD,PVOID);

typedef ULONG (CALLBACK*  LPVCI_GetReceiveNum)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_ClearBuffer)(DWORD,DWORD,DWORD);

typedef DWORD (CALLBACK*  LPVCI_StartCAN)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_ResetCAN)(DWORD,DWORD,DWORD);

typedef ULONG (CALLBACK*  LPVCI_Transmit)(DWORD,DWORD,DWORD,PVCI_CAN_OBJ,ULONG);
typedef ULONG (CALLBACK*  LPVCI_Receive)(DWORD,DWORD,DWORD,PVCI_CAN_OBJ,ULONG,INT);

typedef DWORD (CALLBACK*  LPVCI_GetReference2)(DWORD,DWORD,DWORD,DWORD,PVCI_REF_STRUCT);
typedef DWORD (CALLBACK*  LPVCI_SetReference2)(DWORD,DWORD,DWORD,DWORD,PVOID);
typedef DWORD (CALLBACK*  LPVCI_ResumeConfig)(DWORD,DWORD,DWORD);

typedef DWORD (CALLBACK*  LPVCI_ConnectDevice)(DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_UsbDeviceReset)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_FindUsbDevice)(PVCI_BOARD_INFO1);

#endif

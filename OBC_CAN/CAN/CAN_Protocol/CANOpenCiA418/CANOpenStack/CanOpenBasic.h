/******************************************************************************************************
*            CanOpenBasic.h
******************************************************************************************************
*
******************************************************************************************************
******************************************************************************************************
*    FILE NAME: CanOpenBasic.h
*
*    DESCRIPTION: Header file for task define
*
*    ORIGINATOR: DYH
*
*    DATE: 2018/5/24 21:48:19
*
*             Version   Author     Modification                                  Date
*    HISTORY:  V1.0      DYH       Initial Version based on can festival        2018/8/25 16:29:19
******************************************************************************************************/

#ifndef _CANOPENBASIC_H
#define _CANOPENBASIC_H

#ifdef __cplusplus
 extern "C" {
#endif
   
#include  <stdint.h>
#include "CAN_Portable.h"
#include "CanOpenState.h"
#include "CanOpenOdTypes.h"
#include "CanOpenConfig.h"

#ifndef NULL
#define NULL (0)
#endif

/* basic CANOPEN message */
typedef struct
{
    uint16_t cob_id;	/**< message's ID */
    uint8_t rtr;		/**< remote transmission request. (0 if not rtr message, 1 if rtr message) */
    uint8_t len;		/**< message's length (0 to 8) */
    uint8_t data[8]; /**< message's datas */
}stCanMessage_t;


/* CANOPEN struct to store data and state */
typedef struct
{
    uint32_t     NodeId;
    enNodeState NodeState;
    uint8_t     SlaveNodeFlag;
    uint8_t     SyncState;
    uint8_t     SyncTimeoutError;
    uint8_t     SyncWindowTime_ms;
    uint16_t    SyncCyclicTime_ms;
    uint16_t    SyncCyclicCounter_ms;
    
    uint16_t    HeartBeatTimer_ms;
    uint16_t    HeartBeatCounter_ms;
    
    uint8_t     ReceivePdoFlag;
    uint8_t     NextPDOIndex;
    
    uint8_t     CanBusActiveFlag;
    uint16_t     CanFrameCnt;
    uint8_t     BigEndianFlag;
}stCanOpenDate_t;

extern stCanOpenDate_t stCanOpenDate;


typedef struct
{
    uint16_t NodeId: 7;
    uint16_t StartTimeout: 1;

    uint16_t DeviceProfile: 8;

    uint16_t WaitCounter: 16;
}stNodeDeviceProfile_t;
extern stNodeDeviceProfile_t stNodeDeviceProfile[MAX_CAN_NODE];

/*  Function Codes
   ---------------
  defined in the canopen DS301
*/
#define NMT        (uint16_t)0//0x0u
#define SYNC       (uint16_t)1//0x1u
#define TIME_STAMP (uint16_t)2//0x2u
#define PDO1tx     (uint16_t)3//0x3u
#define PDO1rx     (uint16_t)4//0x4u
#define PDO2tx     (uint16_t)5//0x5u
#define PDO2rx     (uint16_t)6//0x6u
#define PDO3tx     (uint16_t)7//0x7u
#define PDO3rx     (uint16_t)8//0x8u
#define PDO4tx     (uint16_t)9//0x9u
#define PDO4rx     (uint16_t)10//0xAu
#define SDOtx      (uint16_t)11//0xBu
#define SDOrx      (uint16_t)12//0xCu
#define NODE_GUARD (uint16_t)14//0xEu
#define LSS        (uint16_t)15//0xFu

#define GET_NODE_ID(m)         (uint16_t(m.cob_id) & 0x7f)
#define GET_FUNCTION_CODE(m)   (uint16_t(m.cob_id) >> 7)


/* NMT Command Specifier, sent by master to change a slave state */
/* ------------------------------------------------------------- */
/* Should not be modified */
#define NMT_Start_Node              0x01
#define NMT_Stop_Node               0x02
#define NMT_Enter_PreOperational    0x80
#define NMT_Reset_Node              0x81
#define NMT_Reset_Comunication      0x82

/** Status of the SDO transmission
 */
#define SDO_RESET                0x0      /* Transmission not started. Init state. */
#define SDO_FINISHED             0x1      /* data are available */                          
#define	SDO_ABORTED_RCV          0x80     /* Received an abort message. Data not available */
#define	SDO_ABORTED_INTERNAL     0x85     /* Aborted but not because of an abort message. */
#define	SDO_DOWNLOAD_IN_PROGRESS 0x2 
#define	SDO_UPLOAD_IN_PROGRESS   0x3   
#define	SDO_BLOCK_DOWNLOAD_IN_PROGRESS 0x4 
#define	SDO_BLOCK_UPLOAD_IN_PROGRESS   0x5

/** getReadResultNetworkDict may return any of above status value or this one
 */
#define SDO_PROVIDED_BUFFER_TOO_SMALL   0x8A

/* Status of the node during the SDO transfert : */
#define SDO_SERVER  0x1
#define SDO_CLIENT  0x2
#define SDO_UNKNOWN 0x3             

/* SDOrx ccs: client command specifier */
#define DOWNLOAD_SEGMENT_REQUEST     0
#define INITIATE_DOWNLOAD_REQUEST    1
#define INITIATE_UPLOAD_REQUEST      2
#define UPLOAD_SEGMENT_REQUEST       3
#define ABORT_TRANSFER_REQUEST       4
#define BLOCK_UPLOAD_REQUEST         5
#define BLOCK_DOWNLOAD_REQUEST       6

/* SDOtx scs: server command specifier */
#define UPLOAD_SEGMENT_RESPONSE      0
#define DOWNLOAD_SEGMENT_RESPONSE    1
#define INITIATE_DOWNLOAD_RESPONSE   3
#define INITIATE_UPLOAD_RESPONSE     2
#define ABORT_TRANSFER_REQUEST       4
#define BLOCK_DOWNLOAD_RESPONSE    	 5
#define BLOCK_UPLOAD_RESPONSE        6

/* SDO block upload client subcommand */
#define SDO_BCS_INITIATE_UPLOAD_REQUEST 0
#define SDO_BCS_END_UPLOAD_REQUEST      1
#define SDO_BCS_UPLOAD_RESPONSE         2
#define SDO_BCS_START_UPLOAD            3

/* SDO block upload server subcommand */
#define SDO_BSS_INITIATE_UPLOAD_RESPONSE 0
#define SDO_BSS_END_UPLOAD_RESPONSE      1

/* SDO block download client subcommand */
#define SDO_BCS_INITIATE_DOWNLOAD_REQUEST 0
#define SDO_BCS_END_DOWNLOAD_REQUEST      1

/* SDO block download server subcommand */
#define SDO_BSS_INITIATE_DOWNLOAD_RESPONSE 0
#define SDO_BSS_END_DOWNLOAD_RESPONSE      1
#define SDO_BSS_DOWNLOAD_RESPONSE          2

/* Expedited SDO protocol */
#define EXP_WRITE_ONE_BYTE      0x2F
#define EXP_WRITE_TWO_BYTE      0x2B
#define EXP_WRITE_THREE_BYTE    0x27
#define EXP_WRITE_FOUR_BYTE     0x23
#define EXP_WRITE_ACK           0x60

#define EXP_READ                0x40
#define EXP_READ_ONE_BYTE       0x4F
#define EXP_READ_TWO_BYTE       0x4B
#define EXP_READ_THREE_BYTE     0x47
#define EXP_READE_FOUR_BYTE     0x43
#define EXP_CMD_NACK            0x80


/* sync parameter and setup */
#define SYNC_START    1u
#define SYNC_STOP     0u

/* portable functions prototype */
extern void CAN_TxHandlerTask(void *parameter);
extern void CAN_RxHandlerTask(void* parameter);
extern uint8_t CAN_RequestSend(stCanMessage_t *m);

/* total handler function prototype in CanOpenBasic.c file */
extern uint8_t CanOpenInitial(void);
extern uint8_t CanOpenRxCmdHandler(stCanMessage_t *pCmd);
extern uint8_t CanOpenTimerDispatch(uint16_t callPeriod);

/* Lifeguard function prototype */
extern void HeardBeatInitial(void);
extern void HeardBeatStop(void);
extern void HeartBeatHandler(uint16_t callPeriod);
extern void HeardBeatClearCounter(void);

/* Nmt function prototype */
extern void ChangeNmtState(uint8_t nmtCs, uint8_t nodeId);
extern void ProcessNmtCommand(uint8_t nmtCs);

/* SDO functions prototype */
extern void PollingNodeDeviceProfileType(void);
extern void SDOInitial(void);
extern void SDOCyclicHandler(uint16_t callPeriod);
extern void ProceedExpSdoRxData(stCanMessage_t *pMsg);

/* OD read / write API */
extern uint8_t ReadOdMap(uint16_t OdIndex, uint8_t SubIndex, uint8_t* plength, uint8_t *pdata);
extern uint8_t WriteOdMap(uint16_t OdIndex, uint8_t SubIndex, uint8_t length, uint8_t *pdata);


/* PDO */
extern void SendPdoData(void);
extern void SaveRxPDO1(uint8_t *pData);
extern void SaveRxPDO2(uint8_t *pData);
extern void SaveRxPDO3(uint8_t *pData);

/* SYNC APIs  */
extern void SyncInitial(void);
extern void ProcessSyncData(uint8_t counter);


#ifdef __cplusplus
}
#endif
#endif

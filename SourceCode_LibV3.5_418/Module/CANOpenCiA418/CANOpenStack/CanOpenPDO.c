/******************************************************************************************************
*            CanOpenPDO.c
******************************************************************************************************
*
*
******************************************************************************************************
******************************************************************************************************
*    FILE NAME: CanOpenPDO.c
*
*    DESCRIPTION: CANOPEN protocol handler APIs
*
*    ORIGINATOR: DYH
*
*    DATE: 2018/5/10 22:34:20
*
*             Version   Author     Modification                            Date
*    HISTORY:  V1.0      DYH       Initial Version                       2018/10/11 20:29:25
******************************************************************************************************/
#include "CanOpenBasic.h"

/*********************************************************************************
* Global Functions
*********************************************************************************/


/*******************************************************************************
* Macros
*******************************************************************************/


/*******************************************************************************
* Data Struct Define
*******************************************************************************/

/*******************************************************************************
* Local Variables
*******************************************************************************/

void PDOInitial(void)
{
    stCanOpenDate.NextPDOIndex = 0;
}



/****************************************************************************
*
*  Function: SendPdoData
*
*  Purpose :    Send PDO when receive sync message
*
*  Parms Passed   :   Nothing
*
*  Returns        :   Nothing
*
*  Description    :
*
****************************************************************************/
void SendPdoData(void)
{
    stCanMessage_t PdoMsg = {0};
    
    /* only support standard CAN ID */
    uint32_t u32ReadData = 0;
    uint16_t u16ReadData = 0;
    uint8_t  ReadLength = 0;

    
    PdoMsg.len = (uint8_t)0x08;
    PdoMsg.rtr = 0;

    if(stCanOpenDate.NextPDOIndex++ >= MAX_PDO_NUM)
    {
        stCanOpenDate.NextPDOIndex = 0;

        if(stCanOpenDate.NextPDOIndex == 0) 
        /* get TPDO COB-ID */
        ReadLength = 2;
        ReadOdMap(0x1800 + utCanOpenDate.NextPDOIndex , 0x01, &ReadLength, (uint8_t *)&ReadData);
        PdoMsg.cob_id = (uint16_t)(ReadData & 0xffff) + MY_NODE_ID;
        
        /* Build up CAN data filed 
           TODO: read parameter from OD later, currently use default value*/
        ReadLength = 2;
        ReadOdMap(0x6010 , 0x01, &ReadLength, &u16ReadData);
        PdoMsg.data[0] = (uint8_t)(u16ReadData & 0x00ff);
        PdoMsg.data[1] = (uint8_t)(u16ReadData >> 8);
        
        ReadLength = 1;
        ReadOdMap(0x6000 , 0x01, &ReadLength, &PdoMsg.data[2]);
        
        CAN_RequestSend(&PdoMsg);
    }
}
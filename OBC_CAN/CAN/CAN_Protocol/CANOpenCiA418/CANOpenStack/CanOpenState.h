/******************************************************************************************************
*            CanOpenState.h
******************************************************************************************************
*
******************************************************************************************************
******************************************************************************************************
*    FILE NAME: CanOpenState.h
*
*    DESCRIPTION: Header file for task define
*
*    ORIGINATOR: DYH
*
*    DATE: 2018/5/24 21:48:19
*
*             Version   Author     Modification                            Date
*    HISTORY:  V1.0      DYH       Initial Version                      2018/5/24 21:48:23
******************************************************************************************************/

#ifndef _CANOPENSTATE_H
#define _CANOPENSTATE_H

#ifdef __cplusplus
 extern "C" {
#endif
/**********************************************************************************************
* Macros
**********************************************************************************************/


typedef enum
{
    Initialisation  = 0x00, 
    Disconnected    = 0x01,
    Connecting      = 0x02,
    Preparing       = 0x02,
    Stopped         = 0x04,
    Operational     = 0x05,
    Pre_operational = 0x7F,
    Unknown_state   = 0x0F
}enNodeState;

/**********************************************************************************************
* Global Functions
**********************************************************************************************/
extern void StateInitial(void);
extern enNodeState GetNodeState(void);
extern void SetNodeState(enNodeState NewState);

#ifdef __cplusplus
 }
#endif
#endif

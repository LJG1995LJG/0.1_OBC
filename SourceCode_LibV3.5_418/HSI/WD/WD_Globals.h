/******************************************************************************************************
*            WD_Globals.h
******************************************************************************************************
*
******************************************************************************************************
******************************************************************************************************
*    FILE NAME: PWM_Globals.h
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

#ifndef _WD_GLOBALS_H
#define _WD_GLOBALS_H

#include "stm32f10x_iwdg.h"
/**********************************************************************************************
* Macros
**********************************************************************************************/
#define WD_RELOAD_CNT 1562

/**********************************************************************************************
* Global Functions
**********************************************************************************************/
extern void WD_Initial(void);
extern void WD_FeedDog(void);
#endif

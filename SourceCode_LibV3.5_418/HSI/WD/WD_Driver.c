/******************************************************************************************************
*            WD_Driver.c
******************************************************************************************************
*
*
******************************************************************************************************
******************************************************************************************************
*    FILE NAME: WD_Driver.c
*
*    DESCRIPTION: Define task related API, array, etc
*
*    ORIGINATOR: DYH
*
*    DATE: 2018/5/24 21:51:20
*
*             Version   Author     Modification                            Date
*    HISTORY:  V1.0      DYH       Initial Version                       2018/5/24 21:51:24
******************************************************************************************************/

#include "WD_Globals.h"


/*********************************************************************************
* Global Functions
*********************************************************************************/

/*********************************************************************************
* Task Call back Functions
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


/****************************************************************************
*
*  Function: WD_Initial
*
*  Purpose :    Initial watchdog setting
*
*  Parms Passed   :   Nothing
*
*  Returns        :   Nothing
*
*  Description    :   
*
****************************************************************************/
void WD_Initial(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    IWDG_SetReload(WD_RELOAD_CNT); // about 10s
    IWDG_ReloadCounter();
    IWDG_Enable();
}



/****************************************************************************
*
*  Function: WD_FeedDog
*
*  Purpose :    Feed watch dog
*
*  Parms Passed   :   None
*
*  Returns        :   Nothing
*
*  Description    :   
*
****************************************************************************/
void WD_FeedDog(void)
{
    IWDG_ReloadCounter();
}

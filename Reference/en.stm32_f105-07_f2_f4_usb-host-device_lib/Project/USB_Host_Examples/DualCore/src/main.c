/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V2.2.1
  * @date    17-March-2018
  * @brief   USB host Dual Core demo main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      <http://www.st.com/SLA0044>
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include "dual_core_demo.h"

/** @addtogroup USBH_USER
* @{
*/

/** @defgroup USBH_USR_MAIN
* @brief This file is the USB host Dual Core demo main file
* @{
*/

/** @defgroup USBH_USR_MAIN_Private_TypesDefinitions
* @{
*/
/**
* @}
*/

/** @defgroup USBH_USR_MAIN_Private_Defines
* @{
*/
/**
* @}
*/


/** @defgroup USBH_USR_MAIN_Private_Macros
* @{
*/
/**
* @}
*/


/** @defgroup USBH_USR_MAIN_Private_Variables
* @{
*/

/**
* @}
*/


/** @defgroup USBH_USR_MAIN_Private_FunctionPrototypes
* @{
*/
/**
* @}
*/


/** @defgroup USBH_USR_MAIN_Private_Functions
* @{
*/

/**
* @brief Main routine for MSC/HID class application
* @param  None
* @retval int
*/
int main(void)
{
  __IO uint32_t i = 0;

  /* !< At this stage the microcontroller clock setting is already configured,
   * this is done through SystemInit() function which is called from startup
   * file (startup_stm32fxxx_xx.s) before to branch to application main. To
   * reconfigure the default setting of SystemInit() function, refer to
   * system_stm32fxxx.c file */

  Demo_Init();

  while (1)
  {

    Demo_Process();

    if (i++ == 0x10000)
    {
      STM_EVAL_LEDToggle(LED1);
      STM_EVAL_LEDToggle(LED2);
      STM_EVAL_LEDToggle(LED3);
      STM_EVAL_LEDToggle(LED4);
      i = 0;
    }
  }
}


#ifdef USE_FULL_ASSERT
/**
* @brief  assert_failed
*         Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  File: pointer to the source file name
* @param  Line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t * file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line
   * number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
   * * line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

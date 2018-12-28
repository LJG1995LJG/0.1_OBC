/******************************************************************************************************
*            UART_Driver.c
******************************************************************************************************
*
*
******************************************************************************************************
******************************************************************************************************
*    FILE NAME: UART_Driver.c
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
#include <string.h>
#include "UART_Globals.h"
#include "stm32f10x_gpio.h"
#include "SM_CommonApi.h"

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
uint8_t USART_RxDataBuffer[4] = {0};

/****************************************************************************
*
*  Function: UART_Initial
*
*  Purpose :    Initial USART module
*
*  Parms Passed   :   Nothing
*
*  Returns        :   Nothing
*
*  Description    :
*
****************************************************************************/

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/**
  * @brief  ?a??GPIOA,��??��1����?��
  * @param  None
  * @retval None
  * @note  ??����?3D?GPIO��?��???��??�䨮?1|?��?����?2??a??��t��?����?����?��?1?��?��??�䨮?1|?����???
           ��3��?��??��D����a?a???�䨮?����?��
  */
void USART_RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//?a?�䨮?����?��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_USART1,ENABLE);
}

/**
  * @brief  ����??��??��1����?����??����?��y??��??�꨺?
  * @param  None
  * @retval None
  */
void USART_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;

    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE );
}

/**
  * @brief  ????��??��1��?2�騺1?����??��1
  * @param  None
  * @retval None
  */
void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStruct;

    USART_RCC_Configuration();

    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStruct);
    //	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//��1?��?����??D??
    USART_Cmd(USART1, ENABLE);//��1?����??��1

    USART_GPIO_Configuration();

    USART_SendData(USART1,'T');
    printf("\x0c\0");printf("\x0c\0");//3??????????��
    printf("\033[1;40;32m");//����??3???????��3?��?ao����?��?��?��??a?����?
    printf("\r\n*******************************************************************************");
    printf("\r\n************************          UART Initial OK      ************************");
    printf("\r\n*******************************************************************************");
    printf("\r\n");
}



//2?��1��?��??��?��?�꨺?
#if 1 //��?1???��D?a??��??��D����a?��target?????D????��1��?USE microLIB
//#pragma import(__use_no_semihosting)
//struct __FILE
//{
//    int handle;
//};
FILE __stdout;

void _sys_exit(int x)
{
    x = x;
}
#endif


PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART1,(u8)ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return ch;
}

void USART_RxDataPolling(void)
{
    static uint8_t USART_RxIndex = 0;
    static uint16_t Timeout = 0;

    uint8_t data = 0;
    if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
    {
      data = USART_ReceiveData(USART1);
      if((data != '\r') && (data != '\n'))
      {
      USART_RxDataBuffer[USART_RxIndex] = data;
        USART_RxIndex++;
      }

    }


    if(USART_RxIndex)
    {
        if(Timeout++ >= 2000)
        {
            Timeout = 0;
            memset(&USART_RxDataBuffer[0], 0, sizeof(USART_RxDataBuffer));
        }
    }
    if(USART_RxIndex >= 4)
    {
        if(   (USART_RxDataBuffer[0] == 'c') || (USART_RxDataBuffer[1] == 'm')
           || (USART_RxDataBuffer[2] == 'd')  )
        {
            switch(USART_RxDataBuffer[3])
            {
                case '0':
                    stSystemStateBits.ForceStayInInit = 1;
                    break;

                case '1':
                    stSystemStateBits.ForceStayInInit = 0;
                    break;

                case '2':
                    stSystemStateBits.EnterFCT = 1;
                    break;

                case '3':
                    stSystemStateBits.EnterFCT = 0;
                    break;

                default:
                    break;
            }
        }

        USART_RxIndex = 0;
        memset(&USART_RxDataBuffer[0], 0, sizeof(USART_RxDataBuffer));
    }
}
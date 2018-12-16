/******************************************************************************************************
*            PWM_Driver.c
******************************************************************************************************
*
*
******************************************************************************************************
******************************************************************************************************
*    FILE NAME: PWM_Driver.c
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

#include "PWM_Globals.h"


/*********************************************************************************
* Global Functions
*********************************************************************************/
void PWM_IRefUpdate(uint16_t dutyX10);
void PWM_URefUpdate(uint16_t dutyX10);
uint16_t PWM_GetPwmDuty(uint8_t PwmChannel);

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
*  Function: PWM_Initial
*
*  Purpose :    Initial PWM setting
*
*  Parms Passed   :   Nothing
*
*  Returns        :   Nothing
*
*  Description    :   
*
****************************************************************************/
void PWM_Initial(void)
{
    TIM_TimeBaseInitTypeDef	TIM_TimeBaseInitdata;	 //��������
    TIM_OCInitTypeDef TIM_OCInitStructure;	 //PWM���,
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	 //����tim4��clk,
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4,ENABLE);	 //ͨ����Ӧλ����ʹTim4�Ĵ�����λ,
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4,DISABLE);	//�˳���λ, 
    
    TIM_TimeBaseInitdata.TIM_Prescaler = 0x0;	 //����tim��Ԥ��Ƶϵ��=0,72MȫƵ,
    TIM_TimeBaseInitdata.TIM_ClockDivision = TIM_CKD_DIV1;	 //����tim��ʱ�ӷ�Ƶ����,Tdts=n*Tck_int,
    TIM_TimeBaseInitdata.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���,
    TIM_TimeBaseInitdata.TIM_Period = PWM_VAL_MAX;	 //����tim���Զ�����,13λ�ֱ���Լ7.5K,
    TIM_TimeBaseInitdata.TIM_RepetitionCounter = 0x00;	 //������tim1&tim8,
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitdata);
    TIM_ARRPreloadConfig(TIM4,ENABLE);	 //����Tim2��������ARR�Զ����ػ���,
    
    //----Tim4��CHx_PWM�ĳ�ʼ������,-----------------------------------------------
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;	 //����OC1M[2:0]Ϊpwm1���ģʽ,OC1REF="1"Ϊ��Ч,
    TIM_OCInitStructure.TIM_Pulse=0x1fff;	 //����ռ�ձ�ʱ��,ֵ���Զ�д��CCR1,
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;	 //�����������,CCER��CC1Pλ,ʵ��1=OC1REF����Ч��ƽ,
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	 //ʹ�ܸ�ͨ�����,CCER��CC1Eλ,
    
    //----�߼���ʱ�����еĲ���,----------------------------------------------------
    TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset;	 //����/�������״̬=0,Timx_CR2��OISx,ֻ��Tim1/8��,
    TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;	 //����/�������״̬=0,Timx_CR2��OISxN,ֻ��Tim1/8��,
    TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;	 //���û������������,CCER��CC1NPλ,
    TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;	//�޻��������,CCER��CC1NEλ,
    
    //----����ָ��������ʼ��TIM_OC1~4,
    TIM_OC3Init(TIM4,&TIM_OCInitStructure);	 //����ָ��������ʼ��TIM_OC3,
    TIM_OC3FastConfig(TIM4,TIM_OCFast_Enable); //�����������ģʽ,3����,
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIM2��CCR3�ϵ�Ԥװ�ؼĴ���,CCMR2_OC3PE=1,
    TIM_OC4Init(TIM4,&TIM_OCInitStructure);	 //����ָ��������ʼ��TIM_OC4,
    TIM_OC4FastConfig(TIM4,TIM_OCFast_Enable); //�����������ģʽ,3����,
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIM2��CCR4�ϵ�Ԥװ�ؼĴ���,CCMR2_OC4PE=1,
    
    //----��ʱ������-----------------------
    TIM_ITConfig(TIM4, TIM_IT_Update,DISABLE); //���ж�,
    TIM_ClearFlag(TIM4, TIM_FLAG_Update); //�������������ʱ������ĸ��±�־,
    TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��,
    
    //PWM_URefUpdate(200);
    //PWM_IRefUpdate(500);
}



/****************************************************************************
*
*  Function: PWM_Initial
*
*  Purpose :    Initial PWM setting
*
*  Parms Passed   :   dutyX10: e.g: 500 means 50%
*
*  Returns        :   Nothing
*
*  Description    :   
*
****************************************************************************/
void PWM_IRefUpdate(uint16_t dutyX10)
{
    uint16_t newCompareVal = 0;
    
    if(dutyX10 != 0)
    {
        newCompareVal = dutyX10 * PWM_CNT_0_1_DUTY;
        
        if(newCompareVal > PWM_VAL_MAX)
        {
            newCompareVal = PWM_VAL_MAX;
        }
        TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��,
        TIM_SetCompare3(TIM4, newCompareVal);
    }
    else
    {
        TIM_SetCompare3(TIM4, 0);
        TIM_Cmd(TIM4, DISABLE); //ʹ�ܶ�ʱ��,
    }
}


/****************************************************************************
*
*  Function: PWM_Initial
*
*  Purpose :    Initial PWM setting
*
*  Parms Passed   :   dutyX10: e.g: 500 means 50%
*
*  Returns        :   Nothing
*
*  Description    :   
*
****************************************************************************/
void PWM_URefUpdate(uint16_t dutyX10)
{
    uint16_t newCompareVal = 0;
    
    if(dutyX10 != 0)
    {
        newCompareVal = dutyX10 * PWM_CNT_0_1_DUTY;
        
        if(newCompareVal > PWM_VAL_MAX)
        {
            newCompareVal = PWM_VAL_MAX;
        }
        TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��,
        TIM_SetCompare4(TIM4, newCompareVal);
    }
    else
    {
        TIM_SetCompare4(TIM4, 0);
        TIM_Cmd(TIM4, DISABLE); //ʹ�ܶ�ʱ��,
    }
}
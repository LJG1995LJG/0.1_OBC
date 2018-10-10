/****************************************************************
 Copyright (C),2014-2016,SZZKJ Technology
 File name:		lcd.c
 Author:		WangFeng
 Version:		1.00
 Date:			2014-11-8
 Description:	
 
 Others:		
 
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 History
 ----------------------------------------------------------------
 Index:			1
 Date:			2014-11-8
 Author:		WangFeng
 Modification:	Create this file
****************************************************************/
/*Include files -----------------------------------------------*/
#include "lcd.h"
#include "spi.h"
#include "stm32f10x_gpio.h"


/*Defines -----------------------------------------------------*/


#define CD_LOW()		GPIOA->BRR = GPIO_Pin_7			
#define CD_HIGH()		GPIOA->BSRR = GPIO_Pin_7
#define CD_INIT()		{PORTAbits.RA7 = 1;TRISAbits.TRISA7=0;}
#define RES_LOW()		GPIOB->BRR = GPIO_Pin_5
#define RES_HIGH()		GPIOB->BSRR = GPIO_Pin_5
#define RES_INIT()		{PORTBbits.RB5 = 1;TRISBbits.TRISB5=0;}
#define _nop_()			SPI_Dly()
#define CLR_WDT()		IWDG_ReloadCounter()

/*Extern data & funtion----------------------------------------*/

/*Global data -------------------------------------------------*/
BYTE LcdPartIndex = LCD_PART_LEFT;
BYTE LcdData[LCD_DATA_Y_MAX][LCD_DATA_X_MAX>>1];
BYTE Curve;

BYTE ContrastLevel= 0x02;
/*datas & funcitons define area -------------------------------*/


//-----------------------------------
// delayms routine
//-----------------------------------
void delayms(U16 m)        // 12MHz Xtal, close to ms value
{
    WORD j;
    WORD i;
    
    for(i=0; i<m; i++)
    {
		if (!(i%2000))
		{
			CLR_WDT();
		}
        for(j=0; j<10000; j++)
            _nop_();
    }
}

//-----------------------------------
// ����ͨѶ��ʽ��������
//-----------------------------------
  void SdCmd(U8 Command)
        {
          SPI_SCK_HIGH();                   // ��ʼ��SCLK
          _nop_();
           CD_LOW();                    // ѡ��ָ��ͨ��
           SPI_CHN_LCD_CE_LOW();                   // ѡͨģ��
           _nop_();
          if((Command&0x80)==0x80){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();
		  if((Command&0x40)==0x40){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();
		  if((Command&0x20)==0x20){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH(); 
          _nop_();
		  if((Command&0x10)==0x10){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();
          _nop_();
		  if((Command&0x08)==0x08){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();
          _nop_();
		  if((Command&0x04)==0x04){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();   
          _nop_();
		  if((Command&0x02)==0x02){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();
		  if((Command&0x01)==0x01){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
			_nop_();
		  SPI_CHN_LCD_CE_HIGH();                      // ����ģ��
       }
//-----��ʾ����д�뺯��----------------------------
void SdData(U8 DData)
      {
          SPI_SCK_HIGH();                   // ��ʼ��SCLK
          _nop_();
          CD_HIGH();                    // ѡ������ͨ��
          SPI_CHN_LCD_CE_LOW();                    // ѡͨģ��
          _nop_();
          if((DData&0x80)==0x80){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();if((DData&0x40)==0x40){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();if((DData&0x20)==0x20){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();if((DData&0x10)==0x10){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();if((DData&0x08)==0x08){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();if((DData&0x04)==0x04){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();   
          _nop_();if((DData&0x02)==0x02){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
          _nop_();if((DData&0x01)==0x01){SPI_SDO_HIGH();}else{SPI_SDO_LOW();}SPI_SCK_LOW();_nop_();SPI_SCK_HIGH();  
		  _nop_();
		  SPI_CHN_LCD_CE_HIGH();                      // ����ģ��
      }

/*Functions ---------------------------------------------------*/
/****************************************************************
* Function:		
* Description:	
* Input:		
* Output:		
* Return:		
* Other:		
****************************************************************/
void LcdIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	//CD_INIT();
	//RES_INIT();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	 /*!< Configure PC.08, PC.09, PC.10, PC.11, PC.12 pin: D0, D1, D2, D3, CLK pin */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);

	return;
}

/****************************************************************
* Function:		
* Description:	
* Input:		
* Output:		
* Return:		
* Other:		
****************************************************************/
void LcdInit(void)
{
	LcdIOInit();
	RES_LOW(); delayms(200);   //Ӳ����λ
    RES_HIGH(); delayms(200);  //��λ���ӳ�800ms����ʱ��
   // ContrastLevel=0x05;    
   //ContrastLevel ++;
    SdCmd(0x25);                                // �����¶Ȳ���ϵ��-0.05%/C
    SdCmd(0x2b);                                // �ڲ�DC-DC
	SdCmd(0xc4);                                // LCDӳ��MY=1��MX=0��LC0=0  c4
	SdCmd(0xa0);                                // ������ɨ��Ƶ��  fr=76.34hz a1
	SdCmd(0xd1);                                // ��ɫ���ݸ�ʽR-G-B  d1
	SdCmd(0xd5);								// ��������λΪ12λRRRR-GGGG-BBBB
	SdCmd(0xc8); SdCmd(0x00);                   // ����M�ź�Ϊ19�з�ת 11
	SdCmd(0xeb);                                // ����ƫѹ��1/12
	SdCmd(0xa6);                                // ������ʾ
	SdCmd(0xa4);                                // ������ʾ
	SdCmd(0x81); SdCmd(0x25/*ContrastLevel*/);          //���öԱȶ�bf
	SdCmd(0xd8);                                // ����ɨ��ģʽd8

    SdCmd(0xf1);SdCmd(147);     //������CEN,159
    SdCmd(0xf2);SdCmd(20);     //��ʼDST
    SdCmd(0xf3);SdCmd(147);     //����DEN
	SdCmd(0x85); 
	LcdClr();
	SdCmd(0xad);   delayms(100);                // ����ʾad
	return;
}

/****************************************************************
* Function:		
* Description:	
* Input:		
* Output:		
* Return:		
* Other:		
****************************************************************/
void LcdClr(void)
{
	UINT p; 
   U8 i,j,k,m,Ddata,x,y;
   x=24;                                  // ��ʼ�е�ַƫ��������
   y=0;                                  // ��ʼ�е�ַƫ��������
   SdCmd(0xf4); SdCmd(x);                   // ���ò���������߽�
   SdCmd(0xf5); SdCmd(y+20);                        // ���ò��������ϱ߽� 
   SdCmd(0xf6); SdCmd(x+240/3-1);             // ���ò��������ұ߽�
   SdCmd(0xf7); SdCmd(y+20+128-1);                   // ���ò��������±߽�
   SdCmd(0xf8);		                    		 // ���ô��ڲ���ʹ��
   SdCmd(x&0x0f);SdCmd(0x10|(x>>4));             // ������ʼ�е�ַ

   SdCmd(0x60+(y&0x0f)); SdCmd(0x70+(y>>4));     // ������ʼ�е�ַ
   //p=0;                                          // ����ָ���ʼ��
   for(i=0;i<128;i++)                           // ѭ����������
     {
	 for ( j=0;j<240/8;j++)                    // ѭ���ֽ���/��
	     {
          //k=pData[p++];                            // ȡͼ������
          for (m=0;m<4;m++)                      // 1�ֽ�ת����4���ֽ�����д��
              {
    	       /*switch (k&0xc0)                   // ��������λֵ������ʾɫ����
                   {
		            case 0x00 : Ddata=0x00;break;
		            case 0x40 : Ddata=0x0f;break;
		            case 0x80 : Ddata=0xf0;break;
		            case 0xc0 : Ddata=0xff;break;
		           }*/
              SdData(0x00);                      // д������
		      //k=k<<2;
		      }
       }

  }
	return;
}

void LcdSet(void)
{
	UINT p; 
   U8 i,j,k,m,Ddata,x,y;
   x=24;                                  // ��ʼ�е�ַƫ��������
   y=0;                                  // ��ʼ�е�ַƫ��������
   SdCmd(0xf4); SdCmd(x);                   // ���ò���������߽�
   SdCmd(0xf5); SdCmd(y+20);                        // ���ò��������ϱ߽� 
   SdCmd(0xf6); SdCmd(x+240/3-1);             // ���ò��������ұ߽�
   SdCmd(0xf7); SdCmd(y+20+128-1);                   // ���ò��������±߽�
   SdCmd(0xf8);		                    		 // ���ô��ڲ���ʹ��
   SdCmd(x&0x0f);SdCmd(0x10|(x>>4));             // ������ʼ�е�ַ

   SdCmd(0x60+(y&0x0f)); SdCmd(0x70+(y>>4));     // ������ʼ�е�ַ
   //p=0;                                          // ����ָ���ʼ��
   for(i=0;i<128;i++)                           // ѭ����������
     {
	 for ( j=0;j<240/8;j++)                    // ѭ���ֽ���/��
	     {
          //k=pData[p++];                            // ȡͼ������
          for (m=0;m<4;m++)                      // 1�ֽ�ת����4���ֽ�����д��
              {
    	       /*switch (k&0xc0)                   // ��������λֵ������ʾɫ����
                   {
		            case 0x00 : Ddata=0x00;break;
		            case 0x40 : Ddata=0x0f;break;
		            case 0x80 : Ddata=0xf0;break;
		            case 0xc0 : Ddata=0xff;break;
		           }*/
              SdData(0xff);                      // д������
		      //k=k<<2;
		      }
       }

  }
	return;
}



/****************************************************************
* Function:		
* Description:	
* Input:		
* Output:		
* Return:		
* Other:		
****************************************************************/
void LcdRefresh(WORD x, WORD y, WORD cx, WORD cy, BYTE *pData)
{
	// ����XΪ�����п�0-79�п飬3���ص�����/�п�
// ����YΪ���ص�����0-159
// ͼ�ο��widthΪˮƽ�����������Ҫ���ֵΪ6�ı���
// ͼ�θ߶�highΪ��ֱ�����������ȡֵΪ0-159
// ͼ������bmp[]Ϊ��Ҫд���ͼ�����ݣ���1bpp��8dots/byte)��ˮƽ���и�ʽ��ʾ


   UINT p; 
   U8 i,j,k,m,Ddata;



   x = x/3;
   x=x+24;                                  // ��ʼ�е�ַƫ��������
   y=y;                                  // ��ʼ�е�ַƫ��������
   SdCmd(0xf4); SdCmd(x);                   // ���ò���������߽�
   SdCmd(0xf5); SdCmd(y + 20);                        // ���ò��������ϱ߽� 
   SdCmd(0xf6); SdCmd(x+cx/3-1);             // ���ò��������ұ߽�
   SdCmd(0xf7); SdCmd(y+ 20 + cy-1);                   // ���ò��������±߽�
   SdCmd(0xf8);		                    		 // ���ô��ڲ���ʹ��
   SdCmd(x&0x0f);SdCmd(0x10|(x>>4));             // ������ʼ�е�ַ

   SdCmd(0x60+(y&0x0f)); SdCmd(0x70+(y>>4));     // ������ʼ�е�ַ


   
   p=cx/8;  p*=cy;  p --;                                      // ����ָ���ʼ��
   for(i=0;i<cy;i++)                           // ѭ����������
     {
	 	//p=cx*(cy - i) - 1;
		//p = cx/8;
		//p*=(cy-i);
		//p--;
	 for ( j=0;j<cx/8;j++)                    // ѭ���ֽ���/��
	     {
          k=pData[p--];                            // ȡͼ������
          for (m=0;m<4;m++)                      // 1�ֽ�ת����4���ֽ�����д��
              {
    	       switch (k&0x03)                   // ��������λֵ������ʾɫ����
                   {
		            case 0x00 : Ddata=0x00;break;
		            case 0x01 : Ddata=0xf0;break;
		            case 0x02 : Ddata=0x0f;break;
		            case 0x03 : Ddata=0xff;break;
		           }
              SdData(Ddata);                      // д������
		      k=k>>2;
		      }
       }

  }
   
}

/* end of file */



/****************************************************************
 Copyright (C),2014-2016,SZZKJ Technology
 File name:     display.c
 Author:        WangFeng
 Version:       1.00
 Date:          2014-11-8
 Description:   
 
 Others:        
 
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 History
 ----------------------------------------------------------------
 Index:         1
 Date:          2014-11-8
 Author:        WangFeng
 Modification:  Create this file
****************************************************************/
/*Include files -----------------------------------------------*/

#include "lcd.h"
#include "db.h"
#include "ctrl.h"
#include "display.h"


/*Defines -----------------------------------------------------*/
#define S16 short
#define DWORD unsigned long
#define UINT unsigned int

#define DISPLAY_MENU_LVL0       0
#define DISPLAY_MENU_LVL1       1
#define DISPLAY_MENU_LVL2       2

#define DISPLAY_ML0_IDX_XXX     0


    
#define DISPLAY_T_CO_MARK_LEN   3
#define DISPLAY_U_CO_MARK_LEN   3
#define DISPLAY_I_CO_MARK_LEN   3
#define DISPLAY_U_I_CO_OFFSET   7
#define DISPLAY_T_CO_OFFSET     7

#define DISPLAY_AREA_WIDTH      (LCD_CX >> 1)
#define DISPLAY_AREA_HEIGHT     (LCD_CY - 16)
#define DISPLAY_U_CO_OFFSET     DISPLAY_U_I_CO_OFFSET
#define DISPLAY_I_CO_OFFSET     (DISPLAY_AREA_WIDTH - 1 - DISPLAY_U_I_CO_OFFSET)

#define DISPLAY_CURVE_WIDTH     (DISPLAY_AREA_WIDTH - 2*DISPLAY_U_I_CO_OFFSET)
#define DISPLAY_CURVE_HEIGHT    (DISPLAY_AREA_HEIGHT - DISPLAY_T_CO_OFFSET)

/*
:.0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
*/
typedef enum {
    SPACE = 0,
    SYM_MINUS,
    SYM_DASH,
    SYM_COLON,
    SYM_PERIOD,
    DIG_0,
    DIG_1,
    DIG_2,
    DIG_3,
    DIG_4,
    DIG_5,
    DIG_6,
    DIG_7,
    DIG_8,
    DIG_9,
    ALPH_A,
    ALPH_B,
    ALPH_C,
    ALPH_D,
    ALPH_E,
    ALPH_F,
    ALPH_G,
    ALPH_H,
    ALPH_I,
    ALPH_J,
    ALPH_K,
    ALPH_L,
    ALPH_M,
    ALPH_N,
    ALPH_O,
    ALPH_P,
    ALPH_Q,
    ALPH_R,
    ALPH_S,
    ALPH_T,
    ALPH_U,
    ALPH_V,
    ALPH_W,
    ALPH_X,
    ALPH_Y,
    ALPH_Z,
    ALPH_a,
    ALPH_b,
    ALPH_c,
    ALPH_d,
    ALPH_e,
    ALPH_f,
    ALPH_g,
    ALPH_h,
    ALPH_i,
    ALPH_j,
    ALPH_k,
    ALPH_l,
    ALPH_m,
    ALPH_n,
    ALPH_o,
    ALPH_p,
    ALPH_q,
    ALPH_r,
    ALPH_s,
    ALPH_t,
    ALPH_u,
    ALPH_v,
    ALPH_w,
    ALPH_x,
    ALPH_y,
    ALPH_z,
    FONT_DIG_ALPH_MAX
        
} FONT_DIG_ALPH_T;


/*
深圳宇杰达机型电压流时间容量曲线
*/
typedef enum {
    CHR_SHEN = 0,
    CHR_ZHEN,
    CHR_YU,
    CHR_JIE,
    CHR_DA,
    CHR_JI,
    CHR_XING,
    CHR_DIAN,
    CHR_YA,
    CHR_LIU,
    CHR_SHI,
    CHR_JIAN,
    CHR_RONG,
    CHR_LIANG,
    CHR_QU,
    CHR_XIAN,
    FONT_CHINESE_MAX
} FONT_CHINESE_T;

/*Extern data & funtion----------------------------------------*/
extern ConfigData_t stSelConfigData;

/*Global data -------------------------------------------------*/
BYTE byMenuLevel = 0;
BYTE byMenuL0CurIndex = 0;
BYTE byMenuL1CurIndex = 0;
BYTE byMenuL2CurIndex = 0;

U8 byMID = MID_TOP;
U16 wdML1Offset = 0;
U16 wdML1OffsetMax = 0;
U16 wdML1OffsetSel = 0xffff; /* 0xffff 表示未选定 */
U16 wdML2CfgOffset = 0;
U16 wdML2CfgOffsetMax = 0;
U16 wdML2CfgOffsetSel = 0xffff; /* 0xffff 表示未选定 */
U16 wdML2ChgOffset = 0;
U16 wdML2ChgOffsetMax = 0;
U16 wdML2ChgOffsetSel = 0xffff; /* 0xffff 表示未选定 */

/*datas & funcitons define area -------------------------------*/
S16 CurX = 0;
S16 CurY = 0;
BYTE byLineWidth = 1;
WORD wdCoTimeMin = 0;
WORD wdCoTimeScale = 1;
BYTE wdCoTimeMarkSpace = 8;
WORD wdCoUMin = 0;
WORD wdCoUMax = 0;
BYTE wdCoUMarkSpace = 8;
WORD wdCoUScale = 1;
BYTE wdCoIMarkSpace = 8;
WORD wdCoIMin = 0;
WORD wdCoIMax = 0;
WORD wdCoIScale = 1;

//DWORD dwdCurT = 0;
BYTE byDispNum = 0;

U16 CurveTMin = 0;
U16 CurveTMax = 0;
U16 CurveUMin = 0;
U16 CurveUMax = 0;
U16 CurveIMin = 0;
U16 CurveIMax = 0;
U16 UnitT = 1;
U16 UnitU = 1;
U16 UnitI = 1;

S16 TMarkSpace = 20;
S16 UMarkSpace = 20;
S16 IMarkSpace = 20;
U32 dwdDispUITCnt = 0;
U16 wdDispCurUITFileInex = 0;
INT iDispCurErr = 0;

U32 dwdDispChgTmLen = 0;
U32 dwdDispChgCapacity = 0;
//ConfigData_t stDispCfgData;





WORD CurveUBuf[DISPLAY_CURVE_WIDTH];
WORD CurveIBuf[DISPLAY_CURVE_WIDTH];

const BYTE abyCfgCurveUBuf[CCE_MAX][100] =
{
    {
        10,14,18,21,24,27,30,33,36,38,40,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,
        58,59,60,61,62,63,64,64,65,65,65,66,66,66,67,67,67,68,68,69,70,71,72,73,75,75,75,
        75,76,76,76,76,76,76,76,77,77,77,77,77,77,77,78,78,78,78,78,78,79,79,79,79,79,79,
        80,80,80,80,80,80,80,70,70,70,70,70,70,70,70,70,70,70,70
    },
    {
        10,15,20,24,28,31,34,37,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,
        70,70,71,71,71,72,72,72,72,73,73,73,73,74,74,74,74,75,75,75,75,76,76,76,76,77,77,
        77,77,77,77,77,77,78,78,78,78,78,78,78,78,78,79,79,79,79,79,79,79,79,79,79,80,80,
        80,80,80,80,80,80,80,70,70,70,70,70,70,70,70,70,70,70,70
    },
    {
        10,15,20,24,28,31,34,37,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,75,
        75,76,76,76,76,77,77,77,77,77,78,78,78,78,78,79,79,79,79,79,80,80,80,80,81,81,82,
        82,83,83,84,84,84,85,85,85,86,86,86,86,86,87,87,87,87,87,88,88,88,88,88,89,89,89,
        89,89,89,90,90,90,90,70,70,70,70,70,70,70,70,70,70,70,70
    },
    {
        10,15,20,25,30,34,38,42,46,50,53,56,59,62,66,70,72,75,70,71,72,72,73,73,74,74,75,
        75,75,76,76,76,76,77,77,77,77,77,78,78,78,78,78,78,78,79,79,79,79,79,79,79,79,79,
        79,79,79,79,79,80,80,80,80,80,80,80,80,82,83,84,84,85,85,85,86,86,86,87,87,88,88,
        88,89,89,89,90,90,90,70,70,70,70,70,70,70,70,70,70,70,70
    }
};

const BYTE abyCfgCurveIBuf[CCE_MAX][100] =
{
    {
        80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,
        80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,79,74,
        69,64,59,55,51,47,43,40,37,34,31,29,27,25,23,21,19,17,16,15,14,14,13,13,13,12,12,
        12,12,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,10
    },
    {
        80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,
        60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,57,53,
        50,47,44,41,38,36,34,32,30,28,26,24,22,20,18,17,16,15,15,14,14,14,13,13,13,12,12,
        12,12,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,10
    },
    {
        80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,
        78,76,72,68,64,59,55,51,48,45,42,39,36,33,28,26,24,22,20,18,17,17,16,16,15,15,15,
        15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
        15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10
    },
    {
        80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,60,60,60,60,60,60,60,60,60,
        60,60,60,60,60,60,60,60,60,60,60,57,53,50,47,44,41,38,36,34,32,30,28,26,25,24,23,
        22,21,20,19,19,18,18,17,17,17,16,16,16,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
        15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10
    }
};


const BYTE aBitMask[8] = 
{
    //0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80
    0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
};

const BYTE abyFontDigAlph[FONT_DIG_ALPH_MAX][16] = 
{
/*    (0)  -(0) _(1) :(2) .(2) 0(3) 1(4) 2(5) 3(6) 4(7) 5(8) 6(9) 7(10) 8(11) 9(12) a(13) b(14) c(15)
 d(16) e(17) f(18) g(19) h(20) i(21) j(22) k(23) l(24) m(25) n(26) o(27) p(28) q(29) r(30) s(31)
 t(32) u(33) v(34) w(35) x(36) y(37) z(38) A(39) B(40) C(41) D(42) E(43) F(44) G(45) H(46) I(47)
 J(48) K(49) L(50) M(51) N(52) O(53) P(54) Q(55) R(56) S(57) T(58) U(59) V(60) W(61) X(62) Y(63)
 Z(64)
*/
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
    
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"-",0*/
    
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},/*"_",1*/
    
    {0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00},/*":",2*/
    
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00},/*".",2*/
    
    {0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00},/*"0",3*/
    
    {0x00,0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00},/*"1",4*/
    
    {0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x04,0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00},/*"2",5*/
    
    {0x00,0x00,0x00,0x3C,0x42,0x42,0x04,0x18,0x04,0x02,0x02,0x42,0x44,0x38,0x00,0x00},/*"3",6*/
    
    {0x00,0x00,0x00,0x04,0x0C,0x14,0x24,0x24,0x44,0x44,0x7E,0x04,0x04,0x1E,0x00,0x00},/*"4",7*/
    
    {0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x58,0x64,0x02,0x02,0x42,0x44,0x38,0x00,0x00},/*"5",8*/
    
    {0x00,0x00,0x00,0x1C,0x24,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x24,0x18,0x00,0x00},/*"6",9*/
    
    {0x00,0x00,0x00,0x7E,0x44,0x44,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00},/*"7",10*/
    
    {0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00},/*"8",11*/
    
    {0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x26,0x1A,0x02,0x02,0x24,0x38,0x00,0x00},/*"9",12*/
    
    {0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00},/*"A",39*/
    
    {0x00,0x00,0x00,0xF8,0x44,0x44,0x44,0x78,0x44,0x42,0x42,0x42,0x44,0xF8,0x00,0x00},/*"B",40*/
    
    {0x00,0x00,0x00,0x3E,0x42,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x44,0x38,0x00,0x00},/*"C",41*/
    
    {0x00,0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00},/*"D",42*/
    
    {0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x42,0x42,0xFC,0x00,0x00},/*"E",43*/
    
    {0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x40,0x40,0xE0,0x00,0x00},/*"F",44*/
    
    {0x00,0x00,0x00,0x3C,0x44,0x44,0x80,0x80,0x80,0x8E,0x84,0x44,0x44,0x38,0x00,0x00},/*"G",45*/
    
    {0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"H",46*/
    
    {0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00},/*"I",47*/
    
    {0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0xF0},/*"J",48*/
    
    {0x00,0x00,0x00,0xEE,0x44,0x48,0x50,0x70,0x50,0x48,0x48,0x44,0x44,0xEE,0x00,0x00},/*"K",49*/
    
    {0x00,0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0xFE,0x00,0x00},/*"L",50*/
    
    {0x00,0x00,0x00,0xEE,0x6C,0x6C,0x6C,0x6C,0x54,0x54,0x54,0x54,0x54,0xD6,0x00,0x00},/*"M",51*/
    
    {0x00,0x00,0x00,0xC7,0x62,0x62,0x52,0x52,0x4A,0x4A,0x4A,0x46,0x46,0xE2,0x00,0x00},/*"N",52*/
    
    {0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00},/*"O",53*/
    
    {0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0xE0,0x00,0x00},/*"P",54*/
    
    {0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0xB2,0xCA,0x4C,0x38,0x06,0x00},/*"Q",55*/
    
    {0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x48,0x48,0x44,0x44,0x42,0xE3,0x00,0x00},/*"R",56*/
    
    {0x00,0x00,0x00,0x3E,0x42,0x42,0x40,0x20,0x18,0x04,0x02,0x42,0x42,0x7C,0x00,0x00},/*"S",57*/
    
    {0x00,0x00,0x00,0xFE,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00},/*"T",58*/
    
    {0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00},/*"U",59*/
    
    {0x00,0x00,0x00,0xE7,0x42,0x42,0x44,0x24,0x24,0x28,0x28,0x18,0x10,0x10,0x00,0x00},/*"V",60*/
    
    {0x00,0x00,0x00,0xD6,0x92,0x92,0x92,0x92,0xAA,0xAA,0x6C,0x44,0x44,0x44,0x00,0x00},/*"W",61*/
    
    {0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00},/*"X",62*/
    
    {0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00},/*"Y",63*/
    
    {0x00,0x00,0x00,0x7E,0x84,0x04,0x08,0x08,0x10,0x20,0x20,0x42,0x42,0xFC,0x00,0x00},/*"Z",64*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x1E,0x22,0x42,0x42,0x3F,0x00,0x00},/*"a",13*/

    {0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x00,0x00},/*"b",14*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x40,0x40,0x40,0x22,0x1C,0x00,0x00},/*"c",15*/

    {0x00,0x00,0x00,0x06,0x02,0x02,0x02,0x1E,0x22,0x42,0x42,0x42,0x26,0x1B,0x00,0x00},/*"d",16*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x40,0x40,0x42,0x3C,0x00,0x00},/*"e",17*/

    {0x00,0x00,0x00,0x0F,0x11,0x10,0x10,0x7E,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00},/*"f",18*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x44,0x44,0x38,0x40,0x3C,0x42,0x42,0x3C},/*"g",19*/

    {0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"h",20*/

    {0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00},/*"i",21*/

    {0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x1C,0x04,0x04,0x04,0x04,0x04,0x04,0x44,0x78},/*"j",22*/

    {0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x4E,0x48,0x50,0x68,0x48,0x44,0xEE,0x00,0x00},/*"k",23*/

    {0x00,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00},/*"l",24*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x49,0x49,0x49,0x49,0x49,0xED,0x00,0x00},/*"m",25*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDC,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"n",26*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00},/*"o",27*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD8,0x64,0x42,0x42,0x42,0x44,0x78,0x40,0xE0},/*"p",28*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x22,0x42,0x42,0x42,0x22,0x1E,0x02,0x07},/*"q",29*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x32,0x20,0x20,0x20,0x20,0xF8,0x00,0x00},/*"r",30*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x40,0x3C,0x02,0x42,0x7C,0x00,0x00},/*"s",31*/

    {0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x0C,0x00,0x00},/*"t",32*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00},/*"u",33*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x28,0x10,0x10,0x00,0x00},/*"v",34*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD7,0x92,0x92,0xAA,0xAA,0x44,0x44,0x00,0x00},/*"w",35*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6E,0x24,0x18,0x18,0x18,0x24,0x76,0x00,0x00},/*"x",36*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x28,0x18,0x10,0x10,0xE0},/*"y",37*/

    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x44,0x08,0x10,0x10,0x22,0x7E,0x00,0x00},/*"z",38*/


};

const BYTE FontChinese[FONT_CHINESE_MAX][32] = 
{
    /*
     深(0) 圳(1) 宇(2) 杰(3) 达(4) 机(5) 型(6) 电(7) 压(8) 流(9) 时(10) 间(11) 容(12) 量(13) 曲(14) 线(15)
    
    */
#if 0

{0x00,0x00,0xE4,0x3F,0x28,0x20,0x28,0x25,0x81,0x08,0x42,0x10,0x02,0x02,0x08,0x02,0xE8,0x3F,0x04,0x02,0x07,0x07,0x84,0x0A,0x44,0x12,0x34,0x62,0x04,0x02,0x00,0x02},/*"深",0*/

{0x88,0x20,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0xBF,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0xB8,0x24,0x87,0x24,0x42,0x24,0x40,0x20,0x20,0x20},/*"圳",1*/

{0x40,0x00,0x80,0x00,0xFE,0x7F,0x02,0x40,0x01,0x20,0xFC,0x1F,0x80,0x00,0x80,0x00,0x80,0x00,0xFF,0x7F,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0xA0,0x00,0x40,0x00},/*"宇",2*/

{0x80,0x00,0x80,0x00,0x80,0x00,0xFE,0x3F,0xC0,0x01,0xA0,0x02,0x90,0x04,0x88,0x08,0x84,0x10,0x83,0x60,0x80,0x00,0x00,0x00,0x24,0x11,0x44,0x22,0x42,0x22,0x01,0x20},/*"杰",3*/

{0x00,0x02,0x04,0x02,0x08,0x02,0x08,0x02,0xE0,0x7F,0x00,0x02,0x0F,0x02,0x08,0x05,0x08,0x09,0x88,0x10,0x48,0x20,0x28,0x20,0x08,0x00,0x14,0x00,0xE2,0x7F,0x00,0x00},/*"达",4*/

{0x08,0x00,0x88,0x0F,0x88,0x08,0x88,0x08,0xBF,0x08,0x88,0x08,0x8C,0x08,0x9C,0x08,0xAA,0x08,0xAA,0x08,0x89,0x08,0x88,0x48,0x88,0x48,0x48,0x48,0x48,0x70,0x28,0x00},/*"机",5*/

{0x00,0x20,0xFE,0x21,0x48,0x24,0x48,0x24,0x48,0x24,0xFF,0x25,0x48,0x24,0x44,0x20,0x44,0x28,0x82,0x10,0x81,0x00,0xFC,0x1F,0x80,0x00,0x80,0x00,0xFF,0x7F,0x00,0x00},/*"型",6*/

{0x80,0x00,0x80,0x00,0x80,0x00,0xFC,0x1F,0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,0x84,0x10,0x84,0x10,0x84,0x10,0xFC,0x1F,0x84,0x50,0x80,0x40,0x80,0x40,0x00,0x7F},/*"电",7*/

{0x00,0x00,0xFC,0x7F,0x04,0x00,0x04,0x01,0x04,0x01,0x04,0x01,0x04,0x01,0xF4,0x3F,0x04,0x01,0x04,0x01,0x04,0x09,0x04,0x11,0x04,0x11,0x02,0x01,0xFA,0x7F,0x01,0x00},/*"压",8*/

{0x00,0x01,0x04,0x02,0xE8,0x7F,0x08,0x01,0x81,0x08,0x42,0x10,0xE2,0x3F,0x08,0x20,0x08,0x00,0x44,0x12,0x47,0x12,0x44,0x12,0x44,0x12,0x44,0x52,0x24,0x52,0x10,0x62},/*"流",9*/

{0x00,0x10,0x00,0x10,0x3E,0x10,0x22,0x10,0xA2,0x7F,0x22,0x10,0x22,0x10,0x3E,0x10,0x22,0x11,0x22,0x12,0x22,0x12,0x22,0x10,0x3E,0x10,0x22,0x10,0x00,0x14,0x00,0x08},/*"时",10*/

{0x04,0x00,0xC8,0x3F,0x08,0x20,0x02,0x20,0xE2,0x23,0x22,0x22,0x22,0x22,0x22,0x22,0xE2,0x23,0x22,0x22,0x22,0x22,0x22,0x22,0xE2,0x23,0x02,0x20,0x02,0x28,0x02,0x10},/*"间",11*/

{0x40,0x00,0x80,0x00,0xFE,0x7F,0x02,0x40,0x11,0x24,0x88,0x08,0x44,0x11,0x20,0x02,0x10,0x04,0x0C,0x18,0xFB,0x6F,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0x0F,0x08,0x08},/*"容",12*/

{0x00,0x00,0xF8,0x0F,0x08,0x08,0xF8,0x0F,0x08,0x08,0xFF,0x7F,0x00,0x00,0xF8,0x0F,0x88,0x08,0xF8,0x0F,0x88,0x08,0xF8,0x0F,0x80,0x00,0xF8,0x0F,0x80,0x00,0xFE,0x3F},/*"量",13*/

{0x20,0x02,0x20,0x02,0x20,0x02,0x20,0x02,0xFE,0x3F,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0xFE,0x3F,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0xFE,0x3F,0x02,0x20},/*"曲",14*/

{0x08,0x0A,0x08,0x12,0x04,0x02,0x24,0x3A,0xA2,0x07,0x1F,0x02,0x08,0x7A,0xC4,0x07,0x02,0x22,0x3F,0x12,0x02,0x0C,0x00,0x44,0x38,0x4A,0x07,0x51,0xC2,0x60,0x00,0x40},/*"线",15*/

#else
        {0x00,0x00,0x27,0xFC,0x14,0x04,0x14,0xA4,0x81,0x10,0x42,0x08,0x40,0x40,0x10,0x40,0x17,0xFC,0x20,0x40,0xE0,0xE0,0x21,0x50,0x22,0x48,0x2C,0x46,0x20,0x40,0x00,0x40},/*"深",0*/
        
        {0x11,0x04,0x11,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0xFD,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x1D,0x24,0xE1,0x24,0x42,0x24,0x02,0x04,0x04,0x04},/*"圳",1*/
        
        {0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x80,0x04,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},/*"宇",2*/
        
        {0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFC,0x03,0x80,0x05,0x40,0x09,0x20,0x11,0x10,0x21,0x08,0xC1,0x06,0x01,0x00,0x00,0x00,0x24,0x88,0x22,0x44,0x42,0x44,0x80,0x04},/*"杰",3*/
        
        {0x00,0x40,0x20,0x40,0x10,0x40,0x10,0x40,0x07,0xFE,0x00,0x40,0xF0,0x40,0x10,0xA0,0x10,0x90,0x11,0x08,0x12,0x04,0x14,0x04,0x10,0x00,0x28,0x00,0x47,0xFE,0x00,0x00},/*"达",4*/
        
        {0x10,0x00,0x11,0xF0,0x11,0x10,0x11,0x10,0xFD,0x10,0x11,0x10,0x31,0x10,0x39,0x10,0x55,0x10,0x55,0x10,0x91,0x10,0x11,0x12,0x11,0x12,0x12,0x12,0x12,0x0E,0x14,0x00},/*"机",5*/
        
        {0x00,0x04,0x7F,0x84,0x12,0x24,0x12,0x24,0x12,0x24,0xFF,0xA4,0x12,0x24,0x22,0x04,0x22,0x14,0x41,0x08,0x81,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0xFF,0xFE,0x00,0x00},/*"型",6*/
        
        {0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x0A,0x01,0x02,0x01,0x02,0x00,0xFE},/*"电",7*/
        
        {0x00,0x00,0x3F,0xFE,0x20,0x00,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x2F,0xFC,0x20,0x80,0x20,0x80,0x20,0x90,0x20,0x88,0x20,0x88,0x40,0x80,0x5F,0xFE,0x80,0x00},/*"压",8*/
        
        {0x00,0x80,0x20,0x40,0x17,0xFE,0x10,0x80,0x81,0x10,0x42,0x08,0x47,0xFC,0x10,0x04,0x10,0x00,0x22,0x48,0xE2,0x48,0x22,0x48,0x22,0x48,0x22,0x4A,0x24,0x4A,0x08,0x46},/*"流",9*/
        
        {0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08,0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10},/*"时",10*/
        
        {0x20,0x00,0x13,0xFC,0x10,0x04,0x40,0x04,0x47,0xC4,0x44,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x44,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x40,0x04,0x40,0x14,0x40,0x08},/*"间",11*/
        
        {0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x88,0x24,0x11,0x10,0x22,0x88,0x04,0x40,0x08,0x20,0x30,0x18,0xDF,0xF6,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10},/*"容",12*/
        
        {0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0xFF,0xFE,0x00,0x00,0x1F,0xF0,0x11,0x10,0x1F,0xF0,0x11,0x10,0x1F,0xF0,0x01,0x00,0x1F,0xF0,0x01,0x00,0x7F,0xFC},/*"量",13*/
        
        {0x04,0x40,0x04,0x40,0x04,0x40,0x04,0x40,0x7F,0xFC,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x7F,0xFC,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x7F,0xFC,0x40,0x04},/*"曲",14*/
        
        {0x10,0x50,0x10,0x48,0x20,0x40,0x24,0x5C,0x45,0xE0,0xF8,0x40,0x10,0x5E,0x23,0xE0,0x40,0x44,0xFC,0x48,0x40,0x30,0x00,0x22,0x1C,0x52,0xE0,0x8A,0x43,0x06,0x00,0x02},/*"线",15*/
#endif
};


const BYTE abyFontT2B5x7[18][5] =
{
//(0) A(1) V(2) M(3) -(4) >(5) <(6) 0(7) 1(8) 2(9) 3(10) 4(11) 5(12) 6(13) 7(14) 8(15) 9(16)

{0x00<<1, 0x00<<1, 0x00<<1, 0x00<<1, 0x00<<1 },/*" ",0*/
{0x00<<1, 0x20<<1, 0x00<<1, 0x00<<1, 0x00<<1 },/*".",0*/

{0x20<<1, 0x1C<<1, 0x16<<1, 0x18<<1, 0x20<<1 },/*"A",1*/

{0x02<<1, 0x1C<<1, 0x30<<1, 0x0C<<1, 0x02<<1 },/*"V",2*/

{0x3E<<1, 0x0E<<1, 0x38<<1, 0x06<<1, 0x3E<<1 },/*"M",3*/

{0x08<<1, 0x08<<1, 0x08<<1, 0x08<<1, 0x08<<1 },/*"-",4*/

{0x02<<1, 0x24<<1, 0x14<<1, 0x08<<1, 0x08<<1 },/*">",5*/

{0x08<<1, 0x08<<1, 0x14<<1, 0x22<<1, 0x00<<1 },/*"<",6*/

{0x1C<<1, 0x22<<1, 0x22<<1, 0x3E<<1, 0x00<<1 },/*"0",7*/

{0x00<<1, 0x04<<1, 0x3E<<1, 0x00<<1, 0x00<<1 },/*"1",8*/

{0x00<<1, 0x22<<1, 0x32<<1, 0x2E<<1, 0x00<<1 },/*"2",9*/

{0x00<<1, 0x22<<1, 0x2A<<1, 0x3E<<1, 0x00<<1 },/*"3",10*/

{0x10<<1, 0x18<<1, 0x14<<1, 0x3E<<1, 0x10<<1 },/*"4",11*/

{0x0C<<1, 0x2A<<1, 0x2A<<1, 0x3A<<1, 0x00<<1 },/*"5",12*/

{0x10<<1, 0x2C<<1, 0x2A<<1, 0x28<<1, 0x10<<1 },/*"6",13*/

{0x02<<1, 0x22<<1, 0x1A<<1, 0x06<<1, 0x02<<1 },/*"7",14*/

{0x14<<1, 0x2A<<1, 0x2A<<1, 0x3E<<1, 0x00<<1 },/*"8",15*/

{0x0C<<1, 0x2A<<1, 0x12<<1, 0x0E<<1, 0x00<<1 },/*"9",16*/
    

};

const BYTE abyFontB2T5x7[18][5] =
{
     // (0) A(1) V(2) M(3) -(4) >(5) <(6) 0(7) 1(8) 2(9) 3(10) 4(11) 5(12) 6(13) 7(14) 8(15) 9(16)

{0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x04,0x00,0x00,0x00},/*".",0*/

{0x04,0x38,0x68,0x18,0x04},/*"A",1*/

{0x40,0x38,0x0C,0x30,0x40},/*"V",2*/

{0x7C,0x70,0x1C,0x60,0x7C},/*"M",3*/

{0x10,0x10,0x10,0x10,0x10},/*"-",4*/

{0x40,0x24,0x28,0x10,0x10},/*">",5*/

{0x10,0x10,0x28,0x44,0x00},/*"<",6*/

{0x38,0x44,0x44,0x7C,0x00},/*"0",7*/

{0x00,0x20,0x7C,0x00,0x00},/*"1",8*/

{0x00,0x44,0x4C,0x74,0x00},/*"2",9*/

{0x00,0x44,0x54,0x7C,0x00},/*"3",10*/

{0x08,0x18,0x28,0x7C,0x08},/*"4",11*/

{0x30,0x54,0x54,0x5C,0x00},/*"5",12*/

{0x08,0x34,0x54,0x14,0x08},/*"6",13*/

{0x40,0x44,0x58,0x60,0x40},/*"7",14*/

{0x28,0x54,0x54,0x7C,0x00},/*"8",15*/

{0x30,0x54,0x48,0x70,0x00},/*"9",16*/
};

const BYTE abyLogoBmp[16][30] = 
{
#if 1
    /*--  调入了一幅图像：F:\cloud\data\work\charger\codes\powerfirst.bmp  --*/
    /*--  宽度x高度=240x16  --*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x80,
    0x00,0x00,0x00,0x0F,0xC3,0x00,0x00,0x00,0x00,0x0F,0xC0,0x00,0x0C,0x00,0x00,0x03,
    0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x00,0x0C,0x0F,0xCF,0x00,0x0C,0xC0,0x00,0x00,
    0x00,0x0C,0x00,0x00,0x00,0x06,0x00,0x03,0x00,0x00,0x0C,0x00,0x00,0x03,0x00,0x00,
    0x00,0x00,0x0C,0xC0,0x00,0x00,0x0C,0x03,0x0D,0x80,0x0C,0xC0,0x00,0x00,0x00,0x0C,
    0x00,0x00,0x00,0x06,0x00,0x03,0x00,0x00,0x0C,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
    0x0C,0xC0,0x00,0x00,0x0C,0x03,0x0D,0xC0,0x0C,0xC7,0x9B,0xC7,0x8F,0x8C,0x03,0x0F,
    0x8F,0x9F,0x80,0x03,0x07,0x87,0x8F,0x8F,0x87,0x83,0x07,0x87,0xCC,0xC0,0x0C,0x07,
    0x80,0x00,0x0C,0x03,0x0C,0xC0,0x0F,0x8D,0xDF,0xCD,0xCE,0x0F,0x83,0x0E,0x0D,0x86,
    0x00,0x03,0x0D,0xCD,0xCC,0xCC,0xCD,0xC3,0x0D,0xCD,0x8D,0x80,0x1C,0x0D,0xC0,0x00,
    0x0C,0x03,0x0C,0xC0,0x0C,0x1C,0xCF,0xCF,0xCE,0x0C,0x03,0x0E,0x0F,0x06,0x00,0x03,
    0x0F,0xDC,0x0C,0xCC,0xDC,0xC3,0x1C,0xCD,0x8D,0x80,0x1C,0xDC,0xC0,0x00,0x0C,0x03,
    0x0C,0xC0,0x0C,0x1C,0xCF,0x8C,0x0C,0x0C,0x03,0x0C,0x01,0x86,0x00,0x03,0x0C,0x1C,
    0xCC,0xCC,0xDC,0xC3,0x1C,0xCF,0x07,0x80,0x0C,0xDC,0xC0,0x00,0x0C,0x03,0x0D,0xC0,
    0x0C,0x0D,0xCF,0x8D,0xCC,0x0C,0x03,0x0C,0x0D,0xC6,0x00,0x03,0x0D,0xCD,0xCC,0xCC,
    0xCD,0xC3,0x0D,0xCC,0x07,0x00,0x0D,0xCD,0xC0,0x00,0x0C,0x03,0x0D,0x80,0x0C,0x07,
    0x8D,0x87,0x8C,0x0C,0x03,0x0C,0x07,0x83,0xC0,0x03,0x07,0x87,0x8C,0xCC,0xC7,0x83,
    0x07,0x8F,0xC7,0x00,0x07,0x87,0x8C,0x00,0x0F,0xC3,0x0F,0x0C,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,
    0xC6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x8E,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
#else
    /*--  宽度x高度=240x16  --*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x80,
    0x00,0x00,0x00,0x00,0x3F,0x0C,0x00,0x00,0x00,0x00,0xFC,0x00,0x00,0xC0,0x00,0x00,
    0x30,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x30,0x3F,0x3C,0x00,0x0C,0xC0,0x00,0x00,
    0x00,0x00,0x30,0x00,0x00,0x00,0x18,0x00,0x30,0x00,0x00,0xC0,0x00,0x00,0x30,0x00,
    0x00,0x00,0x01,0x98,0x00,0x00,0x30,0x0C,0x36,0x00,0x0C,0xC0,0x00,0x00,0x00,0x00,
    0x30,0x00,0x00,0x00,0x18,0x00,0x30,0x00,0x00,0xC0,0x00,0x00,0x30,0x00,0x00,0x00,
    0x01,0x98,0x00,0x00,0x30,0x0C,0x37,0x00,0x0C,0xC7,0x9B,0xC7,0x8F,0x80,0x30,0x0C,
    0x3E,0x3E,0x7E,0x00,0x30,0x78,0x78,0xF8,0xF8,0x78,0x30,0x78,0x7C,0xCC,0x01,0x80,
    0xF0,0x00,0x30,0x0C,0x33,0x00,0x0F,0x8D,0xDF,0xCD,0xCE,0x00,0x3E,0x0C,0x38,0x32,
    0x18,0x00,0x30,0xDC,0xDC,0xCC,0xCC,0xDC,0x30,0xDC,0xD8,0xD8,0x03,0x81,0xB8,0x00,
    0x30,0x0C,0x33,0x00,0x0C,0x1C,0xCF,0xCF,0xCE,0x00,0x30,0x0C,0x38,0x3C,0x18,0x00,
    0x30,0xFD,0xC0,0xCC,0xCD,0xCC,0x31,0xCC,0xD8,0xD8,0x03,0x9B,0x98,0x00,0x30,0x0C,
    0x33,0x00,0x0C,0x1C,0xCF,0x8C,0x0C,0x00,0x30,0x0C,0x30,0x06,0x18,0x00,0x30,0xC1,
    0xCC,0xCC,0xCD,0xCC,0x31,0xCC,0xF0,0x78,0x01,0x9B,0x98,0x00,0x30,0x0C,0x37,0x00,
    0x0C,0x0D,0xCF,0x8D,0xCC,0x00,0x30,0x0C,0x30,0x37,0x18,0x00,0x30,0xDC,0xDC,0xCC,
    0xCC,0xDC,0x30,0xDC,0xC0,0x70,0x01,0xB9,0xB9,0x80,0x30,0x0C,0x36,0x30,0x0C,0x07,
    0x8D,0x87,0x8C,0x00,0x30,0x0C,0x30,0x1E,0x0F,0x00,0x30,0x78,0x78,0xCC,0xCC,0x78,
    0x30,0x78,0xFC,0x70,0x00,0xF0,0xF1,0x80,0x3F,0x0C,0x3C,0x30,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xCC,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0xE0,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

#endif
};


/* end of file */


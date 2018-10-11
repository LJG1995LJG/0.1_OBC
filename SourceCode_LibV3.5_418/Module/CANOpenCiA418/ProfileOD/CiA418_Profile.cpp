/******************************************************************************************************
*            CiA418_Profile.c
******************************************************************************************************
*
*
******************************************************************************************************
******************************************************************************************************
*    FILE NAME: CiA418_Profile.c
*
*    DESCRIPTION: CiA418 profile
*
*    ORIGINATOR: DYH
*
*    DATE: 2018/5/10 22:34:20
*
*             Version   Author     Modification                            Date
*    HISTORY:  V1.0      DYH       Initial Version                       2018/5/10 22:34:22
******************************************************************************************************/
#include <string.h>
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
/* Object 0x1000 */
uint32_t OD_u32DeviceType = 0x1A2ul;
stOdSubInfo_t stOb1000_DeviceType[] =
{
    RO,                  //u8AccessType
    UNSIGNED32,          //u8DataType
    sizeof(uint32_t),    //u8size
    (void *)&OD_u32DeviceType, //pObject
};

/* Object 0x1001 */


stErrorRegister_t stErrorRegister = {0};
stOdSubInfo_t stOb1001_ErrorRegister[] =
{
    RO,                  //u8AccessType
    UNSIGNED8,          //u8DataType
    sizeof(uint8_t),    //u8size
    (void *)&stErrorRegister, //pObject
};


/* Object 0x1012 */
stTimeStamp_t OD_u32TimeStamp =
{
    0
    //.Consume = 0,
    //.Produce = 0,
    //.Frame = 0,
    //.ExtCanId = 0,
    //.StdCanId = 0x100
};

stOdSubInfo_t stOb1012_TimeStamp[] =
{
    RW,                  //u8AccessType
    UNSIGNED32,          //u8DataType
    sizeof(uint32_t),    //u8size
    (void *)&OD_u32TimeStamp, //pObject
};


/* Object 0x1017 */
uint16_t OD_u16HeartBeat_ms = 1000u;

stOdSubInfo_t stOb1017_HeartBeat[] =
{
    RW,                  //u8AccessType
    UNSIGNED16,          //u8DataType
    sizeof(uint16_t),    //u8size
    (void *)&OD_u16HeartBeat_ms, //pObject
};


/* Object 0x1018 */
const uint8_t OD_u8MaxSubIndex_1018 = 0x4u;
uint32_t OD_u32VendorId = 0x12345678;
uint32_t OD_u32ProductCode = 0x87654321;
uint32_t OD_u32RevisionNum = 0x12345678;
uint32_t OD_u32SerialNum = 0x12345678;

stOdSubInfo_t stOb1017_Identify[] =
{
    {
        RO,                  //u8AccessType
        UNSIGNED8,          //u8DataType
        sizeof(uint8_t),    //u8size
        (void *)&OD_u8MaxSubIndex_1018 //pObject
    },

    {
        RO,                  //u8AccessType
        UNSIGNED32,          //u8DataType
        sizeof(uint32_t),    //u8size
        (void *)&OD_u32VendorId //pObject
    },

    {
        RO,                  //u8AccessType
        UNSIGNED32,          //u8DataType
        sizeof(uint32_t),    //u8size
        (void *)&OD_u32ProductCode //pObject
    },

    {
        RO,                  //u8AccessType
        UNSIGNED32,          //u8DataType
        sizeof(uint32_t),    //u8size
        (void *)&OD_u32RevisionNum //pObject
    },

    {
        RO,                  //u8AccessType
        UNSIGNED32,          //u8DataType
        sizeof(uint32_t),    //u8size
        (void *)&OD_u32SerialNum //pObject
    }
};


/* Object 0x1029 */
const uint8_t OD_u8MaxSubIndex_1029 = 0x3;
uint8_t OD_u8ErrorBehavior_01 = CHANGE_TO_PRE_OPERATION;
uint8_t OD_u8ErrorBehavior_02 = NO_CHANGE_STATE;
uint8_t OD_u8ErrorBehavior_03 = CHANGE_TO_STOPPED;

stOdSubInfo_t stOb1029_ErrorBehavior[] =
{
    {
        RO,                  //u8AccessType
        UNSIGNED8,          //u8DataType
        sizeof(uint8_t),    //u8size
        (void *)&OD_u8MaxSubIndex_1029, //pObject
    },

    {
        RW,                  //u8AccessType
        UNSIGNED8,          //u8DataType
        sizeof(uint8_t),    //u8size
        (void *)&OD_u8ErrorBehavior_01, //pObject
    },

    {
        RW,                  //u8AccessType
        UNSIGNED8,          //u8DataType
        sizeof(uint8_t),    //u8size
        (void *)&OD_u8ErrorBehavior_02, //pObject
    },

    {
        RW,                  //u8AccessType
        UNSIGNED8,          //u8DataType
        sizeof(uint8_t),    //u8size
        (void *)&OD_u8ErrorBehavior_03, //pObject
    }
};

/* index 0x1400 :  RPDO1 communication parameter */
const uint8_t OD_u8MaxSubIndex_1400 = 5; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32CobIdUsedByRPDO1 = 0x80000200 | MY_NODE_ID;
uint8_t OD_u8TransmissionTypeRPDO1 = 0xFF; /* 0 */

uint16_t OD_u16EventTimerRPDO1_ms = 0x0;  /* 0 */
uint8_t OD_u8SyncStartValRPDO1 = 0x0;
stOdSubInfo_t stOb1400_RPDO1[] =
{
    { RO,            UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8MaxSubIndex_1400 },                //0
    { RW,            UNSIGNED32, sizeof (uint32_t ),(void*)&OD_u32CobIdUsedByRPDO1 }, //1
    { RW|TO_BE_SAVE, UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8TransmissionTypeRPDO1 },  //2
    { RW|TO_BE_SAVE, UNSIGNED16, sizeof (uint16_t), NULL },                                         //3
    { RO,            UNSIGNED8,  sizeof(uint8_t),   NULL },                                         //4
    { RW,            UNSIGNED16, sizeof(uint16_t),  (void*)&OD_u16EventTimerRPDO1_ms },        //5
    { RW,            UNSIGNED8,  sizeof(uint8_t),   (void*)&OD_u8SyncStartValRPDO1}         //6
};


/* index 0x1600 :  RPDO1 mapping parameter */
const uint8_t OD_u8MaxSubIndex_1600 = 1; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32AppObj1_1600 = 0x60100010;

stOdSubInfo_t stOb1600_RPDO1[] =
{
    { RO, UNSIGNED8, sizeof(uint8_t), (void*)&OD_u8MaxSubIndex_1600 },   //0
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj1_1600 },         //1
};


/* index 0x1800 :  TPDO1 communication parameter */
const uint8_t OD_u8MaxSubIndex_1800 = 5; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32CobIdUsedByTPDO1 = 0x80000180 | MY_NODE_ID;
uint8_t OD_u8TransmissionTypeTPDO1 = 0xFF; /* 0xff */
uint16_t OD_u8InhibitTImeTPDO1_us = 0; /* 0 */
uint16_t OD_u16EventTimerTPDO1_ms = 0x0;  /* 0 */
uint8_t OD_u8SyncStartValTPDO1 = 0x0;
stOdSubInfo_t stOb1800_TPDO1[] =
{
    { RO,            UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8MaxSubIndex_1800 },                //0
    { RW,            UNSIGNED32, sizeof (uint32_t ),(void*)&OD_u32CobIdUsedByTPDO1 }, //1
    { RW|TO_BE_SAVE, UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8TransmissionTypeTPDO1 },  //2
    { RW|TO_BE_SAVE, UNSIGNED16, sizeof (uint16_t), (void*)&OD_u8InhibitTImeTPDO1_us },                                         //3
    { RO,            UNSIGNED8,  sizeof(uint8_t),   NULL },                                         //4
    { RW,            UNSIGNED16, sizeof(uint16_t),  (void*)&OD_u16EventTimerTPDO1_ms },        //5
    { RW,            UNSIGNED8,  sizeof(uint8_t),   (void*)&OD_u8SyncStartValTPDO1}         //6
};


/* index 0x1A00 :  TPDO1 mapping parameter */
const uint8_t OD_u8MaxSubIndex_1A00 = 2; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32AppObj1_1A00 = 0x60100010;
uint32_t OD_u32AppObj2_1A00 = 0x60000008;

stOdSubInfo_t stOb1A00_TPDO1[] =
{
    { RO, UNSIGNED8, sizeof(uint8_t), (void*)&OD_u8MaxSubIndex_1A00 },   //0
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj1_1A00 },         //1
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj2_1A00 },         //2
};

/* index 0x1401 :  RPDO2 communication parameter */
const uint8_t OD_u8MaxSubIndex_1401 = 5; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32CobIdUsedByRPDO2 = 0x00000300 | MY_NODE_ID;
uint8_t OD_u8TransmissionTypeRPDO2 = 0xFF; /* 0xff */

uint16_t OD_u16EventTimerRPDO2_ms = 0x0;  /* 0 */
uint8_t OD_u8SyncStartValRPDO2 = 0x0;
stOdSubInfo_t stOb1401_RPDO2[] =
{
    { RO,            UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8MaxSubIndex_1401 },                //0
    { RW,            UNSIGNED32, sizeof (uint32_t ),(void*)&OD_u32CobIdUsedByRPDO2 }, //1
    { RW|TO_BE_SAVE, UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8TransmissionTypeRPDO2 },  //2
    { RW|TO_BE_SAVE, UNSIGNED16, sizeof (uint16_t), NULL },                                         //3
    { RO,            UNSIGNED8,  sizeof(uint8_t),   NULL },                                         //4
    { RW,            UNSIGNED16, sizeof(uint16_t),  (void*)&OD_u16EventTimerRPDO2_ms },        //5
    { RW,            UNSIGNED8,  sizeof(uint8_t),   (void*)&OD_u8SyncStartValRPDO2}         //6
};


/* index 0x1601 :  RPDO1 mapping parameter */
const uint8_t OD_u8MaxSubIndex_1601 = 2; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32AppObj1_1601 = 0x60010008;
uint32_t OD_u32AppObj2_1601 = 0x60520010;

stOdSubInfo_t stOb1601_RPDO2[] =
{
    { RO, UNSIGNED8, sizeof(uint8_t), (void*)&OD_u8MaxSubIndex_1601 },   //0
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj1_1601 },         //1
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj2_1601 },         //2
};


/* index 0x1801 :  TPDO2 communication parameter */
const uint8_t OD_u8MaxSubIndex_1801 = 5; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32CobIdUsedByTPDO2 = 0x00000280 | MY_NODE_ID;
uint8_t OD_u8TransmissionTypeTPDO2 = 0xFF; /* 0xff */
uint16_t OD_u16InhibitTimerTPDO2_us = 0x0;  /* 0 */
uint16_t OD_u16EventTimerTPDO2_ms = 0x0;  /* 0 */
uint8_t OD_u8SyncStartValTPDO2 = 0x0;
stOdSubInfo_t stOb1801_TPDO2[] =
{
    { RO,            UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8MaxSubIndex_1801 },                //0
    { RW,            UNSIGNED32, sizeof (uint32_t ),(void*)&OD_u32CobIdUsedByTPDO2 }, //1
    { RW|TO_BE_SAVE, UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8TransmissionTypeTPDO2 },  //2
    { RW|TO_BE_SAVE, UNSIGNED16, sizeof (uint16_t), (void*)&OD_u16InhibitTimerTPDO2_us },                                         //3
    { RO,            UNSIGNED8,  sizeof(uint8_t),   NULL },                                         //4
    { RW,            UNSIGNED16, sizeof(uint16_t),  (void*)&OD_u16EventTimerTPDO2_ms },        //5
    { RW,            UNSIGNED8,  sizeof(uint8_t),   (void*)&OD_u8SyncStartValTPDO2}         //6
};


/* index 0x1A01 :  TPDO2 mapping parameter */
const uint8_t OD_u8MaxSubIndex_1A01 = 3; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32AppObj1_1A01 = 0x60100010;
uint32_t OD_u32AppObj2_1A01 = 0x60000008;
uint32_t OD_u32AppObj3_1A01 = 0x60600020;

stOdSubInfo_t stOb1A01_TPDO2[] =
{
    { RO, UNSIGNED8, sizeof(uint8_t), (void*)&OD_u8MaxSubIndex_1A01 },   //0
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj1_1A01 },         //1
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj2_1A01 },         //2
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj3_1A01 },         //2
};


/* index 0x1402 :  RPDO3 communication parameter */
const uint8_t OD_u8MaxSubIndex_1402 = 5; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32CobIdUsedByRPDO3 = 0x00000300 | MY_NODE_ID;
uint8_t OD_u8TransmissionTypeRPDO3 = 0xFF; /* 0xff */

uint16_t OD_u16EventTimerRPDO3_ms = 0x0;  /* 0 */
uint8_t OD_u8SyncStartValRPDO3 = 0x0;
stOdSubInfo_t stOb1402_RPDO3[] =
{
    { RO,            UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8MaxSubIndex_1402 },                //0
    { RW,            UNSIGNED32, sizeof (uint32_t ),(void*)&OD_u32CobIdUsedByRPDO3 }, //1
    { RW|TO_BE_SAVE, UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8TransmissionTypeRPDO3 },  //2
    { RW|TO_BE_SAVE, UNSIGNED16, sizeof (uint16_t), NULL },                                         //3
    { RO,            UNSIGNED8,  sizeof(uint8_t),   NULL },                                         //4
    { RW,            UNSIGNED16, sizeof(uint16_t),  (void*)&OD_u16EventTimerRPDO3_ms },        //5
    { RW,            UNSIGNED8,  sizeof(uint8_t),   (void*)&OD_u8SyncStartValRPDO3}         //6
};


/* index 0x1602 :  RPDO3 mapping parameter */
const uint8_t OD_u8MaxSubIndex_1602 = 2; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32AppObj1_1602 = 0x60010008;
uint32_t OD_u32AppObj2_1602 = 0x60520010;
uint32_t OD_u32AppObj3_1602 = 0x60800008;

stOdSubInfo_t stOb1602_RPDO3[] =
{
    { RO, UNSIGNED8, sizeof(uint8_t), (void*)&OD_u8MaxSubIndex_1602 },   //0
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj1_1602 },         //1
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj2_1602 },         //2
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj3_1602 },         //3
};


/* index 0x1802 :  TPDO3 communication parameter */
const uint8_t OD_u8MaxSubIndex_1802 = 5; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32CobIdUsedByTPDO3 = 0x80000380 | MY_NODE_ID;
uint8_t OD_u8TransmissionTypeTPDO3 = 0xFF; /* 0xff */
uint16_t OD_u16InhibitTimerTPDO3_us = 0x0;  /* 0 */
uint16_t OD_u16EventTimerTPDO3_ms = 0x0;  /* 0 */
uint8_t OD_u8SyncStartValTPDO3 = 0x0;
stOdSubInfo_t stOb1802_TPDO3[] =
{
    { RO,            UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8MaxSubIndex_1802 },                //0
    { RW,            UNSIGNED32, sizeof (uint32_t ),(void*)&OD_u32CobIdUsedByTPDO3 }, //1
    { RW|TO_BE_SAVE, UNSIGNED8,  sizeof (uint8_t),  (void*)&OD_u8TransmissionTypeTPDO3 },  //2
    { RW|TO_BE_SAVE, UNSIGNED16, sizeof (uint16_t), (void*)&OD_u16InhibitTimerTPDO3_us },                                         //3
    { RO,            UNSIGNED8,  sizeof(uint8_t),   NULL },                                         //4
    { RW,            UNSIGNED16, sizeof(uint16_t),  (void*)&OD_u16EventTimerTPDO3_ms },        //5
    { RW,            UNSIGNED8,  sizeof(uint8_t),   (void*)&OD_u8SyncStartValTPDO3}         //6
};


/* index 0x1A02 :  TPDO3 mapping parameter */
const uint8_t OD_u8MaxSubIndex_1A02 = 3; /* number of stOdSubInfo_t - 1*/
uint32_t OD_u32AppObj1_1A02 = 0x60700010;
uint32_t OD_u32AppObj2_1A02 = 0x60810008;

stOdSubInfo_t stOb1A02_TPDO3[] =
{
    { RO, UNSIGNED8, sizeof(uint8_t), (void*)&OD_u8MaxSubIndex_1A02 },   //0
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj1_1A02 },         //1
    { RW, UNSIGNED32, sizeof(uint32_t), (void*)&OD_u32AppObj2_1A02 },         //2
};


/***************** Application ******************/
/* battery status */
uint8_t OBJ6000_BattStatus = 0u;

stOdSubInfo_t stObIndex6000[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6000_BattStatus }
};

/* charger status */
uint8_t OBJ6001_ChargerStatus = 0u;

stOdSubInfo_t stObIndex6001[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6000_BattStatus }
};


/* battery temperature */
uint8_t OBJ6010_BattTemperature = 0u;

stOdSubInfo_t stObIndex6010[] =
{
    { RW, UNSIGNED16, sizeof (uint16_t), (void*)&OBJ6010_BattTemperature }
};


/* battery parameter */
const uint8_t OBJ6020_HighestSubIndex = 4u;
uint16_t OBJ6020_BattType = 0u;
uint16_t OBJ6020_AhCap = 0u;
uint16_t OBJ6020_MaxChgCurrent = 0u;
uint16_t OBJ6020_CellNum = 0u;

stOdSubInfo_t stObIndex6020[] =
{
    { RW, UNSIGNED8,  sizeof(uint8_t),  (void*)&OBJ6020_HighestSubIndex},
    { RW, UNSIGNED16, sizeof(uint16_t), (void*)&OBJ6020_BattType},
    { RW, UNSIGNED16, sizeof(uint16_t), (void*)&OBJ6020_AhCap},
    { RW, UNSIGNED16, sizeof(uint16_t), (void*)&OBJ6020_MaxChgCurrent},
    { RW, UNSIGNED16, sizeof(uint16_t), (void*)&OBJ6020_CellNum}
};

/* battery serial number */
const uint8_t OBJ6030_HighestSubIndex = 3u;
uint32_t OBJ6030_SerialNum0 = 0u;
uint32_t OBJ6030_SerialNum1 = 0u;
uint32_t OBJ6030_SerialNum2 = 0u;

stOdSubInfo_t stObIndex6030[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6030_HighestSubIndex },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6030_SerialNum0 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6030_SerialNum1 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6030_SerialNum2 }
};


/* battery ID */
const uint8_t OBJ6031_HighestSubIndex = 3u;
uint32_t OBJ6031_ID0 = 0u;
uint32_t OBJ6031_ID1 = 0u;
uint32_t OBJ6031_ID2 = 0u;
uint32_t OBJ6031_ID3 = 0u;

stOdSubInfo_t stObIndex6031[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6031_HighestSubIndex },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6031_ID0 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6031_ID1 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6031_ID2 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6031_ID3 }
};

/* Vehicle serial number */
const uint8_t OBJ6040_HighestSubIndex = 3u;
uint32_t OBJ6040_SerialNum0 = 0u;
uint32_t OBJ6040_SerialNum1 = 0u;
uint32_t OBJ6040_SerialNum2 = 0u;
uint32_t OBJ6040_SerialNum3 = 0u;

stOdSubInfo_t stObIndex6040[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6040_HighestSubIndex },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6040_SerialNum0 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6040_SerialNum1 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6040_SerialNum2 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6040_SerialNum3 }
};

/* Vehicle ID */
const uint8_t OBJ6041_HighestSubIndex = 3u;
uint32_t OBJ6041_ID0 = 0u;
uint32_t OBJ6041_ID1 = 0u;
uint32_t OBJ6041_ID2 = 0u;
uint32_t OBJ6041_ID3 = 0u;

stOdSubInfo_t stObIndex6041[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6041_HighestSubIndex },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6041_ID0 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6041_ID1 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6041_ID2 },
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6041_ID3 }
};

/* Object 6050h: Cumulative total Ah charge */
uint32_t OBJ6050_CumulativeTotal_AH = 0;
stOdSubInfo_t stObIndex6050[] =
{
    { RW, UNSIGNED32, sizeof (uint32_t), (void*)&OBJ6050_CumulativeTotal_AH }
};

/* Object 6051h: Ah expended since last charge, uinit is 0.125AH */
uint16_t OBJ6051_LastExpended_0_125_AH = 0;
stOdSubInfo_t stObIndex6051[] =
{
    { RW, UNSIGNED16, sizeof (uint16_t), (void*)&OBJ6051_LastExpended_0_125_AH }
};

/* Object 6052h: Ah returned during last charge, uinit is 0.125AH */
uint16_t OBJ6052_LastChg_0_125_AH = 0;
stOdSubInfo_t stObIndex6052[] =
{
    { RW, UNSIGNED16, sizeof (uint16_t), (void*)&OBJ6052_LastChg_0_125_AH }
};

/* Object 6053h: Ah since last equalization, uinit is 0.125AH */
uint16_t OBJ6053_LastEqual_0_125_AH = 0;
stOdSubInfo_t stObIndex6053[] =
{
    { RW, UNSIGNED16, sizeof (uint16_t), (void*)&OBJ6053_LastEqual_0_125_AH }
};

/* Object 6054h: Date of last equalization */
const uint8_t  OBJ6054_SubHighestIndex = 2u;
uint16_t OBJ6054_MinuteOfLastEqual = 0;
uint16_t OBJ6054_DayOfLastEqual = 0;
stOdSubInfo_t stObIndex6054[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6054_SubHighestIndex },
    { RW, UNSIGNED16, sizeof (uint16_t), (void*)&OBJ6054_MinuteOfLastEqual },
    { RW, UNSIGNED16, sizeof (uint16_t), (void*)&OBJ6054_DayOfLastEqual }
};


/* Object 6060h: Battery voltage */
uint32_t OBJ6060_BatteryVolts_Q10V = 0;
stOdSubInfo_t stObIndex6060[] =
{
    { RW, UNSIGNED16, sizeof (uint16_t), (void*)&OBJ6060_BatteryVolts_Q10V }
};

/* Object 6070h: Charge current requested */
uint32_t OBJ6070_ChargeCurrntRequest_Q4A = 0;
stOdSubInfo_t stObIndex6070[] =
{
    { RW, UNSIGNED16, sizeof (uint16_t), (void*)&OBJ6070_ChargeCurrntRequest_Q4A }
};


/* Object 6080h: Charger state of charge, unit is 1% */
uint8_t OBJ6080_ChargeSOC = 0xFF;
stOdSubInfo_t stObIndex6080[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6080_ChargeSOC }
};


/* Object 6081h: Battery state of charge, unit is 1% */
uint8_t OBJ6081_BatterySOC = 0xFF;
stOdSubInfo_t stObIndex6081[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6081_BatterySOC }
};


/* Object 6090h: Water level status */
uint8_t OBJ6090_WaterLevelStatus = 0;
stOdSubInfo_t stObIndex6090[] =
{
    { RW, UNSIGNED8, sizeof (uint8_t), (void*)&OBJ6090_WaterLevelStatus }
};



stOdSubInfoMap_t stOdSubInfoMap_CiA418[] =
{
    /* pSubIndex                                u8SubCount           u16OdIndex */
    {(stOdSubInfo_t *)&stOb1000_DeviceType,     1u,   0x1000},
    {(stOdSubInfo_t *)&stOb1001_ErrorRegister,  1u,   0x1001},
    {(stOdSubInfo_t *)&stOb1012_TimeStamp,      1u,   0x1012},
    {(stOdSubInfo_t *)&stOb1017_HeartBeat,      1u,   0x1017},
    {(stOdSubInfo_t *)&stOb1017_Identify,      OD_u8MaxSubIndex_1018 + 1u,   0x1018},
    {(stOdSubInfo_t *)&stOb1029_ErrorBehavior, OD_u8MaxSubIndex_1029 + 1u,   0x1029},
    {(stOdSubInfo_t *)&stOb1400_RPDO1,         OD_u8MaxSubIndex_1400 + 1u,   0x1400},
    {(stOdSubInfo_t *)&stOb1600_RPDO1,         OD_u8MaxSubIndex_1600 + 1u,   0x1600},
    {(stOdSubInfo_t *)&stOb1800_TPDO1,         OD_u8MaxSubIndex_1800 + 1u,   0x1800},
    {(stOdSubInfo_t *)&stOb1A00_TPDO1,         OD_u8MaxSubIndex_1A00 + 1u,   0x1A00},
    {(stOdSubInfo_t *)&stOb1401_RPDO2,         OD_u8MaxSubIndex_1401 + 1u,   0x1401},
    {(stOdSubInfo_t *)&stOb1601_RPDO2,         OD_u8MaxSubIndex_1601 + 1u,   0x1601},
    {(stOdSubInfo_t *)&stOb1801_TPDO2,         OD_u8MaxSubIndex_1801 + 1u,   0x1801},
    {(stOdSubInfo_t *)&stOb1A01_TPDO2,         OD_u8MaxSubIndex_1A01 + 1u,   0x1A01},
    {(stOdSubInfo_t *)&stOb1402_RPDO3,         OD_u8MaxSubIndex_1402 + 1u,   0x1402},
    {(stOdSubInfo_t *)&stOb1602_RPDO3,         OD_u8MaxSubIndex_1602 + 1u,   0x1602},
    {(stOdSubInfo_t *)&stOb1802_TPDO3,         OD_u8MaxSubIndex_1802 + 1u,   0x1802},
    {(stOdSubInfo_t *)&stOb1A02_TPDO3,         OD_u8MaxSubIndex_1A02 + 1u,   0x1A02},
    {(stOdSubInfo_t *)&stObIndex6000,          1u,   0x6000},
    {(stOdSubInfo_t *)&stObIndex6001,          1u,   0x6001},
    {(stOdSubInfo_t *)&stObIndex6010,          1u,   0x6010},
    {(stOdSubInfo_t *)&stObIndex6020,          OBJ6020_HighestSubIndex + 1u,   0x6020},
    {(stOdSubInfo_t *)&stObIndex6030,          OBJ6030_HighestSubIndex + 1u,   0x6030},
    {(stOdSubInfo_t *)&stObIndex6031,          OBJ6031_HighestSubIndex + 1u,   0x6031},
    {(stOdSubInfo_t *)&stObIndex6040,          OBJ6040_HighestSubIndex + 1u,   0x6040},
    {(stOdSubInfo_t *)&stObIndex6041,          OBJ6041_HighestSubIndex + 1u,   0x6041},
    {(stOdSubInfo_t *)&stObIndex6050,          1u,   0x6050},
    {(stOdSubInfo_t *)&stObIndex6051,          1u,   0x6051},
    {(stOdSubInfo_t *)&stObIndex6052,          1u,   0x6052},
    {(stOdSubInfo_t *)&stObIndex6053,          1u,   0x6053},
    {(stOdSubInfo_t *)&stObIndex6054,          OBJ6054_SubHighestIndex + 1,   0x6054},
    {(stOdSubInfo_t *)&stObIndex6060,          1u,   0x6060},
    {(stOdSubInfo_t *)&stObIndex6070,          1u,   0x6070},
    {(stOdSubInfo_t *)&stObIndex6080,          1u,   0x6080},
    {(stOdSubInfo_t *)&stObIndex6081,          1u,   0x6081},
    {(stOdSubInfo_t *)&stObIndex6090,          1u,   0x6090}
};

#define CIA_418_TABLE_SIZE (sizeof(stOdSubInfoMap_CiA418) / sizeof(stOdSubInfoMap_t))



uint8_t ReadOdMap(uint16_t OdIndex, uint8_t SubIndex, uint8_t *plength, uint8_t *pdata)
{
    uint8_t i = 0u;
    uint8_t readLen = 0;
    uint8_t result = OD_RW_SUCCESS;

    if(  (OdIndex >= stOdSubInfoMap_CiA418[0].u16OdIndex)
       ||(OdIndex <= stOdSubInfoMap_CiA418[CIA_418_TABLE_SIZE - 1].u16OdIndex) )
    {
        for(i = 0u; i < CIA_418_TABLE_SIZE; i++)
        {
            /* find the Od index */
            if(OdIndex == stOdSubInfoMap_CiA418[i].u16OdIndex)
            {
                /* check sub index is valid or not */
                if(SubIndex < stOdSubInfoMap_CiA418[i].u8SubCount)
                {
                    readLen = stOdSubInfoMap_CiA418[i].pSubIndex[SubIndex].u8size;
                }
                else
                {
                    result = OD_RW_SUB_INDEX_ERROR;
                }

                break; /* break from for(;;) loop */
            }
        }
    }
    else
    {
        result = OD_RW_OUT_OF_RANGE;
    }

    if(OD_RW_SUCCESS == result)
    {
        *plength = readLen;
        memcpy(&pdata[0], stOdSubInfoMap_CiA418[i].pSubIndex[SubIndex].pObject, readLen);
    }

    return result;
}



/* */
uint8_t WriteOdMap(uint16_t OdIndex, uint8_t SubIndex, uint8_t length, uint8_t *pdata)
{
    uint8_t i = 0u;
    uint8_t writeLen = 0;
    uint8_t result = OD_RW_SUCCESS;

    if(  (OdIndex >= stOdSubInfoMap_CiA418[0].u16OdIndex)
       ||(OdIndex <= stOdSubInfoMap_CiA418[CIA_418_TABLE_SIZE - 1].u16OdIndex) )
    {
        for(i = 0u; i < CIA_418_TABLE_SIZE; i++)
        {
            /* find the Od index */
            if(OdIndex == stOdSubInfoMap_CiA418[i].u16OdIndex)
            {
                /* check sub index is valid or not */
                if(SubIndex < stOdSubInfoMap_CiA418[i].u8SubCount)
                {
                    
                    if(length > stOdSubInfoMap_CiA418[i].pSubIndex[SubIndex].u8size)
                    {
                        result = OD_RW_LENGTH_ERROR;
                    }
                    /* means write whole subindex value */
                    else if(length == 0)
                    {
                        writeLen = stOdSubInfoMap_CiA418[i].pSubIndex[SubIndex].u8size;
                    }
                    else
                    {
                        writeLen = length;
                    }
                }
                else
                {
                    result = OD_RW_SUB_INDEX_ERROR;
                }

                break;
            }
        }
        
        if(OD_RW_SUCCESS == result)
        {
            memcpy(stOdSubInfoMap_CiA418[i].pSubIndex[SubIndex].pObject, &pdata[0], writeLen);
        }
    }
    else
    {
        result = OD_RW_OUT_OF_RANGE;
    }
    
    return result;
}


void TestOdReadWrite(void)
{
    uint8_t write[2] = {0x01, 0x01};
    uint8_t read[2] = {0};
    
    WriteOdMap(0x1001, 0, 0, &write[0]);
    ReadOdMap(0x1001, 0, 0, &read[0]);
    
    write[1] = 0x02;
    WriteOdMap(0x1800, 5, 0, &write[0]);
    ReadOdMap(0x1800, 5, 0, &read[0]);
}
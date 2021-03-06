//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CANSetup.h"
#include "CanDriver.h"
#include "CanTool_OBC.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TCanSetupDlg *CanSetupDlg;
//--------------------------------------------------------------------- 
__fastcall TCanSetupDlg::TCanSetupDlg(TComponent* AOwner)
	: TForm(AOwner)
{
    DeviceReady = 0;
}
//---------------------------------------------------------------------



void __fastcall TCanSetupDlg::OKBtnClick(TObject *Sender)
{
    USHORT DeviceBrand;
    DWORD DeviceType;
    USHORT Error;
    
    switch(CanToolSelect->ItemIndex)
    {
        case 0:
            DeviceType = VCI_USBCAN1;
            DeviceBrand = ZLG_DEVICE;
            break;
            
        case 1:
            DeviceType = VCI_USBCAN2;
            DeviceBrand = ZLG_DEVICE;
            break;
            
        case 2:
            DeviceType = VCI_USBCAN_E_U;
            DeviceBrand = ZLG_DEVICE;
            break;
            
        case 3:
            DeviceType = VCI_USBCAN_2E_U;
            DeviceBrand = ZLG_DEVICE;
            break;
        
        case 4:
            DeviceType = VCI_USBCAN1;
            DeviceBrand = ZHCX_DEVICE;
            break;
            
        case 5:
            DeviceType = VCI_USBCAN2;
            DeviceBrand = ZHCX_DEVICE;
            break;
            
        case 6:
            DeviceType = VCI_USBCAN_E_U;
            DeviceBrand = ZHCX_DEVICE;
            break;
            
        case 7:
            DeviceType = VCI_USBCAN_2E_U;
            DeviceBrand = ZHCX_DEVICE;
            break;
        
        default:
            DeviceType = VCI_USBCAN2;
            DeviceBrand = ZHCX_DEVICE;
            break;
    }
    
    Error = CanDriverObj->ConfigCanDevice(BaudRate->ItemIndex, DeviceBrand, DeviceType,
                                          DeviceIndex->ItemIndex, ChannelSet->ItemIndex);

    if(Error == DLL_NOT_EXIST)
    {
        MainForm->CommState->Caption = "Communication: Fail";
        ShowMessage("Load DLL Fail!");
    }
    else if(Error == DEVICE_OPEN_FAIL)
    {
         MainForm->CommState->Caption = "Communication: Fail";
         ShowMessage("Device Open Fail!");
    }
    else if(Error == DEVICE_INITIAL_FAIL)
    {
       MainForm->CommState->Caption = "Communication: Fail";
       ShowMessage("Device Initial Fail!");
    }
    else if(Error == DEVICE_START_FAIL)
    {
       MainForm->CommState->Caption = "Communication: Fail";
       ShowMessage("Device Start Fail!");
    }
    else if(Error == DEVICE_INIT_OK)
    {
        MainForm->CommState->Caption = "Communication: Ok";
        ShowMessage("Device Initial OK!");

        Close();
        DeviceReady = 1;
    }
    else
    {
        MainForm->CommState->Caption = "Communication: Fail";
        ShowMessage("Unknown Issue!");
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TCanSetupDlg::CancelBtnClick(TObject *Sender)
{
    BaudRate->ItemIndex = 0;
    ChannelSet->ItemIndex = 0;
    CanToolSelect->ItemIndex = 0;
    DeviceIndex->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TCanSetupDlg::CanSetupInit(TObject *Sender)
{
    BaudRate->ItemIndex = 0;
    ChannelSet->ItemIndex = 0;
    CanToolSelect->ItemIndex = 0;
    DeviceIndex->ItemIndex = 0;
}
//---------------------------------------------------------------------------


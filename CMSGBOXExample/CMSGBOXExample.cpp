// CMSGBOXExample.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CMSGBOXExample.h"
#include "CMessageBox/CMessageBox.hpp"

#include <shellapi.h>

#define MAX_LOADSTRING 100

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    std::vector<TASKDIALOG_BUTTON> customButtons = { {101, L"And"}, {102, L"custom buttons"}, {103, L"too!"} };
    std::vector<TASKDIALOG_BUTTON> customRadioButtons = { {201, L"This supports"}, {202, L"Infinite"}, {203, L"Radio Buttons!"} };

    CMessageBox::TDMessageBoxProperties MsgProperties;
    MsgProperties.title = L"CMessageBox Example";
    MsgProperties.instructionText = L"CMessageBox Demo Project";
    MsgProperties.text = L"This little program shows you the intended way of using CMessageBox";
    MsgProperties.expandedInfoText = L"TaskDialogIndirect is really cool!";
    MsgProperties.footerText = L"Made by D24 (aka. Davide_24)";
    MsgProperties.verificationText = L"Is this cool?";
    MsgProperties.TDFlags = TDF_ALLOW_DIALOG_CANCELLATION | TDF_EXPAND_FOOTER_AREA;
    MsgProperties.commonButtons = TDCBF_OK_BUTTON;
    MsgProperties.customButtons = customButtons;
    MsgProperties.defaultButton = 102;
    MsgProperties.radioButtons = customRadioButtons;
    MsgProperties.LNKAdminButtonIDs = {102}; // This is an std::vector that tells the dialog which button IDs to add a shield to.

    MsgProperties.mainIcon_PCWSTR = IDI_INFORMATION;
    MsgProperties.footerIcon_PCWSTR = IDI_SHIELD;

    int result;
    CMessageBox::TDMessageBox(NULL, NULL, MsgProperties, &result);

    MsgProperties.TDFlags |= TDF_USE_COMMAND_LINKS;
    MsgProperties.text = L"You can also use command links like here!";
    CMessageBox::TDMessageBox(NULL, NULL, MsgProperties, &result);

    return result;
}

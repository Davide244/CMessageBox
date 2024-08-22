// CMessageBox.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "CMessageBox.hpp"
#include <string>
#include <shellapi.h>
#include <winnt.h>
#include <shellapi.h>

HRESULT __stdcall Callback(HWND hwnd,
	UINT uNotification,
	WPARAM wParam,
	LPARAM lParam,
	LONG_PTR data)
{
	std::vector<int>* LNKAdminButtonIDs;

	switch (uNotification)
	{
	case TDN_CREATED:
		// Sets admin icon for buttons
		LNKAdminButtonIDs = (std::vector<int>*)data;
		for (int i = 0; i < LNKAdminButtonIDs->size(); i++)
			SendMessage(hwnd, TDM_SET_BUTTON_ELEVATION_REQUIRED_STATE, (*LNKAdminButtonIDs)[i], TRUE);

		break;
	case TDN_HYPERLINK_CLICKED:
		ShellExecute(hwnd, _T("open"), (LPCWSTR)lParam, NULL, NULL, SW_SHOW);
		break;
	}

	return S_OK;

}

HRESULT CMessageBox::TDMessageBox(
	HWND hwnd,
	HINSTANCE hInstance,
	PCWSTR text,
	PCWSTR title,
	TDMessageBoxProperties properties,
	int* PressedButton,
	BOOL* VerificationChecked,
	int* PressedRadioButton)
{
	HRESULT hRes;
	TASKDIALOGCONFIG tdmbInfo = { sizeof(TASKDIALOGCONFIG) };

	tdmbInfo.hInstance = hInstance;
	tdmbInfo.hwndParent = hwnd;

	tdmbInfo.pszWindowTitle = title;
	tdmbInfo.pszContent = text;
	if (properties.instructionText != NULL)			tdmbInfo.pszMainInstruction = properties.instructionText;
	if (properties.verificationText != NULL)		tdmbInfo.pszVerificationText = properties.verificationText;
	if (properties.expandedInfoText != NULL)		tdmbInfo.pszExpandedInformation = properties.expandedInfoText;

	tdmbInfo.pButtons = properties.customButtons.data();
	tdmbInfo.cButtons = properties.customButtons.size();
	tdmbInfo.pRadioButtons = properties.radioButtons.data();
	tdmbInfo.cRadioButtons = properties.radioButtons.size();

	tdmbInfo.pfCallback = Callback;
	tdmbInfo.lpCallbackData = (LONG_PTR)&properties.LNKAdminButtonIDs;


	// Set Icons
	if (std::holds_alternative<HICON>(properties.mainIcon))
	{
		tdmbInfo.dwFlags |= TDF_USE_HICON_MAIN;
		tdmbInfo.hMainIcon = std::get<HICON>(properties.mainIcon);
	}
	else if (std::holds_alternative<PCWSTR>(properties.mainIcon)) {
		tdmbInfo.dwFlags |= TDF_USE_HICON_MAIN;
		tdmbInfo.pszMainIcon = std::get<PCWSTR>(properties.mainIcon);
	}


	if (std::holds_alternative<HICON>(properties.footerIcon))
	{
		tdmbInfo.dwFlags |= TDF_USE_HICON_FOOTER;
		tdmbInfo.hFooterIcon = std::get<HICON>(properties.footerIcon);
	}
	else if (std::holds_alternative<PCWSTR>(properties.footerIcon)) {
		tdmbInfo.dwFlags |= TDF_USE_HICON_FOOTER;
		tdmbInfo.pszFooterIcon = std::get<PCWSTR>(properties.footerIcon);
	}


	tdmbInfo.dwCommonButtons = properties.commonButtons;
	tdmbInfo.dwFlags = properties.TDFlags | TDF_ENABLE_HYPERLINKS;
	if (~properties.defaultButton < 0) tdmbInfo.nDefaultButton = properties.defaultButton;

	hRes = TaskDialogIndirect(&tdmbInfo, PressedButton, PressedRadioButton, VerificationChecked);

	return hRes;
}


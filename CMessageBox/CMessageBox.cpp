// CMessageBox.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "CMessageBox.hpp"
#include <string>
#include <shellapi.h>
#include <winnt.h>
#include <shellapi.h>

// Make a union for MainIcon_opt and FooterIcon_opt so we can use both HICON and PCWSTR

union TDCallbackDataCombined {
	int AdminBtns[];

};

HRESULT __stdcall Callback(HWND hwnd,
	UINT uNotification,
	WPARAM wParam,
	LPARAM lParam,
	LONG_PTR data)
{
	std::vector<int>* LNKAdminButtonIDs;

	//std::wstring debug = L"DATA: " + data;
	//OutputDebugString(debug.c_str());
	//MessageBox(NULL, debug.c_str(), L"Debug", MB_OK);

	switch (uNotification)
	{
	case TDN_CREATED:
		// Sets admin icon for buttons
		LNKAdminButtonIDs = (std::vector<int>*)data;
		for (int i = 0; i < LNKAdminButtonIDs->size(); i++)
		{
			SendMessage(hwnd, TDM_SET_BUTTON_ELEVATION_REQUIRED_STATE, (*LNKAdminButtonIDs)[i], TRUE);
			#ifdef _DEBUG
			// output to debug console
			std::wstring debug = L"Button ID: " + std::to_wstring((*LNKAdminButtonIDs)[i]);
			OutputDebugString(debug.c_str());
			#endif
		}

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
	_TASKDIALOG_FLAGS mbFlags,
	int* PressedButton,
	PCWSTR text,
	PCWSTR title,
	PCWSTR Instructiontxt_opt,
	PCWSTR FooterText_opt,
	PCWSTR VerificationText_opt,
	BOOL* VerificationChecked,
	PCWSTR ExpandedInformation_opt,
	std::variant<HICON, PCWSTR> MainIcon_opt,
	std::variant<HICON, PCWSTR> FooterIcon_opt,
	_TASKDIALOG_COMMON_BUTTON_FLAGS CommonButtons_opt,
	std::vector<_TASKDIALOG_BUTTON> CustomButtons_opt,
	int DefaultButton,
	std::vector<int> LNKAdminButtonIDs,
	std::vector<_TASKDIALOG_BUTTON> radioButtons_opt,
	int* PressedRadioButton
)
{
	HRESULT hRes;
	TASKDIALOGCONFIG tdmbInfo = { sizeof(TASKDIALOGCONFIG) };

	tdmbInfo.hInstance = hInstance;
	tdmbInfo.hwndParent = hwnd;

	tdmbInfo.pszWindowTitle = title;
	tdmbInfo.pszContent = text;
	if (Instructiontxt_opt != NULL)			tdmbInfo.pszMainInstruction = Instructiontxt_opt;
	if (FooterText_opt != NULL)				tdmbInfo.pszFooter = FooterText_opt;
	if (VerificationText_opt != NULL)		tdmbInfo.pszVerificationText = VerificationText_opt;
	if (ExpandedInformation_opt != NULL)	tdmbInfo.pszExpandedInformation = ExpandedInformation_opt;

	tdmbInfo.pButtons = CustomButtons_opt.data();
	tdmbInfo.cButtons = CustomButtons_opt.size();
	tdmbInfo.pRadioButtons = radioButtons_opt.data();
	tdmbInfo.cRadioButtons = radioButtons_opt.size();

	tdmbInfo.pfCallback = Callback;
	tdmbInfo.lpCallbackData = (LONG_PTR)&LNKAdminButtonIDs;


	// Set Icons
	if (std::holds_alternative<HICON>(MainIcon_opt))
	{
		tdmbInfo.dwFlags |= TDF_USE_HICON_MAIN;
		tdmbInfo.hMainIcon = std::get<HICON>(MainIcon_opt);
	}
	else if (std::holds_alternative<PCWSTR>(MainIcon_opt)) {
		tdmbInfo.dwFlags |= TDF_USE_HICON_MAIN;
		tdmbInfo.pszMainIcon = std::get<PCWSTR>(MainIcon_opt);
	}


	if (std::holds_alternative<HICON>(FooterIcon_opt))
	{
		tdmbInfo.dwFlags |= TDF_USE_HICON_FOOTER;
		tdmbInfo.hFooterIcon = std::get<HICON>(FooterIcon_opt);
	}
	else if (std::holds_alternative<PCWSTR>(FooterIcon_opt)) {
		tdmbInfo.dwFlags |= TDF_USE_HICON_FOOTER;
		tdmbInfo.pszFooterIcon = std::get<PCWSTR>(FooterIcon_opt);
	}


	tdmbInfo.dwCommonButtons = CommonButtons_opt;
	tdmbInfo.dwFlags = mbFlags | TDF_ENABLE_HYPERLINKS;
	if (~DefaultButton < 0) tdmbInfo.nDefaultButton = DefaultButton;

	hRes = TaskDialogIndirect(&tdmbInfo, PressedButton, PressedRadioButton, VerificationChecked);

	return hRes;

}


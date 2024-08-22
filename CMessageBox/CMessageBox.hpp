//---------------------- CMessageBox -----------------------\\
//															\\
//	       Created by: David Simon Jonjic					\\
//	       Date: 22.08.2024									\\
//	       Version: 2.0										\\
//	       License: MIT										\\
//	       GitHub: https://github.com/Davide244/CMessageBox \\
//															\\
//---------------------- CMessageBox -----------------------\\

#pragma once

#include <vector>
#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>

#define CMB_PCWSTR_TYPE 0
#define CMB_HICON_TYPE 1

namespace CMessageBox
{
	struct TDMessageBoxProperties 
	{
		PCWSTR title;
		PCWSTR text;
		PCWSTR instructionText;
		PCWSTR footerText;
		PCWSTR expandedInfoText;
		PCWSTR verificationText;
		int TDFlags;

		PCWSTR mainIcon_PCWSTR = (PCWSTR)NULL;
		HICON mainIcon_HICON = (HICON)NULL;
		PCWSTR footerIcon_PCWSTR = (PCWSTR)NULL;
		HICON footerIcon_HICON = (HICON)NULL;

		_TASKDIALOG_COMMON_BUTTON_FLAGS commonButtons = (_TASKDIALOG_COMMON_BUTTON_FLAGS)0;
		std::vector<_TASKDIALOG_BUTTON> customButtons = {};
		int defaultButton = -1;
		std::vector<int> LNKAdminButtonIDs = {};
		std::vector<_TASKDIALOG_BUTTON> radioButtons = {};
	};

	// Create a messagebox using TaskDialogIndirect. This is a wrapper for the TaskDialogIndirect function.
	HRESULT TDMessageBox(
		HWND hwnd,
		HINSTANCE hInstance,
		TDMessageBoxProperties properties,
		int* PressedButton,
		BOOL* VerificationChecked = NULL,
		int* PressedRadioButton = NULL);
};

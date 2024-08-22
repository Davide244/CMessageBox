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

#include <variant>
#include <vector>
#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>

#define CMB_PCWSTR_TYPE 0
#define CMB_HICON_TYPE 1

class CMessageBox
{
	struct TDMessageBoxProperties 
	{
		PCWSTR instructionText;
		PCWSTR footerText;
		PCWSTR expandedInfoText;
		PCWSTR verificationText;
		_TASKDIALOG_FLAGS TDFlags;
		std::variant<HICON, PCWSTR> mainIcon = (PCWSTR)NULL;
		std::variant<HICON, PCWSTR> footerIcon = (PCWSTR)NULL;
		_TASKDIALOG_COMMON_BUTTON_FLAGS commonButtons = (_TASKDIALOG_COMMON_BUTTON_FLAGS)0;
		std::vector<_TASKDIALOG_BUTTON> customButtons = {};
		int defaultButton = -1;
		std::vector<int> LNKAdminButtonIDs = {};
		std::vector<_TASKDIALOG_BUTTON> radioButtons = {};
	};

public:
	// Create a messagebox using TaskDialogIndirect. This is a wrapper for the TaskDialogIndirect function.
	static HRESULT TDMessageBox(
		HWND hwnd,
		HINSTANCE hInstance,
		PCWSTR text,
		PCWSTR title,
		TDMessageBoxProperties properties,
		int* PressedButton,
		BOOL* VerificationChecked = NULL,
		int* PressedRadioButton = NULL);
};

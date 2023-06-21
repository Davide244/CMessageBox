//------------------- CMessageBox -------------------\\
//													 \\
//	       Created by: David Simon Jonjic			 \\
//	       Date: 12.06.2023							 \\
//	       Version: 1.0								 \\
//	       License: MIT								 \\
//	       GitHub:									 \\
//													 \\
//------------------- CMessageBox -------------------\\

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
public:
	// Create a messagebox using TaskDialogIndirect. This is a wrapper for the TaskDialogIndirect function.
	static HRESULT TDMessageBox(
		HWND hwnd,
		HINSTANCE hInstance,
		_TASKDIALOG_FLAGS mbFlags,
		int* PressedButton,
		PCWSTR text,
		PCWSTR title,
		PCWSTR Instructiontxt_opt = NULL,
		PCWSTR FooterText_opt = NULL,
		PCWSTR VerificationText_opt = NULL,
		BOOL* VerificationChecked = NULL,
		PCWSTR ExpandedInformation_opt = NULL,
		std::variant<HICON, PCWSTR> MainIcon_opt = (PCWSTR)NULL,
		std::variant<HICON, PCWSTR> FooterIcon_opt = (PCWSTR)NULL,
		_TASKDIALOG_COMMON_BUTTON_FLAGS CommonButtons_opt = (_TASKDIALOG_COMMON_BUTTON_FLAGS)0,
		std::vector<_TASKDIALOG_BUTTON> CustomButtons_opt = {},
		int DefaultButton = -1,
		std::vector<int> LNKAdminButtonIDs = {},
		std::vector<_TASKDIALOG_BUTTON> radioButtons_opt = {},
		int* PressedRadioButton = NULL);
};

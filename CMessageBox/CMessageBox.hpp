//---------------------- CMessageBox -----------------------\\
//															\\
//	       Created by: D244									\\
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
	/// <summary>
	/// Struct containing information for the TDMessageBox function.
	/// </summary>
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

    /// <summary>
    /// Creates a TaskDialogIndirect message box dialog with custom properties.
    /// </summary>
    /// <param name="hwnd">- The parent window's HWND. Set to NULL (or 0) to not parent to any window.</param>
    /// <param name="hInstance">- The handle to the application instance. This is required for custom icons.</param>
    /// <param name="properties">- The <see cref="CMessageBox::TDMessageBoxProperties"/> struct.</param>
    /// <param name="PressedButton">- A pointer to an integer that will receive the ID of the button that was pressed by the user.</param>
    /// <param name="VerificationChecked">- A pointer to a BOOL that will receive the state of the verification checkbox.</param>
    /// <param name="PressedRadioButton">- A pointer to an integer that will receive the ID of the radio button that was pressed by the user.</param>
    /// <returns>Returns an HRESULT indicating success or failure.</returns>
	HRESULT TDMessageBox(
		HWND hwnd,
		HINSTANCE hInstance,
		TDMessageBoxProperties properties,
		int* PressedButton,
		BOOL* VerificationChecked = NULL,
		int* PressedRadioButton = NULL);
};

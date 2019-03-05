// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+

#pragma once

#include "Fractal.h"

// CFractalDialog dialog Base Class.

class CFractalDialog : public CDialog
{
	DECLARE_DYNAMIC(CFractalDialog)

protected:
	//Data pointer.
	CFractal *m_pfrxParent;
	CFractal::FractalData m_frdData;

	LPCTSTR ModeToStr(int intColorMode);

	int StrToMode(LPCTSTR strColorName);

public:
	// standard constructor
	CFractalDialog(UINT IDD, CWnd* pParent = NULL);
	virtual ~CFractalDialog();

	// Initializing Dialog.
	virtual BOOL OnInitDialog();

	// Create Fractal Dialog.
	INT_PTR DoModal(); // Make Parent Function Override.

	// Get Fractal Data.
	virtual CFractal::FractalData GetFractalData();

	enum FractalDialogResult
	{
		CreateSuccessfulAndPressOk = 0,
		CreateSuccessfulAndPressCancel = 1,
		CreateUnsuccessful = 2
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCheckSierpinskiTransparent();
	afx_msg void OnCbnSelchangeComboSierpinskiColorMode();
	afx_msg void OnBnClickedButtonSierpinskiSelectCustomColor();
	afx_msg void OnNMCustomdrawSliderSierpinskiDepth(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	CSliderCtrl m_SldDepth;
	BOOL m_blnChkTransparent;
	CString m_strCmbColorMode;
};

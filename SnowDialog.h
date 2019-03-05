// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+

#pragma once


// CSnowDialog dialog

class CSnowDialog : public CFractalDialog
{
	DECLARE_DYNAMIC(CSnowDialog)

public:
	// standard constructor
	CSnowDialog(CWnd* pParent = NULL);
	virtual ~CSnowDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_SNOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CSliderCtrl m_sldFractalTileMode;
public:
	afx_msg void OnNMCustomdrawSliderDepth2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};

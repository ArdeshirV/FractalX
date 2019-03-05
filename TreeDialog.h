// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+

#pragma once


// CTreeDialog dialog

class CTreeDialog : public CFractalDialog
{
	DECLARE_DYNAMIC(CTreeDialog)

public:
	// standard constructor
	CTreeDialog(CWnd* pParent = NULL);
	virtual ~CTreeDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_TREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CSliderCtrl m_sldIncDegree;
	CSliderCtrl m_sldIncRadious;
	CSliderCtrl m_sldInitDegree;
	CSliderCtrl m_sldInitRadious;
	BOOL m_blnRandom;
public:
	afx_msg void OnNMCustomdrawSliderDepth2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderDepth3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderDepth4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderDepth5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckTreeRandom();
};

// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+

#pragma once


// CSierpinskiDialog dialog

class CSierpinskiDialog : public CFractalDialog
{
	DECLARE_DYNAMIC(CSierpinskiDialog)

public:
	// standard constructor
	CSierpinskiDialog(CWnd* pParent = NULL);
	virtual ~CSierpinskiDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG_SIERPINSKI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

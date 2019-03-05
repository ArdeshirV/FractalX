// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// SierpinskiDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FractalDialog.h"
#include "SierpinskiDialog.h"



// CSierpinskiDialog dialog

IMPLEMENT_DYNAMIC(CSierpinskiDialog, CFractalDialog)
CSierpinskiDialog::CSierpinskiDialog(CWnd* pParent)
	: CFractalDialog(CSierpinskiDialog::IDD, pParent)
{

}

CSierpinskiDialog::~CSierpinskiDialog()
{
}

void CSierpinskiDialog::DoDataExchange(CDataExchange* pDX)
{
	CFractalDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSierpinskiDialog, CFractalDialog)
END_MESSAGE_MAP()


// CSierpinskiDialog message handlers

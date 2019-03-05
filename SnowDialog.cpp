// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// SnowDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FractalDialog.h"
#include "SnowDialog.h"


// CSnowDialog dialog

IMPLEMENT_DYNAMIC(CSnowDialog, CFractalDialog)
CSnowDialog::CSnowDialog(CWnd* pParent /*=NULL*/)
	: CFractalDialog(CSnowDialog::IDD, pParent)
{

}

CSnowDialog::~CSnowDialog()
{
}

void CSnowDialog::DoDataExchange(CDataExchange* pDX)
{
	CFractalDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_DEPTH2, m_sldFractalTileMode);
}


BEGIN_MESSAGE_MAP(CSnowDialog, CFractalDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DEPTH2, OnNMCustomdrawSliderDepth2)
END_MESSAGE_MAP()


// CSnowDialog message handlers

void CSnowDialog::OnNMCustomdrawSliderDepth2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	this->m_frdData.dblTilCount = (double)this->m_sldFractalTileMode.GetPos() / 10;
}

BOOL CSnowDialog::OnInitDialog()
{
	CFractalDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	this->m_sldFractalTileMode.SetRange(0, 20);
	this->m_sldFractalTileMode.SetPos(int(this->m_frdData.dblTilCount * 10));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

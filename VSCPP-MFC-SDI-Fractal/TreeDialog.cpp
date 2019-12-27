// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// TreeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FractalDialog.h"
#include "TreeDialog.h"


// CTreeDialog dialog

IMPLEMENT_DYNAMIC(CTreeDialog, CFractalDialog)
CTreeDialog::CTreeDialog(CWnd* pParent /*=NULL*/)
	: CFractalDialog(CTreeDialog::IDD, pParent)
{
	this->m_blnRandom = this->m_frdData.blnRandom;
}

CTreeDialog::~CTreeDialog()
{
}

void CTreeDialog::DoDataExchange(CDataExchange* pDX)
{
	CFractalDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SLIDER_DEPTH2, m_sldIncDegree);
	DDX_Control(pDX, IDC_SLIDER_DEPTH3, m_sldIncRadious);
	DDX_Control(pDX, IDC_SLIDER_DEPTH4, m_sldInitDegree);
	DDX_Control(pDX, IDC_SLIDER_DEPTH5, m_sldInitRadious);
	DDX_Check(pDX, IDC_CHECK_TREE_RANDOM, m_blnRandom);
}

BEGIN_MESSAGE_MAP(CTreeDialog, CFractalDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DEPTH2, OnNMCustomdrawSliderDepth2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DEPTH3, OnNMCustomdrawSliderDepth3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DEPTH4, OnNMCustomdrawSliderDepth4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DEPTH5, OnNMCustomdrawSliderDepth5)
	ON_BN_CLICKED(IDC_CHECK_TREE_RANDOM, OnBnClickedCheckTreeRandom)
END_MESSAGE_MAP()


// CTreeDialog message handlers


BOOL CTreeDialog::OnInitDialog()
{
	CFractalDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_sldIncDegree.SetRange(-15, 15, TRUE);
	m_sldIncRadious.SetRange(-6, 6, TRUE);
	m_sldInitRadious.SetRange(10, 50, TRUE);
	m_sldInitDegree.SetRange(-90, 90, TRUE);

	m_sldIncDegree.SetPos(this->m_frdData.intIncA);
	m_sldIncRadious.SetPos(this->m_frdData.intIncR);
	m_sldInitDegree.SetPos(this->m_frdData.intInitalA);
	m_sldInitRadious.SetPos(this->m_frdData.intInitalR);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTreeDialog::OnNMCustomdrawSliderDepth2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	this->m_frdData.intIncA = this->m_sldIncDegree.GetPos();
}

void CTreeDialog::OnNMCustomdrawSliderDepth3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	this->m_frdData.intIncR = this->m_sldIncRadious.GetPos();
}

void CTreeDialog::OnNMCustomdrawSliderDepth4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	this->m_frdData.intInitalA = this->m_sldInitDegree.GetPos();
}

void CTreeDialog::OnNMCustomdrawSliderDepth5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	this->m_frdData.intInitalR = this->m_sldInitRadious.GetPos();
}

void CTreeDialog::OnBnClickedCheckTreeRandom()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	m_frdData.blnRandom = m_blnRandom ? true : false;
}

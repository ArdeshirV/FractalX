// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// FractalDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FractalView.h"
#include "FractalDialog.h"


// CFractalDialog dialog

IMPLEMENT_DYNAMIC(CFractalDialog, CDialog)
CFractalDialog::CFractalDialog(UINT IDD, CWnd* pParent)
	: CDialog(IDD, pParent)
{
	CFractalView *l_frv;

	if(l_frv = reinterpret_cast<CFractalView*>(pParent))
	{
		m_pfrxParent = l_frv->m_frcFractal;
		m_frdData = l_frv->GetFractalData();
	}
	else
		PostMessage(WM_CLOSE, NULL, NULL);
}

CFractalDialog::~CFractalDialog()
{
}

void CFractalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SLIDER_DEPTH, m_SldDepth);
	DDX_Text(pDX, IDC_COMBO_COLOR_MODE, m_strCmbColorMode);
	DDX_Check(pDX, IDC_CHECK_TRANSPARENT, m_blnChkTransparent);
}

CFractal::FractalData CFractalDialog::GetFractalData()
{
	return m_frdData;
}

INT_PTR CFractalDialog::DoModal()
{
	if(m_frdData.pDC != NULL)
		return CDialog::DoModal() == IDOK ?
				CFractalDialog::CreateSuccessfulAndPressOk :
				CFractalDialog::CreateSuccessfulAndPressCancel;
	else
		return	CFractalDialog::CreateUnsuccessful;
}

LPCTSTR CFractalDialog::ModeToStr(int intColorMode)
{
	switch(intColorMode)
	{
	case 0:
		return LPCTSTR("Red");
	case 2:
		return LPCTSTR("Blue");
	case 3:
		return LPCTSTR("Custom");
	case 4:
		return LPCTSTR("Random");
	default:
		return LPCTSTR("Green");
	}	
}

int CFractalDialog::StrToMode(LPCTSTR strColorName)
{
	LPCTSTR l_strArrOfNames[5] = {"Red", "Green", "Blue", "Custom", "Random"};

	for(int l_intIndexer = 0; l_intIndexer < 5; l_intIndexer++)
		if(!strcmp(l_strArrOfNames[l_intIndexer], strColorName))
			return l_intIndexer;

	return 1;
}


BEGIN_MESSAGE_MAP(CFractalDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR_MODE, OnCbnSelchangeComboSierpinskiColorMode)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_CUSTOM_COLOR, OnBnClickedButtonSierpinskiSelectCustomColor)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_DEPTH, OnNMCustomdrawSliderSierpinskiDepth)
	ON_BN_CLICKED(IDC_CHECK_TRANSPARENT, OnBnClickedCheckSierpinskiTransparent)
END_MESSAGE_MAP()


// CFractalDialog message handlers

void CFractalDialog::OnCbnSelchangeComboSierpinskiColorMode()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	this->m_frdData.clmColorMode = 
		(CFractal::ColorMode)CFractalDialog::StrToMode(m_strCmbColorMode);
	if(this->m_frdData.clmColorMode == CFractal::Custom)
		GetDlgItem(IDC_BUTTON_SELECT_CUSTOM_COLOR)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_BUTTON_SELECT_CUSTOM_COLOR)->EnableWindow(FALSE);
}

void CFractalDialog::OnBnClickedButtonSierpinskiSelectCustomColor()
{
	// TODO: Add your control notification handler code here
	CColorDialog l_dlgColor(this->m_frdData.clrColor, 0, this);
	
	if(l_dlgColor.DoModal() == IDOK)
		this->m_frdData.clrColor = l_dlgColor.GetColor();
}

void CFractalDialog::OnNMCustomdrawSliderSierpinskiDepth(NMHDR *pNMHDR,
															LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	this->m_frdData.intDepth = m_SldDepth.GetPos();
}

void CFractalDialog::OnBnClickedCheckSierpinskiTransparent()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	m_frdData.blnIsTr = (m_blnChkTransparent)? true: false;
}

BOOL CFractalDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int l_MaxDepth = m_pfrxParent->Get_Max();

	m_SldDepth.SetRange(1, l_MaxDepth);

	if(l_MaxDepth >= m_frdData.intDepth)
		m_SldDepth.SetPos(m_frdData.intDepth);
	else
		m_SldDepth.SetPos(l_MaxDepth);

	m_blnChkTransparent = (m_frdData.blnIsTr)? TRUE: FALSE;
	m_strCmbColorMode = CFractalDialog::ModeToStr(m_frdData.clmColorMode);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

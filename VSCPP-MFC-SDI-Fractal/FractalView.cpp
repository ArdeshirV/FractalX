// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// FractalView.cpp : implementation of the CFractalView class
//

#include "stdafx.h"
#include "Fractal.h"
#include "FractalView.h"

#include "FractalDialog.h"
#include "SnowDialog.h"
#include "TreeDialog.h"
#include "SierpinskiDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFractalView

IMPLEMENT_DYNCREATE(CFractalView, CView)

BEGIN_MESSAGE_MAP(CFractalView, CView)
	// Standard printing commands
	ON_UPDATE_COMMAND_UI(IDS_DEPTH, OnUpdateStatusDepth)//Me!
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVE_AS_IMAGE, OnFileSaveAsImage)
	ON_COMMAND(ID_FRACTAL_PREVIOUSDEPTH, OnFractalPreviousdepth)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_PREVIOUSDEPTH, OnUpdateFractalPreviousdepth)
	ON_COMMAND(ID_FRACTAL_NEXTDEPTH, OnFractalNextdepth)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_NEXTDEPTH, OnUpdateFractalNextdepth)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_COLOR_RED, OnUpdateFractalColorRed)
	ON_COMMAND(ID_FRACTAL_COLOR_RED, OnFractalColorRed)
	ON_COMMAND(ID_FRACTAL_COLOR_GREEN, OnFractalColorGreen)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_COLOR_GREEN, OnUpdateFractalColorGreen)
	ON_COMMAND(ID_FRACTAL_COLOR_BLUE, OnFractalColorBlue)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_COLOR_BLUE, OnUpdateFractalColorBlue)
	ON_COMMAND(ID_FRACTAL_RANDOMCOLOR, OnFractalRandomcolor)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_RANDOMCOLOR, OnUpdateFractalRandomcolor)
	ON_COMMAND(ID_FRACTAL_CUSTOMECOLOR, OnFractalCustomecolor)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_CUSTOMECOLOR, OnUpdateFractalCustomecolor)
	ON_COMMAND(ID_FRACTAL_TRANSPARENT, OnFractalTransparent)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_TRANSPARENT, OnUpdateFractalTransparent)
	ON_COMMAND(ID_FRACTAL_RANDOMDRAW, OnFractalRandomdraw)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_RANDOMDRAW, OnUpdateFractalRandomdraw)
	ON_COMMAND(ID_FRACTAL_PROPERTIES, OnFractalProperties)
	ON_COMMAND(ID_FRACTAL_SIERPINSKI, OnFractalSierpinski)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_SIERPINSKI, OnUpdateFractalSierpinski)
	ON_COMMAND(ID_FRACTAL_SNOW, OnFractalSnow)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_SNOW, OnUpdateFractalSnow)
	ON_COMMAND(ID_FRACTAL_TREE, OnFractalTree)
	ON_UPDATE_COMMAND_UI(ID_FRACTAL_TREE, OnUpdateFractalTree)
//	ON_WM_SIZE()
END_MESSAGE_MAP()

// CFractalView construction/destruction

CFractalView::CFractalView() : m_frcFractal(NULL)
{
	EnableActiveAccessibility();
}

CFractalView::~CFractalView()
{
	if(m_frcFractal)
		delete m_frcFractal, m_frcFractal = NULL;
}

// CFractalView drawing

void CFractalView::OnDraw(CDC* pDC)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect l_rctClientRect;
	GetClientRect(&l_rctClientRect);
	pDoc->m_frdFractalData.pDC = pDC;
	pDoc->m_frdFractalData.rctRect = l_rctClientRect;

	if(m_frcFractal)
		delete m_frcFractal, m_frcFractal = NULL;

	switch(pDoc->m_frtFractalType)
	{
	case None:
		m_frcFractal = NULL;
		break;
	case Tree:
		m_frcFractal = new CTree();
		break;
	case Snow:
		m_frcFractal = new CSnow();
		break;
	case Sierpinski:
		m_frcFractal = new CSierpinski();
	}

	if(m_frcFractal)
	{
		if(m_frcFractal->Get_Max() < pDoc->m_frdFractalData.intDepth)
			pDoc->m_frdFractalData.intDepth = m_frcFractal->Get_Max();

		m_frcFractal->Draw(&pDoc->m_frdFractalData);
	}
	else
		pDC->FillRect(&l_rctClientRect, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
}

void CFractalView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch(pDoc->m_frtFractalType)
	{
	case None:
		m_frcFractal = NULL;
		break;
	case Tree:
		m_frcFractal = new CTree();
		break;
	case Snow:
		m_frcFractal = new CSnow();
		break;
	case Sierpinski:
		m_frcFractal = new CSierpinski();
	}
}


// CFractalView printing

BOOL CFractalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CFractalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CFractalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}


// CFractalView diagnostics

#ifdef _DEBUG
void CFractalView::AssertValid() const
{
	CView::AssertValid();
}

void CFractalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFractalDoc* CFractalView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFractalDoc)));
	return (CFractalDoc*)m_pDocument;
}
#endif //_DEBUG


// CFractalView message handlers

void CFractalView::OnFileSaveAsImage()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CBitmap l_bmp;
	CRect l_rctClient;
	CDC pCompatibleDC;
	CDC *pDC = GetDC();
	CHAR l_bufBuffer[80];
	CFileDialog l_dlgSaveFile(FALSE, "bmp");
	GetTempPath(sizeof(l_bufBuffer), l_bufBuffer);
	CString l_strTempFilePathName = CString(l_bufBuffer) + "X.bmp";
	GetClientRect(&l_rctClient);
	pCompatibleDC.CreateCompatibleDC(pDC);
	l_bmp.CreateCompatibleBitmap(pDC, l_rctClient.Width(), l_rctClient.Height());
	pCompatibleDC.SelectObject(&l_bmp);
	pCompatibleDC.BitBlt(0, 0, l_rctClient.Width(), l_rctClient.Height(), pDC, 0, 0, SRCCOPY);
	CreateBMPFile(l_strTempFilePathName.GetBuffer(), CreateBitmapInfoStruct(l_bmp), l_bmp, pDC->m_hDC);

	if(l_dlgSaveFile.DoModal() == IDOK)
	{
		MoveFile(l_strTempFilePathName, l_dlgSaveFile.GetPathName());
		l_dlgSaveFile.GetPathName();
	}
	else
		DeleteFile(l_strTempFilePathName);
}

void CFractalView::OnUpdateFractalPreviousdepth(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(pDoc->m_frdFractalData.intDepth > 1);
}

void CFractalView::OnFractalPreviousdepth()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frdFractalData.intDepth > 1)
	{
		pDoc->m_frdFractalData.intDepth--;
		Invalidate(FALSE);
	}
}

void CFractalView::OnFractalNextdepth()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frdFractalData.intDepth < m_frcFractal->Get_Max())
	{
		pDoc->m_frdFractalData.intDepth++;
		Invalidate(FALSE);
	}
}

void CFractalView::OnUpdateFractalNextdepth(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(pDoc->m_frdFractalData.intDepth < m_frcFractal->Get_Max());
}

void CFractalView::OnUpdateFractalColorRed(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetRadio(pDoc->m_frdFractalData.clmColorMode == CFractal::Red);
}

void CFractalView::OnFractalColorRed()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frdFractalData.clmColorMode != CFractal::Red)
	{
		pDoc->m_frdFractalData.clmColorMode = CFractal::Red;
		Invalidate(FALSE);
	}
}

void CFractalView::OnFractalColorGreen()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frdFractalData.clmColorMode != CFractal::Green)
	{
		pDoc->m_frdFractalData.clmColorMode = CFractal::Green;
        Invalidate(FALSE);
	}
}

void CFractalView::OnUpdateFractalColorGreen(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetRadio(pDoc->m_frdFractalData.clmColorMode == CFractal::Green);
}

void CFractalView::OnFractalColorBlue()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frdFractalData.clmColorMode != CFractal::Blue)
	{
		pDoc->m_frdFractalData.clmColorMode = CFractal::Blue;
		Invalidate(FALSE);
	}
}

void CFractalView::OnUpdateFractalColorBlue(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetRadio(pDoc->m_frdFractalData.clmColorMode == CFractal::Blue);
}

void CFractalView::OnFractalRandomcolor()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frdFractalData.clmColorMode != CFractal::Random)
	{
		pDoc->m_frdFractalData.clmColorMode = CFractal::Random;
		Invalidate(FALSE);
	}
}

void CFractalView::OnUpdateFractalRandomcolor(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetRadio(pDoc->m_frdFractalData.clmColorMode == CFractal::Random);
}

void CFractalView::OnFractalCustomecolor()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CColorDialog l_dlgColorDialog(pDoc->m_frdFractalData.clrColor, 0, this);
	
	if(l_dlgColorDialog.DoModal() == IDOK && l_dlgColorDialog.GetColor() != pDoc->m_frdFractalData.clrColor)
	{
		pDoc->m_frdFractalData.clrColor = l_dlgColorDialog.GetColor();
		pDoc->m_frdFractalData.clmColorMode = CFractal::Custom;
		Invalidate(FALSE);
	}
}

void CFractalView::OnUpdateFractalCustomecolor(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetRadio(pDoc->m_frdFractalData.clmColorMode == CFractal::Custom);
}

void CFractalView::OnFractalTransparent()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_frdFractalData.blnIsTr = !pDoc->m_frdFractalData.blnIsTr;
	Invalidate(FALSE);
}

void CFractalView::OnUpdateFractalTransparent(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetCheck(pDoc->m_frdFractalData.blnIsTr == true);
}

void CFractalView::OnFractalRandomdraw()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_frdFractalData.blnRandom = !pDoc->m_frdFractalData.blnRandom;
	Invalidate(FALSE);
}

void CFractalView::OnUpdateFractalRandomdraw(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(pDoc->m_frtFractalType == Tree);
	pCmdUI->SetCheck(pDoc->m_frdFractalData.blnRandom == true);
}

void CFractalView::OnFractalProperties()
{
	CFractalDialog *l_dlgFractal = NULL;
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch(pDoc->m_frtFractalType)
	{
	case Tree:
		l_dlgFractal = new CTreeDialog(this);
		break;
	case Snow:
		l_dlgFractal = new CSnowDialog(this);
		break;
	case Sierpinski:
		l_dlgFractal = new CSierpinskiDialog(this);
		break;
	default:
		return;
	}

	if(l_dlgFractal && l_dlgFractal->DoModal() == CFractalDialog::CreateSuccessfulAndPressOk)
	{
		pDoc->m_frdFractalData = l_dlgFractal->GetFractalData();
		Invalidate(FALSE);
	}

	if(l_dlgFractal)
		delete l_dlgFractal;
}

void CFractalView::OnFractalSierpinski()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frtFractalType != Sierpinski)
	{
		ChooseFractal(pDoc->m_frtFractalType = Sierpinski);
		Invalidate(FALSE);
	}
}

void CFractalView::OnUpdateFractalSierpinski(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetRadio(pDoc->m_frtFractalType == Sierpinski);
}

void CFractalView::OnFractalSnow()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frtFractalType != Snow)
	{
		ChooseFractal(pDoc->m_frtFractalType = Snow);
		Invalidate(FALSE);
	}
}

void CFractalView::OnUpdateFractalSnow(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetRadio(pDoc->m_frtFractalType == Snow);
}

void CFractalView::OnFractalTree()
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_frtFractalType != Tree)
	{
		ChooseFractal(pDoc->m_frtFractalType = Tree);
		Invalidate(FALSE);
	}
}

void CFractalView::OnUpdateFractalTree(CCmdUI *pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetRadio(pDoc->m_frtFractalType == Tree);
}

afx_msg void CFractalView::OnUpdateStatusDepth(CCmdUI* pCmdUI)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetText(CString("Depth = ") + GetNumString(pDoc->m_frdFractalData.intDepth));
}

CFractal::FractalData CFractalView::GetFractalData() const
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	return pDoc->m_frdFractalData;
}

void CFractalView::ChooseFractal(FractalType newType)
{
	CFractalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(newType == frtCurrentType)//m_frcFractal->GetFractalType())
		return;

	if(m_frcFractal)
		delete m_frcFractal, m_frcFractal = NULL;

	switch(newType)
	{
	case None:
		m_frcFractal = NULL;
		break;
	case Tree:
		m_frcFractal = new CTree();
		break;
	case Snow:
		m_frcFractal = new CSnow();
		break;
	case Sierpinski:
		m_frcFractal = new CSierpinski();
	}

	newType = frtCurrentType;
}

PBITMAPINFO CFractalView::CreateBitmapInfoStruct(HBITMAP hBmp)
{
    BITMAP bmp;
    WORD cClrBits;
    PBITMAPINFO pbmi;

    if(!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
		errhandler("GetObject");

    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
    
	if(cClrBits == 1)
        cClrBits = 1;
    else if(cClrBits <= 4)
        cClrBits = 4;
    else if(cClrBits <= 8)
        cClrBits = 8;
    else if(cClrBits <= 16)
        cClrBits = 16;
    else if(cClrBits <= 24)
        cClrBits = 24;
    else
		cClrBits = 32;
	
	if(cClrBits != 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
		sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits));
	else
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));

	pbmi->bmiHeader.biWidth = bmp.bmWidth;
    pbmi->bmiHeader.biHeight = bmp.bmHeight;
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    if(cClrBits < 24)
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits);

	pbmi->bmiHeader.biCompression = BI_RGB;
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31)
		& ~31) /8 * pbmi->bmiHeader.biHeight;
	pbmi->bmiHeader.biClrImportant = 0;

	return pbmi;
}

void CFractalView::CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC)
{ 
	DWORD cb;
	BYTE *hp;
	HANDLE hf;
	DWORD dwTmp;
	DWORD dwTotal;
	LPBYTE lpBits;
	BITMAPFILEHEADER hdr;
	PBITMAPINFOHEADER pbih;

	pbih = (PBITMAPINFOHEADER)pbi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if(!lpBits)
		errhandler("GlobalAlloc");

    if(!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS))
        errhandler("GetDIBits");

	hf = CreateFile(pszFile, GENERIC_READ | GENERIC_WRITE,
		(DWORD) 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

	if(hf == INVALID_HANDLE_VALUE)
		errhandler("CreateFile");

	hdr.bfType = 0x4d42;
	hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0;
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage); 

	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed  * sizeof (RGBQUAD);

	if(!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp,  NULL))
		errhandler("WriteFile");

	if(!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)
	+ pbih->biClrUsed * sizeof (RGBQUAD), (LPDWORD) &dwTmp, ( NULL)))
		errhandler("WriteFile");

	hp = lpBits;
	dwTotal = cb = pbih->biSizeImage;

	if(!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL))
		errhandler("WriteFile");

     if(!CloseHandle(hf))
		errhandler("CloseHandle");

	GlobalFree((HGLOBAL)lpBits);
}

void CFractalView::errhandler(char* pStr) const
{
	::MessageBox(m_hWnd, pStr, "Error", MB_OK | MB_ICONINFORMATION);
	exit(-1);
}

char* CFractalView::GetNumString(int intDepth) const
{
	switch(intDepth)
	{
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";
	case 10:
		return "10";
	case 11:
		return "11";
	case 12:
		return "12";
	}

	return "X";
}




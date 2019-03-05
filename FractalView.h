// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// FractalView.h : interface of the CFractalView class
//


#pragma once

#include "FractalDoc.h"

class CFractalView : public CView
{
protected: // create from serialization only
	CFractalView();
	DECLARE_DYNCREATE(CFractalView)

// Attributes
public:
	CFractal* m_frcFractal;
	CFractalDoc* GetDocument() const;
	CFractal::FractalData GetFractalData() const;

// Utility Functions
private:
	FractalType frtCurrentType;
	void errhandler(char*) const;
	void ChooseFractal(FractalType);
	char* GetNumString(int intDepth) const;
	PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
	void CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CFractalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnUpdateStatusDepth(CCmdUI* pCmdUI);//Me!
	afx_msg void OnFileSaveAsImage();
	afx_msg void OnFractalPreviousdepth();
	afx_msg void OnUpdateFractalPreviousdepth(CCmdUI *pCmdUI);
	afx_msg void OnFractalNextdepth();
	afx_msg void OnUpdateFractalNextdepth(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFractalColorRed(CCmdUI *pCmdUI);
	afx_msg void OnFractalColorRed();
	afx_msg void OnFractalColorGreen();
	afx_msg void OnUpdateFractalColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnFractalColorBlue();
	afx_msg void OnUpdateFractalColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnFractalRandomcolor();
	afx_msg void OnUpdateFractalRandomcolor(CCmdUI *pCmdUI);
	afx_msg void OnFractalCustomecolor();
	afx_msg void OnUpdateFractalCustomecolor(CCmdUI *pCmdUI);
	afx_msg void OnFractalTransparent();
	afx_msg void OnUpdateFractalTransparent(CCmdUI *pCmdUI);
	afx_msg void OnFractalRandomdraw();
	afx_msg void OnUpdateFractalRandomdraw(CCmdUI *pCmdUI);
	afx_msg void OnFractalProperties();
	afx_msg void OnFractalSierpinski();
	afx_msg void OnUpdateFractalSierpinski(CCmdUI *pCmdUI);
	afx_msg void OnFractalSnow();
	afx_msg void OnUpdateFractalSnow(CCmdUI *pCmdUI);
	afx_msg void OnFractalTree();
	afx_msg void OnUpdateFractalTree(CCmdUI *pCmdUI);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in FractalView.cpp
inline CFractalDoc* CFractalView::GetDocument() const
   { return reinterpret_cast<CFractalDoc*>(m_pDocument); }
#endif


// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// FractalDoc.h : interface of the CFractalDoc class
//

#pragma once


struct FractalDataSaver
{
	int intIncR;
	int intIncA;
	int intDepth;
	bool blnIsTr;
	int intInitalR;
	int intInitalA;
	bool blnRandom;
	COLORREF clrColor;
	double dblTilCount;
	FractalType frtFractalType;
	CFractal::ColorMode clmColorMode;
};

class CFractalDoc : public CDocument
{
protected: // create from serialization only
	CFractalDoc();
	void Initialization();
	DECLARE_DYNCREATE(CFractalDoc)

// Attributes
public:
	FractalType m_frtFractalType;
	CFractal::FractalData m_frdFractalData;

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CFractalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};



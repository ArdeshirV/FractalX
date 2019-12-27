// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// FractalDoc.cpp : implementation of the CFractalDoc class
//

#include "stdafx.h"
#include "Fractal.h"

#include "FractalDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFractalDoc

IMPLEMENT_DYNCREATE(CFractalDoc, CDocument)

BEGIN_MESSAGE_MAP(CFractalDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFractalDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_IFractal to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {DF116BC7-030F-47DE-A348-CA46EA558694}
static const IID IID_IFractal =
{ 0xDF116BC7, 0x30F, 0x47DE, { 0xA3, 0x48, 0xCA, 0x46, 0xEA, 0x55, 0x86, 0x94 } };

BEGIN_INTERFACE_MAP(CFractalDoc, CDocument)
	INTERFACE_PART(CFractalDoc, IID_IFractal, Dispatch)
END_INTERFACE_MAP()


// CFractalDoc construction/destruction

CFractalDoc::CFractalDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CFractalDoc::~CFractalDoc()
{
	AfxOleUnlockApp();
}

BOOL CFractalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	Initialization();

	return TRUE;
}

void CFractalDoc::Initialization()
{
	m_frdFractalData.pDC = NULL;
	m_frdFractalData.intIncR = 4;
	m_frtFractalType = Sierpinski;
	m_frdFractalData.intIncA = 10;
	m_frdFractalData.intDepth = 1;
	m_frdFractalData.intInitalA = 0;
	m_frdFractalData.rctRect = NULL;
	m_frdFractalData.blnIsTr = false;
	m_frdFractalData.intInitalR = 30;
	m_frdFractalData.blnRandom = false;
	m_frdFractalData.dblTilCount = 1.4;
	m_frdFractalData.blnFillBack = false;
	m_frdFractalData.pvidReserved = NULL;
	m_frdFractalData.clrColor = RGB(0, 255, 0);
	m_frdFractalData.clmColorMode = CFractal::Green;
}

// CFractalDoc serialization

void CFractalDoc::Serialize(CArchive& ar)
{
	FractalDataSaver l_frcSaver;

	if(ar.IsStoring())
	{
		l_frcSaver.frtFractalType = m_frtFractalType;
		l_frcSaver.intIncR = m_frdFractalData.intIncR;
		l_frcSaver.intIncA = m_frdFractalData.intIncA;
		l_frcSaver.blnIsTr = m_frdFractalData.blnIsTr;
		l_frcSaver.intDepth = m_frdFractalData.intDepth;
		l_frcSaver.clrColor = m_frdFractalData.clrColor;
		l_frcSaver.blnRandom = m_frdFractalData.blnRandom;
		l_frcSaver.intInitalA = m_frdFractalData.intInitalA;
		l_frcSaver.intInitalR = m_frdFractalData.intInitalR;
		l_frcSaver.dblTilCount = m_frdFractalData.dblTilCount;
		l_frcSaver.clmColorMode = m_frdFractalData.clmColorMode;

		ar.Write(&l_frcSaver, sizeof(FractalDataSaver));
	}
	else
	{
		try
		{
			ar.Read(&l_frcSaver, sizeof(FractalDataSaver));
		}
		catch(...)
		{
		}

		m_frtFractalType = l_frcSaver.frtFractalType;
		m_frdFractalData.intIncR = l_frcSaver.intIncR;
		m_frdFractalData.intIncA = l_frcSaver.intIncA;
		m_frdFractalData.blnIsTr = l_frcSaver.blnIsTr;
		m_frdFractalData.intDepth = l_frcSaver.intDepth;
		m_frdFractalData.clrColor = l_frcSaver.clrColor;
		m_frdFractalData.blnRandom = l_frcSaver.blnRandom;
		m_frdFractalData.intInitalA = l_frcSaver.intInitalA;
		m_frdFractalData.intInitalR = l_frcSaver.intInitalR;
		m_frdFractalData.dblTilCount = l_frcSaver.dblTilCount;
		m_frdFractalData.clmColorMode = l_frcSaver.clmColorMode;
	}
}


// CFractalDoc diagnostics

#ifdef _DEBUG
void CFractalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFractalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFractalDoc commands

// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+
// Fractal.h : main header file for the Fractal application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CFractalApp:
// See Fractal.cpp for the implementation of this class
//

class CFractalApp : public CWinApp
{
public:
	CFractalApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFractalApp theApp;

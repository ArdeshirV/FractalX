// Copyright (c) 2002-2003 ardeshirv@protonmail.com, Licensed Under GPLv3+
#pragma once

#include "StdAfx.h"
#include "fractal.h"

#define RGB_GETRED(X) char((X))
#define RGB_GETBLUE(X) char((X)& 0xff)
#define RGB_GETGREEN(X) char(((X)>> 8)& 0xff)

////////////////////////////////////////////////////////////////////////////////
CFractal::CFractal()
{
	m_pMemDC = NULL;
	m_blnIsTr = NULL;
	m_prfdData = NULL;
	m_blnRandom = false;
	//m_frtFractalType = 0;
	m_clr = RGB(0, 255, 0);
	srand((unsigned int)time(NULL));
	m_clmColorMode = CFractal::Green;
}
//------------------------------------------------------------------------------
/*void CFractal::SetFractalType(FractalType frtFractalType)
{
	m_frtFractalType = frtFractalType;
}*/
//------------------------------------------------------------------------------
void CFractal::Draw(const FractalData *pfdData)
{
	if(m_prfdData == NULL || pfdData == NULL)
		throw CFractalException("Data not compelete (m_ptrData was NULL)");

#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		CDC dcMem;
		CBitmap l_bmp;

		this->m_pMemDC = &dcMem;
		this->m_clr = pfdData->clrColor;
		this->m_blnIsTr = pfdData->blnIsTr;
		this->m_blnRandom = pfdData->blnRandom;
		this->m_clmColorMode = pfdData->clmColorMode;

#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
			if(pfdData->blnFillBack)
			{
				CBrush l_brsNew;
				l_brsNew.CreateSolidBrush(RGB(0, 0, 0));
				pfdData->pDC->FillRect(pfdData->rctRect, &l_brsNew);
			}

#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException(
				"Error occured in CFractal::Draw(...) while Fill Background");
		}
#endif

#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
			//Create Independent Bitmap:
			dcMem.CreateCompatibleDC(pfdData->pDC);
			l_bmp.CreateCompatibleBitmap(pfdData->pDC, pfdData->rctRect.Width(),
				pfdData->rctRect.Height());
			dcMem.SelectObject(&l_bmp);
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException(
				"Error while try to create CompatibleDC in CFractal::Draw(...)");
		}
#endif

#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
            Returnee(this->m_prfdData);
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException(
				"Error occured in CFractal::Draw(...) while Returnee(...) Called");
		}
#endif

#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
            //Draw to Real dc.
			pfdData->pDC->BitBlt(0, 0, pfdData->rctRect.Width(),
				pfdData->rctRect.Height(), &dcMem, 0, 0, SRCCOPY);
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException(
				"Error occured in CFractal::Draw(...) while CDC::BitBlt(...) called");
		}
#endif
#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw "Error occured in CFractal::Draw";
	}
#endif
}
//------------------------------------------------------------------------------
void CFractal::Update(const FractalData *pfrdData, ReturneeFractalData *prfdData)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		this->m_prfdData = prfdData;

		CFractal::Draw(pfrdData);

#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException((CString)"Error Occured in " +
			"CFractal::Update(...) while CFractal::Draw(...) Called.");
	}
#endif
}
//------------------------------------------------------------------------------
CDC* CFractal::Get_pMemDC()
{
	return m_pMemDC;
}
//------------------------------------------------------------------------------
COLORREF CFractal::Get_Color(int Depth)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		switch(this->m_clmColorMode)
		{
		case CFractal::Custom:
			return (Depth % 2 == 0 && !Get_Transparent())?	m_clr:
				::abs((long)m_clr - Depth * 10);
		case CFractal::Random:
			return RGB(rand() % 256, rand() % 256, rand() % 256);
		case CFractal::Red:
			return (Get_Transparent())? RGB((256 / Get_Max())* Depth, 0, 0):
				RGB(256 - (256 / Get_Max())* Depth, 0, 0);
		case CFractal::Green:
			return (Get_Transparent())? RGB(0, (256 / Get_Max())* Depth, 0):
				RGB(0, 256 - (256 / Get_Max())* Depth, 0);
		case CFractal::Blue:
			return (Get_Transparent())? RGB(0, 0, (256 / Get_Max())* Depth):
				RGB(0, 0, 256 - (256 / Get_Max())* Depth);
		default:
			return this->m_clr;
		}
#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException("Error occured in CFractal::Get_Color(int)");
	}
#endif
}
//------------------------------------------------------------------------------
bool CFractal::Get_Random()
{
	return this->m_blnRandom;
}
//------------------------------------------------------------------------------
bool CFractal::Get_Transparent()
{
	return this->m_blnIsTr;
}
//------------------------------------------------------------------------------
CFractal::ColorMode CFractal::Get_ColorMode()
{
	return this->m_clmColorMode;
}
//------------------------------------------------------------------------------
int CFractal::Get_Max()
{
	return g_const_int_CFractal_Maximized;
}
////////////////////////////////////////////////////////////////////////////////
CFractal::ReturneeFractalData::ReturneeFractalData()
{
	m_intDepth = 1;
}
//------------------------------------------------------------------------------
CFractal::ReturneeFractalData::ReturneeFractalData(const FractalData *pfrdData)
{
	CFractal::ReturneeFractalData::Set_Data(pfrdData);
}
//------------------------------------------------------------------------------
void CFractal::ReturneeFractalData::Set_Data(const FractalData *pfrdData)
{
	m_intDepth = pfrdData->intDepth;
}
////////////////////////////////////////////////////////////////////////////////
CFractal::CFractalException::CFractalException(CString ErrorMessage, int ErrorLevel)
{
	this->m_intErrorLevel = ErrorLevel;
	this->m_strErrorMessage = ErrorMessage;
}
//------------------------------------------------------------------------------
int CFractal::CFractalException::Get_ErrorLevel()
{
	return this->m_intErrorLevel;
}
//------------------------------------------------------------------------------
CString CFractal::CFractalException::Get_ErrorMessage()
{
	return this->m_strErrorMessage;
}
////////////////////////////////////////////////////////////////////////////////


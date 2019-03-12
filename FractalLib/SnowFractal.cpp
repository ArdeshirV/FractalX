// Copyright (c) 2002-2003 ardeshirv@protonmail.com, Licensed Under GPLv3+
#pragma once

#include "StdAfx.h"
#include "SnowFractal.h"

////////////////////////////////////////////////////////////////////////////////
CSnow::CSnow() : CFractal()
{

}
//------------------------------------------------------------------------------
void CSnow::Draw(const FractalData *pfrdData)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		ReturneeSnowData l_rsd(pfrdData);

		//Initial Area:
		this->m_dblIncrementR = pfrdData->dblTilCount + 4;

		CFractal::Update(pfrdData, &l_rsd);
#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException("Error occured in CSnow::Draw(...)");
	}
#endif
}
//------------------------------------------------------------------------------
inline CRect CSnow::Convertor(const POINT &pnt, const CRect &rct)
{
	double l_intTempX = rct.Width() / Get_IncR(),
		   l_intTempY = rct.Height() / Get_IncR();

	return CRect(int(pnt.x - l_intTempX), int(pnt.y - l_intTempY),
				 int(pnt.x + l_intTempX), int(pnt.y + l_intTempY));
}
//------------------------------------------------------------------------------
void CSnow::CreatePoint(const CRect &rct)
{
	int l_intTemp = rct.Height() / 4;

	this->m_pntTemp[6].x = this->m_pntTemp[0].x = this->m_pntTemp[3].x = rct.Width()
		/ 2 +(this->m_pntTemp[5].x = this->m_pntTemp[4].x = rct.left);
	this->m_pntTemp[1].x = this->m_pntTemp[2].x = rct.right;
	this->m_pntTemp[0].y = rct.top;
	this->m_pntTemp[5].y = this->m_pntTemp[1].y = l_intTemp + rct.top;
	this->m_pntTemp[4].y = this->m_pntTemp[2].y = l_intTemp * 3 + rct.top;
	this->m_pntTemp[3].y = rct.bottom;
	this->m_pntTemp[6].y = rct.Height() / 2 + rct.top;
}
//------------------------------------------------------------------------------
void CSnow::DrawHexagon(const CRect &rct)
{
	POINT l_pntTemp[3];

	l_pntTemp[0] = m_pntTemp[0];
	l_pntTemp[1] = m_pntTemp[2];
	l_pntTemp[2] = m_pntTemp[4];
	Get_pMemDC()->Polygon(l_pntTemp, 3);

	l_pntTemp[0] = m_pntTemp[1];
	l_pntTemp[1] = m_pntTemp[3];
	l_pntTemp[2] = m_pntTemp[5];
	Get_pMemDC()->Polygon(l_pntTemp, 3);
}
//------------------------------------------------------------------------------
void CSnow::Returnee(const ReturneeFractalData *pDataStruct)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
		const ReturneeSnowData* l_rsd;
		ReturneeSnowData l_rsdData[7];
		COLORREF l_clrPenColor;
		CBrush l_brsNew, *l_brsOld;
		CPen l_penNew, *l_penOld;
#endif
#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
			l_rsd = dynamic_cast<const ReturneeSnowData *>(pDataStruct);
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException((CString)
				"Error occur in CSnow::Returnee(...) while creating instance of " +
				"ReturneeSnowData* from ReturneeFractalData");
		}
#endif

#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
			l_rsdData[7];
			l_clrPenColor = Get_Color(l_rsd->m_intDepth);
			l_brsNew.CreateSolidBrush(l_clrPenColor);
			l_brsOld = Get_pMemDC()->SelectObject(&l_brsNew);
			l_penNew.CreatePen(PS_SOLID, 1, l_clrPenColor);
			l_penOld = Get_pMemDC()->SelectObject(&l_penNew);
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException(
				"Error occured in CSnow::Returnee(...) while declered variables.");
		}
#endif

#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
			CreatePoint(l_rsd->m_rctRect);
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException(
				"Error occured in CSnow::Returnee(...) while CreatePoint(...) called");
		}
#endif

#ifdef FractalLibrary_Catch_Error_Defined
		int l_intIndexer = 0;

		try
		{	
#endif
			for(
#ifndef FractalLibrary_Catch_Error_Defined
				int l_intIndexer = 0
#endif
				; l_intIndexer < 7; l_intIndexer++)
			{
				l_rsdData[l_intIndexer].m_intDepth = l_rsd->m_intDepth - 1;
				l_rsdData[l_intIndexer].m_rctRect = Convertor(m_pntTemp[l_intIndexer],
					l_rsd->m_rctRect);
			
				DrawHexagon(l_rsdData[l_intIndexer].m_rctRect);
			}
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			char l_chrArrInteger[10];
			itoa(l_intIndexer, l_chrArrInteger, 8);
			throw CFractal::CFractalException((CString)
				"Error occured in CSnow::Returnee(...) while CSnow::DrawHexagon(...)" +
				"called in a loop in <" + l_chrArrInteger + "> Index");
		}
#endif

#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
            Get_pMemDC()->SelectObject(l_brsOld);
			Get_pMemDC()->SelectObject(l_penOld);
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException((CString)
				"Error occured in CSnow::Returnee(...) while CDC::SelectObject(...) " +
				"called");
		}
#endif
	
		if(l_rsd->m_intDepth <= 1)
			return;

#ifdef FractalLibrary_Catch_Error_Defined
		try
		{
#endif
			for(l_intIndexer = 0; l_intIndexer < 7; l_intIndexer++)
				this->Returnee(&l_rsdData[l_intIndexer]);
#ifdef FractalLibrary_Catch_Error_Defined
		}
		catch(...)
		{
			throw CFractal::CFractalException((CString)
				"Error occured in CSnow::Returnee(...) while CSnow::Returnee(...)" +
				" called in a loop");
		}
#endif

	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException(
			"Error occur in CSnow::Returnee(...)");
	}
}
//------------------------------------------------------------------------------
double CSnow::Get_IncR()
{
	return this->m_dblIncrementR;
}
//------------------------------------------------------------------------------
int CSnow::Get_Max()
{
	return g_const_int_CSnow_Maximized;
}
////////////////////////////////////////////////////////////////////////////////
CSnow::ReturneeSnowData::ReturneeSnowData() : ReturneeFractalData()
{

}
//------------------------------------------------------------------------------
CSnow::ReturneeSnowData::ReturneeSnowData(const FractalData *pfrdData) :
	ReturneeFractalData(pfrdData)
{
	Set_Data(pfrdData);
}
//------------------------------------------------------------------------------
void CSnow::ReturneeSnowData::Set_Data(const FractalData *pfrdData)
{
	CFractal::ReturneeFractalData::Set_Data(pfrdData);
	POINT l_pntTemp = pfrdData->rctRect.CenterPoint();
	int l_intTempX = pfrdData->rctRect.Width() / 4,
		l_intTempY = pfrdData->rctRect.Height() / 4;

	this->m_rctRect.SetRect(l_pntTemp.x - l_intTempX, l_pntTemp.y - l_intTempY,
							l_pntTemp.x + l_intTempX, l_pntTemp.y + l_intTempY);
}
////////////////////////////////////////////////////////////////////////////////


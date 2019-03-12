// Copyright (c) 2002-2003 ardeshirv@protonmail.com, Licensed Under GPLv3+
#pragma once

#include "stdafx.h"
#include "SierpinskiFractal.h"

//------------------------------------------------------------------------------
CSierpinski::CSierpinski() : CFractal()
{
	//m_frtFractalType = 1;
}
//------------------------------------------------------------------------------
/*inline void CSierpinski::GetFractalType()
{
	return m_frtFractalType;
}*/
//------------------------------------------------------------------------------
inline POINT CSierpinski::Midle(const POINT& pntSource1, const POINT& pntSource2)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		POINT l_pntTemp;

		l_pntTemp.x = (pntSource1.x + pntSource2.x) / 2;
		l_pntTemp.y = (pntSource1.y + pntSource2.y) / 2;

		return l_pntTemp;
#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException(
			"Error occured in CSierpinski::Midl(...)");
	}
#endif
}
//------------------------------------------------------------------------------
void CSierpinski::Draw(const FractalData *pfrdData)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		ReturneeSerpineskeyData l_rsd(pfrdData);
	
		CFractal::Update(pfrdData, &l_rsd);
#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException("Error occured in CSierpinski::Draw(...)");
	}
#endif
}
//------------------------------------------------------------------------------
void CSierpinski::Returnee(const ReturneeFractalData *pData)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		const ReturneeSerpineskeyData* l_rsd
			= dynamic_cast<const ReturneeSerpineskeyData *>(pData);

		CBrush l_brs(Get_Color(l_rsd->m_intDepth)), *l_brsOld;

		for(int l_intIndexer = 0; l_intIndexer < 3; l_intIndexer++)
			m_pntTemp[l_intIndexer] = l_rsd->pntArr[l_intIndexer];

		l_brsOld = Get_pMemDC()->SelectObject(&l_brs);
		Get_pMemDC()->SelectStockObject(BLACK_PEN);
		Get_pMemDC()->Polygon(m_pntTemp, 3);
		Get_pMemDC()->SelectObject(l_brsOld);

		if(l_rsd->m_intDepth <= 1)
			return;

		POINT l_pntX, l_pntY, l_pntZ;
		l_pntX = Midle(l_rsd->pntArr[0], l_rsd->pntArr[1]);
		l_pntY = Midle(l_rsd->pntArr[0], l_rsd->pntArr[2]);
		l_pntZ = Midle(l_rsd->pntArr[1], l_rsd->pntArr[2]);

		ReturneeSerpineskeyData l_rsdData;
		l_rsdData.m_intDepth = l_rsd->m_intDepth - 1;

		l_rsdData.pntArr[0] = l_rsd->pntArr[0];
		l_rsdData.pntArr[1] = l_pntX;
		l_rsdData.pntArr[2] = l_pntY;
		this->Returnee(&l_rsdData);

		l_rsdData.pntArr[0] = l_pntX;
		l_rsdData.pntArr[1] = l_rsd->pntArr[1];
		l_rsdData.pntArr[2] = l_pntZ;
		this->Returnee(&l_rsdData);

		l_rsdData.pntArr[0] = l_pntY;
		l_rsdData.pntArr[1] = l_pntZ;
		l_rsdData.pntArr[2] = l_rsd->pntArr[2];
		this->Returnee(&l_rsdData);

#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException("Error occured in CSierpinski::Returnee(...)");
	}
#endif
}
////////////////////////////////////////////////////////////////////////////////
CSierpinski::ReturneeSerpineskeyData::ReturneeSerpineskeyData() :
	CFractal::ReturneeFractalData()
{

}
//------------------------------------------------------------------------------
CSierpinski::ReturneeSerpineskeyData::ReturneeSerpineskeyData(
	const FractalData* pfrdData) : CFractal::ReturneeFractalData(pfrdData)
{
	Set_Data(pfrdData);
}
//------------------------------------------------------------------------------
void CSierpinski::ReturneeSerpineskeyData::Set_Data(const FractalData *pfrdData)
{
	CFractal::ReturneeFractalData::Set_Data(pfrdData);

	pntArr[1].y = pntArr[0].x = 0;
	pntArr[2].y = pntArr[0].y = pfrdData->rctRect.Height() - 1;
	pntArr[1].x = (pntArr[2].x = pfrdData->rctRect.Width())/ 2;
}
////////////////////////////////////////////////////////////////////////////////


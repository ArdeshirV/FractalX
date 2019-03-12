// Copyright (c) 2002-2003 ardeshirv@protonmail.com, Licensed Under GPLv3+
#pragma once

#include "StdAfx.h"
#include "treefractal.h"

////////////////////////////////////////////////////////////////////////////////
CTree::CTree() : CFractal()
{

}
//------------------------------------------------------------------------------
void CTree::Draw(const FractalData *pfdData)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		ReturneeTreeData l_rtd(pfdData);

		//Special this Class & Sub Classes.
		this->m_intIecreaseR = pfdData->intIncR;
		this->m_intIecreaseDegree = pfdData->intIncA;

		CFractal::Update(pfdData, &l_rtd);
#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException("Error occured in CTree::Draw(...)");
	}
#endif
}
//------------------------------------------------------------------------------
inline double CTree::dtor(double Degree)
{
	return (Degree * 0.017453292519943295769236907684886);
}
//------------------------------------------------------------------------------
void CTree::Returnee(const ReturneeFractalData *prfdData)
{
#ifdef FractalLibrary_Catch_Error_Defined
	try
	{
#endif
		const ReturneeTreeData *l_rtd = dynamic_cast<const ReturneeTreeData*>(prfdData);

		POINT pl, pr;
		int R, al, ar;

		if(Get_Random())
		{
			R = l_rtd->m_intR + rand() % (this->m_intIecreaseR * 2);
			al = l_rtd->m_intA - rand() % (this->m_intIecreaseDegree * 2);
			ar = l_rtd->m_intA + rand() % (this->m_intIecreaseDegree * 2);
		}
		else
		{
			R = l_rtd->m_intR + this->m_intIecreaseR;
			al = l_rtd->m_intA - this->m_intIecreaseDegree;
			ar = l_rtd->m_intA + this->m_intIecreaseDegree;
		}

		pl.x = l_rtd->m_pntRoot.x +	int(mSin(ar) * (l_rtd->m_intR));
		pl.y = l_rtd->m_pntRoot.y - int(mCos(ar) * (l_rtd->m_intR));
		pr.x = l_rtd->m_pntRoot.x + int(mSin(al) * (l_rtd->m_intR));
		pr.y = l_rtd->m_pntRoot.y - int(mCos(al) * (l_rtd->m_intR));
	
		CPen l_penNew(PS_SOLID, 1, Get_Color(l_rtd->m_intDepth)),
			*l_penOld = Get_pMemDC()->SelectObject(&l_penNew);
		Get_pMemDC()->MoveTo(l_rtd->m_pntRoot);
		Get_pMemDC()->LineTo(pl);
		Get_pMemDC()->MoveTo(l_rtd->m_pntRoot);
		Get_pMemDC()->LineTo(pr);
		Get_pMemDC()->SelectObject(&l_penOld);

		if(l_rtd->m_intDepth <= 1)
		{
			CPen *l_penOld, l_penNew(PS_SOLID, 1, RGB(128, 128, 128));
			l_penOld = Get_pMemDC()->SelectObject(&l_penNew);
			Get_pMemDC()->MoveTo(pr);
			Get_pMemDC()->LineTo(pr.x, pr.y - 2);
			Get_pMemDC()->MoveTo(pl);
			Get_pMemDC()->LineTo(pl.x, pl.y - 2);
			Get_pMemDC()->SelectObject(l_penOld);
			return;
		}

		ReturneeTreeData l_rtdData;
		l_rtdData.m_intDepth = l_rtd->m_intDepth - 1;
		l_rtdData.m_intR = R;

		l_rtdData.m_intA = ar;
		l_rtdData.m_pntRoot = pl;
		Returnee(&l_rtdData);

		l_rtdData.m_intA = al;
		l_rtdData.m_pntRoot = pr;
		Returnee(&l_rtdData);
#ifdef FractalLibrary_Catch_Error_Defined
	}
	catch(CFractal::CFractalException exp)
	{
		throw exp;
	}
	catch(...)
	{
		throw CFractal::CFractalException("Error occured in CTree::Returnee(...)");
	}
#endif
}
//------------------------------------------------------------------------------
int CTree::Get_IncR()
{
	return this->m_intIecreaseR;
}
//------------------------------------------------------------------------------
int CTree::Get_IncA()
{
	return this->m_intIecreaseDegree;
}
//------------------------------------------------------------------------------
int CTree::Get_Max()
{
	return g_const_int_CTree_Maximized;
}
//------------------------------------------------------------------------------
inline double CTree::mSin(double d)
{
	return sin(dtor(d));
}
//------------------------------------------------------------------------------
inline double CTree::mCos(double d)
{
	return cos(dtor(d));
}
////////////////////////////////////////////////////////////////////////////////
CTree::ReturneeTreeData::ReturneeTreeData() : ReturneeFractalData()
{
	m_intR = m_intA = m_pntRoot.x = m_pntRoot.y = 0;
}
//------------------------------------------------------------------------------
CTree::ReturneeTreeData::ReturneeTreeData(const FractalData *pfrdData) :
	ReturneeFractalData(pfrdData)
{
	this->Set_Data(pfrdData);
}
//------------------------------------------------------------------------------
void CTree::ReturneeTreeData::Set_Data(const FractalData *pfrdData)
{
	CFractal::ReturneeFractalData::Set_Data(pfrdData);

	m_intA = pfrdData->intInitalA;
	m_intR = pfrdData->intInitalR;
	m_pntRoot.x = pfrdData->rctRect.Width() / 2;
	m_pntRoot.y = pfrdData->rctRect.Height() - 1;
}
////////////////////////////////////////////////////////////////////////////////


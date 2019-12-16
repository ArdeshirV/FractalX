// Copyright (c) 2002-2003 ardeshirv@protonmail.com, Licensed Under GPLv3+
#pragma once

#ifndef CSnow_Class_1
#define CSnow_Class_1

#include "fractal.h"

class CSnow : public CFractal
{
private:
	POINT m_pntTemp[7];
	double m_dblIncrementR;

	//Private Overrided Functions:
	void Returnee(const ReturneeFractalData *pDataStruct);

protected:
	//Utility Functions:
	void DrawHexagon(const CRect&);
	void CreatePoint(const CRect &);
	CRect Convertor(const POINT &, const CRect &);
	
	//Data Access:
	virtual double Get_IncR();

	//Inner Types:
	struct ReturneeSnowData : public CFractal::ReturneeFractalData
	{
		CRect m_rctRect;

		//Constructor:
		ReturneeSnowData();

		//Constructor:
        ReturneeSnowData(const FractalData *pfrdData);
        
		//Virtual Function:
		void Set_Data(const FractalData *pfrdData);
	};

public:
	//Constructor:
	CSnow();

	//Public Overrided Function:
	int Get_Max();

	//Public Overrided Function:
	void Draw(const FractalData *);

	//enum private:
	enum
	{
		g_const_int_CSnow_Maximized = 5
	};
};

#endif


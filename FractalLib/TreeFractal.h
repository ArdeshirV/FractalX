// Copyright (c) 2002-2003 ardeshirv@protonmail.com, Licensed Under GPLv3+
#pragma once

#ifndef CTree_Class_1
#define CTree_Class_1

#include "fractal.h"
#include <cmath>

class CTree : public CFractal
{
private:
	//Data:
	int m_intIecreaseR;
	int m_intIecreaseDegree;

	//Private Overrided Functions:
	void Returnee(const ReturneeFractalData *prfdData);

protected:
	//Utility Function:
	double dtor(double d);
	double mSin(double d);
	double mCos(double d);

	//Data Access:
	int Get_IncR();
	int Get_IncA();

	//Utility Structure:
	struct ReturneeTreeData : public CFractal::ReturneeFractalData
	{
		int m_intR;
		int m_intA;
		POINT m_pntRoot;

		//Constructor:
		ReturneeTreeData();

		//Constructor:
		ReturneeTreeData(const FractalData *pfrdData);

		//Public virtual function:
		void Set_Data(const FractalData *pfrdData);
	};

public:
	//Constructor:
	CTree();

	//Public Overrided Functions:
	int Get_Max();
	void Draw(const FractalData *pfdData);

	//enum private:
	enum
	{
		g_const_int_CTree_Maximized = 12
	};
};

#endif

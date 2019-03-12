// Copyright (c) 2002-2003 ardeshirv@protonmail.com, Licensed Under GPLv3+
#pragma once

#ifndef Saeed_CSierpinski_Class_1
#define Saeed_CSierpinski_Class_1

#include "stdafx.h"
#include "Fractal.h"

class CSierpinski : public CFractal
{
private:
	//Temp Point Array for best code.
	POINT m_pntTemp[3];

protected:
	//Private Overrided Functions:
	void Returnee(const ReturneeFractalData *pData);

	//Utility Functions:
	POINT Midle(const POINT&, const POINT&);

	//Inner Types:
	struct ReturneeSerpineskeyData : public CFractal::ReturneeFractalData
	{
		//Next Frame.
		POINT pntArr[3];

		//Constructor.
		ReturneeSerpineskeyData();

		//Constructor.
		ReturneeSerpineskeyData(const FractalData *);

		//Overrided Function.
		void Set_Data(const FractalData *);
	};

public:
	//Constructor:
	CSierpinski();

	//Public Overrided Function:
	void GetFractalType();
	void Draw(const FractalData *);
};

#endif

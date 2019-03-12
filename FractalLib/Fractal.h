// Copyright (c) 2002-2003 ardeshirv@protonmail.com, Licensed Under GPLv3+
#pragma once

#ifndef Saeed_CFractal_Class_1
#define Saeed_CFractal_Class_1

#define FractalLibrary_Catch_Error_Defined


class CFractal
{
	//Forward:
protected:
	struct ReturneeFractalData;

public:
	enum ColorMode;
	struct FractalData;

private:
	CDC *m_pMemDC;
	ReturneeFractalData *m_prfdData;

	//Data:
	COLORREF m_clr;
	bool m_blnIsTr;
	bool m_blnRandom;
	ColorMode m_clmColorMode;
	virtual void Returnee(const ReturneeFractalData *) = 0;

protected:
	//Data Access:
	virtual bool Get_Random();
	virtual bool Get_Transparent();
	virtual ColorMode Get_ColorMode();
	virtual COLORREF Get_Color(int Depth = 0);

	//Protected Functions:
	CDC* Get_pMemDC();
	//void SetFractalType(FractalType);
	void Update(const FractalData *, ReturneeFractalData *);

	//Protected Fractal Data:
	struct ReturneeFractalData
	{
		//Public Data:
		int m_intDepth;

		//Constructor:
		ReturneeFractalData();

		//Constructor:
		ReturneeFractalData(const FractalData *pfrdData);

		//Public virtual function:
		virtual void Set_Data(const FractalData *pfrdData);
	};

public:
	//Constructor:
	CFractal();

	//Get Maximized Depth for Fractal:
	virtual int Get_Max();
	// Get current fractal type in its object:
	//virtual void GetFractalType() = 0;
	//Draw Fractal on screen:
	virtual void Draw(const FractalData *pfdData);

	//enum private Data:
	enum
	{
		g_const_int_CFractal_Maximized = 10
	};

	//Inner Types
	enum ColorMode
	{
		Red = 0,
		Green = 1,
		Blue = 2,
		Custom = 3,
		Random = 4
	};

	struct FractalData
	{
		//Pointer to Device Context Class.
		CDC *pDC;
		int intIncR;
		int intIncA;
		int intDepth;
        bool blnIsTr;
		CRect rctRect;
		int intInitalR;
		int intInitalA;
		bool blnRandom;
		double dblTilCount;
		bool blnFillBack;
		COLORREF clrColor;
		ColorMode clmColorMode;
		//Don't use in this edition.
		void *pvidReserved;
	};

	class CFractalException
	{
	private:
		//Error Level.
		int m_intErrorLevel;
		//Error Message.
		CString m_strErrorMessage;

	public:
		//Constructor:
		CFractalException(CString ErrorMessage, int ErrorLevel = 1);

		//Get Error Level.
		int Get_ErrorLevel();
		//Get Error Message.
		CString Get_ErrorMessage();
	};
};

#endif


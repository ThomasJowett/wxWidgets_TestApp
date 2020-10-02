#include "stdafx.h"

#include "Plot.h"
#include "CartesianPlotData.h"

// ----------------------------------------------------------------------------
CartesianPlotData::CartesianPlotData(void)
{
	m_Title = "Plots";
	m_DefaultLineColor = *wxBLUE;
	m_DefaultTextColor = *wxRED;

    m_cXStart = -180;
	m_cXEnd = 180;

    m_cYStart = 0;
	m_cYEnd = 1;

    //m_cXEnd = 8;
    //m_cYEnd = 14;

	m_intSize = sizeof(double);

	wxBrush * brush1 = wxTheBrushList->FindOrCreateBrush(wxColour(255, 174, 42));		// *wxYELLOW
	wxBrush * brush2 = wxTheBrushList->FindOrCreateBrush(*wxGREEN);
	wxBrush * brush3 = wxTheBrushList->FindOrCreateBrush(*wxRED);
	wxBrush * brush4 = wxTheBrushList->FindOrCreateBrush(*wxBLUE);
	wxBrush * brush5 = wxTheBrushList->FindOrCreateBrush(*wxCYAN);
	wxBrush * brush6 = wxTheBrushList->FindOrCreateBrush(*wxLIGHT_GREY);
	wxBrush * brush7 = wxTheBrushList->FindOrCreateBrush(wxColour(197, 255, 0));		// Light lime
	wxBrush * brush8 = wxTheBrushList->FindOrCreateBrush(wxColour(192, 0, 255));		// Magenta
	wxBrush * brush9 = wxTheBrushList->FindOrCreateBrush(wxColour(42, 128, 42));		// Dark Green
	wxBrush * brush10 = wxTheBrushList->FindOrCreateBrush(wxColour(128, 0, 128));		// Purple-Brown

	std::vector<double> tempX;
	std::vector<double> tempY;

	//double tmpX[] = {1,2,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	//double tmpY[] = {1,1,2, 2, 3, 3, 4, 4, 5,  5,  6,  6,  7,  7};

//   m_tempX.reserve(xSize1);
//   m_tempY.reserve(ySize1);

	//m_tempX.assign(tmpX1, tmpX1 + xSize1);
	//m_tempY.assign(tmpY1, tmpY1 + xSize1);

	int size = 13;
	//					1			2				3			4			5			6				7			8			9				10			11			12			13
	double tmpX1[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180};
	double tmpY1[] = {0.029765547,	0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.59765547, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.029765547};

	double tmpX2[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY2[] = { 0.29765547,	0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.0856682, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.29765547 };

	double tmpX3[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY3[] = { 0.59765547,	0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.0856682, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.59765547 };

	double tmpX4[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY4[] = { 0.09765547,	0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.09765547, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.09765547 };

	double tmpX5[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY5[] = { 0.65547,		0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.35547, 0.999141563, 0.497571158, 0.0306197971,		0.400856682, 0.498425176, 0.65547 };

	double tmpX6[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY6[] = { 0.029765547,	0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.000856682, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.029765547 };

	double tmpX7[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY7[] = { 0.129765547,	0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.129765547, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.129765547 };

	double tmpX8[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY8[] = { 0.029765547,	0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.000856682, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.029765547 };

	double tmpX9[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY9[] = { 0.729765547,	0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.529765547, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.729765547 };

	double tmpX10[] = { -180,		-150,		-120,			-90,		-60,		-30,			0,			30,			60,				90,			120,		150,		180 };
	double tmpY10[] = { 0.529765547, 0.497572851, 0.300856682, 0.0306197971, 0.498425176, 0.999141563, 0.529765547, 0.999141563, 0.497571158, 0.0306197971, 0.400856682, 0.498425176, 0.529765547 };

	for (int i = 0; i < size; i++)
	{
		tmpY2[i] *= 0.8;
		tmpY3[i] *= 0.74;
		tmpY4[i] *= 0.44;
		tmpY5[i] *= 0.31;
		tmpY6[i] *= 0.2;
		tmpY7[i] *= 0.36;
		tmpY8[i] *= 0.51;
		tmpY9[i] *= 0.66;
		tmpY10[i] *= 0.8;
	}

	tempX.assign(tmpX1, tmpX1 + size);
	tempY.assign(tmpY1, tmpY1 + size);

	PopulatePlotData("M,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush1);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX2, tmpX2 + size);
	tempY.assign(tmpY2, tmpY2 + size);

	PopulatePlotData("F,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush2);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX3, tmpX3 + size);
	tempY.assign(tmpY3, tmpY3 + size);

	PopulatePlotData("K,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush3);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX4, tmpX4 + size);
	tempY.assign(tmpY4, tmpY4 + size);

	PopulatePlotData("G,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush4);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX5, tmpX5 + sizeof(tmpX5) / m_intSize);
	tempY.assign(tmpY5, tmpY5 + sizeof(tmpY5) / m_intSize);

	PopulatePlotData("P,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush5);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX6, tmpX6 + size);
	tempY.assign(tmpY6, tmpY6 + size);

	//PopulatePlotData("MF,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush6);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX7, tmpX7 + size);
	tempY.assign(tmpY7, tmpY7 + size);

	//PopulatePlotData("MK,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush7);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX8, tmpX8 + size);
	tempY.assign(tmpY8, tmpY8 + size);

	//PopulatePlotData("FK,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush8);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX9, tmpX9 + size);
	tempY.assign(tmpY9, tmpY9 + size);

	//PopulatePlotData("PK,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush9);

	tempX.clear();
	tempY.clear();
	tempX.assign(tmpX10, tmpX10 + size);
	tempY.assign(tmpY10, tmpY10 + size);

	//PopulatePlotData("MFK,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving", tempX, tempY, brush10);

    m_StartXpercent = 10;
    m_StartYpercent = 10;

	if (m_cXEnd > m_cYEnd)
	{
		m_isPortrate = false;

		m_EndXpercent = 5;
		m_EndYpercent = 20;
	}
	else
	{
		m_isPortrate = true;

		m_EndXpercent = 20;
		m_EndYpercent = 5;
	}

	m_LegendPositionXDelta = 45;
	m_DefaultBorderWidth = 3;
	m_DefaultPlotPenWidth = 2;
	m_DefaultGridWidth = 1;

	m_VerticalCount = size - 2;		//	m_cXEnd - m_cXStart;
	m_HorizontalCount = 9;			// m_cYEnd - m_cYStart;

    m_CaptionVisible = true;
    m_CaptionPrecision = 0;
}
// ----------------------------------------------------------------------------
void CartesianPlotData::PopulatePlotData(std::string plotName, std::vector<double> x, std::vector<double> y, wxBrush * brush)
{
	int xSize = x.size();
	int ySize = y.size();

	if (xSize != ySize)
		throw;

	Plot plot(plotName);

	std::vector<std::pair <double, double>> plotData;

	for (int i = 0; i < xSize; i++ )
	{
		std::pair <double, double> cell = std::make_pair (x[i], y[i]);

		plotData.push_back(cell);
	}

	plot.SetPlotValues(plotData);
	plot.brush = brush;

	m_plotData.push_back(plot);
}
// ----------------------------------------------------------------------------
CartesianPlotData::~CartesianPlotData(void)
{
}
// ----------------------------------------------------------------------------
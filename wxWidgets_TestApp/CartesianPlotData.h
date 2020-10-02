#pragma once

#include <wx/string.h>
#include <wx/colordlg.h>
#include <wx/brush.h>

#include <vector>

#include "Plot.h"

// ----------------------------------------------------------------------------
class CartesianPlotData
{
public:

	CartesianPlotData(void);
	~CartesianPlotData(void);

public:

	wxString m_Title;
	wxColour m_DefaultLineColor;
	wxColour m_DefaultTextColor;

	int m_intSize;

	int m_StartXpercent;
    int m_StartYpercent;
    int m_EndXpercent;
    int m_EndYpercent;

    int m_cXStart;
    int m_cYStart;
    int m_cXEnd;
    int m_cYEnd;

    int m_NSamples;

    std::vector<double> m_tempX;
    std::vector<double> m_tempY;

    std::vector< Plot > m_plotData;

	bool m_isPortrate;

	int m_LegendPositionXDelta;

	int m_DefaultBorderWidth;
	int m_DefaultPlotPenWidth;
	int m_DefaultGridWidth;
	
	int m_VerticalCount;
	int m_HorizontalCount;
    bool m_CaptionVisible;
    int m_CaptionPrecision;


private:

	void PopulatePlotData(std::string plotName, std::vector<double> x, std::vector<double> y, wxBrush * brush);

	//wxFontData* m_fontDataValue;
	//wxFont* m_fontValue;
};
// ----------------------------------------------------------------------------

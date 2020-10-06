#include "stdafx.h"
#include "PlotGeneratorHelper.h"

#include <ctime>

PlotGeneratorHelper::PlotGeneratorHelper()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	m_Names.push_back("M,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving");
	m_Names.push_back("F,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving");
	m_Names.push_back("K,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving");
	m_Names.push_back("G,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving");
	m_Names.push_back("P,BTR80_NATO_AVT-127,BigATGM,Single,1500m,Firer/Target=Static/Moving");

	m_Brushes.push_back(wxTheBrushList->FindOrCreateBrush(wxColour(255, 174, 42)));
	m_Brushes.push_back(wxTheBrushList->FindOrCreateBrush(*wxGREEN));
	m_Brushes.push_back(wxTheBrushList->FindOrCreateBrush(*wxRED));
	m_Brushes.push_back(wxTheBrushList->FindOrCreateBrush(*wxBLUE));
	m_Brushes.push_back(wxTheBrushList->FindOrCreateBrush(*wxCYAN));
}

void PlotGeneratorHelper::AddRandomPlotline(PolarPlotData* polarPlotData, int datapoints)
{
	it++;
	if (it >= m_Names.size())
	{
		it = 0;
	}
	std::vector<double> tempX;
	std::vector<double> tempY;

	for (int i = 1; i <= datapoints; i++)
	{
		tempX.push_back((i * (360.0/(double)datapoints)) - 180);
	}

	for (int i = 0; i < datapoints; i++)
	{
		tempY.push_back(rnd() + (it * 0.2));
	}

	polarPlotData->AddPlotLine(m_Names[it], tempX, tempY, m_Brushes[it]);
}

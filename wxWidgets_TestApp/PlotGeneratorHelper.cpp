#include "stdafx.h"
#include "PlotGeneratorHelper.h"

#include <ctime>

PlotGeneratorHelper::PlotGeneratorHelper(unsigned int seed)
{
	std::srand(seed);

	m_Names.push_back("Example 1");
	m_Names.push_back("Example 1");
	m_Names.push_back("Example 1");
	m_Names.push_back("Example 1");
	m_Names.push_back("Example 1");

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
	if (datapoints == 5)
		tempX = std::vector<double>({ -180,-70, -30, 0, 80 });

	for (int i = 0; i < datapoints; i++)
	{
		tempY.push_back(rnd() + (it * 0.2));
	}

	polarPlotData->AddPlotLine(m_Names[it], tempX, tempY, m_Brushes[it]);
}

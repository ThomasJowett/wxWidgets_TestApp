#pragma once

#include "PolarPlotData.h"

class PlotGeneratorHelper
{
public:
	PlotGeneratorHelper();
	void AddRandomPlotline(PolarPlotData* polarPlotData, int datapoints);
private:
	std::vector<std::string> m_Names;
	std::vector<wxBrush*> m_Brushes;
	int it = 0;

	double rnd() { return ((double)rand() / (RAND_MAX)) * 0.1; }
};
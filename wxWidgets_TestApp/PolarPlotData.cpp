#include "stdafx.h"

#include "Plot.h"
#include "PolarPlotData.h"



// ----------------------------------------------------------------------------
PolarPlotData::PolarPlotData(std::string title, std::string xAxisLabel, std::string yAxisLabel)
	:m_Title(title), m_XAxisLabel(xAxisLabel), m_YAxisLabel(yAxisLabel)
{
}
// ----------------------------------------------------------------------------
void PolarPlotData::AddPlotLine(std::string plotName, std::vector<double> x, std::vector<double> y, wxBrush* brush)
{
	int xSize = x.size();
	int ySize = y.size();

	if (xSize != ySize)
		throw;


	std::vector<std::pair <double, double>> plotData;

	for (int i = 0; i < xSize; i++)
	{
		std::pair <double, double> cell = std::make_pair(x[i], y[i]);

		plotData.push_back(cell);
	}

	Plot plot;
	plot.Name = plotName;
	plot.PlotValues = plotData;
	plot.Brush = brush;

	m_PlotData.push_back(plot);
}
// ----------------------------------------------------------------------------
PolarPlotData::~PolarPlotData()
{
}
// ----------------------------------------------------------------------------
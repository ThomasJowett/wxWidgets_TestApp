#pragma once

#include <wx/string.h>
#include <wx/colordlg.h>
#include <wx/brush.h>

#include <vector>

#include "Plot.h"

// ----------------------------------------------------------------------------
class PolarPlotData
{
public:
	PolarPlotData(std::string title);
	~PolarPlotData();

	const std::string& Title() const { return m_Title; }
	const std::vector<Plot>& PlotData() const { return m_PlotData; }
	const int NumberOfPlots() { return m_PlotData.size(); }

	void AddPlotLine(std::string plotName, std::vector<double> x, std::vector<double> y, wxBrush* brush);

	std::vector<Plot>::const_iterator begin() const { return m_PlotData.begin(); }
	std::vector<Plot>::const_iterator end() const { return m_PlotData.end(); }
	std::vector<Plot>::const_reverse_iterator rbegin() const { return m_PlotData.rbegin(); }
	std::vector<Plot>::const_reverse_iterator rend() const { return m_PlotData.rend(); }

	std::vector<Plot>::iterator begin() { return m_PlotData.begin(); }
	std::vector<Plot>::iterator end() { return m_PlotData.end(); }
	std::vector<Plot>::reverse_iterator rbegin() { return m_PlotData.rbegin(); }
	std::vector<Plot>::reverse_iterator rend() { return m_PlotData.rend(); }

private:
	std::string m_Title;
    std::vector< Plot > m_PlotData;

	double m_MaxValue;
};
// ----------------------------------------------------------------------------

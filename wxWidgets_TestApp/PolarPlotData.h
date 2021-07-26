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
	PolarPlotData(std::string title, std::string xAxisLabel = "", std::string yAxisLabel = "");
	~PolarPlotData();

	const std::string& Title() const { return m_Title; }
	const std::vector<Plot>& PlotData() const { return m_PlotData; }
	std::vector<Plot>& PlotData() { return m_PlotData; }
	const int NumberOfPlots() { return m_PlotData.size(); }
	const std::string& XAxisLabel() const { return m_XAxisLabel; }
	const std::string& YAxisLabel() const { return m_YAxisLabel; }

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
	std::string m_XAxisLabel;
	std::string m_YAxisLabel;

	double m_MaxValue;
};
// ----------------------------------------------------------------------------

#pragma once

#include <vector>
#include <set>
#include <string>

#include "wx/wxprec.h"
// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
struct Plot
{
	std::string Name;
	wxBrush * Brush = nullptr;
	std::vector<std::pair<double, double>> PlotValues;
	bool IsVisible;

	std::vector<std::pair<double, double>>::const_iterator begin() const { return PlotValues.begin(); }
	std::vector<std::pair<double, double>>::const_iterator end() const { return PlotValues.end(); }
	std::vector<std::pair<double, double>>::const_reverse_iterator rbegin() const { return PlotValues.rbegin(); }
	std::vector<std::pair<double, double>>::const_reverse_iterator rend() const { return PlotValues.rend(); }
};
// ----------------------------------------------------------------------------

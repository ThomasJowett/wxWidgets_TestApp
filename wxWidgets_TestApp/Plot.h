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
class Plot
{

public:

	Plot(void);
	Plot(std::string name);
	~Plot(void);

	void setName(std::string name);
	std::string getName();

	wxBrush * brush;

	std::vector<std::pair<double, double>> GetPlotValues();
	void SetPlotValues(std::vector<std::pair<double, double>> plotValues);

private:
	std::vector<std::pair<double, double>> mPlotValues;
	std::string mName;
};
// ----------------------------------------------------------------------------

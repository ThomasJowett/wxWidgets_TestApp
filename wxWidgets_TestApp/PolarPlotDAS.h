#pragma once

#include <wx/window.h>	
#include <wx/listctrl.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/checklst.h>

#include "wxPolarPlot.h"
#include "PolarPlotData.h"

class PolarPlotDAS :
	public wxDialog
{
public:
	enum
	{
		ID_PolarPlot = wxID_ANY,
		ID_LinearPlot = wxID_ANY,
		ID_PlotLegend = wxID_ANY,
		ID_ListBox_Elevations = wxID_ANY,
		ID_CheckListBox_Metrics = wxID_ANY,
	};

	PolarPlotDAS(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		std::vector<PolarPlotData> plotData,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE
	);
	~PolarPlotDAS(void);

	void OnPlotLineToggle(wxCommandEvent& event);
	void OnElevationSelected(wxCommandEvent& event);

private:
	wxPlotStyle* mPlotStyle;

	wxListBox* mElevationsListBox;

	wxCheckListBox* mMetricsListBox;

	std::vector<PolarPlotData> mPlotData;

	wxPolarPlot* mPolarPlot;
	wxPolarPlot* mLinearPlot;
	wxPlotLegend* mPlotLegend;
};


#pragma once

#include "wx/window.h"			
#include "wx/listctrl.h"
#include <wx/grid.h>
#include <wx/button.h>

#define ID_TARGET_LISTBOX       1
#define ID_ELEVATION_LISTBOX    2
#define ID_MINMAX_LISTBOX       3
#define ID_DISPERSION_LISTBOX   4
#define ID_THREAT_LISTBOX       5
#define ID_RANGE_LISTBOX        6 
#define ID_SHOT_LISTBOX         7
#define ID_TARGETSTATUS_LISTBOX 8
#define ID_FIRERSTATUS_LISTBOX  9
#define ID_DEGRADATION_LISTBOX  10
#define ID_POLAR_BUTTON			11
#define ID_POLARLEGEND_BUTTON	12
#define ID_LINEAR_BUTTON		13
#define ID_LINEARLEGEND_BUTTON	14

#include "wxPolarPlot.h"

// ----------------------------------------------------------------------------
class PolarPlotWindow : public wxDialog
{
public:
	PolarPlotWindow(wxWindow *parent, wxWindowID, const wxString& title, const wxPoint &pos, const wxSize &size, long style);
	~PolarPlotWindow(void);

private:

	void OnButtonPolar(wxCommandEvent& event);
	void OnButtonPolarLegend(wxCommandEvent& event);
	void OnButtonLinear(wxCommandEvent& event);
	void OnButtonLinearLegend(wxCommandEvent& event);

	wxButton* mPolarExport;
	wxButton* mPolarLegendExport;
	wxButton* mLinearExport;
	wxButton* mLinearLegendExport;

	wxPlotStyle* m_PlotStyle;

	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};
// ----------------------------------------------------------------------------


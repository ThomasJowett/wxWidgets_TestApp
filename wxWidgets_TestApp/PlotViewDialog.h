#pragma once

#include "wx/window.h"
#include "CartesianPlotData.h"


#define wxTestDialogStyle (wxOK | wxCANCEL | wxCENTRE | wxWS_EX_VALIDATE_RECURSIVELY)		// wxDEFAULT_DIALOG_STYLE
						// wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX

class wxPlot;

// ----------------------------------------------------------------------------
class PlotViewDialog : public wxDialog
{
public:

	PlotViewDialog(wxWindow *parent, wxWindowID, const wxString& title , const wxPoint &pos, const wxSize &size, long style);
	~PlotViewDialog(void);

	//void GraphDataInit(KillZonesData * graphData);

	//void OnPaint( wxPaintEvent &event );
	//void OnInitDialog( wxInitDialogEvent &event );
	//void OnClose( wxCloseEvent &event );
	void OnOkClick( wxCommandEvent &event );

private:
	wxPlot*	m_drawPanel;

    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()};
// ----------------------------------------------------------------------------

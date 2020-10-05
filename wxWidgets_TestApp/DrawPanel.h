#pragma once

#include "wx/dcgraph.h"

class CartesianPlotData;
//class wxPaintDC;

// ----------------------------------------------------------------------------
class wxPlot : public wxPanel
{
	struct wxPlotStyle
	{
		wxColour TitleColour = *wxBLACK;
		wxColour LabelsColour = *wxBLACK;
		wxColour BackgroundColour = *wxWHITE;
		wxColour GridLineColour = *wxLIGHT_GREY;
		wxPenStyle GridLineStyle = wxPENSTYLE_SOLID;
		int GridLineWidth = 1;
		wxColour BorderColour = *wxLIGHT_GREY;
		int BorderWidth = 1;
		wxPenStyle BorderStyle = wxPENSTYLE_SOLID;
		wxPenStyle PlotLineStyle = wxPENSTYLE_SOLID;
		int PlotLineWidth = 2;
	};
public:

	const double PI = 3.1415926535897931;
	const double PId2 = PI / 2.0;
	const double PI2 = PI * 2.0;
	const double PId2degree = PI / 180.0;

	bool m_bIsPolarPlot;

	wxPlot(wxWindow *parent,
		CartesianPlotData * graphData,
		bool useTitle = true,
		bool useLegend = true,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL | wxNO_BORDER,
		const wxString& name = wxPanelNameStr
	);

	~wxPlot(void);

	void OnPaint(wxPaintEvent &event);
	void OnEraseBackground(wxEraseEvent& event) {}
	void OnSize(wxSizeEvent& event) { Refresh(); }

	wxPlotStyle& Style() { return m_PlotStyle; }

private:

	void DrawGridWithCaptions(wxGCDC* dc, int borderX, int borderY, int width, int height);
	void DrawPolarGridWithCaptions(wxGCDC* dc, int borderX, int borderY, int width, int height);

	void DrawPlots(wxGCDC* dc, int borderX, int borderY, int width, int height);
	void DrawPolarPlots(wxGCDC* dc, int borderX, int borderY, int width, int height);

	void DrawGridLegend(wxGCDC* dc, int borderX, int borderY, int width, int height);
	void DrawPolarGridLegend(wxGCDC* dc, int borderX, int borderY, int width, int height);

	CartesianPlotData	  * m_graphData;
	bool					m_useTitle;
	bool					m_useLegend;

	wxPlotStyle m_PlotStyle;
};
// ----------------------------------------------------------------------------

class DrawLegend : public wxPanel
{
public:

	DrawLegend(wxWindow *parent,
		CartesianPlotData * graphData,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL | wxNO_BORDER,
		const wxString& name = wxPanelNameStr);

	~DrawLegend(void);

	void OnPaint(wxPaintEvent &event);

private:

	CartesianPlotData	  * m_graphData;

	DECLARE_EVENT_TABLE()
};

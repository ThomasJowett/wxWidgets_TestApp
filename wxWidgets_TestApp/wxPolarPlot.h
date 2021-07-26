#pragma once

#include "wx/dcgraph.h"

class PolarPlotData;
//class wxPaintDC;

// ----------------------------------------------------------------------------
struct wxPlotStyle
{
	wxColour TitleColour = *wxBLACK;
	wxColour CaptionsColour = *wxBLACK;
	wxColour BackgroundColour = *wxWHITE;
	wxColour GridLineColour = *wxLIGHT_GREY;
	wxPenStyle GridLineStyle = wxPENSTYLE_SOLID;
	int GridLineWidth = 1;
	wxPenStyle PlotLineStyle = wxPENSTYLE_SOLID;
	int PlotLineWidth = 2;
};
// ----------------------------------------------------------------------------
class wxPolarPlot : public wxPanel
{
public:
	wxPolarPlot(wxWindow* parent,
		PolarPlotData* graphData,
		wxPlotStyle* plotStyle = new wxPlotStyle(),
		bool useTitle = true,
		bool useLegend = true,
		bool isLinear = false,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL | wxNO_BORDER,
		const wxString& name = wxPanelNameStr
	);

	~wxPolarPlot(void);

	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event) {}
	void OnSize(wxSizeEvent& event) { Refresh(); }

	wxPlotStyle* Style() { return m_PlotStyle; }

	void ShowTitle(bool showTitle) { m_useTitle = showTitle; }
	void ShowLegend(bool showLegend) { m_useLegend = showLegend; }

	void SetPlotData(PolarPlotData* graphData) { m_GraphData = graphData; Refresh(); }

private:

	void DrawLinearGridWithCaptions(wxDC* dc, wxRect gridArea);
	void DrawPolarGridLines(wxDC* dc, wxRect gridArea);

	void DrawLinearPlots(wxDC* dc, wxRect gridArea);
	void DrawPolarPlots(wxDC* dc, wxRect gridArea);

	void DrawPolarGridCaptions(wxDC* dc, wxRect gridArea);

	PolarPlotData* m_GraphData;
	bool m_IsLinear;
	bool m_useTitle;
	bool m_useLegend;

	wxPlotStyle* m_PlotStyle;

	int m_VerticalGridLines = 12;
	int m_HorizontalGridLines = 10;
};
// ----------------------------------------------------------------------------

class wxPlotLegend : public wxScrolledWindow
{
public:

	wxPlotLegend(wxWindow* parent,
		PolarPlotData* graphData,
		wxPlotStyle* plotStyle = new wxPlotStyle(),
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL | wxNO_BORDER,
		const wxString& name = wxPanelNameStr);

	~wxPlotLegend(void);

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event) { Refresh(); }

private:
	PolarPlotData* m_GraphData;
	wxPlotStyle* m_PlotStyle;
};

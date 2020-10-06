#pragma once

#include "wx/dcgraph.h"

class PolarPlotData;
//class wxPaintDC;

// ----------------------------------------------------------------------------
class wxPolarPlot : public wxPanel
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


	wxPolarPlot(wxWindow* parent,
		PolarPlotData* graphData,
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

	void OnPaint(wxPaintEvent &event);
	void OnEraseBackground(wxEraseEvent& event) {}
	void OnSize(wxSizeEvent& event) { Refresh(); }

	wxPlotStyle& Style() { return m_PlotStyle; }

	void ShowTitle(bool showTitle) { m_useTitle = showTitle; }
	void ShowLegend(bool showLegend) { m_useLegend = showLegend; }

private:

	void DrawLinearGridWithCaptions(wxDC* dc, int borderX, int borderY, int width, int height);
	void DrawPolarGridLines(wxDC* dc, int borderX, int borderY, int width, int height);

	void DrawLinearPlots(wxDC* dc, int borderX, int borderY, int width, int height);
	void DrawPolarPlots(wxDC* dc, int borderX, int borderY, int width, int height);

	void DrawPolarGridCaptions(wxDC* dc, int borderX, int borderY, int width, int height);

	void DrawLinearGridLegend(wxDC* dc, int borderX, int borderY, int width, int height);
	void DrawPolarGridLegend(wxDC* dc, int borderX, int borderY, int width, int height);

	PolarPlotData	  * m_graphData;
	bool				m_IsLinear;
	bool					m_useTitle;
	bool					m_useLegend;

	wxPlotStyle m_PlotStyle;

	int m_VerticalGridLines = 12;
	int m_HorizontalGridLines = 10;
};
// ----------------------------------------------------------------------------

class DrawLegend : public wxPanel
{
public:

	DrawLegend(wxWindow *parent,
		PolarPlotData * graphData,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL | wxNO_BORDER,
		const wxString& name = wxPanelNameStr);

	~DrawLegend(void);

	void OnPaint(wxPaintEvent &event);

private:

	PolarPlotData	  * m_graphData;

	DECLARE_EVENT_TABLE()
};

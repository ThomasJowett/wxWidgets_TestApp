#pragma once


class CartesianPlotData;
//class wxPaintDC;

// ----------------------------------------------------------------------------
class DrawPanel : public wxPanel
{
public:

	const double PI = 3.1415926535897931;
	const double PId2 = PI / 2.0;
	const double PI2 = PI * 2.0;
	const double PId2degree = PI / 180.0;

	bool m_bIsPolarPlot;

	DrawPanel(wxWindow *parent,
		CartesianPlotData * graphData,
		bool useTitle = true,
		bool useLegend = true,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL | wxNO_BORDER,
		const wxString& name = wxPanelNameStr
	);

	~DrawPanel(void);

	void OnPaint(wxPaintEvent &event);

private:

	void DrawGridWithCaptions(wxPaintDC * dc, int borderX, int borderY, int width, int height);
	void DrawPolarGridWithCaptions(wxPaintDC * dc, int borderX, int borderY, int width, int height);

	void DrawPlots(wxPaintDC * dc, int borderX, int borderY, int width, int height);
	void DrawPolarPlots(wxPaintDC * dc, int borderX, int borderY, int width, int height);

	void DrawGridLegend(wxPaintDC * dc, int borderX, int borderY, int width, int height);
	void DrawPolarGridLegend(wxPaintDC * dc, int borderX, int borderY, int width, int height);

	CartesianPlotData	  * m_graphData;
	bool					m_useTitle;
	bool					m_useLegend;

	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
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

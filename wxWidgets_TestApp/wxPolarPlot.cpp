#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"



// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "Plot.h"
#include "PolarPlotData.h"
#include "wxPolarPlot.h"
#include "wx/dcbuffer.h"


// ----------------------------------------------------------------------------
wxPolarPlot::wxPolarPlot(wxWindow* parent,
	PolarPlotData* graphData,
	wxPlotStyle* plotStyle,
	bool useTitle,
	bool useLegend,
	bool isLinear,
	wxWindowID id,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name)
	: wxPanel(parent, id, pos, size, style, name),
	m_GraphData(graphData),
	m_PlotStyle(plotStyle),
	m_useTitle(useTitle),
	m_useLegend(useLegend),
	m_IsLinear(isLinear)
{
	//Bind the events
	Bind(wxEVT_PAINT, &wxPolarPlot::OnPaint, this);
	Bind(wxEVT_SIZE, &wxPolarPlot::OnSize, this);
	Bind(wxEVT_ERASE_BACKGROUND, &wxPolarPlot::OnEraseBackground, this);
}
// ----------------------------------------------------------------------------
wxPolarPlot::~wxPolarPlot(void)
{
}
// ----------------------------------------------------------------------------
void wxPolarPlot::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxBufferedPaintDC dc(this);

	wxGCDC gdc(dc);

	dc.SetBackgroundMode(wxTRANSPARENT);

	wxSize sz = GetClientSize();

	dc.Clear();

	int margin = 10;
	int width = sz.x - margin - margin;
	int height = sz.y - margin - margin;

	// -----------------------------------------------------------------
	// Step 1. Drawing the grid area 
	// Step 2. Drawing the Plots


	if (m_IsLinear)
	{
		int linearGridBorderX = 60;
		int linearGridBorderY = 20;
		wxRect linearGridRect = wxRect(linearGridBorderX, linearGridBorderY, width - linearGridBorderX, height - linearGridBorderY - 20);
		DrawLinearGridWithCaptions(&gdc, linearGridRect);
		DrawLinearPlots(&gdc, linearGridRect);
	}
	else
	{
		int polarGridBorder = 20;
		wxRect polarGridRect = wxRect(polarGridBorder, polarGridBorder, width - polarGridBorder, height - polarGridBorder);
		DrawPolarGridLines(&gdc, polarGridRect);
		DrawPolarPlots(&gdc, polarGridRect);
		DrawPolarGridCaptions(&gdc, polarGridRect);
	}

	// Step 3. Drawing the title
	//
	if (m_useTitle)
	{
		wxFont font = wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial"));
		dc.SetTextForeground(m_PlotStyle->TitleColour);
		dc.SetFont(font);
		dc.DrawText(m_GraphData->Title(), margin * 3, margin * 2);
	}
	// -----------------------------------------------------------------
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawLinearGridWithCaptions(wxDC* dc, wxRect gridArea)
{
	wxBrush* gridBrush = wxTheBrushList->FindOrCreateBrush(m_PlotStyle->BackgroundColour, wxBRUSHSTYLE_SOLID);
	dc->SetBrush(*gridBrush);
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle->GridLineColour, m_PlotStyle->GridLineWidth, m_PlotStyle->GridLineStyle);
	dc->SetPen(*gridPen);

	int dx = gridArea.width / (m_VerticalGridLines);
	int dy = gridArea.height / (m_HorizontalGridLines);

	dc->DrawRectangle(gridArea);

	wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetTextForeground(m_PlotStyle->CaptionsColour);
	dc->SetFont(font);

	int xFinal = 0;
	int yFinal = 0;
	wxString capTxt;

	capTxt = wxString::Format(wxT("%d"), -180);
	dc->DrawText(capTxt, gridArea.GetLeft() - 8, gridArea.GetBottom());

	for (int i = 1; i < m_VerticalGridLines; i++)
	{
		// Draw a vertical line
		int xStart = gridArea.GetLeft() + i * dx;
		int yStart = gridArea.GetTop();
		int xEnd = xStart;
		int yEnd = gridArea.GetBottom();

		xFinal = xStart;
		yFinal = yEnd;

		dc->DrawLine(xStart, yStart, xEnd, yEnd);

		capTxt = wxString::Format(wxT("%2.0f"), -180 + (360.0 / (double)(m_VerticalGridLines)) * ((double)i));
		dc->DrawText(capTxt, xStart - 8, yEnd);
	}

	capTxt = wxString::Format(wxT("%d"), 180);
	dc->DrawText(capTxt, gridArea.GetRight() - 8, yFinal);

	dy = gridArea.height / (m_HorizontalGridLines);

	capTxt = wxString::Format(wxT("%2.1f"), 0.0);
	dc->DrawText(capTxt, gridArea.GetLeft() - 24, gridArea.GetBottom() - 8);

	for (int i = 1; i < m_HorizontalGridLines; i++)
	{
		// Draw a horizontal line
		int xStart = gridArea.GetLeft();
		int yStart = gridArea.GetBottom() - i * dy;
		int xEnd = gridArea.GetRight();
		int yEnd = yStart;

		xFinal = xStart;

		dc->DrawLine(xStart, yStart, xEnd, yEnd);

		capTxt = wxString::Format(wxT("%2.1f"), (double)i / 10.0);
		dc->DrawText(capTxt, gridArea.GetLeft() - 24, yStart - 8);
	}
	capTxt = wxString::Format(wxT("%2.1f"), 1.0);
	dc->DrawText(capTxt, gridArea.GetLeft() - 24, gridArea.GetTop() - 8);

	dc->DrawText(m_GraphData->XAxisLabel(), gridArea.width / 2 + 40, gridArea.GetBottom() + 15);
	dc->DrawRotatedText(m_GraphData->YAxisLabel(), gridArea.GetLeft() - 44, gridArea.height, 90);
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawPolarGridLines(wxDC* dc, wxRect gridArea)
{
	wxBrush* gridBrush = wxTheBrushList->FindOrCreateBrush(m_PlotStyle->BackgroundColour, wxBRUSHSTYLE_SOLID);
	dc->SetBrush(*gridBrush);
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle->GridLineColour, m_PlotStyle->GridLineWidth, m_PlotStyle->GridLineStyle);
	dc->SetPen(*gridPen);

	int centerPointX = gridArea.GetLeft() + gridArea.width / 2.0;
	int centerPointY = gridArea.GetTop() + gridArea.height / 2.0;

	int dx = min(gridArea.height, gridArea.width) / 2.0 / (m_HorizontalGridLines);

	// Draw concentric circles
	int radius = 0;
	for (int i = 0; i < (m_HorizontalGridLines); i++)
	{
		radius = (double)min(gridArea.height, gridArea.width) / 2.0 - i * dx;
		dc->DrawCircle(centerPointX, centerPointY, radius);
	}

	int xStart = centerPointX;
	int yStart = centerPointY;

	// Draw radius lines
	radius = min(gridArea.height, gridArea.width) / 2.0;
	for (int i = 0; i <= (m_VerticalGridLines); i++)
	{
		double angle = 0.0 + i * M_PI / (m_VerticalGridLines / 2.0f);

		int xEnd = centerPointX + radius * cos(angle);
		int yEnd = centerPointY - radius * sin(angle);

		dc->DrawLine(xStart, yStart, xEnd, yEnd);
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawLinearPlots(wxDC* dc, wxRect gridArea)
{
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle->GridLineColour, m_PlotStyle->GridLineWidth, m_PlotStyle->GridLineStyle);
	dc->SetPen(*gridPen);

	double xMin = -180.0;
	double xMax = 180.0;

	double yMin = 0.0;
	double yMax = 1.0;

	int dx = gridArea.width / m_VerticalGridLines;
	int dy = gridArea.height / m_HorizontalGridLines;

	double xScale = (xMax - xMin) / gridArea.width;
	double yScale = (yMax - yMin) / gridArea.height;

	int plotsInTotal = m_GraphData->NumberOfPlots();

	for (auto plot : m_GraphData->PlotData())
	{
		if (!plot.IsVisible)
			continue;

		dc->SetBrush(*plot.Brush);

		int xPrevious = gridArea.GetLeft();
		int yPrevious = gridArea.GetBottom();
		int xEnd = xPrevious;
		int yEnd = yPrevious;

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), m_PlotStyle->PlotLineWidth, m_PlotStyle->PlotLineStyle);
		dc->SetPen(*plotPen);

		wxPoint point;

		wxPoint* points = new wxPoint[plot.PlotValues.size() + 2];

		size_t i = 1;
		for (std::pair<double, double> plotValue : plot.PlotValues)
		{
			double currentX = plotValue.first;
			double currentY = plotValue.second;

			point.x = gridArea.GetLeft() + (currentX + xMax) / xScale;
			point.y = gridArea.GetTop() + (yMax - currentY) / yScale;

			points[i] = point;

			dc->DrawCircle(point, m_PlotStyle->PlotLineWidth * 1.5f);

			i++;
		}

		double lastToEnd = xMax - plot.PlotValues.back().first;
		double minToFirst = plot.PlotValues.front().first - xMin;
		double alpha = lastToEnd / (minToFirst + lastToEnd);

		double endYValue = (plot.PlotValues.front().second * alpha) + (plot.PlotValues.back().second * (1 - alpha));

		points[0] = wxPoint(gridArea.GetLeft(), gridArea.GetTop() + (yMax - endYValue) / yScale);
		points[i] = wxPoint(gridArea.GetLeft() + (xMax * 2) / xScale, gridArea.GetTop() + (yMax - endYValue) / yScale);

		dc->DrawLines(plot.PlotValues.size() + 2, points);
		//dc->DrawSpline(plot.PlotValues.size() + 1, points);

		if (plot.PlotValues.back().first > 179.0)
			dc->DrawCircle(points[0], m_PlotStyle->PlotLineWidth * 1.5f);
		if (plot.PlotValues.front().first < -179)
			dc->DrawCircle(points[i], m_PlotStyle->PlotLineWidth * 1.5f);
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawPolarPlots(wxDC* dc, wxRect gridArea)
{
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle->GridLineColour, m_PlotStyle->GridLineWidth, m_PlotStyle->GridLineStyle);
	dc->SetPen(*gridPen);

	double xMin = -180.0;
	double xMax = 180.0;

	double yMin = 0.0;
	double yMax = 1.0;

	int dx = gridArea.width / (m_VerticalGridLines);
	int dy = gridArea.height / (m_HorizontalGridLines);

	double xScale = (xMax - xMin) / gridArea.width;
	double yScale = (yMax - yMin) / gridArea.height;

	int plotsInTotal = m_GraphData->NumberOfPlots();

	for (auto plot : m_GraphData->PlotData())
	{
		if (!plot.IsVisible)
			continue;

		int centerPointX = gridArea.GetLeft() + gridArea.width / 2.0;
		int centerPointY = gridArea.GetTop() + gridArea.height / 2.0;

		dc->SetBrush(*plot.Brush);

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), m_PlotStyle->PlotLineWidth, m_PlotStyle->PlotLineStyle);
		dc->SetPen(*plotPen);

		wxPoint point;

		wxPoint* points = new wxPoint[plot.PlotValues.size() + 1];

		int i = 0;
		double radius;
		for (std::pair<double, double> plotValue : plot.PlotValues)
		{
			double azimuth = wxDegToRad(plotValue.first);
			double ro = plotValue.second;

			double angle = (0.0 + azimuth) + (M_PI / 2);
			radius = min(gridArea.height, gridArea.width) / 2.0 * ro;

			point.x = centerPointX + radius * cos(angle);
			point.y = centerPointY - radius * sin(angle);

			dc->DrawCircle(point, m_PlotStyle->PlotLineWidth * 1.5f);

			points[i] = point;
			dc->DrawPoint(point);

			i++;
		}

		//the last point should be equal to the first point to complete the loop
		points[i] = points[0];

		//dc->DrawSpline(plotValues.size(), points);

		dc->DrawLines(plot.PlotValues.size() + 1, points);
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawPolarGridCaptions(wxDC* dc, wxRect gridArea)
{
	wxFont font(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetTextForeground(m_PlotStyle->CaptionsColour);
	dc->SetFont(font);

	wxString capTxt;
	int dx = min(gridArea.height, gridArea.width) / 2.0 / (m_HorizontalGridLines);
	int centerPointX = gridArea.GetLeft() + gridArea.width / 2.0;
	int centerPointY = gridArea.GetTop() + gridArea.height / 2.0;

	capTxt = wxString::Format(wxT("%d"), 0);
	int radius = min(gridArea.height, gridArea.width) / 2.0;

	dc->DrawText(capTxt, centerPointX - 5, centerPointY - (radius + 15));
	for (int i = 1; i < m_VerticalGridLines; i++)
	{
		double angle = 0.0 + i * (M_PI * 2.0) / (m_VerticalGridLines)+(M_PI / 2);

		int xEnd = centerPointX + radius * cos(angle);
		int yEnd = centerPointY - radius * sin(angle);

		double degree = i * 360.0 / (m_VerticalGridLines);

		if (degree > 180)
			degree -= 360;

		capTxt = wxString::Format(wxT("%2.0f"), degree);
		if (degree <= 90.0 && degree >= 0.0)
			dc->DrawText(capTxt, xEnd - 20, yEnd - 10);
		else if (degree <= 180.0 && degree >= 0.0)
			dc->DrawText(capTxt, xEnd - 20, yEnd + 5);
		else if (degree <= -90)
			dc->DrawText(capTxt, xEnd + 4, yEnd);
		else
			dc->DrawText(capTxt, xEnd + 5, yEnd - 10);
	}

	radius = 0;
	for (int i = 1; i < m_HorizontalGridLines; i++)
	{
		radius = min(gridArea.height, gridArea.width) / 2.0 - i * dx;

		double angle = wxDegToRad(32);

		int xEnd = centerPointX + radius * cos(angle);
		int yEnd = centerPointY - radius * sin(angle);

		capTxt = wxString::Format(wxT("%2.1f"), 1.0 - ((double)i) / 10.0);
		dc->DrawText(capTxt, xEnd - 3, yEnd - 15);
	}
}

//PLOT LEGEND ------------------------------------------------------------------------------------------------------------------------
wxPlotLegend::wxPlotLegend(wxWindow* parent,
	PolarPlotData* graphData,
	wxPlotStyle* plotStyle,
	wxWindowID id,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name)
	: wxScrolledWindow(parent, id),
	m_GraphData(graphData),
	m_PlotStyle(plotStyle)
{
	wxSize parentSize = parent->GetSize();
	SetScrollbars(1, 1, 0, m_GraphData->NumberOfPlots() * 16, 0, 0);
	Bind(wxEVT_PAINT, &wxPlotLegend::OnPaint, this);
	Bind(wxEVT_SIZE, &wxPlotLegend::OnSize, this);
}

wxPlotLegend::~wxPlotLegend(void)
{
}

void wxPlotLegend::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	if (m_GraphData->NumberOfPlots() == 0)
		return;

	wxBufferedPaintDC dc(this);
	PrepareDC(dc);			// DoPrepareDC(dc); - This sets the device context’s deviceorigin
							// Alternatively, you can override the OnDraw virtual function;
							// wxWindow creates a paint device context and calls DoPrepareDC for you before calling your OnDraw function
	wxGCDC gdc(dc);
	dc.Clear();
	wxSize sz = GetClientSize();

	auto width = sz.x;
	auto height = sz.y;

	const int ZoneNumberThreshold = 10;
	const int legendRectWidth = 20;
	const int legendRectShift = 10;
	const int legentYShift = 0;
	const int legentY2ndShift = 0;

	int legendRectHalfWidth = legendRectWidth / 2;

	wxFont font(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	gdc.SetFont(font);

	int graphVisibleCount = m_GraphData->NumberOfPlots();

	int xLegend = 20;
	int yLegend = 10;
	int delta = 16;

	int graphCount = 1;
	for (Plot plot : m_GraphData->PlotData())
	{
		gdc.SetBrush(*plot.Brush);

		wxString nameTxt = wxString::Format(wxT("%s"), plot.Name);

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), m_PlotStyle->PlotLineWidth, m_PlotStyle->PlotLineStyle);
		gdc.SetPen(*plotPen);

		gdc.DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend - 6);

		gdc.DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);

		gdc.DrawCircle(xLegend, yLegend, m_PlotStyle->PlotLineWidth * 1.5f);

		yLegend += delta;

		graphCount++;
	}
}

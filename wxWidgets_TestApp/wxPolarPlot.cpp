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
	m_graphData(graphData),
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
	//PrepareDC(dc);			// DoPrepareDC(dc); - This sets the device context’s deviceorigin
	wxGCDC gdc(dc);
	// Alternatively, you can override the OnDraw virtual function;
	// wxWindow creates a paint device context and calls DoPrepareDC for you before calling your OnDraw function

	dc.SetBackgroundMode(wxTRANSPARENT);

	wxSize sz = GetClientSize();

	dc.Clear();

	int positionX = 10;
	int positionY = 10;
	int width = sz.x - positionX - positionX;
	int height = sz.y - positionY - positionY;

	// -----------------------------------------------------------------
	// Step 1. Drawing the grid area 
	//
	int dx1 = width / 10;
	int dy1 = height / 10;

	int dx2 = width / 20;
	int dy2 = height / 20;

	int gridBorderX = dx1;
	int gridBorderY = dy1;

	int gridWidth0 = width - dx1 - dx2;
	int gridHeight0 = height - dy1 - dy2;

	int dx = gridWidth0 / (m_VerticalGridLines);
	int dy = gridHeight0 / (m_HorizontalGridLines);

	int gridWidth = (m_VerticalGridLines)*dx;
	int gridHeight = (m_HorizontalGridLines)*dy;

	if (m_IsLinear)
		DrawLinearGridWithCaptions(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);
	else
		DrawPolarGridLines(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);

	// -----------------------------------------------------------------
	// Step 2. Drawing the Plots 
	//
	if (m_IsLinear)
		DrawLinearPlots(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);
	else
		DrawPolarPlots(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);

	if (!m_IsLinear)
		DrawPolarGridCaptions(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);

	// -----------------------------------------------------------------
	// Step 3. Drawing the title
	//
	if (m_useTitle)
	{
		wxFont font = wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial"));
		dc.SetTextForeground(m_PlotStyle->TitleColour);
		dc.SetFont(font);
		dc.DrawText(m_graphData->Title(), positionX * 3, positionY * 2);
	}
	// -----------------------------------------------------------------
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawLinearGridWithCaptions(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxBrush* gridBrush = wxTheBrushList->FindOrCreateBrush(m_PlotStyle->BackgroundColour, wxBRUSHSTYLE_SOLID);
	dc->SetBrush(*gridBrush);
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle->GridLineColour, m_PlotStyle->GridLineWidth, m_PlotStyle->GridLineStyle);
	dc->SetPen(*gridPen);

	int dx = width / (m_VerticalGridLines);
	int dy = height / (m_HorizontalGridLines);

	//wxRect borderRect(borderX, borderY, width, height);
	wxRect borderRect(borderX, borderY, width, height);
	dc->DrawRectangle(borderRect);

	wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetTextForeground(m_PlotStyle->CaptionsColour);
	dc->SetFont(font);

	//int dx = width / (m_graphData->m_VerticalCount + 1);

	int xFinal = 0;
	int yFinal = 0;
	wxString capTxt;

	capTxt = wxString::Format(wxT("%d"), -180);
	dc->DrawText(capTxt, borderX, borderY + height);

	for (int i = 1; i < m_VerticalGridLines; i++)
	{
		// Draw a vertical line
		int xStart = borderX + i * dx;
		int yStart = borderY;
		int xEnd = xStart;
		int yEnd = borderY + height;

		xFinal = xStart;
		yFinal = yEnd;

		dc->DrawLine(xStart, yStart, xEnd, yEnd);

		capTxt = wxString::Format(wxT("%2.0f"), -180 + (360.0 / (double)(m_VerticalGridLines)) * ((double)i));
		dc->DrawText(capTxt, xStart, yEnd);
	}

	capTxt = wxString::Format(wxT("%d"), 180);
	dc->DrawText(capTxt, borderX + width, yFinal);

	dy = height / (m_HorizontalGridLines);

	capTxt = wxString::Format(wxT("%2.1f"), 0.0);
	dc->DrawText(capTxt, borderX - dx / 2, borderY + height - 8);

	for (int i = 1; i < m_HorizontalGridLines; i++)
	{
		// Draw a horizontal line
		int xStart = borderX;
		int yStart = borderY + height - i * dy;
		int xEnd = borderX + width;
		int yEnd = yStart;

		xFinal = xStart;

		dc->DrawLine(xStart, yStart, xEnd, yEnd);

		capTxt = wxString::Format(wxT("%2.1f"), (double)i / 10.0);
		dc->DrawText(capTxt, xStart - dx / 2, yStart - 8);
	}
	capTxt = wxString::Format(wxT("%2.1f"), 1.0);
	dc->DrawText(capTxt, xFinal - dx / 2, borderY - 8);
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawPolarGridLines(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxBrush* gridBrush = wxTheBrushList->FindOrCreateBrush(m_PlotStyle->BackgroundColour, wxBRUSHSTYLE_SOLID);
	dc->SetBrush(*gridBrush);
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle->GridLineColour, m_PlotStyle->GridLineWidth, m_PlotStyle->GridLineStyle);
	dc->SetPen(*gridPen);

	//wxRect borderRect(borderX, borderY, width, height);
	wxRect borderRect(borderX, borderY, width, height);
	//dc->DrawRectangle(borderRect);

	int centerPointX = borderX + width / 2.0;
	int centerPointY = borderY + height / 2.0;

	int dx = min(height, width) / 2.0 / (m_HorizontalGridLines);

	// Draw concentric circles
	int radius = 0;
	for (int i = 0; i < (m_HorizontalGridLines); i++)
	{
		radius = min(height, width) / 2.0 - i * dx;
		dc->DrawCircle(centerPointX, centerPointY, radius);
	}

	int xStart = centerPointX;
	int yStart = centerPointY;

	// Draw radius lines
	radius = min(height, width) / 2.0;
	for (int i = 0; i <= (m_VerticalGridLines); i++)
	{
		double angle = 0.0 + i * M_PI / (m_VerticalGridLines/2.0f);

		int xEnd = centerPointX + radius * cos(angle);
		int yEnd = centerPointY - radius * sin(angle);

		dc->DrawLine(xStart, yStart, xEnd, yEnd);
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawLinearPlots(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle->GridLineColour, m_PlotStyle->GridLineWidth, m_PlotStyle->GridLineStyle);
	dc->SetPen(*gridPen);

	double xMin = -180.0;
	double xMax = 180.0;

	double yMin = 0.0;
	double yMax = 1.0;

	int dx = width / m_VerticalGridLines;
	int dy = height / m_HorizontalGridLines;

	double xScale = (xMax - xMin) / width;
	double yScale = (yMax - yMin) / height;

	int plotsInTotal = m_graphData->NumberOfPlots();

	for (auto plot : m_graphData->PlotData())
	{
		dc->SetBrush(*plot.Brush);

		int xPrevious = borderX;
		int yPrevious = borderY + height;
		int xEnd = xPrevious;
		int yEnd = yPrevious;

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), m_PlotStyle->PlotLineWidth, m_PlotStyle->PlotLineStyle);
		dc->SetPen(*plotPen);

		wxPoint point;

		wxPoint* points = new wxPoint[plot.PlotValues.size() + 1];

		int i = 1;
		for (std::pair<double, double> plotValue : plot.PlotValues)
		{
			double currentX = plotValue.first;
			double currentY = plotValue.second;

			point.x = borderX + (currentX + xMax) / xScale;
			point.y = borderY + (yMax - currentY) / yScale;

			points[i] = point;

			dc->DrawCircle(point, m_PlotStyle->PlotLineWidth * 1.5f);

			i++;
		}

		//Draw a point at the start that is -360 from the end
		points[0] = wxPoint(points[i - 1].x - (xMax - xMin) / xScale, points[i - 1].y);

		dc->DrawLines(plot.PlotValues.size() + 1, points);
		//dc->DrawSpline(plot.PlotValues.size() + 1, points);

		dc->DrawCircle(points[0], m_PlotStyle->PlotLineWidth * 1.5f);
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawPolarPlots(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle->GridLineColour, m_PlotStyle->GridLineWidth, m_PlotStyle->GridLineStyle);
	dc->SetPen(*gridPen);

	double xMin = -180.0;
	double xMax = 180.0;

	double yMin = 0.0;
	double yMax = 1.0;

	int dx = width / (m_VerticalGridLines);
	int dy = height / (m_HorizontalGridLines);

	double xScale = (xMax - xMin) / width;
	double yScale = (yMax - yMin) / height;

	int plotsInTotal = m_graphData->NumberOfPlots();

	for (auto plot : m_graphData->PlotData())
	{
		int centerPointX = borderX + width / 2.0;
		int centerPointY = borderY + height / 2.0;

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
			radius = min(height, width) / 2.0 * ro;

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
void wxPolarPlot::DrawPolarGridCaptions(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxFont font(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetTextForeground(m_PlotStyle->CaptionsColour);
	dc->SetFont(font);

	wxString capTxt;
	int dx = min(height, width) / 2.0 / (m_HorizontalGridLines);
	int centerPointX = borderX + width / 2.0;
	int centerPointY = borderY + height / 2.0;

	capTxt = wxString::Format(wxT("%d"), 0);
	int radius = min(height, width) / 2.0;

	dc->DrawText(capTxt, centerPointX - 5, centerPointY - (radius + 15));
	for (int i = 1; i < m_VerticalGridLines; i++)
	{
		double angle = 0.0 + i * (M_PI * 2.0) / (m_VerticalGridLines) + (M_PI / 2);

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
		radius = min(height, width) / 2.0 - i * dx;

		capTxt = wxString::Format(wxT("%2.1f"), 1.0 - ((double)i) / 10.0);
		dc->DrawText(capTxt, centerPointX + 2 + radius, centerPointY - 12);
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
	: wxPanel(parent, id, pos, size, style, name),
	m_GraphData(graphData),
	m_PlotStyle(plotStyle)
{
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
	int delta = height / graphVisibleCount;

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

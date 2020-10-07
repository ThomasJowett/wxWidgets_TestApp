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

	// -----------------------------------------------------------------
	// Step 1. Drawing the client area border
	//
	wxPen* borderPen = wxThePenList->FindOrCreatePen(m_PlotStyle.BorderColour, m_PlotStyle.BorderWidth, m_PlotStyle.BorderStyle);
	dc.SetPen(*borderPen);

	int positionX = 10;
	int positionY = 10;
	int width = sz.x - positionX - positionX;
	int height = sz.y - positionY - positionY;

	wxRect borderRect(positionX, positionY, width, height);
	//dc.DrawRectangle(borderRect);
	// -----------------------------------------------------------------

	// -----------------------------------------------------------------
	// Step 2. Drawing the grid area 
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

	// -----------------------------------------------------------------
	// Step 3. Drawing the Plots 
	//
	if (m_IsLinear)
		DrawLinearPlots(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);
	else
		DrawPolarPlots(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);

	if (!m_IsLinear)
		DrawPolarGridCaptions(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);

	// -----------------------------------------------------------------
	// Step 4. Drawing the Grid Legend 
	//
	if (m_useLegend)
		DrawLinearGridLegend(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);

	// -----------------------------------------------------------------
	// Step 5. Drawing the title
	//
	if (m_useTitle)
	{
		wxFont font = wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial"));
		dc.SetTextForeground(m_PlotStyle.TitleColour);
		dc.SetFont(font);
		dc.DrawText(m_graphData->Title(), positionX * 3, positionY * 2);
	}
	// -----------------------------------------------------------------
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawLinearGridWithCaptions(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle.GridLineColour, m_PlotStyle.GridLineWidth, m_PlotStyle.GridLineStyle);
	dc->SetPen(*gridPen);

	int dx = width / (m_VerticalGridLines);
	int dy = height / (m_HorizontalGridLines);

	//wxRect borderRect(borderX, borderY, width, height);
	wxRect borderRect(borderX, borderY, width, height);
	dc->DrawRectangle(borderRect);

	wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetTextForeground(m_PlotStyle.LabelsColour);
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

		capTxt = wxString::Format(wxT("%2.1f"), -180 + (360.0 / (double)(m_VerticalGridLines)) * ((double)i));
		dc->DrawText(capTxt, xStart, yEnd);
	}

	capTxt = wxString::Format(wxT("%d"), 180);
	dc->DrawText(capTxt, borderX + width, yFinal);

	dy = height / (m_HorizontalGridLines);

	capTxt = wxString::Format(wxT("%2.2f"), 0.0);
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

		capTxt = wxString::Format(wxT("%2.2f"), (double)i / 10.0);
		dc->DrawText(capTxt, xStart - dx / 2, yStart - 8);
	}
	capTxt = wxString::Format(wxT("%2.2f"), 1.0);
	dc->DrawText(capTxt, xFinal - dx / 2, borderY - 8);
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawPolarGridLines(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle.GridLineColour, m_PlotStyle.GridLineWidth, m_PlotStyle.GridLineStyle);
	dc->SetPen(*gridPen);

	//wxRect borderRect(borderX, borderY, width, height);
	wxRect borderRect(borderX, borderY, width, height);
	//dc->DrawRectangle(borderRect);

	int centerPointX = borderX + width / 2.0;
	int centerPointY = borderY + height / 2.0;

	int dx = height / 2.0 / (m_HorizontalGridLines);

	// Draw concentric circles
	int radius = 0;
	for (int i = 0; i < (m_HorizontalGridLines); i++)
	{
		radius = height / 2.0 - i * dx;
		dc->DrawCircle(centerPointX, centerPointY, radius);
	}

	int xStart = centerPointX;
	int yStart = centerPointY;

	// Draw radius lines
	radius = height / 2.0;
	for (int i = 0; i <= 2 * (m_VerticalGridLines); i++)
	{
		double angle = 0.0 + i * M_PI / (m_VerticalGridLines);

		int xEnd = centerPointX + radius * cos(angle);
		int yEnd = centerPointY - radius * sin(angle);

		dc->DrawLine(xStart, yStart, xEnd, yEnd);
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawLinearPlots(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle.GridLineColour, m_PlotStyle.GridLineWidth, m_PlotStyle.GridLineStyle);
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

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), m_PlotStyle.PlotLineWidth, m_PlotStyle.PlotLineStyle);
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

			dc->DrawCircle(point, m_PlotStyle.PlotLineWidth * 1.5f);

			i++;
		}

		//Draw a point at the start that is -360 from the end
		points[0] = wxPoint(points[i - 1].x - (xMax - xMin) / xScale, points[i - 1].y);

		dc->DrawLines(plot.PlotValues.size() + 1, points);
		//dc->DrawSpline(plot.PlotValues.size() + 1, points);

		dc->DrawCircle(points[0], m_PlotStyle.PlotLineWidth * 1.5f);
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawPolarPlots(wxDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen* gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle.GridLineColour, m_PlotStyle.GridLineWidth, m_PlotStyle.GridLineStyle);
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

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), m_PlotStyle.PlotLineWidth, m_PlotStyle.PlotLineStyle);
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
			radius = height / 2.0 * ro;

			point.x = centerPointX + radius * cos(angle);
			point.y = centerPointY - radius * sin(angle);

			dc->DrawCircle(point, m_PlotStyle.PlotLineWidth * 1.5f);

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
	dc->SetTextForeground(m_PlotStyle.LabelsColour);
	dc->SetFont(font);

	wxString capTxt;
	int dx = height / 2.0 / (m_HorizontalGridLines);
	int centerPointX = borderX + width / 2.0;
	int centerPointY = borderY + height / 2.0;

	capTxt = wxString::Format(wxT("%d"), 0);
	dc->DrawText(capTxt, centerPointX - 5, borderY - 20);

	int radius = height / 2.0;
	for (int i = 1; i < 2 * m_VerticalGridLines; i++)
	{
		double angle = 0.0 + i * (M_PI * 2.0) / (2 * m_VerticalGridLines) + (M_PI / 2);

		int xEnd = centerPointX + radius * cos(angle);
		int yEnd = centerPointY - radius * sin(angle);

		double degree = i * 360.0 / (2 * m_VerticalGridLines);

		capTxt = wxString::Format(wxT("%2.0f"), degree);
		if (degree <= 90.0)
			dc->DrawText(capTxt, xEnd - 20, yEnd - 10);
		else if (degree < 180.0)
			dc->DrawText(capTxt, xEnd - 20, yEnd + 5);
		else if (degree <= 270.0)
			dc->DrawText(capTxt, xEnd + 4, yEnd);
		else
			dc->DrawText(capTxt, xEnd + 5, yEnd - 10);
	}

	radius = 0;
	for (int i = 1; i < m_HorizontalGridLines; i++)
	{
		radius = height / 2.0 - i * dx;

		capTxt = wxString::Format(wxT("%2.1f"), 1.0 - ((double)i) / 10.0);
		dc->DrawText(capTxt, centerPointX + 2 + radius, centerPointY - 12);
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawLinearGridLegend(wxDC* dc, int borderX, int borderY, int width, int height)
{
	const int ZoneNumberThreshold = 5;
	const int legendRectWidth = 20;
	const int legendRectShift = 10;
	const int legentYShift = 50;
	const int legentY2ndShift = 30;

	int legendRectHalfWidth = legendRectWidth / 2;

	wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetFont(font);

	int graphVisibleCount = m_graphData->NumberOfPlots();
	int xLegend = 0;
	int yLegend = 0;
	int delta = 0;


	xLegend = borderX;
	yLegend = borderY + height + legentYShift;

	if (graphVisibleCount < ZoneNumberThreshold)
		delta = width / graphVisibleCount;
	else
		delta = width / ZoneNumberThreshold;


	int graphCount = 1;
	for (Plot plot : m_graphData->PlotData())
	{
		dc->SetBrush(*plot.Brush);

		wxString nameTxt = wxString::Format(wxT("%s"), plot.Name);

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), m_PlotStyle.PlotLineWidth, m_PlotStyle.PlotLineStyle);
		dc->SetPen(*plotPen);


		if ((graphVisibleCount > ZoneNumberThreshold) && (graphCount > ZoneNumberThreshold))
		{
			delta = width / ZoneNumberThreshold;
			xLegend = borderX + (graphCount - ZoneNumberThreshold - 1) * delta;
			yLegend = borderY + height + legentYShift + legentY2ndShift;

			dc->DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend - legendRectHalfWidth);

			//wxRect borderRect( xLegend, yLegend, legendRectWidth, legendRectWidth);
			//dc->DrawRectangle( borderRect );

			dc->DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);
		}
		else
		{
			yLegend = borderY + height + legentYShift + legentY2ndShift;
			dc->DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend - legendRectHalfWidth);

			//wxRect borderRect( xLegend, yLegend, legendRectWidth, legendRectWidth);
			//dc->DrawRectangle( borderRect );

			dc->DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);

			xLegend += delta;
		}

		graphCount++;
	}
}
// ----------------------------------------------------------------------------
void wxPolarPlot::DrawPolarGridLegend(wxDC* dc, int borderX, int borderY, int width, int height)
{
	const int ZoneNumberThreshold = 5;
	const int legendRectWidth = 20;
	const int legendRectShift = 10;
	const int legentYShift = 50;
	const int legentY2ndShift = 30;

	int legendRectHalfWidth = legendRectWidth / 2;

	wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetFont(font);

	int graphVisibleCount = m_graphData->NumberOfPlots();
	int xLegend = 0;
	int yLegend = 0;
	int delta = 0;


	xLegend = borderX;
	yLegend = borderY + height + legentYShift;

	if (graphVisibleCount < ZoneNumberThreshold)
		delta = width / graphVisibleCount;
	else
		delta = width / ZoneNumberThreshold;


	int graphCount = 1;
	for (Plot plot : m_graphData->PlotData())
	{
		dc->SetBrush(*plot.Brush);

		wxString nameTxt = wxString::Format(wxT("%s"), plot.Name);

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), m_PlotStyle.PlotLineWidth, m_PlotStyle.PlotLineStyle);
		dc->SetPen(*plotPen);


		if ((graphVisibleCount > ZoneNumberThreshold) && (graphCount > ZoneNumberThreshold))
		{
			delta = width / ZoneNumberThreshold;
			xLegend = borderX + (graphCount - ZoneNumberThreshold - 1) * delta;
			yLegend = borderY + height + legentYShift + legentY2ndShift;

			dc->DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend - legendRectHalfWidth);

			//wxRect borderRect( xLegend, yLegend, legendRectWidth, legendRectWidth);
			//dc->DrawRectangle( borderRect );

			dc->DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);
		}
		else
		{
			dc->DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend - legendRectHalfWidth);

			//wxRect borderRect( xLegend, yLegend, legendRectWidth, legendRectWidth);
			//dc->DrawRectangle( borderRect );

			dc->DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);

			xLegend += delta;
		}


		graphCount++;
	}
}
// ----------------------------------------------------------------------------

//DRAW LEGEND -----------------------------------------------------------------

BEGIN_EVENT_TABLE(wxPlotLegend, wxPanel)
EVT_PAINT(wxPlotLegend::OnPaint)
END_EVENT_TABLE()

wxPlotLegend::wxPlotLegend(wxWindow* parent,
	PolarPlotData* graphData,
	wxWindowID id,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name)
	: wxPanel(parent, id, pos, size, style, name),
	m_graphData(graphData)
{
	SetBackgroundColour(*wxWHITE);
}

wxPlotLegend::~wxPlotLegend(void)
{
}

void wxPlotLegend::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	if (m_graphData->NumberOfPlots() == 0)
		return;

	wxPaintDC dc(this);
	PrepareDC(dc);			// DoPrepareDC(dc); - This sets the device context’s deviceorigin
							// Alternatively, you can override the OnDraw virtual function;
							// wxWindow creates a paint device context and calls DoPrepareDC for you before calling your OnDraw function

	wxSize sz = GetClientSize();		// 800, 600

	auto width = sz.x;
	auto height = sz.y;

	const int ZoneNumberThreshold = 10;
	const int legendRectWidth = 20;
	const int legendRectShift = 10;
	const int legentYShift = 0;
	const int legentY2ndShift = 0;

	int legendRectHalfWidth = legendRectWidth / 2;

	wxFont font(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc.SetFont(font);

	int graphVisibleCount = m_graphData->NumberOfPlots();

	int xLegend = 20;
	int yLegend = 10;
	int delta = height / graphVisibleCount;


	int graphCount = 1;
	for (Plot plot : m_graphData->PlotData())
	{
		dc.SetBrush(*plot.Brush);

		wxString nameTxt = wxString::Format(wxT("%s"), plot.Name);

		wxPen* plotPen = wxThePenList->FindOrCreatePen(plot.Brush->GetColour(), 2);
		dc.SetPen(*plotPen);

		dc.DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend - 6);

		//wxRect borderRect( xLegend, yLegend, legendRectWidth, legendRectWidth);
		//dc->DrawRectangle( borderRect );

		dc.DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);

		yLegend += delta;

		graphCount++;
	}

}

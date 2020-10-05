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
#include "CartesianPlotData.h"
#include "DrawPanel.h"


// ----------------------------------------------------------------------------
wxPlot::wxPlot(wxWindow * parent,
	CartesianPlotData * graphData,
	bool useTitle,
	bool useLegend,
	wxWindowID id,
	const wxPoint & pos,
	const wxSize & size,
	long style,
	const wxString & name)
	: wxPanel(parent, id, pos, size, style, name),
	m_graphData(graphData),
	m_useTitle(useTitle),
	m_useLegend(useLegend)
{
	m_bIsPolarPlot = false;

	//Bind the events
	Bind(wxEVT_PAINT, &wxPlot::OnPaint, this);
	Bind(wxEVT_SIZE, &wxPlot::OnSize, this);
	Bind(wxEVT_ERASE_BACKGROUND, &wxPlot::OnEraseBackground, this);
}
// ----------------------------------------------------------------------------
wxPlot::~wxPlot(void)
{
}
// ----------------------------------------------------------------------------
void wxPlot::OnPaint(wxPaintEvent &WXUNUSED(event))
{
	wxPaintDC dc(this);
	PrepareDC(dc);			// DoPrepareDC(dc); - This sets the device context’s deviceorigin
	wxGCDC gdc(dc);
	// Alternatively, you can override the OnDraw virtual function;
	// wxWindow creates a paint device context and calls DoPrepareDC for you before calling your OnDraw function

	dc.SetBackgroundMode(wxTRANSPARENT);

	wxSize sz = GetClientSize();

	dc.Clear();

	// -----------------------------------------------------------------
	// Step 1. Drawing the client area border
	//
	wxPen * borderPen = wxThePenList->FindOrCreatePen(m_PlotStyle.BorderColour, m_PlotStyle.BorderWidth, m_PlotStyle.BorderStyle);
	dc.SetPen(*borderPen);

	int positionX = 10;
	int positionY = 10;
	int width = sz.x - positionX - positionX;
	int height = sz.y - positionY - positionY;

	wxRect borderRect(positionX, positionY, width, height);
	//dc.DrawRectangle(borderRect);
	// -----------------------------------------------------------------


	// -----------------------------------------------------------------
	// Step 2. Drawing the title
	//
	if (m_useTitle)
	{
		wxFont font = wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial"));
		dc.SetTextForeground(m_PlotStyle.TitleColour);
		dc.SetFont(font);
		dc.DrawText(m_graphData->m_Title, positionX * 3, positionY * 2);
	}
	// -----------------------------------------------------------------


	// -----------------------------------------------------------------
	// Step 3. Drawing the grid area 
	//
	int dx1 = width * m_graphData->m_StartXpercent / 100;
	int dy1 = height * m_graphData->m_StartYpercent / 100;

	int dx2 = width * m_graphData->m_EndXpercent / 100;
	int dy2 = height * m_graphData->m_EndYpercent / 100;

	int gridBorderX = dx1;
	int gridBorderY = dy1;

	int gridWidth0 = width - dx1 - dx2;
	int gridHeight0 = height - dy1 - dy2;

	int dx = gridWidth0 / (m_graphData->m_VerticalCount + 1);
	int dy = gridHeight0 / (m_graphData->m_HorizontalCount + 1);

	int gridWidth = (m_graphData->m_VerticalCount + 1) * dx;
	int gridHeight = (m_graphData->m_HorizontalCount + 1) * dy;

	if (m_bIsPolarPlot)
		DrawPolarGridWithCaptions(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);
	else
		DrawGridWithCaptions(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);
	// -----------------------------------------------------------------


	// -----------------------------------------------------------------
	// Step 4. Drawing the Plots 
	//
	if (m_bIsPolarPlot)
		DrawPolarPlots(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);
	else
		DrawPlots(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);

	// -----------------------------------------------------------------
	// Step 5. Drawing the Grid Legend 
	//
	if (m_useLegend)
		DrawGridLegend(&gdc, gridBorderX, gridBorderY, gridWidth, gridHeight);

	//m_bmp = GetScreenShot();
}
// ----------------------------------------------------------------------------
void wxPlot::DrawGridWithCaptions(wxGCDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen * gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle.GridLineColour, m_PlotStyle.GridLineWidth, m_PlotStyle.GridLineStyle);
	dc->SetPen(*gridPen);

	int dx = width / (m_graphData->m_VerticalCount + 1);
	int dy = height / (m_graphData->m_HorizontalCount + 1);

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

	for (int i = 1; i <= m_graphData->m_VerticalCount; i++)
	{
		// Draw a vertical line
		int xStart = borderX + i * dx;
		int yStart = borderY;
		int xEnd = xStart;
		int yEnd = borderY + height;

		xFinal = xStart;
		yFinal = yEnd;

		dc->DrawLine(xStart, yStart, xEnd, yEnd);

		capTxt = wxString::Format(wxT("%2.1f"), -180 + (360.0 / (double)(m_graphData->m_VerticalCount + 1)) * ((double)i));
		dc->DrawText(capTxt, xStart, yEnd);
	}

	capTxt = wxString::Format(wxT("%d"), 180);
	dc->DrawText(capTxt, borderX + width, yFinal);

	dy = height / (m_graphData->m_HorizontalCount + 1);

	capTxt = wxString::Format(wxT("%2.2f"), 0.0);
	dc->DrawText(capTxt, borderX - dx / 2, borderY + height - 8);

	for (int i = 1; i <= m_graphData->m_HorizontalCount; i++)
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
void wxPlot::DrawPolarGridWithCaptions(wxGCDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen * gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle.GridLineColour, m_PlotStyle.GridLineWidth, m_PlotStyle.GridLineStyle);
	dc->SetPen(*gridPen);

	//wxRect borderRect(borderX, borderY, width, height);
	wxRect borderRect(borderX, borderY, width, height);
	//dc->DrawRectangle(borderRect);

	wxFont font(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetTextForeground(m_PlotStyle.LabelsColour);
	dc->SetFont(font);

	//int dx = width / (m_graphData->m_VerticalCount + 1);

	int xFinal = 0;
	int yFinal = 0;
	wxString capTxt;


	int centerPointX = borderX + width / 2.0;
	int centerPointY = borderY + height / 2.0;

	int dx = height / 2.0 / (m_graphData->m_HorizontalCount + 1);

	// Draw concentric circles
	int radius = 0;
	for (int i = 0; i < (m_graphData->m_HorizontalCount + 1); i++)
	{
		radius = height / 2.0 - i * dx;
		dc->DrawCircle(centerPointX, centerPointY, radius);
	}

	int xStart = centerPointX;
	int yStart = centerPointY;

	// Draw radius lines
	radius = height / 2.0;
	for (int i = 0; i <= 2 * (m_graphData->m_VerticalCount + 1); i++)
	{
		double angle = 0.0 + i * PI / (m_graphData->m_VerticalCount + 1);

		int xEnd = centerPointX + radius * cos(angle);
		int yEnd = centerPointY - radius * sin(angle);

		dc->DrawLine(xStart, yStart, xEnd, yEnd);
	}

	capTxt = wxString::Format(wxT("%d"), 0);
	dc->DrawText(capTxt, centerPointX - 5, borderY - 20);

	radius = height / 2.0;
	for (int i = 1; i < 2 * (m_graphData->m_VerticalCount + 1); i++)
	{
		double angle = 0.0 + i * PI2 / (2 * (m_graphData->m_VerticalCount + 1)) + PId2;

		int xEnd = centerPointX + radius * cos(angle);
		int yEnd = centerPointY - radius * sin(angle);

		double degree = i * 360.0 / (2 * (m_graphData->m_VerticalCount + 1));

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
	for (int i = 1; i < (m_graphData->m_HorizontalCount + 1); i++)
	{
		radius = height / 2.0 - i * dx;

		capTxt = wxString::Format(wxT("%2.1f"), 1.0 - ((double)i) / 10.0);
		dc->DrawText(capTxt, centerPointX + 2 + radius, centerPointY - 12);
	}
}
// ----------------------------------------------------------------------------
void wxPlot::DrawPlots(wxGCDC* dc, int borderX, int borderY, int width, int height)
{
	wxPen * gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle.GridLineColour, m_PlotStyle.GridLineWidth, m_PlotStyle.GridLineStyle);
	dc->SetPen(*gridPen);

	double xMin = -180.0;
	double xMax = 180.0;

	double yMin = 0.0;
	double yMax = 1.0;

	int dx = width / (m_graphData->m_VerticalCount + 1);
	int dy = height / (m_graphData->m_HorizontalCount + 1);

	double xScale = (xMax - xMin) / width;
	double yScale = (yMax - yMin) / height;

	int plotsInTotal = m_graphData->m_plotData.size();;

	for (std::vector< Plot >::iterator plotIter = m_graphData->m_plotData.begin();
		plotIter != m_graphData->m_plotData.end();
		++plotIter)
	{
		std::string plotName = (*plotIter).getName();

		std::vector< std::pair <double, double> > plotValues = plotIter->GetPlotValues();

		dc->SetBrush(*(*plotIter).brush);

		int xPrevious = borderX;
		int yPrevious = borderY + height;
		int xEnd = xPrevious;
		int yEnd = yPrevious;

		wxPen *plotPen = wxThePenList->FindOrCreatePen((*plotIter).brush->GetColour(), m_PlotStyle.PlotLineWidth, m_PlotStyle.PlotLineStyle);
		dc->SetPen(*plotPen);

		wxPoint point;

		wxPoint* points = new wxPoint[plotValues.size() + 1];

		int i = 1;
		for (std::vector< std::pair <double, double> >::iterator plotValuesIter = plotValues.begin();
			plotValuesIter != plotValues.end();
			++plotValuesIter)
		{
			std::pair <double, double> plotValue = *plotValuesIter;

			double currentX = plotValue.first;
			double currentY = plotValue.second;

			point.x = borderX + (xMax - currentX) / xScale;
			point.y = borderY + (yMax - currentY) / yScale;

			points[i] = point;

			dc->DrawCircle(point, m_PlotStyle.PlotLineWidth * 1.5f);

			i++;
		}

		//points[0] = wxPoint((xMax + xMax) / yScale, points[0].y);

		dc->DrawLines(plotValues.size() + 1, points);

		dc->DrawCircle(points[i], m_PlotStyle.PlotLineWidth * 1.5f);
	}
}
// ----------------------------------------------------------------------------
void wxPlot::DrawPolarPlots(wxGCDC * dc, int borderX, int borderY, int width, int height)
{
	wxPen * gridPen = wxThePenList->FindOrCreatePen(m_PlotStyle.GridLineColour, m_PlotStyle.GridLineWidth, m_PlotStyle.GridLineStyle);
	dc->SetPen(*gridPen);

	double xMin = -180.0;
	double xMax = 180.0;

	double yMin = 0.0;
	double yMax = 1.0;

	int dx = width / (m_graphData->m_VerticalCount + 1);
	int dy = height / (m_graphData->m_HorizontalCount + 1);

	double xScale = (xMax - xMin) / width;
	double yScale = (yMax - yMin) / height;

	int plotsInTotal = m_graphData->m_plotData.size();

	for (std::vector< Plot >::iterator plotIter = m_graphData->m_plotData.begin();
		plotIter != m_graphData->m_plotData.end();
		++plotIter)
	{
		int centerPointX = borderX + width / 2.0;
		int centerPointY = borderY + height / 2.0;

		std::string plotName = (*plotIter).getName();

		//std::vector< std::pair <int,int>> killZoneCells = *killZoneIter;
		std::vector< std::pair <double, double> > plotValues = plotIter->GetPlotValues();

		dc->SetBrush(*(*plotIter).brush);

		wxPoint point;

		wxPoint* points = new wxPoint[plotValues.size() + 1];

		int i = 0;
		double radius;
		for (std::vector< std::pair <double, double> >::iterator plotValuesIter = plotValues.begin();
			plotValuesIter != plotValues.end();
			++plotValuesIter)
		{
			std::pair <double, double> plotValue = *plotValuesIter;

			double azimuth = plotValue.first;
			double ro = plotValue.second;

			double angle = (0.0 + azimuth) * PId2degree + PId2;
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

		wxPen* plotPen = wxThePenList->FindOrCreatePen((*plotIter).brush->GetColour(), m_PlotStyle.PlotLineWidth, m_PlotStyle.PlotLineStyle);
		dc->SetPen(*plotPen);

		dc->DrawLines(plotValues.size() + 1, points);
	}
}
// ----------------------------------------------------------------------------
void wxPlot::DrawGridLegend(wxGCDC* dc, int borderX, int borderY, int width, int height)
{
	const int ZoneNumberThreshold = 5;
	const int legendRectWidth = 20;
	const int legendRectShift = 10;
	const int legentYShift = 50;
	const int legentY2ndShift = 30;

	int legendRectHalfWidth = legendRectWidth / 2;

	wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetFont(font);

	int graphVisibleCount = m_graphData->m_plotData.size();
	int xLegend = 0;
	int yLegend = 0;
	int delta = 0;

	if (m_graphData->m_isPortrate)
	{
		xLegend = borderX + width + 30;
		yLegend = borderY;
		delta = height / graphVisibleCount;
	}
	else
	{
		xLegend = borderX;
		yLegend = borderY + height + legentYShift;

		if (graphVisibleCount < ZoneNumberThreshold)
			delta = width / graphVisibleCount;
		else
			delta = width / ZoneNumberThreshold;
	}

	int graphCount = 1;
	for (std::vector< Plot >::iterator plotIter = m_graphData->m_plotData.begin();
		plotIter != m_graphData->m_plotData.end();
		++plotIter)
	{
		std::string plotName = (*plotIter).getName();
		dc->SetBrush(*(*plotIter).brush);

		wxString nameTxt = wxString::Format(wxT("%s"), plotName);

		wxPen *plotPen = wxThePenList->FindOrCreatePen((*plotIter).brush->GetColour(), m_PlotStyle.PlotLineWidth, m_PlotStyle.PlotLineStyle);
		dc->SetPen(*plotPen);

		if (m_graphData->m_isPortrate)
		{
			dc->DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend);

			//wxRect borderRect( xLegend, yLegend, legendRectWidth, legendRectWidth);
			//dc->DrawRectangle( borderRect );

			dc->DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);

			yLegend += delta;
		}
		else
		{
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
		}

		graphCount++;
	}
}
// ----------------------------------------------------------------------------
void wxPlot::DrawPolarGridLegend(wxGCDC* dc, int borderX, int borderY, int width, int height)
{
	const int ZoneNumberThreshold = 5;
	const int legendRectWidth = 20;
	const int legendRectShift = 10;
	const int legentYShift = 50;
	const int legentY2ndShift = 30;

	int legendRectHalfWidth = legendRectWidth / 2;

	wxFont font(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial"));
	dc->SetFont(font);

	int graphVisibleCount = m_graphData->m_plotData.size();
	int xLegend = 0;
	int yLegend = 0;
	int delta = 0;

	if (m_graphData->m_isPortrate)
	{
		xLegend = borderX + width + 10;
		yLegend = borderY;
		delta = height / graphVisibleCount;
	}
	else
	{
		xLegend = borderX;
		yLegend = borderY + height + legentYShift;

		if (graphVisibleCount < ZoneNumberThreshold)
			delta = width / graphVisibleCount;
		else
			delta = width / ZoneNumberThreshold;
	}

	int graphCount = 1;
	for (std::vector< Plot >::iterator plotIter = m_graphData->m_plotData.begin();
		plotIter != m_graphData->m_plotData.end();
		++plotIter)
	{
		std::string plotName = (*plotIter).getName();
		dc->SetBrush(*(*plotIter).brush);

		wxString nameTxt = wxString::Format(wxT("%s"), plotName);

		wxPen *plotPen = wxThePenList->FindOrCreatePen((*plotIter).brush->GetColour(), m_PlotStyle.PlotLineWidth, m_PlotStyle.PlotLineStyle);
		dc->SetPen(*plotPen);

		if (m_graphData->m_isPortrate)
		{
			dc->DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend);

			//wxRect borderRect( xLegend, yLegend, legendRectWidth, legendRectWidth);
			//dc->DrawRectangle( borderRect );

			dc->DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);

			yLegend += delta;
		}
		else
		{
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
		}

		graphCount++;
	}
}
// ----------------------------------------------------------------------------

//DRAW LEGEND -----------------------------------------------------------------

BEGIN_EVENT_TABLE(DrawLegend, wxPanel)
EVT_PAINT(DrawLegend::OnPaint)
END_EVENT_TABLE()

DrawLegend::DrawLegend(wxWindow * parent,
	CartesianPlotData * graphData,
	wxWindowID id,
	const wxPoint & pos,
	const wxSize & size,
	long style,
	const wxString & name)
	: wxPanel(parent, id, pos, size, style, name),
	m_graphData(graphData)
{
	SetBackgroundColour(*wxWHITE);
}

DrawLegend::~DrawLegend(void)
{
}

void DrawLegend::OnPaint(wxPaintEvent &WXUNUSED(event))
{
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

	int graphVisibleCount = m_graphData->m_plotData.size();

	int xLegend = 20;
	int yLegend = 10;
	int delta = height / graphVisibleCount;


	int graphCount = 1;
	for (std::vector< Plot >::iterator plotIter = m_graphData->m_plotData.begin();
		plotIter != m_graphData->m_plotData.end();
		++plotIter)
	{
		std::string plotName = (*plotIter).getName();
		dc.SetBrush(*(*plotIter).brush);

		wxString nameTxt = wxString::Format(wxT("%s"), plotName);

		wxPen *plotPen = wxThePenList->FindOrCreatePen((*plotIter).brush->GetColour(), m_graphData->m_DefaultPlotPenWidth);
		dc.SetPen(*plotPen);

		dc.DrawText(nameTxt, xLegend + legendRectWidth + legendRectShift, yLegend - 6);

		//wxRect borderRect( xLegend, yLegend, legendRectWidth, legendRectWidth);
		//dc->DrawRectangle( borderRect );

		dc.DrawLine(xLegend - legendRectHalfWidth, yLegend, xLegend + legendRectHalfWidth, yLegend);

		yLegend += delta;

		graphCount++;
	}

}

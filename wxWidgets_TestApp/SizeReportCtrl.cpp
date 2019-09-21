#include "stdafx.h"

#include "SizeReportCtrl.h"

wxSizeReportCtrl::wxSizeReportCtrl(wxWindow * parent, wxWindowID id, const wxPoint & pos, const wxSize & size, wxAuiManager * mgr)
	:wxControl(parent, id, pos, size, wxNO_BORDER), m_mgr(mgr)
{
	Bind(wxEVT_PAINT, &wxSizeReportCtrl::OnPaint, this);
	Bind(wxEVT_SIZE, &wxSizeReportCtrl::OnSize, this);
	Bind(wxEVT_ERASE_BACKGROUND, &wxSizeReportCtrl::OnEraseBackground, this);
}

void wxSizeReportCtrl::OnPaint(wxPaintEvent & event)
{
	wxPaintDC dc(this);
	wxSize size = GetClientSize();
	wxString s;
	int h, w, height;

	s.Printf(wxT("Size: %d X %d"), size.x, size.y);

	dc.SetFont(*wxNORMAL_FONT);
	dc.GetTextExtent(s, &w, &height);
	height += 3;
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(*wxWHITE_PEN);
	dc.DrawRectangle(0, 0, size.x, size.y);
	dc.SetPen(*wxLIGHT_GREY_PEN);
	dc.DrawLine(0, 0, size.x, size.y);
	dc.DrawLine(0, size.y, size.x, 0);
	dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2));

	if (m_mgr)
	{
		wxAuiPaneInfo pi = m_mgr->GetPane(this);

		s.Printf(wxT("Layer: %d"), pi.dock_layer);
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2) + (height * 1));

		s.Printf(wxT("Dock: %d Row: %d"), pi.dock_direction, pi.dock_row);
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2) + (height * 2));

		s.Printf(wxT("Position: %d"), pi.dock_pos);
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2) + (height * 3));

		s.Printf(wxT("Proportion: %d"), pi.dock_proportion);
		dc.GetTextExtent(s, &w, &h);
		dc.DrawText(s, (size.x - w) / 2, ((size.y - (height * 5)) / 2) + (height * 4));
	}
}

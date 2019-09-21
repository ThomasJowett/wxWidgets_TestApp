#pragma once
// -- wxSizeReportCtrl --
// (a utility that report the size of it's clients size)

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aui/framemanager.h>

class wxSizeReportCtrl : public wxControl
{
public:
	wxSizeReportCtrl(wxWindow* parent, wxWindowID id = -1,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		wxAuiManager* mgr = NULL);

private:
	void OnPaint(wxPaintEvent& event);
	void OnEraseBackground(wxEraseEvent& event) {}
	void OnSize(wxSizeEvent& event) { Refresh(); }

private:
	wxAuiManager* m_mgr;

};
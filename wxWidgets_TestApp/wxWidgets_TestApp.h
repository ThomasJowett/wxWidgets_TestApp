#pragma once
// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aui/framemanager.h>
#include <wx/grid.h>
#include <wx/treectrl.h>
#include <wx/spinctrl.h>
#include <wx/artprov.h>
#include <wx/image.h>
#include <wx/colordlg.h>
#include <wx/wxhtml.h>

#include "SizeReportCtrl.h"


class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};
wxDECLARE_APP(MyApp);

class MyFrame : public wxFrame
{
	enum
	{
		ID_CreateTree = wxID_HIGHEST + 1,
		ID_CreateGrid,
		ID_CreateText,
		ID_CreateHTML,
		ID_CreateSizeReport,
		ID_GridContent,
		ID_TextContent,
		ID_TreeContent,
		ID_HTMLContent,
		ID_SizeReportContent,
		ID_CreatePerspective,
		ID_CopyPerspectiveCode,
		ID_AllowFloating,
		ID_AllowActivePane,
		ID_TransparentHint,
		ID_HintFade,
		ID_TransparentDrag,
		ID_NoGradient,
		ID_VerticalGradient,
		ID_HorizontalGradient,
		ID_Settings,
		ID_About,
		ID_Hello,
		ID_FirstPerspective = ID_CreatePerspective + 1000
	};

public:
	MyFrame(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

	~MyFrame();

	wxAuiDockArt* GetDockArt();
	void DoUpdate();

private:
	wxTextCtrl* CreateTextCtrl();
	wxGrid* CreateGrid();
	wxTreeCtrl* CreateTreeCtrl();
	wxSizeReportCtrl* CreateSizeReportCtrl(int width = 80, int height = 80);
	wxPoint GetStartPosition();
	wxHtmlWindow* CreateHTMLCtrl();

	wxString GetIntroText();

	void OnEraseBackground(wxEraseEvent& event);
	void OnSize(wxSizeEvent& event);

	void OnCreateTree(wxCommandEvent& event);
	void OnCreateGrid(wxCommandEvent& event);
	void OnCreateHTML(wxCommandEvent& event);
	void OnCreateText(wxCommandEvent& event);
	void OnCreateSizeReport(wxCommandEvent& event);
	void OnChangeContentPane(wxCommandEvent& event);
	void OnCreatePerspective(wxCommandEvent& event);
	void OnCopyPerspectiveCode(wxCommandEvent& event);
	void OnRestorePerspective(wxCommandEvent& event);
	void OnSettings(wxCommandEvent& event);

	void OnGradient(wxCommandEvent& event);
	void OnManagerFlag(wxCommandEvent& event);
	void OnUpdateUI(wxUpdateUIEvent& event);

	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:

	wxAuiManager m_mgr;
	wxArrayString m_perspectives;
	wxMenu* m_perspectives_menu;

	//DECLARE_EVENT_TABLE();
};
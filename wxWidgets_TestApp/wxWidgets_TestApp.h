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

#include "PlotViewDialog.h"
#include "PolarPlotViewDialog.h"

#include "wxPolarPlot.h"

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
		ID_CreatePolarPlot,
		ID_CreateLinearPlot,
		ID_CreatePolarPlotLegend,
		ID_CreatePolarPlotWindow,
		ID_CreatePolarPlotDASWindow,
		ID_CreateText,
		ID_CreateHTML,
		ID_CreateSizeReport,
		ID_CreateNotebook,
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
	wxTextCtrl* CreateTextCtrl(wxWindow* parent);
	wxGrid* CreateGrid(wxWindow* parent);
	wxTreeCtrl* CreateTreeCtrl(wxWindow* parent);
	wxSizeReportCtrl* CreateSizeReportCtrl(wxWindow* parent, int width = 80, int height = 80);
	wxNotebook* CreateNoteBook(wxWindow* parent);
	wxPolarPlot* CreatePolarPlot(wxWindow* parent);
	wxPolarPlot* CreateLinearPlot(wxWindow* parent);
	wxPlotLegend* CreatePolarPlotLegend(wxWindow* parent);
	wxHtmlWindow* CreateHTMLCtrl(wxWindow* parent);

	wxPoint GetStartPosition();

	wxString GetIntroText();

	void OnEraseBackground(wxEraseEvent& event);
	void OnSize(wxSizeEvent& event);

	void OnCreateTree(wxCommandEvent& event);
	void OnCreateGrid(wxCommandEvent& event);
	void OnCreatePolarPlot(wxCommandEvent& event);
	void OnCreateLinearPlot(wxCommandEvent& event);
	void OnCreatePolarPlotLegend(wxCommandEvent& event);
	void OnCreatePolarPlotWindow(wxCommandEvent& event);
	void OnCreatePolarPlotDASWindow(wxCommandEvent& event);
	void OnCreateHTML(wxCommandEvent& event);
	void OnCreateText(wxCommandEvent& event);
	void OnCreateSizeReport(wxCommandEvent& event);
	void OnCreateNotebook(wxCommandEvent& event);
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

	PlotViewDialog* m_CartesianPlot;
	PolarPlotViewDialog* m_PolarPlot;

	PolarPlotData* m_PlotData;
	wxPlotStyle* m_PlotStyle;
};
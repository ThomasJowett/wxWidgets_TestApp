// wxWidgets "wxAUI Test Application" Program

#include "stdafx.h"
#include "wxWidgets_TestApp.h"
#include "PolarPlotWindow.h"
#include "PolarPlotDAS.h"
#include "PolarPlotData.h"
#include "PlotGeneratorHelper.h"
#include <wx/clipbrd.h>

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame(NULL, wxID_ANY, wxT("wxAUI Test Application"), wxDefaultPosition, wxSize(800, 600));
	SetTopWindow(frame);
	frame->Show(true);

	return true;
}
MyFrame::MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	// tell the frame manager to manage this frame
	m_mgr.SetManagedWindow(this);

	// set the frame icon
#ifndef __WXMSW__
	SetIcon(wxIcon(wxT("mondrian"), wxBITMAP_TYPE_ICO_RESOURCE, 16, 16));
#endif // !__WXMSW__

	m_PolarPlot = new PolarPlotViewDialog(this, wxID_ANY, wxT("Polar Plot Test"), wxDefaultPosition, wxSize(850, 650), wxDEFAULT_DIALOG_STYLE);

	m_PlotData = new PolarPlotData("Polar Plot");
	PlotGeneratorHelper generator;
	for (int i = 0; i < 5; ++i)
	{
		generator.AddRandomPlotline(m_PlotData, 36);
	}

	m_PlotStyle = new wxPlotStyle();

	wxMenuBar* menuBar = new wxMenuBar;

	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* view_menu = new wxMenu;
	view_menu->Append(ID_CreateText, _("Create Text Control"));
	view_menu->Append(ID_CreateHTML, _("Create HTML Control"));
	view_menu->Append(ID_CreateTree, _("Create Tree"));
	view_menu->Append(ID_CreateGrid, _("Create Grid"));
	view_menu->Append(ID_CreateSizeReport, _("Create Size Reporter"));
	view_menu->Append(ID_CreateNotebook, _("Create Notebook"));
	view_menu->Append(ID_CreatePolarPlot, _("Create Polar Plot"));
	view_menu->Append(ID_CreateLinearPlot, _("Create Linear Plot"));
	view_menu->Append(ID_CreatePolarPlotLegend, _("Create Polar Plot Legend"));
	view_menu->Append(ID_CreatePolarPlotWindow, _("Create Polar Plot Window"));
	view_menu->Append(ID_CreatePolarPlotDASWindow, _("Create Polar Plot DAS Window"));
	view_menu->AppendSeparator();
	view_menu->Append(ID_GridContent, _("Use a Grid for the Content Pane"));
	view_menu->Append(ID_TextContent, _("Use a Text Control for the context pane"));
	view_menu->Append(ID_HTMLContent, _("Use an HTML Control for the Content Pane"));
	view_menu->Append(ID_TreeContent, _("Use a Tree Control for the Content Pane"));
	view_menu->Append(ID_SizeReportContent, _("Use a Size Reporter for the Content Pane"));

	wxMenu* options_menu = new wxMenu;
	options_menu->AppendCheckItem(ID_AllowFloating, _("Allow Floating"));
	options_menu->AppendCheckItem(ID_TransparentHint, _("Transparent Hint"));
	options_menu->AppendCheckItem(ID_HintFade, _("Transparent Hint Fade-in"));
	options_menu->AppendCheckItem(ID_TransparentDrag, _("Transparent Drag"));
	options_menu->AppendCheckItem(ID_AllowActivePane, _("Allow Active Pane"));
	options_menu->AppendSeparator();
	options_menu->AppendRadioItem(ID_NoGradient, _("No Caption Gradient"));
	options_menu->AppendRadioItem(ID_VerticalGradient, _("Vertical Caption Gradient"));
	options_menu->AppendRadioItem(ID_HorizontalGradient, _("Horizontal Caption Gradient"));
	options_menu->AppendSeparator();
	options_menu->Append(ID_Settings, _("Settings Pane"));

	m_perspectives_menu = new wxMenu;
	m_perspectives_menu->Append(ID_CreatePerspective, _("Create Perspective"));
	m_perspectives_menu->Append(ID_CopyPerspectiveCode, _("Copy Perspective Data To Clipboard"));
	m_perspectives_menu->AppendSeparator();
	m_perspectives_menu->Append(ID_FirstPerspective + 0, _("Default Startup"));
	m_perspectives_menu->Append(ID_FirstPerspective + 1, _("All Panes"));

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	menuBar->Append(menuFile, "&File");
	menuBar->Append(view_menu, "&View");
	menuBar->Append(options_menu, "&Options");
	menuBar->Append(m_perspectives_menu, _("Perspectives"));
	menuBar->Append(menuHelp, "&Help");
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Ready");

	SetMinSize(wxSize(400, 300));

	// create some tool bars
	wxToolBar* tb1 = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);
	tb1->SetToolBitmapSize(wxSize(48, 48));
	tb1->AddTool(101, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
	tb1->AddSeparator();
	tb1->AddTool(102, wxT("Test"), wxArtProvider::GetBitmap(wxART_QUESTION));
	tb1->AddTool(103, wxT("Test"), wxArtProvider::GetBitmap(wxART_INFORMATION));
	tb1->AddTool(103, wxT("Test"), wxArtProvider::GetBitmap(wxART_WARNING));
	tb1->AddTool(103, wxT("Test"), wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
	tb1->Realize();

	wxToolBar* tb2 = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize,
		wxTB_FLAT | wxTB_NODIVIDER);
	tb2->SetToolBitmapSize(wxSize(16, 16));

	wxBitmap tb2_bmp1 = wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, wxSize(16, 16));
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddSeparator();
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddSeparator();
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->AddTool(101, wxT("Test"), tb2_bmp1);
	tb2->Realize();


	wxToolBar* tb3 = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize,
		wxTB_FLAT | wxTB_NODIVIDER);
	tb3->SetToolBitmapSize(wxSize(16, 16));
	wxBitmap tb3_bmp1 = wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16, 16));
	tb3->AddTool(101, wxT("Test"), tb3_bmp1);
	tb3->AddTool(101, wxT("Test"), tb3_bmp1);
	tb3->AddTool(101, wxT("Test"), tb3_bmp1);
	tb3->AddTool(101, wxT("Test"), tb3_bmp1);
	tb3->AddSeparator();
	tb3->AddTool(101, wxT("Test"), tb3_bmp1);
	tb3->AddTool(101, wxT("Test"), tb3_bmp1);
	tb3->Realize();



	wxToolBar* tb4 = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize,
		wxTB_FLAT | wxTB_NODIVIDER | wxTB_HORZ_TEXT);
	tb4->SetToolBitmapSize(wxSize(16, 16));
	wxBitmap tb4_bmp1 = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	tb4->AddTool(101, wxT("Item 1"), tb4_bmp1);
	tb4->AddTool(101, wxT("Item 2"), tb4_bmp1);
	tb4->AddTool(101, wxT("Item 3"), tb4_bmp1);
	tb4->AddTool(101, wxT("Item 4"), tb4_bmp1);
	tb4->AddSeparator();
	tb4->AddTool(101, wxT("Item 5"), tb4_bmp1);
	tb4->AddTool(101, wxT("Item 6"), tb4_bmp1);
	tb4->AddTool(101, wxT("Item 7"), tb4_bmp1);
	tb4->AddTool(101, wxT("Item 8"), tb4_bmp1);
	tb4->Realize();

	// create some center panes

	m_mgr.AddPane(CreateGrid(this), wxAuiPaneInfo().Name(wxT("grid_content")).
		CenterPane().Hide());

	m_mgr.AddPane(CreateTreeCtrl(this), wxAuiPaneInfo().Name(wxT("tree_content")).
		CenterPane().Hide());

	m_mgr.AddPane(CreateSizeReportCtrl(this), wxAuiPaneInfo().Name(wxT("sizereport_content")).
		CenterPane().Hide());

	m_mgr.AddPane(CreateTextCtrl(this), wxAuiPaneInfo().Name(wxT("text_content")).
		CenterPane().Hide());

	m_mgr.AddPane(CreateHTMLCtrl(this), wxAuiPaneInfo().Name(wxT("html_content")).
		CenterPane());

	// add the tool bars to the manager
	m_mgr.AddPane(tb1, wxAuiPaneInfo().Name(wxT("tb1")).Caption(wxT("Big Toolbar"))
		.ToolbarPane().Top().LeftDockable(false).RightDockable(false));

	m_mgr.AddPane(tb2, wxAuiPaneInfo().
		Name(wxT("tb2")).Caption(wxT("Toolbar 2")).
		ToolbarPane().Top().Row(1).
		LeftDockable(false).RightDockable(false));

	m_mgr.AddPane(tb3, wxAuiPaneInfo().
		Name(wxT("tb3")).Caption(wxT("Toolbar 3")).
		ToolbarPane().Top().Row(1).Position(1).
		LeftDockable(false).RightDockable(false));

	m_mgr.AddPane(tb4, wxAuiPaneInfo().
		Name(wxT("tb4")).Caption(wxT("Sample Bookmark Toolbar")).
		ToolbarPane().Top().Row(2).
		LeftDockable(false).RightDockable(false));

	// make some default perspectives

	//wxString perspective_all = m_mgr.SavePerspective();
	//
	//int i, count;
	//wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
	//for (i = 0, count = all_panes.GetCount(); i < count; ++i)
	//	if (!all_panes.Item(i).IsToolbar())
	//		all_panes.Item(i).Hide();
	//m_mgr.GetPane(wxT("tb1")).Hide();
	//m_mgr.GetPane(wxT("tb5")).Hide();
	//m_mgr.GetPane(wxT("test8")).Show().Left().Layer(0).Row(0).Position(0);
	//m_mgr.GetPane(wxT("test10")).Show().Bottom().Layer(0).Row(0).Position(0);
	//m_mgr.GetPane(wxT("html_content")).Show();
	//wxString perspective_default = m_mgr.SavePerspective();
	//
	//m_perspectives.Add(perspective_default);
	//m_perspectives.Add(perspective_all);

	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MyFrame::OnCreateText, this, ID_CreateText);
	Bind(wxEVT_MENU, &MyFrame::OnCreateTree, this, ID_CreateTree);
	Bind(wxEVT_MENU, &MyFrame::OnCreateGrid, this, ID_CreateGrid);
	Bind(wxEVT_MENU, &MyFrame::OnCreatePolarPlot, this, ID_CreatePolarPlot);
	Bind(wxEVT_MENU, &MyFrame::OnCreateLinearPlot, this, ID_CreateLinearPlot);
	Bind(wxEVT_MENU, &MyFrame::OnCreatePolarPlotLegend, this, ID_CreatePolarPlotLegend);
	Bind(wxEVT_MENU, &MyFrame::OnCreatePolarPlotWindow, this, ID_CreatePolarPlotWindow);
	Bind(wxEVT_MENU, &MyFrame::OnCreatePolarPlotDASWindow, this, ID_CreatePolarPlotDASWindow);
	Bind(wxEVT_MENU, &MyFrame::OnCreateHTML, this, ID_CreateHTML);
	Bind(wxEVT_MENU, &MyFrame::OnCreateSizeReport, this, ID_CreateSizeReport);
	Bind(wxEVT_MENU, &MyFrame::OnCreateNotebook, this, ID_CreateNotebook);
	Bind(wxEVT_MENU, &MyFrame::OnCreatePerspective, this, ID_CreatePerspective);
	Bind(wxEVT_MENU, &MyFrame::OnCopyPerspectiveCode, this, ID_CopyPerspectiveCode);
	Bind(wxEVT_MENU, &MyFrame::OnManagerFlag, this, ID_AllowFloating);
	Bind(wxEVT_MENU, &MyFrame::OnManagerFlag, this, ID_TransparentHint);
	Bind(wxEVT_MENU, &MyFrame::OnManagerFlag, this, ID_HintFade);
	Bind(wxEVT_MENU, &MyFrame::OnManagerFlag, this, ID_TransparentDrag);
	Bind(wxEVT_MENU, &MyFrame::OnManagerFlag, this, ID_AllowActivePane);
	Bind(wxEVT_MENU, &MyFrame::OnGradient, this, ID_HorizontalGradient);
	Bind(wxEVT_MENU, &MyFrame::OnGradient, this, ID_NoGradient);
	Bind(wxEVT_MENU, &MyFrame::OnGradient, this, ID_VerticalGradient);
	Bind(wxEVT_MENU, &MyFrame::OnSettings, this, ID_Settings);
	Bind(wxEVT_MENU, &MyFrame::OnChangeContentPane, this, ID_GridContent);
	Bind(wxEVT_MENU, &MyFrame::OnChangeContentPane, this, ID_TreeContent);
	Bind(wxEVT_MENU, &MyFrame::OnChangeContentPane, this, ID_TextContent);
	Bind(wxEVT_MENU, &MyFrame::OnChangeContentPane, this, ID_SizeReportContent);
	Bind(wxEVT_MENU, &MyFrame::OnChangeContentPane, this, ID_HTMLContent);
	Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this, ID_AllowFloating);
	Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this, ID_TransparentHint);
	Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this, ID_HintFade);
	Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this, ID_TransparentDrag);
	Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this, ID_NoGradient);
	Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this, ID_VerticalGradient);
	Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this, ID_HorizontalGradient);

	m_mgr.Update();

}
MyFrame::~MyFrame()
{
	m_mgr.UnInit();
}
wxAuiDockArt* MyFrame::GetDockArt()
{
	return m_mgr.GetArtProvider();
}
void MyFrame::DoUpdate()
{
	m_mgr.Update();
}
wxTextCtrl* MyFrame::CreateTextCtrl(wxWindow* parent)
{
	wxString text;
	static int n = 0;

	text.Printf(wxT("This is text box %d"), ++n);

	return new wxTextCtrl(parent, -1, text,
		wxPoint(0, 0), wxSize(150, 90),
		wxNO_BORDER | wxTE_MULTILINE);
}
wxGrid* MyFrame::CreateGrid(wxWindow* parent)
{
	wxGrid* grid = new wxGrid(parent, -1,
		wxPoint(0, 0),
		wxSize(150, 250),
		wxNO_BORDER | wxWANTS_CHARS);
	grid->CreateGrid(50, 20);
	return grid;
}
wxTreeCtrl* MyFrame::CreateTreeCtrl(wxWindow* parent)
{
	wxTreeCtrl* tree = new wxTreeCtrl(parent, -1,
		wxPoint(0, 0), wxSize(160, 250),
		wxTR_DEFAULT_STYLE | wxNO_BORDER);

	wxTreeItemId root = tree->AddRoot(wxT("wxAUI Project"));
	wxArrayTreeItemIds items;


	wxImageList* imglist = new wxImageList(16, 16, true, 2);
	imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16, 16)));
	imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16)));
	tree->AssignImageList(imglist);

	items.Add(tree->AppendItem(root, wxT("Item 1"), 0));
	items.Add(tree->AppendItem(root, wxT("Item 2"), 0));
	items.Add(tree->AppendItem(root, wxT("Item 3"), 0));
	items.Add(tree->AppendItem(root, wxT("Item 4"), 0));
	items.Add(tree->AppendItem(root, wxT("Item 5"), 0));


	int i, count;
	for (i = 0, count = items.Count(); i < count; ++i)
	{
		wxTreeItemId id = items.Item(i);
		tree->AppendItem(id, wxT("Subitem 1"), 1);
		tree->AppendItem(id, wxT("Subitem 2"), 1);
		tree->AppendItem(id, wxT("Subitem 3"), 1);
		tree->AppendItem(id, wxT("Subitem 4"), 1);
		tree->AppendItem(id, wxT("Subitem 5"), 1);
	}


	tree->Expand(root);

	return tree;
}


void MyFrame::OnEraseBackground(wxEraseEvent& event)
{
	event.Skip();
}
void MyFrame::OnSize(wxSizeEvent& event)
{
	event.Skip();
}
void MyFrame::OnCreateTree(wxCommandEvent& event)
{
	m_mgr.AddPane(CreateTreeCtrl(this), wxAuiPaneInfo().
		Name(wxT("Test")).Caption(wxT("Tree Control")).
		Float().FloatingPosition(GetStartPosition()).
		FloatingSize(wxSize(150, 300)));
	m_mgr.Update();
}
void MyFrame::OnCreateGrid(wxCommandEvent& event)
{
	m_mgr.AddPane(CreateGrid(this), wxAuiPaneInfo().
		Name(wxT("Test")).Caption(wxT("Grid")).
		Float().FloatingPosition(GetStartPosition()).
		FloatingSize(wxSize(300, 200)));
	m_mgr.Update();
}
void MyFrame::OnCreateLinearPlot(wxCommandEvent& event)
{
	m_mgr.AddPane(CreateLinearPlot(this), wxAuiPaneInfo().
		Name(wxT("LinearPlot")).Caption(wxT("Polar Plot")).
		Float().FloatingPosition(GetStartPosition()).
		FloatingSize(wxSize(500, 500)));
	m_mgr.Update();
}
void MyFrame::OnCreatePolarPlotLegend(wxCommandEvent& event)
{
	m_mgr.AddPane(CreatePolarPlotLegend(this), wxAuiPaneInfo().
		Name(wxT("PolarPlotLegend")).Caption(wxT("Polar Plot")).
		Float().FloatingPosition(GetStartPosition()).
		FloatingSize(wxSize(500, 500)));
	m_mgr.Update();
}
void MyFrame::OnCreatePolarPlot(wxCommandEvent& event)
{
	m_mgr.AddPane(CreatePolarPlot(this), wxAuiPaneInfo().
		Name(wxT("PolarPlot")).Caption(wxT("Cartesian Plot")).
		Float().FloatingPosition(GetStartPosition()).
		FloatingSize(wxSize(500, 500)));
	m_mgr.Update();
}
void MyFrame::OnCreatePolarPlotWindow(wxCommandEvent& event)
{
	wxSize minSize = wxSize(1800, 910);
	auto* window = new PolarPlotWindow(this, wxID_ANY, "Polar Plot Window", wxDefaultPosition, minSize, wxDEFAULT_FRAME_STYLE);

	window->SetMinSize(minSize);

	window->ShowModal();
}
void MyFrame::OnCreatePolarPlotDASWindow(wxCommandEvent& event)
{
	wxSize minSize = wxSize(600, 800);
	std::vector<PolarPlotData> multiPlotData;

	for (size_t i = 0; i < 20; i++)
	{
		PolarPlotData* graphData = new PolarPlotData(std::to_string(i * 10), "Azimuth", "Proportion of Shotlines");

		PlotGeneratorHelper generator(i);
		for (int i = 0; i < 5; ++i)
		{
			generator.AddRandomPlotline(graphData, 36);
		}

		multiPlotData.push_back(*graphData);
	}
	PolarPlotDAS* window = new PolarPlotDAS(this, wxID_ANY, "Polar Plot Window", multiPlotData, wxDefaultPosition, minSize, wxDEFAULT_FRAME_STYLE);

	window->SetMinSize(minSize);

	window->ShowModal();
}
void MyFrame::OnCreateHTML(wxCommandEvent& event)
{
	m_mgr.AddPane(CreateHTMLCtrl(this), wxAuiPaneInfo().
		Name(wxT("Test")).Caption(wxT("Grid")).
		Float().FloatingPosition(GetStartPosition()).
		FloatingSize(wxSize(300, 200)));
	m_mgr.Update();
}
void MyFrame::OnCreateText(wxCommandEvent& event)
{
	m_mgr.AddPane(CreateTextCtrl(this), wxAuiPaneInfo().
		Name(wxT("Test")).Caption(wxT("Text Control")).
		Float().FloatingPosition(GetStartPosition()));
	m_mgr.Update();
}
void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets Hello World example",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnSettings(wxCommandEvent& event)
{
	// show the settings pane, and float it
	wxAuiPaneInfo& floating_pane = m_mgr.GetPane(wxT("settings")).Float().Show();

	if (floating_pane.floating_pos == wxDefaultPosition)
	{
		floating_pane.FloatingPosition(GetStartPosition());
	}

	m_mgr.Update();
}

void MyFrame::OnGradient(wxCommandEvent& event)
{
	int gradient = 0;

	switch (event.GetId())
	{
	case ID_NoGradient:		gradient = wxAUI_GRADIENT_NONE; break;
	case ID_VerticalGradient:	gradient = wxAUI_GRADIENT_VERTICAL; break;
	case ID_HorizontalGradient:	gradient = wxAUI_GRADIENT_HORIZONTAL; break;
	default: break;
	}

	//m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_GRADIENT_TYPE, gradient);
	m_mgr.Update();
}

void MyFrame::OnManagerFlag(wxCommandEvent& event)
{
	unsigned int flag = 0;

#ifndef __WXMSW__
	if (event.GetId() == ID_TransparentDrag ||
		event.GetId() == ID_TransparentHint ||
		event.GetId() == ID_TransparentHintFade)
	{
		wxMessageBox(wxT("This option is presently only available on wxMSW"));
		return;
	}
#endif // !__WXMSW__

	switch (event.GetId())
	{
	case ID_AllowFloating:		flag = wxAUI_MGR_ALLOW_FLOATING; break;
	case ID_TransparentDrag:	flag = wxAUI_MGR_TRANSPARENT_DRAG; break;
	case ID_TransparentHint:	flag = wxAUI_MGR_TRANSPARENT_HINT; break;
	case ID_HintFade:			flag = wxAUI_MGR_HINT_FADE; break;
	case ID_AllowActivePane:	flag = wxAUI_MGR_ALLOW_ACTIVE_PANE; break;
	}
	m_mgr.SetFlags(m_mgr.GetFlags() ^ flag);
	m_mgr.Update();
}

void MyFrame::OnUpdateUI(wxUpdateUIEvent& event)
{
	unsigned int flags = m_mgr.GetFlags();

	switch (event.GetId())
	{
	case ID_NoGradient:
		//event.Check(m_mgr.GetArtProvider()->GetMetric)
	default:
		break;
	}
}

wxSizeReportCtrl* MyFrame::CreateSizeReportCtrl(wxWindow* parent, int width, int height)
{
	wxSizeReportCtrl* ctrl = new wxSizeReportCtrl(parent, -1,
		wxDefaultPosition,
		wxSize(width, height), &m_mgr);
	return ctrl;
}

wxNotebook* MyFrame::CreateNoteBook(wxWindow* parent)
{
	wxNotebook* notebook = new wxNotebook(parent, -1,
		wxPoint(0, 0),
		wxSize(150, 250),
		wxNO_BORDER | wxWANTS_CHARS);

	notebook->AddPage(CreateGrid(notebook), "Grid");
	notebook->AddPage(CreateSizeReportCtrl(notebook), "Size Report");
	notebook->AddPage(CreateTreeCtrl(notebook), "Tree Control");
	notebook->AddPage(CreatePolarPlot(notebook), "PolarPlot");
	return notebook;
}

wxPolarPlot* MyFrame::CreateLinearPlot(wxWindow* parent)
{
	wxPolarPlot* drawPanel = new wxPolarPlot(parent, m_PlotData, m_PlotStyle, true, true, true);
	return drawPanel;
}

wxPlotLegend* MyFrame::CreatePolarPlotLegend(wxWindow* parent)
{
	wxPlotLegend* drawLegend = new wxPlotLegend(parent, m_PlotData, m_PlotStyle);
	return drawLegend;
}

wxPolarPlot* MyFrame::CreatePolarPlot(wxWindow* parent)
{
	wxPolarPlot* drawPanel = new wxPolarPlot(parent, m_PlotData, m_PlotStyle, true, true, false);
	return drawPanel;
}

wxPoint MyFrame::GetStartPosition()
{
	static int x = 0;
	x += 20;
	wxPoint pt = ClientToScreen(wxPoint(0, 0));
	return wxPoint(pt.x + x, pt.y + x);
}

wxHtmlWindow* MyFrame::CreateHTMLCtrl(wxWindow* parent)
{
	wxHtmlWindow* ctrl = new wxHtmlWindow(parent, -1,
		wxDefaultPosition,
		wxSize(400, 300));
	ctrl->SetPage(GetIntroText());
	return ctrl;
}

wxString MyFrame::GetIntroText()
{
	const char* text =
		"<html><body>"
		"<h3>Welcome to wxWidgets</h3>"
		"<br/><b>Overview</b><br/>"
		"<p>wxAUI is an Advanced User Interface library for the wxWidgets toolkit "
		"that allows developers to create high-quality, cross-platform user "
		"interfaces quickly and easily.</p>"
		"<p><b>Features</b></p>"
		"<p>With wxAUI version 0.9.2, developers can create application frameworks with:</p>"
		"<ul>"
		"<li>Native, dockable floating frames</li>"
		"<li>Perspective saving and loading</li>"
		"<li>Native toolbars incorporating real-time, &quot;spring-loaded&quot; dragging</li>"
		"<li>Customizable floating/docking behavior</li>"
		"<li>Completely customizable look-and-feel</li>"
		"<li>Optional transparent window effects (while dragging or docking)</li>"
		"</ul>"
		"<p><b>What's new in 0.9.2?</b></p>"
		"<p>The following features/fixes have been added since the last version of wxAUI:</p>"
		"<ul>"
		"<li>Support for wxMac</li>"
		"<li>Updates for wxWidgets 2.6.3</li>"
		"<li>Fix to pass more unused events through</li>"
		"<li>Fix to allow floating windows to receive idle events</li>"
		"<li>Fix for minimizing/maximizing problem with transparent hint pane</li>"
		"<li>Fix to not paint empty hint rectangles</li>"
		"<li>Fix for 64-bit compilation</li>"
		"</ul>"
		"<p><b>What changed in 0.9.1?</b></p>"
		"<p>The following features/fixes were added in wxAUI 0.9.1:</p>"
		"<ul>"
		"<li>Support for MDI frames</li>"
		"<li>Gradient captions option</li>"
		"<li>Active/Inactive panes option</li>"
		"<li>Fix for screen artifacts/paint problems</li>"
		"<li>Fix for hiding/showing floated window problem</li>"
		"<li>Fix for floating pane sizing problem</li>"
		"<li>Fix for drop position problem when dragging around center pane margins</li>"
		"<li>LF-only text file formatting for source code</li>"
		"</ul>"
		"<p>See README.txt for more information.</p>"
		"</body></html>";

	return wxString::FromAscii(text);
}

void MyFrame::OnCreateSizeReport(wxCommandEvent& event)
{
	m_mgr.AddPane(CreateSizeReportCtrl(this), wxAuiPaneInfo()
		.Name(wxT("Test")).Caption(wxT("Client Size Reporter"))
		.Float().FloatingPosition(GetStartPosition()));
	m_mgr.Update();
}

void MyFrame::OnCreateNotebook(wxCommandEvent& event)
{
	m_mgr.AddPane(CreateNoteBook(this), wxAuiPaneInfo()
		.Name(wxT("Notebook")).Caption(wxT("Client Notebook"))
		.Float().FloatingPosition(GetStartPosition()));
	m_mgr.Update();
}

void MyFrame::OnChangeContentPane(wxCommandEvent& event)
{
	m_mgr.GetPane(wxT("grid_content")).Show(event.GetId() == ID_GridContent ? true : false);
	m_mgr.GetPane(wxT("text_content")).Show(event.GetId() == ID_TextContent ? true : false);
	m_mgr.GetPane(wxT("tree_content")).Show(event.GetId() == ID_TreeContent ? true : false);
	m_mgr.GetPane(wxT("sizereport_content")).Show(event.GetId() == ID_SizeReportContent ? true : false);
	m_mgr.GetPane(wxT("html_content")).Show(event.GetId() == ID_HTMLContent ? true : false);
	m_mgr.Update();
}

void MyFrame::OnCreatePerspective(wxCommandEvent& event)
{
	wxTextEntryDialog dlg(this, wxT("Enter a name for the new perspective:"),
		wxT("wxAUI Test"));

	dlg.SetValue(wxString::Format(wxT("Perspective %d"), m_perspectives.GetCount() + 1));
	if (dlg.ShowModal() != wxID_OK)
		return;

	if (m_perspectives.GetCount() == 0)
	{
		m_perspectives_menu->AppendSeparator();
	}

	m_perspectives_menu->Append(ID_FirstPerspective + m_perspectives.GetCount(), dlg.GetValue());
	m_perspectives.Add(m_mgr.SavePerspective());
}

void MyFrame::OnCopyPerspectiveCode(wxCommandEvent& event)
{
	wxString s = m_mgr.SavePerspective();

	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxTextDataObject(s));
		wxTheClipboard->Close();
	}
}

void MyFrame::OnRestorePerspective(wxCommandEvent& event)
{
	m_mgr.LoadPerspective(m_perspectives.Item(event.GetId() - ID_FirstPerspective));
}

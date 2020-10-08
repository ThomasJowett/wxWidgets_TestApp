#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "PolarPlotWindow.h"
#include "PolarPlotData.h"
#include "PlotGeneratorHelper.h"

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(PolarPlotWindow, wxDialog)
EVT_BUTTON(ID_POLAR_BUTTON, PolarPlotWindow::OnButtonPolar)
EVT_BUTTON(ID_POLARLEGEND_BUTTON, PolarPlotWindow::OnButtonPolarLegend)
EVT_BUTTON(ID_LINEAR_BUTTON, PolarPlotWindow::OnButtonLinear)
EVT_BUTTON(ID_LINEARLEGEND_BUTTON, PolarPlotWindow::OnButtonLinearLegend)
END_EVENT_TABLE()


// ----------------------------------------------------------------------------
PolarPlotWindow::PolarPlotWindow(wxWindow * parent, wxWindowID id, const wxString & title, const wxPoint & pos, const wxSize & size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	PolarPlotWindow* setupPanel = this;

	// Top-level sizer
	wxBoxSizer* rootSizer = new wxBoxSizer(wxVERTICAL);
	rootSizer->SetMinSize(wxSize(1800, 900));
	setupPanel->SetSizer(rootSizer);

	//Polar Plot Sizer
	wxBoxSizer* polarPlotSizer = new wxBoxSizer(wxHORIZONTAL);
	rootSizer->Add(polarPlotSizer, 19, wxGROW | wxALL, 3);

	//Polar Plot
	wxStaticBox* polarPlotStaticBox = new wxStaticBox(setupPanel, wxID_ANY, _("Polar Plot"));
	polarPlotSizer->Add(polarPlotStaticBox, 1, wxGROW | wxALL, 5);

	//TEMP CODE ----------------------------------------------------------------------------------------
	//TODO: make data a member and load in the data
	PolarPlotData * graphData = new PolarPlotData("Polar Plots: 1 - 10");

	PlotGeneratorHelper generator;
	for (int i = 0; i < 5; ++i)
	{
		generator.AddRandomPlotline(graphData, 36);
	}
	//--------------------------------------------------------------------------------------------------
	m_PlotStyle = new wxPlotStyle();

	wxPolarPlot* drawPolarPanel = new wxPolarPlot(polarPlotStaticBox, graphData, m_PlotStyle, false, false, false,
		wxID_ANY, wxPoint(18.5, 20), wxSize(550, 490), wxTAB_TRAVERSAL | wxNO_BORDER, title);

	//Linear Plot
	wxStaticBox* linearPlotStaticBox = new wxStaticBox(setupPanel, wxID_ANY, _("Linear Plot"));
	polarPlotSizer->Add(linearPlotStaticBox, 2, wxGROW | wxALL, 5);

	wxPolarPlot* drawCartesianPanel = new wxPolarPlot(linearPlotStaticBox, graphData, m_PlotStyle, false, false, true, wxID_ANY,
		wxPoint(25, 20), wxSize(1120, 490), wxTAB_TRAVERSAL | wxNO_BORDER, title);

	//Controls Sizer
	wxBoxSizer* controlsSizer = new wxBoxSizer(wxHORIZONTAL);
	rootSizer->Add(controlsSizer, 11, wxGROW | wxALL, 3);

	//Controls
	wxStaticBox* controlsStaticBox = new wxStaticBox(setupPanel, wxID_ANY, _("Data Selection"));
	wxStaticBoxSizer* controlsStaticBoxSizer = new wxStaticBoxSizer(controlsStaticBox, wxHORIZONTAL);
	controlsSizer->Add(controlsStaticBoxSizer, 2, wxGROW | wxALL, 5);

	wxGridSizer* gridSizerLeft = new wxGridSizer(2, 2, -1, -1);
	controlsStaticBoxSizer->Add(gridSizerLeft, 0, wxGROW | wxALL, 2);

	wxSize gridSizerLeftItemMaxSize = wxSize(170, 100);

	//Target List Box
	wxStaticBox* targetStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Targets"));
	wxStaticBoxSizer* targetStaticBoxSizer = new wxStaticBoxSizer(targetStaticBox, wxHORIZONTAL);
	gridSizerLeft->Add(targetStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString targetStrings;
	targetStrings.Add(_("BTR80_NATO"));
	wxCheckListBox* targetListBox = new wxCheckListBox(targetStaticBox, ID_TARGET_LISTBOX, wxDefaultPosition, gridSizerLeftItemMaxSize, targetStrings, wxLB_NEEDED_SB);
	targetStaticBoxSizer->Add(targetListBox, 0, wxALL | wxEXPAND, 1);

	//Elevation List Box
	wxStaticBox* elevationStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Elevations"));
	wxStaticBoxSizer* elevationStaticBoxSizer = new wxStaticBoxSizer(elevationStaticBox, wxHORIZONTAL);
	gridSizerLeft->Add(elevationStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString elevationStrings;
	elevationStrings.Add(_("0"));
	elevationStrings.Add(_("30"));
	wxCheckListBox* elevationListBox = new wxCheckListBox(elevationStaticBox, ID_ELEVATION_LISTBOX, wxDefaultPosition, gridSizerLeftItemMaxSize, elevationStrings, wxLB_NEEDED_SB);
	elevationStaticBoxSizer->Add(elevationListBox, 0, wxALL | wxEXPAND, 1);

	//Min/Max List Box
	wxStaticBox* minMaxStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Min / Max"));
	wxStaticBoxSizer* minMaxStaticBoxSizer = new wxStaticBoxSizer(minMaxStaticBox, wxHORIZONTAL);
	gridSizerLeft->Add(minMaxStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString minMaxStrings;
	minMaxStrings.Add(_("No limit"));
	wxCheckListBox* minMaxListBox = new wxCheckListBox(minMaxStaticBox, ID_MINMAX_LISTBOX, wxDefaultPosition, gridSizerLeftItemMaxSize, minMaxStrings, wxLB_NEEDED_SB);
	minMaxStaticBoxSizer->Add(minMaxListBox, 0, wxALL | wxEXPAND, 1);

	//Dispersion Centre List Box
	wxStaticBox* dispersionStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Dispersion"));
	wxStaticBoxSizer* dispersionStaticBoxSizer = new wxStaticBoxSizer(dispersionStaticBox, wxHORIZONTAL);
	gridSizerLeft->Add(dispersionStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString dispersionStrings;
	dispersionStrings.Add(_("Variable"));
	dispersionStrings.Add(_("Fixed"));
	wxCheckListBox* dispersionListBox = new wxCheckListBox(dispersionStaticBox, ID_DISPERSION_LISTBOX, wxDefaultPosition, gridSizerLeftItemMaxSize, dispersionStrings, wxLB_NEEDED_SB);
	dispersionStaticBoxSizer->Add(dispersionListBox, 0, wxALL | wxEXPAND, 1);

	controlsStaticBoxSizer->AddSpacer(20);

	wxGridSizer* gridSizerCentre = new wxGridSizer(1, 2, -1, -1);
	controlsStaticBoxSizer->Add(gridSizerCentre, 0, wxGROW | wxALL, 2);

	wxSize gridSizerCentreItemMaxSize = wxSize(170, 250);

	//Threat List Box
	wxStaticBox* threatStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Threats"));
	wxStaticBoxSizer* threatStaticBoxSizer = new wxStaticBoxSizer(threatStaticBox, wxHORIZONTAL);
	gridSizerCentre->Add(threatStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString threatStrings;
	threatStrings.Add(_("BigATGM"));
	threatStrings.Add(_("MedKE"));
	wxCheckListBox* threatListBox = new wxCheckListBox(threatStaticBox, ID_THREAT_LISTBOX, wxDefaultPosition, gridSizerCentreItemMaxSize, threatStrings, wxLB_NEEDED_SB);
	threatStaticBoxSizer->Add(threatListBox, 0, wxALL | wxEXPAND, 1);

	//Range List Box
	wxStaticBox* rangeStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Ranges"));
	wxStaticBoxSizer* rangeStaticBoxSizer = new wxStaticBoxSizer(rangeStaticBox, wxHORIZONTAL);
	gridSizerCentre->Add(rangeStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString rangeStrings;
	rangeStrings.Add(_("500"));
	rangeStrings.Add(_("1000"));
	rangeStrings.Add(_("1500"));
	wxCheckListBox* rangeListBox = new wxCheckListBox(rangeStaticBox, ID_RANGE_LISTBOX, wxDefaultPosition, gridSizerCentreItemMaxSize, rangeStrings, wxLB_NEEDED_SB);
	rangeStaticBoxSizer->Add(rangeListBox, 0, wxALL | wxEXPAND, 1);

	controlsStaticBoxSizer->AddSpacer(20);

	wxGridSizer* gridSizerRight = new wxGridSizer(3, 1, -1, -1);
	controlsStaticBoxSizer->Add(gridSizerRight, 0, wxGROW | wxALL, 2);

	wxSize gridSizerRightItemMaxSize = wxSize(170, 50);

	//Shot List Box
	wxStaticBox* shotStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Shots"));
	wxStaticBoxSizer* shotStaticBoxSizer = new wxStaticBoxSizer(shotStaticBox, wxHORIZONTAL);
	gridSizerRight->Add(shotStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString shotStrings;
	shotStrings.Add(_("First"));
	shotStrings.Add(_("Single"));
	shotStrings.Add(_("Subsequent"));
	wxCheckListBox* shotListBox = new wxCheckListBox(shotStaticBox, ID_SHOT_LISTBOX, wxDefaultPosition, wxSize(170, 60), shotStrings, wxLB_NEEDED_SB);
	shotStaticBoxSizer->Add(shotListBox, 0, wxALL | wxEXPAND, 1);

	//Target Status List Box
	wxStaticBox* targetStatusStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Target Status"));
	wxStaticBoxSizer* targetStatusStaticBoxSizer = new wxStaticBoxSizer(targetStatusStaticBox, wxHORIZONTAL);
	gridSizerRight->Add(targetStatusStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString targetStatusStrings;
	targetStatusStrings.Add(_("Static"));
	targetStatusStrings.Add(_("Moving"));
	wxCheckListBox* targetStatusListBox = new wxCheckListBox(targetStatusStaticBox, ID_TARGETSTATUS_LISTBOX, wxDefaultPosition, gridSizerRightItemMaxSize, targetStatusStrings, wxLB_NEEDED_SB);
	targetStatusStaticBoxSizer->Add(targetStatusListBox, 0, wxALL | wxEXPAND, 1);

	//Firer Status List Box
	wxStaticBox* firerStatusStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Firer Status"));
	wxStaticBoxSizer* firerStatusStaticBoxSizer = new wxStaticBoxSizer(firerStatusStaticBox, wxHORIZONTAL);
	gridSizerRight->Add(firerStatusStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString firerStatusStrings;
	firerStatusStrings.Add(_("Static"));
	firerStatusStrings.Add(_("Moving"));
	wxCheckListBox* firerStatusListBox = new wxCheckListBox(firerStatusStaticBox, ID_FIRERSTATUS_LISTBOX, wxDefaultPosition, gridSizerRightItemMaxSize, firerStatusStrings, wxLB_NEEDED_SB);
	firerStatusStaticBoxSizer->Add(firerStatusListBox, 0, wxALL | wxEXPAND, 1);

	//Kill Values List Box
	wxStaticBox* killValuesStaticBox = new wxStaticBox(controlsStaticBox, wxID_ANY, _("Kill Values"));
	wxStaticBoxSizer* killValuesStaticBoxSizer = new wxStaticBoxSizer(killValuesStaticBox, wxHORIZONTAL);
	controlsStaticBoxSizer->Add(killValuesStaticBoxSizer, 0, wxALL | wxEXPAND, 5);
	wxArrayString killValuesStrings;
	killValuesStrings.Add(_("M"));
	killValuesStrings.Add(_("F"));
	killValuesStrings.Add(_("K"));
	killValuesStrings.Add(_("G"));
	killValuesStrings.Add(_("P"));
	killValuesStrings.Add(_("MF"));
	killValuesStrings.Add(_("MK"));
	killValuesStrings.Add(_("FK"));
	killValuesStrings.Add(_("PK"));
	killValuesStrings.Add(_("MFK"));
	killValuesStrings.Add(_("PHit"));
	killValuesStrings.Add(_("PFuze"));
	wxCheckListBox* killValuesListBox = new wxCheckListBox(killValuesStaticBox, ID_DEGRADATION_LISTBOX, wxDefaultPosition, wxSize(170, 250), killValuesStrings, wxLB_NEEDED_SB);
	killValuesStaticBoxSizer->Add(killValuesListBox, 0, wxALL | wxEXPAND, 1);

	wxBoxSizer* legendImagesSizer = new wxBoxSizer(wxVERTICAL);
	controlsSizer->Add(legendImagesSizer, 1, wxGROW | wxALL, 0);

	//Legend
	wxStaticBox* legendStaticBox = new wxStaticBox(setupPanel, wxID_ANY, _("Legend"));
	wxStaticBoxSizer* legendStaticBoxSizer = new wxStaticBoxSizer(legendStaticBox, wxHORIZONTAL);
	legendImagesSizer->Add(legendStaticBoxSizer, 0, wxGROW | wxALL, 5);

	wxPlotLegend* drawLegend = new wxPlotLegend(legendStaticBox, graphData, m_PlotStyle, wxID_ANY, wxPoint(50,50), wxSize(600,250), wxTAB_TRAVERSAL | wxNO_BORDER, title);
	legendStaticBoxSizer->Add(drawLegend, 0, wxALL | wxEXPAND, 10);

	//Image Export
	wxStaticBox* imagesStaticBox = new wxStaticBox(setupPanel, wxID_ANY, _("Image Export"));
	wxStaticBoxSizer* imagesStaticBoxSizer = new wxStaticBoxSizer(imagesStaticBox, wxHORIZONTAL);
	legendImagesSizer->Add(imagesStaticBoxSizer, 0, wxGROW | wxALL, 5);

	mPolarExport = new wxButton(setupPanel, ID_POLAR_BUTTON, _("Polar"));
	imagesStaticBoxSizer->Add(mPolarExport, 1, wxLEFT | wxRIGHT, 15);

	mPolarLegendExport = new wxButton(setupPanel, ID_POLARLEGEND_BUTTON, _("Polar / Legend"));
	imagesStaticBoxSizer->Add(mPolarLegendExport, 1, wxLEFT | wxRIGHT, 15);

	mLinearExport = new wxButton(setupPanel, ID_LINEAR_BUTTON, _("Linear"));
	imagesStaticBoxSizer->Add(mLinearExport, 1, wxLEFT | wxRIGHT, 15);

	mLinearLegendExport = new wxButton(setupPanel, ID_LINEARLEGEND_BUTTON, _("Linear / Legend"));
	imagesStaticBoxSizer->Add(mLinearLegendExport, 1, wxLEFT | wxRIGHT, 15);
}
// ----------------------------------------------------------------------------
PolarPlotWindow::~PolarPlotWindow(void)
{
}

void PolarPlotWindow::OnButtonPolar(wxCommandEvent& event)
{

}

void PolarPlotWindow::OnButtonPolarLegend(wxCommandEvent& event)
{

}
void PolarPlotWindow::OnButtonLinear(wxCommandEvent& event)
{

}

void PolarPlotWindow::OnButtonLinearLegend(wxCommandEvent& event)
{

}
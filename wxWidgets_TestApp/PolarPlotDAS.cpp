#include "stdafx.h"
#include "PolarPlotDAS.h"

PolarPlotDAS::PolarPlotDAS(wxWindow* parent,
	wxWindowID id,
	const wxString& title,
	std::vector<PolarPlotData> plotData,
	const wxPoint& pos,
	const wxSize& size,
	long style
)
	:wxDialog(parent, id, title, pos, size, style),
	mPlotData(plotData)
{
	PolarPlotDAS* panel = this;

	mPlotStyle = new wxPlotStyle();

	wxBoxSizer* topLevelSizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(topLevelSizer);

	wxBoxSizer* topHalfSizer = new wxBoxSizer(wxHORIZONTAL);
	topLevelSizer->Add(topHalfSizer, 1, wxGROW, 0);
	wxBoxSizer* bottomHalfSizer = new wxBoxSizer(wxHORIZONTAL);
	topLevelSizer->Add(bottomHalfSizer, 1, wxGROW, 0);

	// Left side --------------------------------------------------------------------------------------------------------

	wxBoxSizer* leftHandSide = new wxBoxSizer(wxVERTICAL);
	topHalfSizer->Add(leftHandSide, 0, wxGROW, 0);

	// Elevations Box -------------------------------------------
	wxArrayString elevations;
	for (size_t i = 0; i < mPlotData.size(); i++)
	{
		elevations.Add(_(mPlotData[i].Title()));
	}

	wxStaticBox* elevationsStaticBox = new wxStaticBox(panel, wxID_STATIC, _("Elevations"));
	wxStaticBoxSizer* elevationsStaticBoxSizer = new wxStaticBoxSizer(elevationsStaticBox, wxVERTICAL);
	wxBoxSizer* horizontalElevationsBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	mElevationsListBox = new wxListBox(panel, ID_ListBox_Elevations, wxDefaultPosition, wxDefaultSize, elevations, wxLB_SINGLE | wxLB_ALWAYS_SB);

	leftHandSide->Add(elevationsStaticBoxSizer, 1, wxGROW | wxALL, 5);
	//elevationsStaticBoxSizer->AddSpacer(10);
	elevationsStaticBoxSizer->Add(horizontalElevationsBoxSizer, 1, wxGROW | wxALL, 0);
	horizontalElevationsBoxSizer->Add(mElevationsListBox, 1, wxGROW | wxALL, 5);
	mElevationsListBox->SetMinSize(wxSize(200, 100));
	mElevationsListBox->Select(0);


	// Metrics Box ----------------------------------------------
	wxArrayString metrics;
	for (size_t i = 0; i < mPlotData[0].NumberOfPlots(); i++)
	{
		metrics.Add(mPlotData[0].PlotData()[i].Name);
	}

	wxStaticBox* metricsStaticBox = new wxStaticBox(panel, wxID_ANY, _("Metrics"));
	wxStaticBoxSizer* metricsBoxSizer = new wxStaticBoxSizer(metricsStaticBox, wxVERTICAL);
	wxBoxSizer* horizontalMetricsBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	mMetricsListBox = new wxCheckListBox(metricsStaticBox, ID_CheckListBox_Metrics, wxDefaultPosition, wxDefaultSize, metrics, wxLB_ALWAYS_SB);

	leftHandSide->Add(metricsBoxSizer, 1, wxGROW | wxALL, 5);
	metricsBoxSizer->Add(horizontalMetricsBoxSizer, 1, wxGROW | wxALL, 0);
	horizontalMetricsBoxSizer->Add(mMetricsListBox, 1, wxGROW | wxALL, 5);

	for (size_t i = 0; i < mMetricsListBox->GetCount(); i++)
	{
		mMetricsListBox->Check(i, true);
	}


	// Legend box -----------------------------------------------
	wxStaticBox* legendStaticBox = new wxStaticBox(panel, wxID_ANY, _("Legend"));
	wxStaticBoxSizer* legendStaticBoxSizer = new wxStaticBoxSizer(legendStaticBox, wxVERTICAL);
	leftHandSide->Add(legendStaticBoxSizer, 1, wxGROW | wxALL, 5);

	mPlotLegend = new wxPlotLegend(legendStaticBox, &mPlotData[0], mPlotStyle, ID_PlotLegend);
	legendStaticBoxSizer->Add(mPlotLegend, 1, wxALL | wxEXPAND, 0);

	// Right side --------------------------------------------------------------------------------------------------------

	wxBoxSizer* rightHandSide = new wxBoxSizer(wxHORIZONTAL);
	topHalfSizer->Add(rightHandSide, 2, wxGROW, 0);

	// Linear -------------------------------------------------------------------
	wxStaticBox* linearPlotStaticBox = new wxStaticBox(panel, wxID_ANY, _("Linear Plot"));
	wxStaticBoxSizer* linearPlotStaticBoxSizer = new wxStaticBoxSizer(linearPlotStaticBox, wxVERTICAL);
	wxBoxSizer* horizontalLinearPlotSizer = new wxBoxSizer(wxHORIZONTAL);
	bottomHalfSizer->Add(linearPlotStaticBoxSizer, 1, wxGROW | wxALIGN_TOP | wxALL, 5);
	linearPlotStaticBoxSizer->SetMinSize(wxSize(300, 300));
	linearPlotStaticBoxSizer->Add(horizontalLinearPlotSizer, 1, wxGROW | wxALL, 0);

	mLinearPlot = new wxPolarPlot(linearPlotStaticBox, &mPlotData[0], mPlotStyle, false, false, true, ID_LinearPlot,
		wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER);
	horizontalLinearPlotSizer->Add(mLinearPlot, 1, wxGROW | wxALIGN_TOP | wxALL, 0);

	// Radar -------------------------------------------------------------------
	wxStaticBox* polarPlotStaticBox = new wxStaticBox(panel, wxID_ANY, _("Radar Plot"));
	wxStaticBoxSizer* polarPlotStaticBoxSizer = new wxStaticBoxSizer(polarPlotStaticBox, wxVERTICAL);
	wxBoxSizer* horizontalPolarPlotSizer = new wxBoxSizer(wxHORIZONTAL);
	rightHandSide->Add(polarPlotStaticBoxSizer, 2, wxGROW | wxALIGN_TOP | wxALL, 5);
	polarPlotStaticBoxSizer->SetMinSize(wxSize(300, 300));
	polarPlotStaticBoxSizer->Add(horizontalPolarPlotSizer, 1, wxGROW | wxALL, 0);

	mPolarPlot = new wxPolarPlot(polarPlotStaticBox, &mPlotData[0], mPlotStyle, false, false, false, ID_PolarPlot,
		wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER);
	horizontalPolarPlotSizer->Add(mPolarPlot, 1, wxGROW | wxALIGN_TOP | wxALL, 0);

	

	Bind(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, &PolarPlotDAS::OnPlotLineToggle, this, ID_CheckListBox_Metrics);
	Bind(wxEVT_LISTBOX, &PolarPlotDAS::OnElevationSelected, this, ID_ListBox_Elevations);
}

PolarPlotDAS::~PolarPlotDAS(void)
{
}

void PolarPlotDAS::OnPlotLineToggle(wxCommandEvent& event)
{
	for (size_t i = 0; i < mPlotData.size(); i++)
	{
		mPlotData[i].PlotData()[event.GetInt()].IsVisible = mMetricsListBox->IsChecked(event.GetInt());
	}
	mPolarPlot->Refresh();
	mLinearPlot->Refresh();
}

void PolarPlotDAS::OnElevationSelected(wxCommandEvent& event)
{
	mPolarPlot->SetPlotData(&mPlotData[mElevationsListBox->GetSelection()]);
	mLinearPlot->SetPlotData(&mPlotData[mElevationsListBox->GetSelection()]);
}


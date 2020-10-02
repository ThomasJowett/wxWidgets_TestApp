#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "CartesianPlotData.h"
#include "DrawPanel.h"
#include "PlotViewDialog.h"

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(PlotViewDialog, wxDialog)
    //EVT_CLOSE(PreviewImageDialog::OnClose)			//	wxEVT_CLOSE wxEVT_CLOSE_WINDOW  -- ??
	//EVT_INIT_DIALOG(PreviewImageDialog::OnInitDialog)
	EVT_BUTTON( wxID_OK, PlotViewDialog::OnOkClick)
END_EVENT_TABLE()


// ----------------------------------------------------------------------------
PlotViewDialog::PlotViewDialog(wxWindow * parent, wxWindowID id,  const wxString & title, const wxPoint & pos, const wxSize & size, long style)
    : wxDialog( parent, id, title, pos, size, style)
{
	wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer *buttonSizer = new wxBoxSizer( wxHORIZONTAL );

	CartesianPlotData * graphData = new CartesianPlotData();
	//GraphDataInit(graphData);

	graphData->m_Title = "Cartesian Plots: 1 - 10";

	m_drawPanel = new DrawPanel(this, graphData, true, true,
								wxID_ANY, wxDefaultPosition, wxSize(800, 600), wxTAB_TRAVERSAL | wxNO_BORDER, title);

	wxButton * okButton = new wxButton(this, wxID_OK, "Ok", wxPoint(10, 10), wxDefaultSize);
	wxButton * cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(10, 10), wxDefaultSize);

	topSizer->Add(  m_drawPanel, 
					1,					// make vertically stretchable
					wxEXPAND |			// make horizontally stretchable
					wxALL,				// and make border all around
					10 );				// set border width to 10

	topSizer->Add( buttonSizer, 0,		// make vertically unstretchable
				   wxALIGN_CENTER );	// no border and centre horizontally

	buttonSizer->Add( okButton,
					  0,				// make horizontally unstretchable
					  wxALL,			// make border all around: implicit top alignment
					  10 );				// set border width to 10
	buttonSizer->Add( cancelButton,
					  0,				// make horizontally unstretchable
					  wxALL,			// make border all around: implicit top alignment
					  10 );				// set border width to 10

	SetSizer( topSizer );				// use the sizer for layout

	topSizer->Fit( this );				// fit the dialog to the contents
	topSizer->SetSizeHints( this );		// set hints to honor min size
}
// ----------------------------------------------------------------------------
PlotViewDialog::~PlotViewDialog(void)
{
}
// ----------------------------------------------------------------------------
void PlotViewDialog::OnOkClick( wxCommandEvent &event )
{
	event.Skip();
}
// ----------------------------------------------------------------------------
//void PlotViewDialog::GraphDataInit(KillZonesData * graphData)
//{
//}
// ----------------------------------------------------------------------------
//void PlotViewDialog::OnInitDialog( wxEVT_INIT_DIALOG &event )
//{
//}
// ----------------------------------------------------------------------------
//bool PlotViewDialog::TransferDataToWindow()
//{
//	//wxTextCtrl* nameCtrl = (wxTextCtrl*) FindWindow(ID_NAME);
//	//wxSpinCtrl* ageCtrl = (wxSpinCtrl*) FindWindow(ID_SAGE);
//	//wxChoice* sexCtrl = (wxChoice*) FindWindow(ID_SEX);
//	//wxCheckBox* voteCtrl = (wxCheckBox*) FindWindow(ID_VOTE);
//	//nameCtrl->SetValue(m_name);
//	//ageCtrl->SetValue(m_age);
//	//sexCtrl->SetSelection(m_sex);
//	//voteCtrl->SetValue(m_vote);
//
//	return true;
//}
//// ----------------------------------------------------------------------------
//bool PlotViewDialog::TransferDataFromWindow()
//{
//	//wxTextCtrl* nameCtrl = (wxTextCtrl*) FindWindow(ID_NAME);
//	//wxSpinCtrl* ageCtrl = (wxSpinCtrl*) FindWindow(ID_SAGE);
//	//wxChoice* sexCtrl = (wxChoice*) FindWindow(ID_SEX);
//	//wxCheckBox* voteCtrl = (wxCheckBox*) FindWindow(ID_VOTE);
//	//m_name = nameCtrl->GetValue();
//	//m_age = ageCtrl->GetValue();
//	//m_sex = sexCtrl->GetSelection();
//	//m_vote = voteCtrl->GetValue();
//
//	//return true;
//}
// ----------------------------------------------------------------------------
//void PlotViewDialog::OnClose( wxCloseEvent &event )
//{
//	// Handlers take a wxCloseEvent object and can veto the close by calling Veto on the object.
//
//	// As with wxFrame, do not use delete to destroy a dialog, but instead use
//	// Destroy or Close to delay deletion until all the object’s events have been processed. 
//	// When you call Close, the default wxEVT_CLOSE handler for this function usually calls Destroy.
//
//	//Show(false);
//}
// ----------------------------------------------------------------------------

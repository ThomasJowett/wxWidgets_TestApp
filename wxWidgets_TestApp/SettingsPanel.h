#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class SettingsPanel : public wxPanel
{
	enum
	{
		ID_PaneBorderSize = wxID_HIGHEST + 1,
		ID_SashSize,
		ID_CaptionSize,
		ID_BackgroundColor,
		ID_SashColor,
		ID_InactiveCaptionColor,
		ID_InactiveCaptionGradientColor,
		ID_InactiveCaptionTextColor,
		ID_ActiveCaptionColor,
		ID_ActiveCaptionGradientColor,
		ID_ActiveCaptionTextColor,
		ID_BorderColor,
		ID_GripperColor
	};

public:
	SettingsPanel(wxWindow* parent, )
};
///-----------------------------------------------------------------
///
/// @file      FrameFrm.cpp
/// @author    user
/// Created:   25/11/2013 17:16:01
/// @section   DESCRIPTION
///            FrameFrm class implementation
///
///------------------------------------------------------------------

#include "FrameFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// FrameFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(FrameFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(FrameFrm::OnClose)
END_EVENT_TABLE()
////Event Table End

FrameFrm::FrameFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

FrameFrm::~FrameFrm()
{
}

void FrameFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	SetTitle(_("Frame"));
	SetIcon(wxNullIcon);
	SetSize(8,8,389,279);
	Center();
	
	////GUI Items Creation End
}

void FrameFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

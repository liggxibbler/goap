///-----------------------------------------------------------------
///
/// @file      InterviewDlg.cpp
/// @author    user
/// Created:   25/11/2013 15:10:55
/// @section   DESCRIPTION
///            InterviewDlg class implementation
///
///------------------------------------------------------------------

#include "InterviewDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// InterviewDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(InterviewDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(InterviewDlg::OnClose)
END_EVENT_TABLE()
////Event Table End

InterviewDlg::InterviewDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

InterviewDlg::~InterviewDlg()
{
} 

void InterviewDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxButton5 = new wxButton(this, ID_WXBUTTON5, _("&Back"), wxPoint(24, 152), wxSize(169, 49), 0, wxDefaultValidator, _("WxButton5"));

	WxButton4 = new wxButton(this, ID_WXBUTTON4, _("&Accuse"), wxPoint(264, 152), wxSize(169, 49), 0, wxDefaultValidator, _("WxButton4"));
	WxButton4->Enable(false);

	WxStaticText6 = new wxStaticText(this, ID_WXSTATICTEXT6, _("at"), wxPoint(248, 104), wxDefaultSize, 0, _("WxStaticText6"));

	WxStaticText5 = new wxStaticText(this, ID_WXSTATICTEXT5, _("at"), wxPoint(248, 72), wxDefaultSize, 0, _("WxStaticText5"));

	WxStaticText4 = new wxStaticText(this, ID_WXSTATICTEXT4, _("at"), wxPoint(248, 40), wxDefaultSize, 0, _("WxStaticText4"));

	WxButton3 = new wxButton(this, ID_WXBUTTON3, _("Ask"), wxPoint(376, 104), wxSize(57, 25), 0, wxDefaultValidator, _("WxButton3"));

	WxButton2 = new wxButton(this, ID_WXBUTTON2, _("Ask"), wxPoint(376, 72), wxSize(57, 25), 0, wxDefaultValidator, _("WxButton2"));

	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("Ask"), wxPoint(376, 40), wxSize(57, 25), 0, wxDefaultValidator, _("WxButton1"));

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("Who had"), wxPoint(24, 104), wxDefaultSize, 0, _("WxStaticText3"));

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("Where was"), wxPoint(24, 72), wxDefaultSize, 0, _("WxStaticText2"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("What was/were"), wxPoint(24, 40), wxDefaultSize, 0, _("WxStaticText1"));

	wxArrayString arrayStringFor_WxComboBox9;
	WxComboBox9 = new wxComboBox(this, ID_WXCOMBOBOX9, _("WxComboBox7"), wxPoint(312, 104), wxSize(49, 23), arrayStringFor_WxComboBox9, 0, wxDefaultValidator, _("WxComboBox9"));

	wxArrayString arrayStringFor_WxComboBox8;
	WxComboBox8 = new wxComboBox(this, ID_WXCOMBOBOX8, _("WxComboBox7"), wxPoint(312, 72), wxSize(49, 23), arrayStringFor_WxComboBox8, 0, wxDefaultValidator, _("WxComboBox8"));

	wxArrayString arrayStringFor_WxComboBox6;
	WxComboBox6 = new wxComboBox(this, ID_WXCOMBOBOX6, _("WxComboBox7"), wxPoint(312, 40), wxSize(49, 23), arrayStringFor_WxComboBox6, 0, wxDefaultValidator, _("WxComboBox6"));

	wxArrayString arrayStringFor_WxComboBox5;
	WxComboBox5 = new wxComboBox(this, ID_WXCOMBOBOX5, _("WxComboBox7"), wxPoint(264, 104), wxSize(49, 23), arrayStringFor_WxComboBox5, 0, wxDefaultValidator, _("WxComboBox5"));

	wxArrayString arrayStringFor_WxComboBox4;
	WxComboBox4 = new wxComboBox(this, ID_WXCOMBOBOX4, _("WxComboBox7"), wxPoint(264, 72), wxSize(49, 23), arrayStringFor_WxComboBox4, 0, wxDefaultValidator, _("WxComboBox4"));

	wxArrayString arrayStringFor_WxComboBox3;
	WxComboBox3 = new wxComboBox(this, ID_WXCOMBOBOX3, _("WxComboBox7"), wxPoint(264, 40), wxSize(49, 23), arrayStringFor_WxComboBox3, 0, wxDefaultValidator, _("WxComboBox3"));

	wxArrayString arrayStringFor_WxComboBox2;
	WxComboBox2 = new wxComboBox(this, ID_WXCOMBOBOX2, _("WxComboBox7"), wxPoint(120, 104), wxSize(121, 23), arrayStringFor_WxComboBox2, 0, wxDefaultValidator, _("WxComboBox2"));

	wxArrayString arrayStringFor_WxComboBox1;
	WxComboBox1 = new wxComboBox(this, ID_WXCOMBOBOX1, _("WxComboBox7"), wxPoint(120, 72), wxSize(121, 23), arrayStringFor_WxComboBox1, 0, wxDefaultValidator, _("WxComboBox1"));

	wxArrayString arrayStringFor_WxComboBox7;
	WxComboBox7 = new wxComboBox(this, ID_WXCOMBOBOX7, _("WxComboBox7"), wxPoint(120, 40), wxSize(121, 23), arrayStringFor_WxComboBox7, 0, wxDefaultValidator, _("WxComboBox7"));

	WxStaticBox1 = new wxStaticBox(this, ID_WXSTATICBOX1, _("WxStaticBox1"), wxPoint(8, 8), wxSize(441, 217));

	SetTitle(_("Interview"));
	SetIcon(wxNullIcon);
	SetSize(8,8,473,270);
	Center();
	
	////GUI Items Creation End
}

void InterviewDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

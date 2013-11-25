///-----------------------------------------------------------------
///
/// @file      testDlg.cpp
/// @author    user
/// Created:   24/11/2013 17:47:12
/// @section   DESCRIPTION
///            testDlg class implementation
///
///------------------------------------------------------------------

#include "testDlg.h"

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// testDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(testDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(testDlg::OnClose)
	EVT_ACTIVATE(testDlg::testDlgActivate)
	EVT_BUTTON(ID_WXBUTTONRIGHT,testDlg::WxButtonRightClick)
	EVT_BUTTON(ID_WXBUTTONLEFT,testDlg::WxButtonLeftClick)
END_EVENT_TABLE()
////Event Table End

testDlg::testDlg(wxWindow *parent, testDlgApp* app, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style), myApp(app)
{
	CreateGUIControls();
}

testDlg::~testDlg()
{
} 

void testDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("Objects"), wxPoint(8, 8), wxDefaultSize, 0, _("WxStaticText3"));

	WxMemo1 = new wxTextCtrl(this, ID_WXMEMO1, wxEmptyString, wxPoint(304, 8), wxSize(225, 169), wxTE_MULTILINE, wxDefaultValidator, _("WxMemo1"));
	WxMemo1->SetMaxLength(0);
	WxMemo1->Enable(false);
	WxMemo1->AppendText(_("WxMemo1"));
	WxMemo1->SetFocus();
	WxMemo1->SetInsertionPointEnd();

	WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("Agents"), wxPoint(16, 152), wxDefaultSize, 0, _("WxStaticText2"));

	WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("Objects"), wxPoint(16, 120), wxDefaultSize, 0, _("WxStaticText1"));
    
    
    wxString* stuff;
    int size;
    if(myApp != 0)
    {
        if(myApp->m_room != 0)
        {
            size = myApp->m_room->m_objects.size();
        }
        else
        {
            MessageBox(NULL, L"room", L" ", MB_OK);
        }
    }
    else
    {
        MessageBox(NULL, L"myApp", L" ", MB_OK);
    }
    stuff = new wxString[size];
    std::list<Object*>::iterator iter = myApp->m_room->m_objects.begin();
    for(int i=0; i<size; ++i)
    {
        stuff[i] = (*iter)->m_name;
        ++iter;
    }
    
	wxArrayString arrayStringFor_ComboAgents(size, stuff);
	ComboAgents = new wxComboBox(this, ID_COMBOAGENTS, _("WxComboBox1"), wxPoint(152, 152), wxSize(137, 23), arrayStringFor_ComboAgents, 0, wxDefaultValidator, _("ComboAgents"));

	wxArrayString arrayStringFor_WxComboBox1;
	WxComboBox1 = new wxComboBox(this, ID_WXCOMBOBOX1, _("WxComboBox1"), wxPoint(152, 120), wxSize(137, 23), arrayStringFor_WxComboBox1, 0, wxDefaultValidator, _("WxComboBox1"));

	WxButtonRight = new wxButton(this, ID_WXBUTTONRIGHT, _("&Right"), wxPoint(153, 48), wxSize(140, 62), 0, wxDefaultValidator, _("WxButtonRight"));

	WxButtonLeft = new wxButton(this, ID_WXBUTTONLEFT, _("&Left"), wxPoint(9, 48), wxSize(132, 62), 0, wxDefaultValidator, _("WxButtonLeft"));

	SetTitle(_("test"));
	SetIcon(wxNullIcon);
	SetSize(8,8,553,227);
	Center();
	
	////GUI Items Creation End
}

void testDlg::OnClose(wxCloseEvent& e)
{
	Destroy();
}

/*
 * testDlgActivate
 */
void testDlg::testDlgActivate(wxActivateEvent& event)
{
	// insert your code here
}

/*
 * WxButtonLeftClick
 */
void testDlg::WxButtonLeftClick(wxCommandEvent& event)
{
	// insert your code here
	myApp->m_room = myApp->m_room->m_left;
	UpdateCombos();
}

/*
 * WxButtonRightClick
 */
void testDlg::WxButtonRightClick(wxCommandEvent& event)
{
	// insert your code here
	myApp->m_room = myApp->m_room->m_right;
	UpdateCombos();
}

void testDlg::UpdateCombos()
{
    wxString* stuff;
    int size = myApp->m_room->m_objects.size();
    stuff = new wxString[size];
    std::list<Object*>::iterator iter = myApp->m_room->m_objects.begin();
    for(int i=0; i<size; ++i)
    {
        stuff[i] = (*iter)->m_name;
        ++iter;
    }
    
	delete ComboAgents;
    wxArrayString arrayStringFor_ComboAgents(size, stuff);
	ComboAgents = new wxComboBox(this, ID_COMBOAGENTS, _("WxComboBox1"), wxPoint(152, 152), wxSize(137, 23), arrayStringFor_ComboAgents, 0, wxDefaultValidator, _("ComboAgents"));

//	wxArrayString arrayStringFor_WxComboBox1;
//	WxComboBox1 = new wxComboBox(this, ID_WXCOMBOBOX1, _("WxComboBox1"), wxPoint(152, 120), wxSize(137, 23), arrayStringFor_WxComboBox1, 0, wxDefaultValidator, _("WxComboBox1"));
}

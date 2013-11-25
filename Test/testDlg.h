///-----------------------------------------------------------------
///
/// @file      testDlg.h
/// @author    user
/// Created:   24/11/2013 17:47:12
/// @section   DESCRIPTION
///            testDlg class declaration
///
///------------------------------------------------------------------

#ifndef __TESTDLG_H__
#define __TESTDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/button.h>
////Header Include End

////Dialog Style Start
#undef testDlg_STYLE
#define testDlg_STYLE wxCAPTION | wxDIALOG_NO_PARENT | wxCLOSE_BOX
////Dialog Style End

#include "testApp.h"

class testDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		testDlg(wxWindow *parent, testDlgApp* app, wxWindowID id = 1, const wxString &title = wxT("test"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = testDlg_STYLE);
		virtual ~testDlg();
		void testDlgActivate(wxActivateEvent& event);
		void WxButtonLeftClick(wxCommandEvent& event);
		void SetApp(testDlgApp* app) {myApp = app;}
		void WxButtonRightClick(wxCommandEvent& event);
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxStaticText *WxStaticText3;
		wxTextCtrl *WxMemo1;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxComboBox *ComboAgents;
		wxComboBox *WxComboBox1;
		wxButton *WxButtonRight;
		wxButton *WxButtonLeft;
		////GUI Control Declaration End
		
		testDlgApp *myApp;
		
		void UpdateCombos();
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXSTATICTEXT3 = 1009,
			ID_WXMEMO1 = 1007,
			ID_WXSTATICTEXT2 = 1006,
			ID_WXSTATICTEXT1 = 1005,
			ID_COMBOAGENTS = 1004,
			ID_WXCOMBOBOX1 = 1003,
			ID_WXBUTTONRIGHT = 1002,
			ID_WXBUTTONLEFT = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

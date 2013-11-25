///-----------------------------------------------------------------
///
/// @file      InterviewDlg.h
/// @author    user
/// Created:   25/11/2013 15:10:55
/// @section   DESCRIPTION
///            InterviewDlg class declaration
///
///------------------------------------------------------------------

#ifndef __INTERVIEWDLG_H__
#define __INTERVIEWDLG_H__

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
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/statbox.h>
////Header Include End

////Dialog Style Start
#undef InterviewDlg_STYLE
#define InterviewDlg_STYLE wxCAPTION | wxDIALOG_NO_PARENT | wxCLOSE_BOX
////Dialog Style End

class InterviewDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		InterviewDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Interview"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = InterviewDlg_STYLE);
		virtual ~InterviewDlg();
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *WxButton5;
		wxButton *WxButton4;
		wxStaticText *WxStaticText6;
		wxStaticText *WxStaticText5;
		wxStaticText *WxStaticText4;
		wxButton *WxButton3;
		wxButton *WxButton2;
		wxButton *WxButton1;
		wxStaticText *WxStaticText3;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxComboBox *WxComboBox9;
		wxComboBox *WxComboBox8;
		wxComboBox *WxComboBox6;
		wxComboBox *WxComboBox5;
		wxComboBox *WxComboBox4;
		wxComboBox *WxComboBox3;
		wxComboBox *WxComboBox2;
		wxComboBox *WxComboBox1;
		wxComboBox *WxComboBox7;
		wxStaticBox *WxStaticBox1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBUTTON5 = 1031,
			ID_WXBUTTON4 = 1030,
			ID_WXSTATICTEXT6 = 1029,
			ID_WXSTATICTEXT5 = 1028,
			ID_WXSTATICTEXT4 = 1027,
			ID_WXBUTTON3 = 1026,
			ID_WXBUTTON2 = 1025,
			ID_WXBUTTON1 = 1024,
			ID_WXSTATICTEXT3 = 1023,
			ID_WXSTATICTEXT2 = 1022,
			ID_WXSTATICTEXT1 = 1021,
			ID_WXCOMBOBOX9 = 1020,
			ID_WXCOMBOBOX8 = 1019,
			ID_WXCOMBOBOX6 = 1018,
			ID_WXCOMBOBOX5 = 1017,
			ID_WXCOMBOBOX4 = 1016,
			ID_WXCOMBOBOX3 = 1015,
			ID_WXCOMBOBOX2 = 1014,
			ID_WXCOMBOBOX1 = 1013,
			ID_WXCOMBOBOX7 = 1012,
			ID_WXSTATICBOX1 = 1011,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif

//---------------------------------------------------------------------------
//
// Name:        FrameApp.h
// Author:      user
// Created:     25/11/2013 17:16:01
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __FRAMEFRMApp_h__
#define __FRAMEFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class FrameFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif

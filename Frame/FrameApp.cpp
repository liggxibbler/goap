//---------------------------------------------------------------------------
//
// Name:        FrameApp.cpp
// Author:      user
// Created:     25/11/2013 17:16:01
// Description: 
//
//---------------------------------------------------------------------------

#include "FrameApp.h"
#include "FrameFrm.h"

IMPLEMENT_APP(FrameFrmApp)

bool FrameFrmApp::OnInit()
{
    FrameFrm* frame = new FrameFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int FrameFrmApp::OnExit()
{
	return 0;
}

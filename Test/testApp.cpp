//---------------------------------------------------------------------------
//
// Name:        testApp.cpp
// Author:      user
// Created:     24/11/2013 17:47:12
// Description: 
//
//---------------------------------------------------------------------------

#include "testApp.h"
#include "testDlg.h"
#include "InterviewDlg.h"

IMPLEMENT_APP(testDlgApp)

bool testDlgApp::OnInit()
{
    Object *knife, *rope, *table, *statue, *lamp;
    Room *kitchen, *living, *dining;
    
    m_world = new World("world");
    kitchen = m_world->AddRoom("Kitchen");
    living = m_world->AddRoom("Living Room");
    dining = m_world->AddRoom("Dining Room");
    
    kitchen->m_left = living;
    living->m_right = kitchen;
    
    living->m_left = dining;
    dining->m_right = living;
    
    dining->m_left = kitchen;
    kitchen->m_right = dining;
    
    knife = kitchen->AddObject("Knife");
    rope = kitchen->AddObject("Rope");
    table = dining->AddObject("Table");
    statue = living->AddObject("Statue");
    lamp = living->AddObject("Lamp");
    
    m_room = living;

	testDlg* dialog = new testDlg(NULL, this);
	SetTopWindow(dialog);
    //dialog->SetApp(this);
    dialog->Show(true);
    
   	InterviewDlg* iDialog = new InterviewDlg(NULL);
//	SetTopWindow(dialog);
	iDialog->Show(false);	
    
	return true;
}
 
int testDlgApp::OnExit()
{
	return 0;
}

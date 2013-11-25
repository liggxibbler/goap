//---------------------------------------------------------------------------
//
// Name:        testApp.h
// Author:      user
// Created:     24/11/2013 17:47:12
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __TESTDLGApp_h__
#define __TESTDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

#include <iostream>
#include <list>
#include <string>

using namespace std;

class Object
{
public:
    Object(string name) : m_name(name) {}
    string m_name;
};

class Room
{
public:
    Room(string name) : m_name(name) {}
    list<Object*> m_objects;
    string m_name;
    Object* AddObject(string name)
    {
        Object* obj = new Object(name);
        m_objects.push_back(obj);
        return obj;
    }
    
    Room* m_left;
    Room* m_right;
    
};

class World
{
public:
    World(string name) : m_name(name) {}
    list<Room*> m_rooms;
    string m_name;
    Room* AddRoom(string name)
    {
        Room* room = new Room(name);
        m_rooms.push_back(room);
        return room;
    }
};

class testDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
	    World* m_world;
	    Room* m_room;
};

#endif

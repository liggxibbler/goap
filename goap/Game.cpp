#include "Game.h"

#include "Object.h"
#include "Agent.h"
#include "Room.h"
#include "World.h"
#include "Blade.h"

#include <iostream>
using namespace std;

using namespace GOAP;

Game::Game() : m_roam(true), m_running(true)
{
}

Game::Game(const Game& other)
{
}

Game::~Game()
{
}

void Game::Initialize()
{
	m_world = new World();

	Room *kitchen, *living, *dining;
	
	Blade *knife;
	Object *rope, *table, *statue, *lamp;

	kitchen = m_world->AddRoom("Kitchen");
	living = m_world->AddRoom("Living Room");
	dining = m_world->AddRoom("Dining Room");

	knife = new Blade("Knife");
	kitchen->AddObject(knife);

	rope = kitchen->AddObject("Rope");

	statue = living->AddObject("Statue");
	lamp = living->AddObject("Lamp");

	table = dining->AddObject("Table");

	//Blade* obj = new Blade("Knife");

	knife->SetAttrib(ATTRIB_TYPE_POSX, 4);
	knife->SetAttrib(ATTRIB_TYPE_POSY, 2);
	/*obj->SetAttrib(ATTRIB_TYPE_HEIGHT, 10);
	obj->SetAttrib(ATTRIB_TYPE_WEIGHT, 20);
	obj->SetAttrib(ATTRIB_TYPE_ALIVE, true);*/

	/*cout << "obj has:" << endl;
	cout << "X: " << obj->GetAttrib(ATTRIB_TYPE_POSX) << endl;
	cout << "Y: " << obj->GetAttrib(ATTRIB_TYPE_POSY) << endl;*/

	GOAP::Agent* al = new GOAP::Agent("Alborz");
	(*al)[ATTRIB_TYPE_POSX] = 3;
	(*al)[ATTRIB_TYPE_POSY] = 1;
	(*al)[ATTRIB_TYPE_HEIGHT] = 30;
	(*al)[ATTRIB_TYPE_WEIGHT] = 20;
	(*al)[ATTRIB_TYPE_ALIVE] = true;

	GOAP::Agent* dysh = new GOAP::Agent("Dysh");
	(*dysh)[ATTRIB_TYPE_POSX] = 5;
	(*dysh)[ATTRIB_TYPE_POSY] = 1;
	(*dysh)[ATTRIB_TYPE_HEIGHT] = 30;
	(*dysh)[ATTRIB_TYPE_WEIGHT] = 20;
	(*dysh)[ATTRIB_TYPE_ALIVE] = true;

	kitchen->AddAgent(al);
	living->AddAgent(dysh);

	m_currentRoom = kitchen;
}

void Game::Roam()
{
	m_vecAgent.clear();
	m_vecObject.clear();
	m_vecRoom.clear();

	cout << "========================\n\n";
	cout << "You are in the " << m_currentRoom->GetName() << "!\n";
	cout << "You can see(examine):\n";
	int item = 1;
	for(auto iter(m_currentRoom->GetFirstObject()); iter != m_currentRoom->GetLastObject(); ++iter)
	{
		cout << item++ << ") " << (*iter)->GetName() << endl;
		m_vecObject.push_back(*iter);
	}
	
	int witness = item;
	cout << "\nYou can interview:\n";
	for(auto iter(m_currentRoom->GetFirstAgent()); iter != m_currentRoom->GetLastAgent(); ++iter)
	{
		cout << item++ << ") " << (*iter)->GetName() << endl;
		m_vecAgent.push_back(*iter);
	}

	int iRoom = item;
	cout << "\nYou can go to:\n";
	for(auto iter(m_world->GetFirstRoom()); iter != m_world->GetLastRoom(); ++iter)
	{
		cout << item++ << ") " << (*iter)->GetName() << endl;
		m_vecRoom.push_back(*iter);
	}
	
	cout << "\n Or enter 0 to quit.\n";

	cout << "\nWhat would you like to do? ";
	int answer;
	cin >> answer;

	if (answer == 0)
	{
		m_running = false;
	}

	if(answer < witness)// examine
	{
		//examine(answer);
	}
	else if(answer>=witness && answer <iRoom)//agent
	{
		m_currentAgent = m_vecAgent[answer - witness];
		m_roam = false;
	}
	else if(answer>=iRoom && answer < item)//change room
	{
		m_currentRoom = m_vecRoom[answer - iRoom];
	}
	else
	{
		// bad answer, do over
	}

}

void Game::Interview()
{
	cout << "========================\n\n";
	cout << "You are interviewing " << m_currentAgent->GetName() << ":\n";
	cout << "What/who would you like to ask about :\n";
	int item = 1;
	for(auto room(m_world->GetFirstRoom()); room != m_world->GetLastRoom(); ++room)
	{
		/*list objects*/
		for(auto object((*room)->GetFirstObject());object != (*room)->GetLastObject(); ++object)
		{
			cout << item++ << ") " << (*object)->GetName() << endl;
		}
	}

	int iAgent = item;
	for(auto room(m_world->GetFirstRoom()); room != m_world->GetLastRoom(); ++room)
	{
		/*list agents*/
		for(auto agent((*room)->GetFirstAgent());agent != (*room)->GetLastAgent(); ++agent)
		{
			cout << item++ << ") " << (*agent)->GetName() << endl;
		}
	}

	/*accuse if available*/

	/*go back (m_currentAgent = 0)*/
	cout << "\nEnter 0 to go back to roam" << endl;
	
	int answer;
	cin >> answer;

	if(answer == 0)
	{
		m_roam = true;
		m_currentAgent = 0;
		return;
	}	

	cout << "You can ask about\n";
	cout << "1) Position\n";
	cout << "2) \n";
	

	/*	
		position
	if choice is agent:
		action
	else choice is object:
		possession
	*/

	/*what time (military)?*/
}

bool Game::Run(/*database class thing*/)
{
	while(m_running)
	{
		if(m_roam)
		{
			Roam();
		}
		else
		{
			Interview();
		}
	}
	return true;
}
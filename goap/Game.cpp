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
	dining = m_world->AddRoom("Dining");

	knife = new Blade("Knife");
	kitchen->AddObject(knife);

	rope = kitchen->AddObject("Rope");

	statue = living->AddObject("Statue");
	lamp = living->AddObject("Lamp");

	table = dining->AddObject("Table");

	m_currentRoom = kitchen;
}

void Game::Roam()
{
	cout << "You are in the " << m_currentRoom->GetName() << "!\n";
	cout << "You can see(examine):\n";
	int item = 1;
	for(auto iter(m_currentRoom->GetFirstObject()); iter != m_currentRoom->GetLastObject(); ++iter)
	{
		cout << item++ << ") " << (*iter)->GetName() << endl;
	}
	cout << "\nYou can interview:\n";
	for(auto iter(m_currentRoom->GetFirstAgent()); iter != m_currentRoom->GetLastAgent(); ++iter)
	{
		cout << item++ << ") " << (*iter)->GetName() << endl;
	}
	cout << "\nYou can go to:\n";
	for(auto iter(m_world->GetFirstRoom()); iter != m_world->GetLastRoom(); ++iter)
	{
		cout << item++ << ") " << (*iter)->GetName() << endl;
	}
	
	cout << "\n Or enter 0 to quit.\n";

	cout << "\nWhat would you like to do? ";
	int answer;
	cin >> answer;

	/*switch(answer)
	{		
	}*/

	if (answer == 0)
	{
		m_running = false;
	}

}

void Game::Interview()
{
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
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
	
	kitchen = m_world->AddRoom("Kitchen", ROOM_KITCHEN);
	living = m_world->AddRoom("Living Room", ROOM_LIVING_ROOM);
	dining = m_world->AddRoom("Dining Room", ROOM_DINING_ROOM);

	InitializeAgents();
	InitializeObjects();

	m_currentRoom = kitchen;
}

void Game::Roam()
{
	m_vecAgent.clear();
	m_vecObject.clear();
	m_vecRoom.clear();

	cout << "========================\n\n";
	cout << "You are in the " << m_currentRoom->GetName() << "\n\n";
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

	cout << "\nWhat would you like to do?\n>>>";
	int answer;
	cin >> answer;

	if (answer == 0)
	{
		m_running = false;
	}

	if(answer < witness)// examine
	{
		//examine(answer-1);
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
	m_vecObject.clear();
	m_vecAgent.clear();

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
			m_vecObject.push_back(*object);
		}
	}

	int iAgent = item;
	for(auto room(m_world->GetFirstRoom()); room != m_world->GetLastRoom(); ++room)
	{
		/*list agents*/
		for(auto agent((*room)->GetFirstAgent());agent != (*room)->GetLastAgent(); ++agent)
		{
			cout << item++ << ") " << (*agent)->GetName() << endl;
			m_vecAgent.push_back(*agent);
		}
	}

	int accuse = item;
	/*accuse if available*/

	/*go back (m_currentAgent = 0)*/
	cout << "\nEnter 0 to go back to roam\n>>>";;
	
	int answer;
	cin >> answer;

	if(answer == 0)
	{
		m_roam = true;
		m_currentAgent = 0;
		return;
	}	

	std::string wasChar, choiceTwo;
	QuestionType qt2;
	Object* qObject = 0;

	if(answer < iAgent)
		// object
	{
		wasChar = "it was";
		choiceTwo = "Who had it";
		qt2 = Q_POSSESSION;
		qObject = m_vecAgent[answer - 1];
	}
	else
		// agent
	{
		wasChar = "they were";
		choiceTwo = "What they were doing";
		qt2 = Q_ACTION;
		qObject = m_vecAgent[answer - iAgent];
	}

	cout << "\nYou can ask about\n";
	cout << "1) Where " <<  wasChar << "\n";
	cout << "2) " << choiceTwo << "\n";
	
	cout << ">>>";
	cin >> answer;

	QuestionType question;

	if(answer == 1)
	{
		question = Q_POSITION;
	}
	else
	{
		question = qt2;
	}

	cout << "\nWhat time?\n>>> ";
	cin >> answer;

	// time = military2time(answer)
	// Ask(m_currentAgent, qObject, question, time);
}

bool Game::Run(/*database class thing*/)
{
	AssignRoles();
	PopulateRooms();
	GeneratePlot();
	
	MainLoop();
	
	return true;
}

void Game::GeneratePlot()
{
	while(!m_murder)
	{
		for(auto room(m_world->GetFirstRoom()); room != m_world->GetLastRoom(); ++room)
		{
			for(auto object((*room)->GetFirstObject()); object != (*room)->GetLastObject(); ++object)
			{
				(*object)->Update();
			}
			for(auto agent((*room)->GetFirstAgent()); agent != (*room)->GetLastAgent(); ++agent)
			{
				(*agent)->Update();
			}
		}
	}
}

void Game::MainLoop()
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
}

void Game::AssignRoles(/*int numWitness*/)
{
	// from agent bank
	// pick a random agent
	// mark as murderer
	// pick a random agent that's not the murderer
	// mark as victim
	// set 'murderer.goal' to be 'victim.isAlive == false'
	// pick (numWitness + 1) agents
	// set as witness(es)
	
	Agent* murderer = m_agents[0];
	Agent* victim = m_agents[1];
	
	GOAP::Condition cond(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_EQUAL);
	cond[0].attrib = ATTRIB_TYPE_ALIVE;
	cond[0].instance = victim;
	cond[0].type = OBJ_TYPE_AGENT;
	cond[0].value = false;

	Goal* goal = new Goal;
	goal->AddCondition(cond);
	murderer->SetGoal(goal);

	murderer->See(victim);
	
	m_actors.push_back(murderer);
	m_actors.push_back(victim);
	m_actors.push_back(m_agents[2]);

	auto room(m_world->GetFirstRoom());
	++room;
	(*room)->AddAgent(murderer);
	(*room)->AddAgent(victim);
	(*room)->AddAgent(m_agents[2]);
}

void Game::PopulateRooms()
{
	/* for each room in world
		from object bank[room]
			pick an object that can be used as a murder weapon
			i.e. that is the instrument in an action with an effect OAV[O.isAlive == false]
			pick 2-4 other objects from that room
	*/
	// kitchen, living, dining

	auto room = m_world->GetFirstRoom(); //kitchen
	(*room)->AddObject(m_objects[1]);
	(*room)->AddObject(m_objects[2]);
	(*room)->AddObject(m_objects[3]);
	++room;

	(*room)->AddObject(m_objects[0]);//living
	(*room)->AddObject(m_objects[4]);
	++room;

	(*room)->AddObject(m_objects[5]);//dining
	(*room)->AddObject(m_objects[6]);	
}

void Game::InitializeAgents()
{
	m_agents.clear();

	m_agents.push_back(new GOAP::Agent("Alborz"));
	(*m_agents[0])[ATTRIB_TYPE_POSX] = 3;
	(*m_agents[0])[ATTRIB_TYPE_POSY] = 1;
	(*m_agents[0])[ATTRIB_TYPE_HEIGHT] = 30;
	(*m_agents[0])[ATTRIB_TYPE_WEIGHT] = 20;
	(*m_agents[0])[ATTRIB_TYPE_ALIVE] = true;

	m_agents.push_back(new GOAP::Agent("Dysh"));
	(*m_agents[1])[ATTRIB_TYPE_POSX] = 5;
	(*m_agents[1])[ATTRIB_TYPE_POSY] = 1;
	(*m_agents[1])[ATTRIB_TYPE_HEIGHT] = 30;
	(*m_agents[1])[ATTRIB_TYPE_WEIGHT] = 20;
	(*m_agents[1])[ATTRIB_TYPE_ALIVE] = true;

	m_agents.push_back(new GOAP::Agent("Jim"));
	(*m_agents[2])[ATTRIB_TYPE_POSX] = 5;
	(*m_agents[2])[ATTRIB_TYPE_POSY] = 1;
	(*m_agents[2])[ATTRIB_TYPE_HEIGHT] = 30;
	(*m_agents[2])[ATTRIB_TYPE_WEIGHT] = 20;
	(*m_agents[2])[ATTRIB_TYPE_ALIVE] = true;

	m_agents.push_back(new GOAP::Agent("Joe"));
	(*m_agents[3])[ATTRIB_TYPE_POSX] = 5;
	(*m_agents[3])[ATTRIB_TYPE_POSY] = 1;
	(*m_agents[3])[ATTRIB_TYPE_HEIGHT] = 30;
	(*m_agents[3])[ATTRIB_TYPE_WEIGHT] = 20;
	(*m_agents[3])[ATTRIB_TYPE_ALIVE] = true;

	m_agents.push_back(new GOAP::Agent("Bob"));
	(*m_agents[4])[ATTRIB_TYPE_POSX] = 5;
	(*m_agents[4])[ATTRIB_TYPE_POSY] = 1;
	(*m_agents[4])[ATTRIB_TYPE_HEIGHT] = 30;
	(*m_agents[4])[ATTRIB_TYPE_WEIGHT] = 20;
	(*m_agents[4])[ATTRIB_TYPE_ALIVE] = true;
}

void Game::InitializeObjects()
{
	/*
	clock
	scissors
	mirror
	bottle
	kettle
	toaster
	fork
	chemicals
	cups
	drinks
	foods
	*/

	m_objects.clear();
	Object* obj = 0;

	obj = new Object("Clock");
	obj->MayBeFoundIn(ROOM_BATHROOM | ROOM_BEDROOM | ROOM_LIVING_ROOM | ROOM_DINING_ROOM);
	m_objects.push_back(obj);

	obj = new Object("Cup");
	obj->MayBeFoundIn(ROOM_KITCHEN | ROOM_DINING_ROOM);
	m_objects.push_back(obj);

	obj = new Blade("Knife");
	obj->MayBeFoundIn(ROOM_KITCHEN | ROOM_DINING_ROOM);
	m_objects.push_back(obj);
	
	obj = new Object("Rope");
	obj->MayBeFoundIn(ROOM_KITCHEN);
	m_objects.push_back(obj);
	
	obj = new Object("Statue");
	obj->MayBeFoundIn(ROOM_LIVING_ROOM | ROOM_BEDROOM);
	m_objects.push_back(obj);

	obj = new Object("Lamp");
	obj->MayBeFoundIn(ROOM_BATHROOM | ROOM_BEDROOM | ROOM_LIVING_ROOM | ROOM_DINING_ROOM);
	m_objects.push_back(obj);

	obj = new Object("Table");
	obj->MayBeFoundIn(ROOM_KITCHEN | ROOM_DINING_ROOM | ROOM_LIVING_ROOM);
	m_objects.push_back(obj);
}
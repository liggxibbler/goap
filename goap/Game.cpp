#include "Game.h"

#include "Object.h"
#include "Agent.h"
#include "Room.h"
#include "Blade.h"
#include "Blunt.h"
#include "Squeezer.h"
#include "Projectile.h"
#include "OperatorManager.h"

#include <iostream>
using namespace std;

using namespace GOAP;

Game::Game() : m_roam(true), m_running(true), m_turn(0)
{
	m_roomManager = 0;
}

Game::Game(const Game& other)
{
}

Game::~Game()
{
}

void Game::Initialize()
{
	m_roomManager = RoomManager::Instance();

	InitializeAgents();
	InitializeObjects();
	m_roomManager->Initialize(m_agents.begin(), m_agents.end());

	m_currentRoom = m_roomManager->GetRoom(ROOM_KITCHEN);
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
	if(m_currentRoom->GetFirstAgent() == m_currentRoom->GetLastAgent())
	{
		cout << "\n[NOBODY]\n";
	}
	else
	{
		for(auto iter(m_currentRoom->GetFirstAgent()); iter != m_currentRoom->GetLastAgent(); ++iter)
		{
			cout << item++ << ") " << (*iter)->GetName();
			if((*iter)->GetAttrib(ATTRIB_TYPE_ALIVE) == false)
			{
				cout << " [DEAD]";
			}
			cout << endl;
			m_vecAgent.push_back(*iter);
		}
	}

	int iRoom = item;
	cout << "\nYou can go to:\n";
	for(auto iter(m_roomManager->GetFirstRoom()); iter != m_roomManager->GetLastRoom(); ++iter)
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
	//m_vecObject.clear();
	//m_vecAgent.clear();

	//cout << "========================\n\n";
	//cout << "You are interviewing " << m_currentAgent->GetName() << ":\n";
	//cout << "What/who would you like to ask about :\n";
	//
	//int item = 1;
	//for(auto room(m_world->GetFirstRoom()); room != m_world->GetLastRoom(); ++room)
	//{
	//	/*list objects*/
	//	for(auto object((*room)->GetFirstObject());object != (*room)->GetLastObject(); ++object)
	//	{
	//		cout << item++ << ") " << (*object)->GetName() << endl;
	//		m_vecObject.push_back(*object);
	//	}
	//}

	//int iAgent = item;
	//for(auto room(m_world->GetFirstRoom()); room != m_world->GetLastRoom(); ++room)
	//{
	//	/*list agents*/
	//	for(auto agent((*room)->GetFirstAgent());agent != (*room)->GetLastAgent(); ++agent)
	//	{
	//		cout << item++ << ") " << (*agent)->GetName() << endl;
	//		m_vecAgent.push_back(*agent);
	//	}
	//}

	//int accuse = item;
	///*accuse if available*/

	///*go back (m_currentAgent = 0)*/
	//cout << "\nEnter 0 to go back to roam\n>>>";;
	//
	//int answer;
	//cin >> answer;

	//if(answer == 0)
	//{
	//	m_roam = true;
	//	m_currentAgent = 0;
	//	return;
	//}	

	//std::string wasChar, choiceTwo;
	//QuestionType qt2;
	//Object* qObject = 0;

	//if(answer < iAgent)
	//	// object
	//{
	//	wasChar = "it was";
	//	choiceTwo = "Who had it";
	//	qt2 = Q_POSSESSION;
	//	qObject = m_vecAgent[answer - 1];
	//}
	//else
	//	// agent
	//{
	//	wasChar = "they were";
	//	choiceTwo = "What they were doing";
	//	qt2 = Q_ACTION;
	//	qObject = m_vecAgent[answer - iAgent];
	//}

	//cout << "\nYou can ask about\n";
	//cout << "1) Where " <<  wasChar << "\n";
	//cout << "2) " << choiceTwo << "\n";
	//
	//cout << ">>>";
	//cin >> answer;

	//QuestionType question;

	//if(answer == 1)
	//{
	//	question = Q_POSITION;
	//}
	//else
	//{
	//	question = qt2;
	//}

	int time;
	cout << "\nWhat time?\n>>> ";
	cin >> time;

	if( time == 0 )
	{
		m_roam = true;
		m_currentAgent = 0;
		return;
	}

	//m_currentAgent->Answer(qObject, question, answer);
	m_currentAgent->Answer(0, Q_ACTION, time);
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
	m_murder = false;

	while(!m_murder)
	{
		for(auto room(m_roomManager->GetFirstRoom()); room != m_roomManager->GetLastRoom(); ++room)
		{
			m_murder = (*room)->Update(Op::OperatorManager::Instance(), m_roomManager, m_turn);
			if(m_murder)
			{
				break;
			}
		}

		for(auto room(m_roomManager->GetFirstRoom()); room != m_roomManager->GetLastRoom(); ++room)
		{
			(*room)->UpdateAgentPositions();
		}


		// this deletion block copied from stackoverflow.com
	
		DUMP("******************************")
		DUMP("Turn " << m_turn << " is over.")
		DUMP("******************************")

#ifdef _DEBUG
		std::cin.get();
#endif
		++m_turn;
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

	Room* room = m_roomManager->GetRoom(ROOM_KITCHEN); //kitchen
	room->AddObject(m_objects[1]);
	room->AddObject(m_objects[2]);
	room->AddObject(m_objects[3]);
	
	room = m_roomManager->GetRoom(ROOM_LIVING_ROOM);
	room->AddObject(m_objects[0]);//living
	room->AddObject(m_objects[4]);
	room->AddObject(m_objects[7]);

	room = m_roomManager->GetRoom(ROOM_DINING_ROOM);
	room->AddObject(m_objects[5]);//dining
	room->AddObject(m_objects[6]);	

	m_roomManager->GetRandomRoom(m_agents[0])->AddAgent(m_agents[0]);
	m_roomManager->GetRandomRoom(m_agents[1])->AddAgent(m_agents[1]);
	m_roomManager->GetRandomRoom(m_agents[2])->AddAgent(m_agents[2]);
}

//hard-coding the characters by passing the variables to agent's initializer method
void Game::InitializeAgents()
{
	unsigned int NUMBER_OF_CHARACTERS = 3;
	int MURDERER_ID = 0;

	m_agents.clear();

	for (unsigned int i = 0 ; i < NUMBER_OF_CHARACTERS ; ++i)
		m_agents.push_back(new GOAP::Agent());
	

	//0. Comrade Tartar
	int locationProbability1[] = {0, 5, 50, 5, 40};
	m_agents[0]->InitializeCharacter(m_roomManager, "Comrade Tartar", MALE
	, "A Russia circus acrobat defected to England. A muscled and strong man that claims he has captured all the circus's bears barehanded"
	, locationProbability1, true, true, false, true, 9, 10);

	//1. Colonel Worcestershire
	int locationProbability2[] = {0, 60, 5, 5, 30};
	m_agents[1]->InitializeCharacter(m_roomManager, "Colonel Worcestershire", MALE
	, "An old British military man. Though respected and feared by his men, old age has left visible marks on his body."
	, locationProbability2, true, false, true, false, 8, 8);

	//2. Don Gravy
	int locationProbability3[] = {0, 30, 30, 5, 35};
	m_agents[2]->InitializeCharacter(m_roomManager, "Don Gravy", MALE
	, "An American mobster on a business trip in England. Famous for never missing a shot or a meal."
	, locationProbability3, true, true, true, true, 6, 9);

	////3. Mademoiselle Velouté
	//int locationProbability4[] = {0, 30, 30, 10, 30};
	//m_agents[3]->InitializeCharacter(m_roomManager, "Mademoiselle Velouté", FEMALE
	//, "A French super model on holidays."
	//, locationProbability4, true, true, true, false, 6, 4);

	////4. Madame Béchamel
	//int locationProbability5[] = {0, 15, 20, 5, 60};
	//m_agents[4]->InitializeCharacter(m_roomManager, "Madame Béchamel", FEMALE
	//, "A middle-aged French woman. Poor soul was widowed five times and every time only a week after her wedding."
	//, locationProbability5, true, true, false, false, 5, 6);

	////5. Mrs.Hollandaise
	//int locationProbability6[] = {30, 5, 30, 5, 30};
	//m_agents[5]->InitializeCharacter(m_roomManager, "Mrs. Hollandaise", FEMALE
	//, "The maid."
	//, locationProbability6, true, true, false, true, 5, 5);

	////6. Mr.Hollandaise
	//int locationProbability7[] = {30, 5, 50, 5, 10};
	//m_agents[6]->InitializeCharacter(m_roomManager, "Mr.Hollandaise", MALE
	//, "The butler. A Dutch and French descendant butler and maid husband and wife"
	//, locationProbability7, true, true, false, true, 7, 6);

	////7. Herr Duckefett
	//int locationProbability8[] = {0, 5, 50, 5, 40};
	//m_agents[7]->InitializeCharacter(m_roomManager, "Herr Duckefett", MALE
	//, "A German explorer. HAs a strange taste when it comes to women"
	//, locationProbability8, true, true, true, true, 8, 7);

	////8. prof.Custard
	//int locationProbability9[] = {0, 35, 50, 5, 10};
	//m_agents[8]->InitializeCharacter(m_roomManager, "prof.Custard", MALE
	//, "British renowned "
	//, locationProbability9, true, true, true, true, 8, 7);

	////9. Signor Bolognese
	//int locationProbability10[] = {0, 50, 5, 5, 40};
	//m_agents[9]->InitializeCharacter(m_roomManager, "Signor Bolognese", MALE
	//, "Italian, sleezy, barber, slim, fast, cheap"
	//, locationProbability10, true, true, true, true, 8, 7);


	//probably just tag murderer here and move these to the agents class:
	//m_agents[MURDERER_ID]->AddAction(ACTION_GOTO);
	m_agents[MURDERER_ID]->AddAction(ACTION_TAKE);
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
	
	obj = new Squeezer("Rope");
	obj->MayBeFoundIn(ROOM_KITCHEN);
	m_objects.push_back(obj);
	
	obj = new Blunt("Statue");
	obj->MayBeFoundIn(ROOM_LIVING_ROOM | ROOM_BEDROOM);
	m_objects.push_back(obj);

	obj = new Object("Lamp");
	obj->MayBeFoundIn(ROOM_BATHROOM | ROOM_BEDROOM | ROOM_LIVING_ROOM | ROOM_DINING_ROOM);
	m_objects.push_back(obj);

	obj = new Object("Table");
	obj->MayBeFoundIn(ROOM_KITCHEN | ROOM_DINING_ROOM | ROOM_LIVING_ROOM);
	m_objects.push_back(obj);

	obj = new Projectile("Gun");
	obj->MayBeFoundIn(ROOM_BEDROOM);
	m_objects.push_back(obj);
}
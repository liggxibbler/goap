#include "Game.h"

#include "Prop.h"
#include "Agent.h"
#include "Room.h"
#include "Blade.h"
#include "Blunt.h"
#include "Squeezer.h"
#include "Projectile.h"
#include "OperatorManager.h"
#include <time.h>

#include "FactManager.h"

#define MAX_TURNS 20
#define NUMBER_OF_CHARACTERS	10
#define NUMBER_OF_ACTORS		4

#include <iostream>
using namespace std;

using namespace GOAP;

Game::Game() : m_roam(true), m_running(true), m_turn(0)
{
	m_roomManager = 0;
	m_seed = (unsigned int)time(NULL);
	//1387930815;/ /Absolutely perfect
	//1387929138;// AWESOME
	//1387926598;// PERFECT
	//////////////////////////////////////////////////////////
	//1387912431;// Interesting: veloute saw taking of knife, but not killing
	//1387381488;// PERFECT
	//1387321436;// PERFECT
	//////////////////////////////////////////////////////////
	//1387369232;// perfect crime in 10 turns
	//1387319010;// perfect crime in less than 10 turns
	//1387307608;// perfect crime
	//1387226864;// with this one, tartar drops the rope and leaves the room
	//1387221411;// this one fails to stab
	//1387226550;// this one succeeds and plans a drop if no one wanders
	srand(m_seed);
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

	m_roomManager->Initialize(/*m_agents.begin(), m_agents.end()*/);
	InitializeAgents();
	InitializeObjects();

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
		if ((*iter)->GetAttrib(ATTRIBUTE_BEARER) == 0)
		{
			item++;
		}
		else
		{
			cout << item++ << ") " << (*iter)->GetName() << endl;
			m_vecObject.push_back(*iter);
		}
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
			if((*iter)->GetAttrib(ATTRIBUTE_ALIVE) == false)
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

#ifdef _GOAP_DEBUG
	int iMap = item;
	cout << "\nOr:\n";
	cout << item << ") SEE THE MAP" << endl;
#endif

	cout << "\n Or enter 0 to quit.\n";

	cout << "\nWhat would you like to do?\n>>> ";
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
	#ifdef _GOAP_DEBUG
	else if(answer == iMap)
	{
		DisplayRoomMap();
	}
	#endif
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

	/*int time;
	cout << "\nEnter 0 to go back \n>>> ";
	cin >> time;

	if( time == 0 )
	{
		m_roam = true;
		m_currentAgent = 0;
		return;
	}*/

	//m_currentAgent->Answer(qObject, question, answer);
	m_currentAgent->Answer(0, Q_ACTION, 0);
	m_roam = true;
	m_currentAgent = 0;
	return;
}

bool Game::Run(/*database class thing*/)
{
	bool result = false;
	while(m_running)
	{
		if (!GeneratePlot())
		{
			return false;
		}

		FactManager::Instance()->Initialize(m_actors);

		MainLoop();
		// prompt for another go
		// if yes :  
		// clear agents, 
		// clear rooms,
		// delete actions
		// 
		// initialize agents,
		// m_running = true;
	}
	return true;
}

bool Game::GeneratePlot()
{
	AssignRoles();
	PopulateRooms();

	m_murder = false;

	while(!m_murder)
	{
		// update murderer first to avoid artefacts
		m_murderer->Update(Op::OperatorManager::Instance(), m_roomManager, m_turn);

		for(auto room(m_roomManager->GetFirstRoom()); room != m_roomManager->GetLastRoom(); ++room)
		{
			(*room)->Update(Op::OperatorManager::Instance(), m_roomManager, m_turn);
		}

		for(auto room(m_roomManager->GetFirstRoom()); room != m_roomManager->GetLastRoom(); ++room)
		{
			if((*room)->UpdateAgentPositions(m_murderer, m_victim))
			{
				m_murder = true;
			}
		}

		for(auto room(m_roomManager->GetFirstRoom()); room != m_roomManager->GetLastRoom(); ++room)
		{
			(*room)->ResetAgentUpdateFlags();
		}

		DUMP("******************************")
		DUMP("Turn " << m_turn << " is over.")
		DUMP("******************************")

#ifdef _GOAP_DEBUG
		std::cin.get();
#endif
		++m_turn;
		if(m_turn >= MAX_TURNS)
		{
			std::cout << "	******************************\n";
			std::cout << "	I have failed you.\n";
			std::cout << "	Seed " << m_seed << " doesn't work," <<endl;
			std::cout << "	\n\n	It's not you, it's me\n";
			std::cout << "	******************************\n";
			std::cin.get();
			return false;
		}
	}
	return true;
}

void Game::MainLoop()
{
	std::cout << "******************************\n";
	std::cout << "Plot successfully generated in " << m_turn << " turns\n";
	std::cout << "Seed used : " << m_seed << endl;
	std::cout << "******************************\n\n";

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

	int character_array[NUMBER_OF_CHARACTERS];
	int role_array[NUMBER_OF_ACTORS];

	for(int index = 0; index < NUMBER_OF_CHARACTERS; ++index)
	{
		character_array[index] = -1;
	}
	for(int role = 0; role < NUMBER_OF_ACTORS; ++role)
	{
		// Pick random agent for each role
		// Make sure collisions are handled
		// In the end, role_array will contain the indices
		//  of agents for each role
		// The roles are:
		// 0  : Murderer
		// 1  : Victim
		// 2+ : Witnesses
		int index = rand() % NUMBER_OF_CHARACTERS;
		while(character_array[index] != -1 )
		{
			++index;
			index %= NUMBER_OF_CHARACTERS;
		}
		character_array[index] = role + 1;
		role_array[role] = index;
	}


	m_murderer = m_agents[role_array[0]];
	m_murderer->SetAsMurderer();

	m_victim = m_agents[role_array[1]];
	m_victim->SetAsVictim();

	GOAP::Condition vicIsDead(OP_LAYOUT_TYPE_OAVB, OPERATOR_EQUAL);
	vicIsDead[0].attrib = ATTRIBUTE_ALIVE;
	vicIsDead[0].instance = m_victim;
	vicIsDead[0].type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	vicIsDead[0].value = false;

	///*m_objects[2]->SetBearer(m_murderer);
	//m_murderer->SetAttribute(ATTRIBUTE_INVENTORY, true);*/

	//m_murderer->See(m_objects[7]);

	//GOAP::Condition cond2(OP_LAYOUT_TYPE_OOB, OPERATOR_HAS);
	//cond2[0].instance = m_murderer;
	//cond2[0].type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	////cond2[0].attrib = ATTRIBUTE_ROOM;
	//cond2[1].instance = m_objects[7];
	//cond2[1].type = m_objects[7]->GetCompoundType();
	////cond2[1].attrib = ATTRIBUTE_ROOM;

	Goal* goal = new Goal;
	goal->SetDepth(0);
	goal->AddCondition(vicIsDead);
	m_murderer->SetGoal(goal);

	m_murderer->See(m_victim);
	m_murderer->AddAction(ACTION_WAITFOR);
    m_murderer->AddAction(ACTION_TAKE);
    m_murderer->AddAction(ACTION_DROP);

	m_roomManager->ShowBedrooms(m_murderer);

	m_actors.push_back(m_murderer);
	m_actors.push_back(m_victim);
	m_actors.push_back(m_agents[role_array[2]]);
	m_actors.push_back(m_agents[role_array[3]]);

	for(auto actor(m_actors.begin()); actor != m_actors.end() ; ++actor )
	{
		m_roomManager->AddAgentProbabilities(*actor);
	}
	
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

	//m_roomManager->GetRoom(ROOM_KITCHEN)->AddAgent(m_agents[0]);
	for(int i=0; i<NUMBER_OF_ACTORS; ++i)
	{
		m_roomManager->GetRoom(ROOM_DINING_ROOM)->AddAgent(m_actors[i]);
	}
}

//hard-coding the characters by passing the variables to agent's initializer method
void Game::InitializeAgents()
{
	int MURDERER_ID = 0;

	m_agents.clear();

	for (unsigned int i = 0 ; i < NUMBER_OF_CHARACTERS; ++i)
		m_agents.push_back(new GOAP::Agent());


	//0. Comrade Tartar
	int locationProbability1[] = {0, 5, 50, 5, 40};
	m_agents[0]->InitializeCharacter("Comrade Tartar", MALE
	, "A Russia circus acrobat defected to England. A muscled and strong man that claims he has captured all the circus's bears barehanded"
	, locationProbability1, true, true, false, true, 9, 10);

	//1. Colonel Worcestershire
	int locationProbability2[] = {0, 60, 5, 5, 30};
	m_agents[1]->InitializeCharacter("Colonel Worcestershire", MALE
	, "An old British military man. Though respected and feared by his men, old age has left visible marks on his body."
	, locationProbability2, true, false, true, false, 8, 8);

	//2. Don Gravy
	int locationProbability3[] = {0, 30, 30, 5, 35};
	m_agents[2]->InitializeCharacter("Don Gravy", MALE
	, "An American mobster on a business trip in England. Famous for never missing a shot or a meal."
	, locationProbability3, true, true, true, true, 6, 9);

	//3. Mademoiselle Velouté
	int locationProbability4[] = {0, 30, 30, 10, 30};
	m_agents[3]->InitializeCharacter("Mademoiselle Velouté", FEMALE
	, "A French super model on holidays."
	, locationProbability4, true, true, true, false, 6, 4);

	//4. Madame Béchamel
	int locationProbability5[] = {0, 15, 20, 5, 60};
	m_agents[4]->InitializeCharacter("Madame Béchamel", FEMALE
	, "A middle-aged French woman. Poor soul was widowed five times and every time only a week after her wedding."
	, locationProbability5, true, true, false, false, 5, 6);

	//5. Mrs.Hollandaise
	int locationProbability6[] = {30, 5, 30, 5, 30};
	m_agents[5]->InitializeCharacter("Mrs. Hollandaise", FEMALE
	, "The maid."
	, locationProbability6, true, true, false, true, 5, 5);

	//6. Mr.Hollandaise
	int locationProbability7[] = {30, 5, 50, 5, 10};
	m_agents[6]->InitializeCharacter("Mr.Hollandaise", MALE
	, "The butler. A Dutch and French descendant butler and maid husband and wife"
	, locationProbability7, true, true, false, true, 7, 6);

	//7. Herr Duckefett
	int locationProbability8[] = {0, 5, 50, 5, 40};
	m_agents[7]->InitializeCharacter("Herr Duckefett", MALE
	, "A German explorer. HAs a strange taste when it comes to women"
	, locationProbability8, true, true, true, true, 8, 7);

	//8. prof.Custard
	int locationProbability9[] = {0, 35, 50, 5, 10};
	m_agents[8]->InitializeCharacter("Prof.Custard", MALE
	, "British renowned "
	, locationProbability9, true, true, true, true, 8, 7);

	//9. Signor Bolognese
	int locationProbability10[] = {0, 50, 5, 5, 40};
	m_agents[9]->InitializeCharacter("Signor Bolognese", MALE
	, "Italian, sleezy, barber, slim, fast, cheap"
	, locationProbability10, true, true, true, true, 8, 7);
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
	Prop* obj = 0;

	obj = new Prop("Clock");
	obj->MayBeFoundIn(ROOM_BATHROOM | ROOM_BEDROOM | ROOM_LIVING_ROOM | ROOM_DINING_ROOM);
	m_objects.push_back(obj);

	obj = new Prop("Cup");
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

	obj = new Prop("Lamp");
	obj->MayBeFoundIn(ROOM_BATHROOM | ROOM_BEDROOM | ROOM_LIVING_ROOM | ROOM_DINING_ROOM);
	m_objects.push_back(obj);

	obj = new Prop("Table");
	obj->MayBeFoundIn(ROOM_KITCHEN | ROOM_DINING_ROOM | ROOM_LIVING_ROOM);
	m_objects.push_back(obj);

	obj = new Projectile("Gun");
	obj->MayBeFoundIn(ROOM_BEDROOM);
	m_objects.push_back(obj);
}

void Game::DisplayRoomMap()
{
	/*for(time)
	{
		for(agent)
		{
			cout << factmgr[agent][time];
		}
	}*/
	FactManager* fm = FactManager::Instance();
	std::cout << "\n******************************\n\n";
	for(int turn=1; turn<m_turn; ++turn)
	{
		cout << turn << ".	";
		for(auto agent(m_agents.begin()); agent != m_agents.end(); ++agent)
		{
			int id = 0;
			if(fm->GetRoom(*agent, turn) != 0)
			{
				id = fm->GetRoom(*agent, turn)->GetID();
			}
			cout << id << "	";
		}
		cout << endl;
	}
	std::cout << "\n	MAP! I HAVE A MAP!\n";
}
#include "Game.h"

#include "Prop.h"
#include "Agent.h"
#include "Room.h"
#include "Blade.h"
#include "Blunt.h"
#include "Squeezer.h"
#include "Projectile.h"
#include "OperatorManager.h"
#include "Action.h"
#include <conio.h>
#include <time.h>

#include "FactManager.h"

#define MAX_TURNS 1000
#define NUMBER_OF_CHARACTERS	10
#define NUMBER_OF_ACTORS		3

#include <iostream>
using namespace std;

using namespace GOAP;

Game::Game() : m_roam(true), m_running(true), m_turn(0), m_timeOfDeath(0), m_accuser(0)
{
	m_roomManager = 0;
	m_seed = (unsigned int)time(NULL);
	//1389116877;// confusing. good.
	//1389116123;// tug of war!
	//1388872701;// perfect: take, wait, fail, replan, take other, kill, drop elsewhere
	//////////////////////////////////////////////////////////
	//1388591446;// Nothing special
	//1387930815;// Absolutely perfect
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
	m_accuser = new Accuser;
	m_roomManager = RoomManager::Instance();

	m_roomManager->Initialize(/*m_agents.begin(), m_agents.end()*/);
	InitializeAgents();
	InitializeObjects();

	m_currentRoom = m_roomManager->GetRoom(ROOM_LIVING_ROOM);
}

void Game::Roam()
{
	m_vecAgent.clear();
	m_vecObject.clear();
	m_vecRoom.clear();

	cout << "=======================================\n\n";
	cout << "You are in " << m_currentRoom->GetName() << "\n\n";
	int item = 1;

	int iRoom = item;
	
	cout << "-----------------------\n";
	cout << "\n* You can go to:\n\n";
	for(auto iter(m_roomManager->GetFirstRoom()); iter != m_roomManager->GetLastRoom(); ++iter)
	{
		std::cout.fill(' ');
		std::cout.width(2);
		cout << item++ << ". " << (*iter)->GetName() << "\n" << endl;
		m_vecRoom.push_back(*iter);
	}

	int iItem = item;

	cout << "-----------------------\n";
	cout << "\n* You can examine:\n\n";
	if(m_currentRoom->GetFirstObject() == m_currentRoom->GetLastObject())
	{
		cout << "[NOTHING]\n";
	}
	else
	{	
		for(auto iter(m_currentRoom->GetFirstObject()); iter != m_currentRoom->GetLastObject(); ++iter)
		{
			if ((*iter)->GetAttrib(ATTRIBUTE_BEARER) != 0)
			{
				//item++;
			}
			else
			{
				std::cout.fill(' ');
				std::cout.width(2);
				cout << item++ << ". " << (*iter)->GetName() << "\n" << endl;
				m_vecObject.push_back(*iter);
			}
		}
	}

	int witness = item;
	cout << "-----------------------\n";
	cout << "\n* You can interview/examine:\n\n";
	if(m_currentRoom->GetFirstAgent() == m_currentRoom->GetLastAgent())
	{
		cout << "[NOBODY]\n";
	}
	else
	{
		for(auto iter(m_currentRoom->GetFirstAgent()); iter != m_currentRoom->GetLastAgent(); ++iter)
		{
			std::cout.fill(' ');
			std::cout.width(2);
			cout << item++ << ". " << (*iter)->GetName();
			if((*iter)->GetAttrib(ATTRIBUTE_ALIVE) == false)
			{
				cout << " [DEAD]";
			}
			cout << "\n" << endl;
			m_vecAgent.push_back(*iter);
		}
	}
	cout << "-----------------------\n";
	int iMap = item;
#ifdef _DEBUG
	cout << "\nOr:\n";
	cout << item << ") SEE THE MAP" << endl;
#endif

	cout << "\n*0. Return to Constable Sauce.\n";

	cout << "\nWhat would you like to do?\n>>> ";
	int answer;
	cin >> answer;

	if (answer == 0)
	{
		m_running = ReturnToConstable();
	}

	if(answer>=iRoom && answer < iItem)//change room
	{
		m_currentRoom = m_vecRoom[answer - iRoom];
	}
	else if(answer >= iItem && answer < witness )// examine
	{
		Prop* prop = m_vecObject[answer - iItem];
		std::cout << "\n" << prop->GetName() << " : " << prop->GetDescription() << std::endl;
		std::cout << "\n--Press any key to continue\n";
		_getch();
		//examine(answer-1);
	}
	else if(answer>=witness && answer <iMap)//agent
	{
		Agent* aWitness = m_vecAgent[answer - witness];
		if(aWitness->GetAttrib(ATTRIBUTE_ALIVE) == true)
		{
			m_currentAgent = aWitness;
			m_roam = false;
		}
		else
		{
#ifdef _DEBUG
			m_currentAgent = aWitness;
			m_roam = false;
#else
			std::cout << "\n" << aWitness->GetName() << " was killed at " << TURN2TIME(m_timeOfDeath) << " with a " << m_murderWeaponType << "." << std::endl;
			std::cout << "\n--Press any key to continue\n";
			_getch();
#endif
		}
	}
#ifdef _DEBUG
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
	
	// ACCUSE
	
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
	bool thiefHasGoal = false;

	while(!m_murder)
	{
		// update murderer first to avoid artefacts
		m_murderer->Update(Op::OperatorManager::Instance(), m_roomManager, m_turn);

		if(!thiefHasGoal)
		{
			if(m_murderer->GetGoal()->GetFirstCondition()->GetOperatorLayoutType() == OP_LAYOUT_TYPE_OAVB)
			{
				if(m_murderer->GetGoal()->GetPlan()->GetStatus() == PLAN_STAT_SUCCESS)
				{
					SetGoalOfThief();
					thiefHasGoal = true;
				}
			}
		}

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

#ifdef _DEBUG
		GETKEY;
#endif
		// Record time of death
		if(m_actors[1]->GetAttrib(ATTRIBUTE_ALIVE) == false && m_timeOfDeath == 0)
		{
			GetMurderWeapon();
			m_timeOfDeath = m_turn;
		}


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
	std::cout << "--Press any key to continue";
	_getch();

	system("cls");

	DisplayIntroduction();
	MoveActorsToLivingRoom();

	while(m_running)
	{
		if(m_roam)
		{
			system("cls");
			Roam();
		}
		else
		{
			system("cls");
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
		// 2  : Thief
		// 3+ : Witnesses
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

	Goal* goal = new Goal;
	goal->SetDepth(0);
	goal->AddCondition(vicIsDead);
	goal->SetPriority(10);
	m_murderer->AddGoal(goal);

	m_murderer->See(m_victim);
	m_murderer->AddAction(ACTION_WAITFOR);
    m_murderer->AddAction(ACTION_TAKE);
    m_murderer->AddAction(ACTION_DROP);

	m_roomManager->ShowBedrooms(m_murderer);

	m_actors.push_back(m_murderer);
	m_actors.push_back(m_victim);
	for(int otherRoles = 2; otherRoles < NUMBER_OF_ACTORS; ++otherRoles)
	{
		m_actors.push_back(m_agents[role_array[otherRoles]]);
	}
	for(auto actor(m_actors.begin()); actor != m_actors.end() ; ++actor )
	{
		m_roomManager->AddAgentProbabilities(*actor);
	}

	m_murderer->PickCurrentGoal();
	
	/*GOAP::Condition cond2(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);
	cond2[0].instance = m_objects[7];
	cond2[0].type = m_objects[7]->GetCompoundType();
	cond2[0].attrib = ATTRIBUTE_ROOM;
	cond2[1].instance = RoomManager::Instance()->GetRoom(ROOM_BEDROOM, m_agents[role_array[2]]);
	cond2[1].type = OBJ_TYPE_ROOM | OBJ_TYPE_OBJECT;
	cond2[1].attrib = ATTRIBUTE_ROOM;

	goal = new Goal;
	goal->SetDepth(0);
	goal->AddCondition(cond2);
	goal->SetPriority(20);*/

	m_agents[role_array[2]]->AddAction(ACTION_TAKE);
	m_agents[role_array[2]]->AddAction(ACTION_DROP);
	////m_victim->AddGoal(goal);
	m_agents[role_array[2]]->PickCurrentGoal();

	if(NUMBER_OF_ACTORS == 4)
	{
		m_accuser->Initialize(m_actors[0], m_actors[2], m_actors[3]);
	}
	else
	{
		m_accuser->Initialize(m_actors[0], m_actors[2], 0);
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

	for(auto object(m_objects.begin()); object != m_objects.end(); ++object)
	{
		Room* room = m_roomManager->GetRoom((*object)->MayBeFoundIn());
		room->AddObject(*object);
	}

	//m_roomManager->GetRoom(ROOM_KITCHEN)->AddAgent(m_agents[0]);
	for(int i=0; i<NUMBER_OF_ACTORS; ++i)
	{
		m_roomManager->GetRoom(ROOM_BEDROOM, m_actors[i])->AddAgent(m_actors[i]);
	}

	// Show everything to murderer and thief
	RoomManager::Instance()->ShowEverything( m_actors[0] );
	RoomManager::Instance()->ShowEverything( m_actors[2] );
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
		for(auto agent(m_actors.begin()); agent != m_actors.end(); ++agent)
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

void Game::DisplayIntroduction()
{
	int m_murderWeapon = 0;
	std::cout << "\n\n\tGood evening. I'm Constable Sauce. Redcurrant Sauce.\n\n\t\
Thank you for helping Scotland Yard with this case.\n\n\t\
We found " << m_actors[1]->GetName() << ", one of the residents of this manor,\n\n\t\
dead in " << m_actors[1]->GetRoom()->GetName()<< ".\n\n\t\
The coroner times the death at " << TURN2TIME(m_timeOfDeath) << ".\n\n\t\
He believes that the victim was killed by " << m_murderWeaponType << "\n\n\
(like " << m_weaponExample1 << " or " << m_weaponExample2 << ").\n\n\t\
I've gathered all other residents in the living room to be interviewed.\n\n\t\
You can go around the house and examine different rooms if you like.\n\n\t\
I know with your talent you can solve the case in no time,\n\n\t\
Just tell me when you are ready to accuse someone...\n\n\t\
Or if you are just bored and want to go home.\n\n" << std::endl;
	std::cout << "--Press any key to continue\n";
	_getch();
}

void Game::MoveActorsToLivingRoom()
{
	Room* livingRoom = m_roomManager->GetRoom(ROOM_LIVING_ROOM);
	for(int actor = 0; actor < NUMBER_OF_ACTORS; ++actor)
	{
		if(actor != 1)
		{
			Room* room = m_actors[actor]->GetRoom();
			if(room != livingRoom)
			{
				m_actors[actor]->GetRoom()->MarkForDeletion(m_actors[actor]);
				livingRoom->AddAgent(m_actors[actor]);
			}
		}
	}

	for(auto room(m_roomManager->GetFirstRoom()); room != m_roomManager->GetLastRoom(); ++room)
	{
		(*room)->UpdateAgentPositions(m_murderer, m_victim);
	}
}

bool Game::ReturnToConstable()
{
	int answer = -1;
	bool done = false;
	while(!done)
	{
		system("cls");
		std::cout << "==================================\n";
		std::cout << "\nYou are talking to Constable Sauce\n\n";
		std::cout << "\nHe asks if you are ready to:\"\n\n";
		std::cout << "1. Accuse someone\n\n";
		std::cout << "2. Continue your investigation\n\n";
		std::cout << "Or\n\n 0. Rage quit\n\n";
		std::cout << ">>> ";
		//accuse?
		//leave?
		//continue?
		std::cin >> answer;
		switch(answer)
		{
		case 0:
			// nag
			return false;
		case 1:
			return Accuse();
		case 2:
			return true;
		default:
			return true;
			break;
		}
	}
	return true;
}

bool Game::Accuse()
// returns whether the game should continue
{
	if(m_accuser->Prompt())
	{
		if(m_accuser->Submit())
		{
			std::cout << "\n\nYay! You won!\n\n";
			_getch();
			return false;
		}
		else
		{
			std::cout << "\n\nYou were wrong! The real killer was " << m_murderer->GetName() << "!";
			_getch();
			return false;
		}
	}
	else
	{
		return true;
	}	
}

void Game::GetMurderWeapon()
{
	for(auto record(m_actors[1]->GetFirstActionRecord()); record != m_actors[1]->GetLastActionRecord();
		++record)
	{
		ActionType at = *(record->action);
		if (at == ACTION_STAB || at == ACTION_BLUDGEON || at == ACTION_STRANGLE || at == ACTION_SHOOT)
		{
			switch(at)
			{
			case ACTION_STAB:
				m_murderWeaponType = "a blade (stabbed)";
				m_weaponExample1 = "a knife";
				m_weaponExample2 = "a sword";
				break;
			case ACTION_BLUDGEON:
				m_murderWeaponType = "a blunt object (bludgeoned)";
				m_weaponExample1 = "a coconut";
				m_weaponExample2 = "a trophy";
				break;
			case ACTION_STRANGLE:
				m_murderWeaponType = "a string (strangled)";
				m_weaponExample1 = "a rope";
				m_weaponExample2 = "a cord";
				break;
			case ACTION_SHOOT:
				m_murderWeaponType = "a projectile (shot)";
				m_weaponExample1 = "a gun";
				m_weaponExample2 = "a pistol";
				break;
			default:
				// WRONG
				break;
			}
		}
	}
}

void Game::SetGoalOfThief()
{
	Goal* murderGoal = m_murderer->GetGoal()->GetPlan()->GetPlan();
	while(murderGoal->GetParent()->GetParent() != 0)
		// find goal whose action is the murder
	{
		murderGoal = murderGoal->GetParent();
	}			

	// extract the murder instrument
	Prop* instrument = (Prop*)murderGoal->GetAction()->GetArg(SEMANTIC_ROLE_INSTRUMENT)->instance;
	instrument->IncreaseValue();
	Goal* goal = 0;
	// make thief want all props of the same type as the instrument
	for(auto item = m_actors[2]->FirstObject(); item != m_actors[2]->LastObject(); ++ item)
	{
		if(item->second->GetCompoundType() == instrument->GetCompoundType())
		{
			Condition wantItem(OP_LAYOUT_TYPE_OAOAB, OPERATOR_EQUAL);

			wantItem[0].instance = (*item).second;
			wantItem[0].type = (*item).second->GetCompoundType();
			wantItem[0].attrib = ATTRIBUTE_ROOM;
			wantItem[1].instance = RoomManager::Instance()->GetRoom(ROOM_BEDROOM, m_actors[2]);
			wantItem[1].type = OBJ_TYPE_ROOM | OBJ_TYPE_OBJECT;
			wantItem[1].attrib = ATTRIBUTE_ROOM;

			goal = new Goal;
			goal->SetDepth(0);
			goal->AddCondition(wantItem);
			goal->SetPriority(20);

			m_actors[2]->AddGoal(goal);
			m_actors[2]->PickCurrentGoal();
		}
	}
}
#include "Game.h"

#include <conio.h>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <time.h>

#include "Action.h"
#include "Agent.h"
#include "OperatorManager.h"
#include "Prop.h"
#include "Room.h"

#include "FactManager.h"

#define MAX_TURNS 1000
#define NUMBER_OF_CHARACTERS	10

using namespace std;
using namespace GOAP;

Game::Game() : m_roam(true), m_running(true), m_turn(0), m_timeOfDeath(0), m_accuser(0)
{
	system("cls");
	//unsigned int answer;
	std::cout << "Enter number of actors (3-4):\n>>> ";
	std::cin >> m_numberOfActors;
	if(m_numberOfActors > 4) m_numberOfActors = 4;
	if(m_numberOfActors < 3) m_numberOfActors = 3;
	std::cout << "\nEnter seed (0 for random seed):\n>>> ";
	std::cin >> std::hex >> m_seed;
	if(m_seed == 0) m_seed = (unsigned int)time(nullptr);
	//m_seed = 1389618615;//(unsigned int)time(nullptr);
	//1389604504
	// HANDPICKED
	// 1389604504 - 4ACTORS
	// 1389618615 - 3ACTORS1
	// 1389608152 - 3ACTORS2
	srand(m_seed);
	std::cin >> std::dec;
}

Game::Game(const Game& other)
{
}

Game::~Game()
{
}

void Game::Initialize()
{
	m_planner.Initialize();

	m_accuser = new Accuser;
	
	LoadAgents();
	PopulateMaps();
	LoadProps();
}

GOAP::Room* Game::Roam(const RoomManager& rm, GOAP::Roles& roles, GOAP::Room* currentRoom)
{
	std::vector<GOAP::Prop*> vecObject;
	std::vector<GOAP::Agent*> vecAgent;
	std::vector<GOAP::Room*> vecRoom;

	cout << "=======================================\n\n";
	cout << "You are in " << currentRoom->GetName() << "\n\n";
	int item = 1;

	int iRoom = item;

	cout << "-----------------------\n";
	cout << "\n* You can go to:\n\n";
	for(Room* room : rm.GetRooms())
	{
		std::cout.fill(' ');
		std::cout.width(2);
		cout << item++ << ". " << room->GetName() << "\n" << endl;
		vecRoom.push_back(room);
	}

	int iItem = item;

	cout << "-----------------------\n";
	cout << "\n* You can examine:\n\n";
	if(currentRoom->GetObjects().empty())
	{
		cout << "[NOTHING]\n";
	}
	else
	{
		for(Prop* prop : currentRoom->GetObjects())
		{
			if (prop->GetBearer())
			{
				//item++;
			}
			else
			{
				std::cout.fill(' ');
				std::cout.width(2);
				cout << item++ << ". " << prop->GetName() << "\n" << endl;
				vecObject.push_back(prop);
			}
		}
	}

	int witness = item;
	cout << "-----------------------\n";
	cout << "\n* You can interview/examine:\n\n";
	if(currentRoom->GetAgents().empty())
	{
		cout << "[NOBODY]\n";
	}
	else
	{
		for (Agent* agent : currentRoom->GetAgents())
		{
			std::cout.fill(' ');
			std::cout.width(2);
			cout << item++ << ". " << agent->GetName();
			if(!agent->IsAlive())
			{
				cout << " [DEAD]";
			}
			cout << "\n" << endl;
			vecAgent.push_back(agent);
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
		m_running = ReturnToConstable(roles);
	}

	if(answer>=iRoom && answer < iItem)//change room
	{
		return vecRoom[answer - iRoom];
	}
	else if(answer >= iItem && answer < witness )// examine
	{
		Prop* prop = vecObject[answer - iItem];
		std::cout << "\n" << prop->GetName() << " : " << prop->GetDescription() << " Usually found in " <<
			rm.GetRoom(prop->MayBeFoundIn())->GetName() << "." << std::endl;
		std::cout << "\n--Press any key to continue\n";
		_getch();
		//examine(answer-1);
	}
	else if(answer>=witness && answer <iMap)//agent
	{
		Agent* aWitness = vecAgent[answer - witness];
		if(aWitness->IsAlive())
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
			MurderWeaponInfo murderWeapon = GetMurderWeaponInfo(roles);
			std::cout << "\n" << aWitness->GetName() << " was killed " << TURN2INTERVAL(m_timeOfDeath) << " with a " << murderWeapon.type << "." << std::endl;
			std::cout << "\n--Press any key to continue\n";
			_getch();
#endif
		}
	}
#ifdef _DEBUG
	else if(answer == iMap)
	{
		//DisplayRoomMap();
	}
#endif
	else
	{
		// bad answer, do over
	}
	return currentRoom;
}

void Game::Interview(const ActionManager& actionManager)
{
	m_currentAgent->Answer(actionManager, nullptr, QuestionType::ACTION, 0);

	// ACCUSE
	m_roam = true;
	m_currentAgent = nullptr;
	return;
}

bool Game::Run()
{
	bool result = false;
	while(m_running)
	{
		Roles roles = AssignRoles();

		if (!GeneratePlot(roles))
		{
			return false;
		}

		//FactManager::Instance()->Initialize(m_actors);

		MainLoop(roles);
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

bool Game::GeneratePlot(GOAP::Roles& roles)
{
	PopulateRooms(m_planner.GetRoomManager(), roles);

	bool wasMurderWitnessed = false;
	bool thiefHasGoal = false;
	Room* murderRoom = nullptr;

	while(!wasMurderWitnessed)
	{
		// update murderer first to avoid artefacts
		roles.murderer->Update(m_planner, m_turn);

		if(!thiefHasGoal)
		{
			if(roles.murderer->GetGoal()->GetConditions().begin()->GetOperatorLayoutType() == OperatorLayoutType::OAVB)
			{
				if(roles.murderer->GetGoal()->GetPlan()->GetStatus() == PlanStatus::SUCCESS)
				{
					SetGoalOfThief(roles);
					thiefHasGoal = true;
				}
			}
		}

		for (Room* room : m_planner.GetRoomManager().GetRooms())
		{
			room->Update(m_planner, m_turn);

			if (!murderRoom)
			{
				if (room->Contains(roles.victim) && !roles.victim->IsAlive())
				{
					murderRoom = room;
				}
			}
		}

		for (Room* room : m_planner.GetRoomManager().GetRooms())
		{
			room->UpdateAgentPositions();
			
			if ((murderRoom == room) && room->ContainsAnyExcept(std::list<Agent*>{roles.murderer, roles.victim}))
			{
				wasMurderWitnessed = true;
			}
		}

		for (Room* room : m_planner.GetRoomManager().GetRooms())
		{
			room->ResetAgentUpdateFlags();
		}

		DUMP("******************************")
		DUMP("Turn " << m_turn << " is over.")
		DUMP("******************************")

#ifdef _DEBUG
		GETKEY;
#endif
		// Record time of death
		if(!roles.victim->IsAlive() && m_timeOfDeath == 0)
		{
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

void Game::MainLoop(GOAP::Roles& roles)
{
	std::cout << "******************************\n";
	std::cout << "Plot successfully generated in " << m_turn << " turns\n";
	std::cout << "Seed used : " << m_seed << endl;
	std::cout << "******************************\n\n";
	std::cout << "--Press any key to continue";
	_getch();

	system("cls");

	DisplayIntroduction(roles);
	MoveActorsToLivingRoom(m_planner.GetRoomManager().GetRoom(RoomName::LIVING_ROOM));
	m_planner.GetRoomManager().UpdateAllRooms();

	Room* currentRoom = m_planner.GetRoomManager().GetRoom(RoomName::LIVING_ROOM);

	while(m_running)
	{
		if(m_roam)
		{
			system("cls");
			Roam(m_planner.GetRoomManager(), roles, currentRoom);
		}
		else
		{
			system("cls");
			Interview(m_planner.GetActionManager());
		}
	}
}

GOAP::Roles Game::AssignRoles()
{
	Roles roles;

	// from agent bank
	// pick a random agent
	// mark as murderer
	// pick a random agent that's not the murderer
	// mark as victim
	// set 'murderer.goal' to be 'victim.isAlive == false'
	// pick (numWitness + 1) agents
	// set as witness(es)

	int character_array[NUMBER_OF_CHARACTERS];
	int* role_array = new int[m_numberOfActors];

	for(int index = 0; index < NUMBER_OF_CHARACTERS; ++index)
	{
		character_array[index] = -1;
	}
	for(int role = 0; role < m_numberOfActors; ++role)
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


	roles.murderer = m_agents[role_array[0]];
	roles.murderer->SetAsMurderer();

	roles.victim = m_agents[role_array[1]];
	roles.victim->SetAsVictim();

	GOAP::Condition vicIsDead(OperatorLayoutType::OAVB, OperatorType::EQUAL);
	vicIsDead.GetParamByIndex(0).attrib = AttributeType::ALIVE;
	vicIsDead.GetParamByIndex(0).instance = roles.victim;
	vicIsDead.GetParamByIndex(0).type = ObjectType::AGENT | ObjectType::OBJECT;
	vicIsDead.GetParamByIndex(0).value = false;

	Goal* goal = new Goal;
	goal->SetDepth(0);
	goal->AddCondition(vicIsDead);
	goal->SetPriority(10);
	roles.murderer->AddGoal(goal);

	roles.murderer->See(roles.victim);
	roles.murderer->AddAction(ActionType::WAITFOR);
    roles.murderer->AddAction(ActionType::TAKE);
    roles.murderer->AddAction(ActionType::DROP);

	m_actors.push_back(roles.murderer);
	m_actors.push_back(roles.victim);

	for(int otherRoles = 2; otherRoles < m_numberOfActors; ++otherRoles)
	{
		m_actors.push_back(m_agents[role_array[otherRoles]]);
	}	

	roles.murderer->PickCurrentGoal();

	roles.thief = m_agents[role_array[2]];
	roles.thief->AddAction(ActionType::TAKE);
	roles.thief->AddAction(ActionType::DROP);	
	roles.thief->PickCurrentGoal();

	delete[] role_array;

	return roles;
}

void Game::PopulateRooms(GOAP::RoomManager& roomManager, GOAP::Roles& roles)
{
	for (Agent* actor : m_actors)
	{
		roomManager.CreateRoomFor(actor);
		roomManager.AddAgentProbabilities(actor);
		roomManager.ShowCommonRooms(actor);
		roomManager.ShowOwnBedroom(actor);
	}

	roomManager.ShowBedrooms(roles.murderer);

	/* for each room in world
		from object bank[room]
			pick an object that can be used as a murder weapon
			i.e. that is the instrument in an action with an effect OAV[O.isAlive == false]
			pick 2-4 other objects from that room
	*/
	// kitchen, living, dining

	for(Prop* object : m_objects)
	{
		Room* room = roomManager.GetRoom(object->MayBeFoundIn());
		room->AddObject(object);
	}

	//m_roomManager->GetRoom(RoomName::KITCHEN)->AddAgent(m_agents[0]);
	for(Agent* actor : m_actors)
	{
		roomManager.GetRoom(RoomName::BEDROOM, actor)->AddAgent(actor);
	}

	// Show everything to murderer and thief
	roomManager.ShowEverything( roles.murderer );
	roomManager.ShowEverything( roles.thief );
}

//hard-coding the characters by passing the variables to agent's initializer method

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
		for(Agent* agent : m_actors)
		{
			int id = 0;
			if(fm->GetRoom(agent, turn) != 0)
			{
				id = fm->GetRoom(agent, turn)->GetID();
			}
			cout << id << "	";
		}
		cout << endl;
	}
	std::cout << "\n	MAP! I HAVE A MAP!\n";
}

void Game::DisplayIntroduction(const GOAP::Roles& roles)
{
	MurderWeaponInfo murderWeapon = GetMurderWeaponInfo(roles);

	std::cout << "\n\n\tGood evening. I'm Constable Sauce. Redcurrant Sauce.\n\n\t\
Thank you for helping Scotland Yard with this case.\n\n\t\
We found " << roles.victim->GetName() << ", one of the residents of this manor,\n\n\t\
dead in " << roles.victim->GetRoom()->GetName()<< ".\n\n\t\
The coroner times the death at " << TURN2INTERVAL(m_timeOfDeath) << ".\n\n\t\
He believes that the victim was killed by " << murderWeapon.type << "\n\n\
(like " << murderWeapon.example1 << " or " << murderWeapon.example2 << ").\n\n\t\
I've gathered all other residents in the living room to be interviewed.\n\n\t\
You can go around the house and examine different rooms if you like.\n\n\t\
I know with your talent you can solve the case in no time,\n\n\t\
Just tell me when you are ready to accuse someone...\n\n\t\
Or if you are just bored and want to go home.\n\n" << std::endl;
	std::cout << "--Press any key to continue\n";
	_getch();
}

void Game::MoveActorsToLivingRoom(GOAP::Room* livingRoom)
{
	for(int actor = 0; actor < m_numberOfActors; ++actor)
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
}

bool Game::ReturnToConstable(GOAP::Roles& roles)
{
	int answer = -1;
	bool done = false;
	while(!done)
	{
		system("cls");
		std::cout	<< "==================================\n"
					<< "\nYou are talking to Constable Sauce\n\n"
					<< "\nHe asks if you are ready to:\"\n\n"
					<< "1. Accuse someone\n\n"
					<< "2. Continue your investigation\n\n"
					<< "Or\n\n 0. Rage quit\n\n"
					<< ">>> ";
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
			return Accuse(roles);
		case 2:
			return true;
		default:
			return true;
			break;
		}
	}
	return true;
}

bool Game::Accuse(GOAP::Roles& roles)
// returns whether the game should continue
{
	if(Agent* allegedMurderer = m_accuser->Prompt(roles))
	{
		if(m_accuser->Submit(roles, allegedMurderer))
		{
			std::cout << "\n\nYay! You won!\n\n";
			_getch();
		}
		else
		{
			std::cout << "\n\nYou were wrong! The real killer was " << roles.murderer->GetName() << "!";
			_getch();
		}

		return false;
	}

	return true;	
}

GOAP::MurderWeaponInfo Game::GetMurderWeaponInfo(const GOAP::Roles& roles) const
{
	for(auto record(roles.victim->GetFirstActionRecord()); record != roles.victim->GetLastActionRecord();
		++record)
	{
		Action* action = record->action;		

		if ((action->GetActionType() & ActionType::MURDER) != ActionType::NONE)
		{
			Object* murderWeaponObject = action->GetArg(SemanticRole::INSTRUMENT).instance;
			Prop* murderWeapon = dynamic_cast<Prop*>(murderWeaponObject);

			switch(action->GetActionType())
			{
			case ActionType::STAB:
				return { murderWeapon, "a blade (stabbed)", "a knife", "a sword" };
			case ActionType::BLUDGEON:
				return { murderWeapon, "a blunt object (bludgeoned)", "a coconut", "a trophy" };
			case ActionType::STRANGLE:
				return { murderWeapon, "a string (strangled)", "a rope", "a cord" };
			case ActionType::SHOOT:
				return { murderWeapon, "a projectile (shot)", "a gun", "a pistol" };
			default:
				return {};
			}
		}
	}

	return {};
}

void Game::SetGoalOfThief(GOAP::Roles& roles)
{
	Room* thiefsBedroom = m_planner.GetRoomManager().GetRoom(RoomName::BEDROOM, roles.thief);

	Goal* murderGoal = roles.murderer->GetGoal()->GetPlan()->GetPlan();
	while(murderGoal->GetParent()->GetParent() != nullptr)
		// find goal whose action is the murder
	{
		murderGoal = murderGoal->GetParent();
	}

	// extract the murder instrument
	Prop* instrument = (Prop*)murderGoal->GetAction()->GetArg(SemanticRole::INSTRUMENT).instance;
	instrument->IncreaseValue();
	Goal* goal = nullptr;
	// make thief want all props of the same type as the instrument
	for(auto item = roles.thief->FirstObject(); item != roles.thief->LastObject(); ++ item)
	{
		if(item->second->GetCompoundType() == instrument->GetCompoundType())
		{
			Condition wantItem(OperatorLayoutType::OAOAB, OperatorType::EQUAL);

			wantItem.GetParamByIndex(0).instance = (*item).second;
			wantItem.GetParamByIndex(0).type = (*item).second->GetCompoundType();
			wantItem.GetParamByIndex(0).attrib = AttributeType::ROOM;
			
			wantItem.GetParamByIndex(1).instance = thiefsBedroom;
			wantItem.GetParamByIndex(1).type = ObjectType::ROOM | ObjectType::OBJECT;
			wantItem.GetParamByIndex(1).attrib = AttributeType::ROOM;

			goal = new Goal;
			goal->SetDepth(0);
			goal->AddCondition(wantItem);
			goal->SetPriority(20);

			roles.thief->AddGoal(goal);
			roles.thief->PickCurrentGoal();
		}
	}
}


void Game::LoadAgents()
{
	// TODO merge this with InitializeObjects

	int MURDERER_ID = 0;

	m_agents.clear();

	std::ifstream ifs("entities.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);
	ifs.close();

	const Json::Value& agents = obj["agents"];

	for (const Json::Value& jsonAgent : agents)
	{
		GOAP::Agent* agent = new GOAP::Agent();
		int room_count = jsonAgent["rooms"].size();
		float* rooms = new float[room_count];
		for (int j = 0; j < room_count; ++j)
		{
			rooms[j] = jsonAgent["rooms"][j].asFloat();
		}

		int action_count = jsonAgent["actions"].size();
		std::string* actions = new string[action_count];
		for (int k = 0; k < action_count; ++ k)
		{
			actions[k] = jsonAgent["actions"][k].asString();
		}

		Gender gender = jsonAgent["gender"].asString().compare("m") == 0 ? Gender::MALE : Gender::FEMALE;

		agent->InitializeCharacter(
		jsonAgent["name"].asString(),
		gender,
		jsonAgent["desc"].asString(),
		rooms,
		room_count,
		actions,
		action_count);

		m_agents.push_back(agent);
	}
}

void Game::LoadProps()
{
	m_objects.clear();

	std::ifstream ifs("entities.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);
	ifs.close();

	const Json::Value& props = obj["props"];

	for (const auto propField : props)
	{
		Prop* prop = new Prop(propField["name"].asString());
		prop->SetCompoundType(m_propTypeMap[propField["class"].asString()]);
		prop->MayBeFoundIn(m_roomEnumMap[propField["room"].asString()]);
		prop->SetDescription(propField["desc"].asString());
		m_objects.push_back(prop);
	}
}

void Game::PopulateMaps()
{
	m_roomEnumMap["LIVING_ROOM"] = RoomName::LIVING_ROOM;
	m_roomEnumMap["DINING_ROOM"] = RoomName::DINING_ROOM;
	m_roomEnumMap["KITCHEN"] = RoomName::KITCHEN;
	m_roomEnumMap["BATHROOM"] = RoomName::BATHROOM;

	m_propTypeMap["Prop"] = ObjectType::OBJECT | ObjectType::PROP;
	m_propTypeMap["Blunt"] = ObjectType::OBJECT | ObjectType::PROP | ObjectType::BLUNT;
	m_propTypeMap["Blade"] = ObjectType::OBJECT | ObjectType::PROP | ObjectType::BLADE;
	m_propTypeMap["Squeezer"] = ObjectType::OBJECT | ObjectType::PROP | ObjectType::SQUEEZER;
	m_propTypeMap["Projectile"] = ObjectType::OBJECT | ObjectType::PROP | ObjectType::PROJECTILE;
}

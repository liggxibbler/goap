#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <map>
#include <string>

#include "RoomManager.h"
#include "Accuser.h"
#include "Common.h"

namespace GOAP
{
	class Agent;
	class Prop;
}

class Game
{
public:
	Game();
	Game(const Game& other);
	~Game();

	void Initialize();

	void Roam();
	void Interview();
	bool Accuse();

	bool Run(const GOAP::Op::OperatorManager& operatorManager);

	void AssignRoles();
	void PopulateRooms();
	bool GeneratePlot(const GOAP::Op::OperatorManager& operatorManager);
	void MainLoop();

	void DisplayRoomMap();
	void DisplayIntroduction();
	void MoveActorsToLivingRoom();
	bool ReturnToConstable();

	void GetMurderWeapon();
	void SetGoalOfThief();

private:
	std::vector<GOAP::Prop*> m_vecObject;
	std::vector<GOAP::Agent*> m_vecAgent;
	std::vector<GOAP::Room*> m_vecRoom;

	std::map<std::string, GOAP::RoomName> m_roomEnumMap;
	std::map<std::string, GOAP::ObjectType> m_propTypeMap;

	/*databaseClassThing* m_database;*/

	void InitializeAgents();
	void InitializeObjects();
	void PopulateDictionaries();

	//GOAP::World* m_world;
	bool m_roam = false;
	GOAP::Room* m_currentRoom = nullptr;
	GOAP::Agent* m_currentAgent = nullptr;
	GOAP::RoomManager* m_roomManager = nullptr;	

	GOAP::Agent* m_murderer = nullptr;
	GOAP::Agent* m_victim = nullptr;

	bool m_running = false;
	bool m_murder = false;

	int m_turn = -1;
	unsigned int m_seed;
	std::vector<GOAP::Agent*>	m_agents;
	std::vector<GOAP::Agent*>	m_actors;
	std::vector<GOAP::Prop*>	m_objects;

	int m_timeOfDeath = -1;
	Accuser* m_accuser = nullptr;

	int m_numberOfActors = -1;

	GOAP::Prop* m_murderWeapon = nullptr;
	std::string m_murderWeaponType;
	std::string m_weaponExample1;
	std::string m_weaponExample2;
};

#endif

#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <map>
#include <string>

#include "Accuser.h"
#include "Common.h"
#include "Planner.h"
#include "RoomManager.h"

namespace GOAP
{
	class Agent;
	class Prop;

	struct MurderWeaponInfo
	{
		Prop* weapon = nullptr;
		std::string type = "INVALID WEAPON";
		std::string example1 = "INVALID EXAMPLE 1";
		std::string example2 = "INVALIDE EXMAPLE 2";
	};
}

class Game
{
public:
	Game();
	Game(const Game& other);
	~Game();

	void Initialize();

	GOAP::Room* Roam(const GOAP::RoomManager& rm, GOAP::Roles& roles, GOAP::Room* currentRoom);
	void Interview(const GOAP::ActionManager& actionManager);
	bool Accuse(GOAP::Roles& roles);

	bool Run();

	GOAP::Roles AssignRoles();
	void PopulateRooms(GOAP::RoomManager& roomManager, GOAP::Roles& roles);
	bool GeneratePlot(GOAP::Roles& roles);
	void MainLoop(GOAP::Roles& roles);

	void DisplayRoomMap();
	void DisplayIntroduction(const GOAP::Roles& roles);
	void MoveActorsToLivingRoom(GOAP::Room* livingRoom);
	bool ReturnToConstable(GOAP::Roles& roles);

	GOAP::MurderWeaponInfo GetMurderWeaponInfo(const GOAP::Roles& roles) const;
	void SetGoalOfThief(GOAP::Roles& roles);

private:
	
	std::map<std::string, GOAP::RoomName> m_roomEnumMap;
	std::map<std::string, GOAP::ObjectType> m_propTypeMap;

	/*databaseClassThing* m_database;*/

	void LoadAgents();
	void LoadProps();
	void PopulateMaps();

	GOAP::Planner m_planner;

	//GOAP::World* m_world;
	bool m_roam = false;
	//GOAP::Room* m_currentRoom = nullptr;
	GOAP::Agent* m_currentAgent = nullptr;	

	bool m_running = false;
	
	int m_turn = -1;
	unsigned int m_seed = 0;
	std::vector<GOAP::Agent*>	m_agents;
	std::vector<GOAP::Agent*>	m_actors;
	std::vector<GOAP::Prop*>	m_objects;

	int m_timeOfDeath = -1;
	Accuser* m_accuser = nullptr;

	int m_numberOfActors = -1;
};

#endif

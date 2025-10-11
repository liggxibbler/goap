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
}

class Game
{
public:
	Game();
	Game(const Game& other);
	~Game();

	void Initialize();

	void Roam(const GOAP::RoomManager& rm);
	void Interview(const GOAP::ActionManager& actionManager);
	bool Accuse();

	bool Run();

	void AssignRoles();
	void PopulateRooms(GOAP::RoomManager& roomManager);
	bool GeneratePlot();
	void MainLoop();

	void DisplayRoomMap();
	void DisplayIntroduction();
	void MoveActorsToLivingRoom(GOAP::Room* livingRoom);
	bool ReturnToConstable();

	void GetMurderWeapon();
	void SetGoalOfThief(GOAP::Room* thiefsBedroom);

	GOAP::Agent* GetMurderer() const { return m_murderer; };
	GOAP::Agent* GetVictim() const { return m_victim; };
	GOAP::Agent* GetThief() const { return m_thief; };

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

	GOAP::Planner m_planner;

	//GOAP::World* m_world;
	bool m_roam = false;
	GOAP::Room* m_currentRoom = nullptr;
	GOAP::Agent* m_currentAgent = nullptr;	

	GOAP::Agent* m_murderer = nullptr;
	GOAP::Agent* m_victim = nullptr;
	GOAP::Agent* m_thief = nullptr;

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

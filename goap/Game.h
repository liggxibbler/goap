#ifndef _GAME_H_
#define _GAME_H_

#include "RoomManager.h"
#include "Accuser.h"
#include <vector>

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

	bool Run(/*database class thing*/);
	
	void AssignRoles();
	void PopulateRooms();
	bool GeneratePlot();
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

	/*databaseClassThing* m_database;*/

	void InitializeAgents();
	void InitializeObjects();

	//GOAP::World* m_world;
	bool m_roam;
	GOAP::Room* m_currentRoom;
	GOAP::Agent* m_currentAgent;
	GOAP::RoomManager* m_roomManager;	
	
	GOAP::Agent* m_murderer;
	GOAP::Agent* m_victim;
	
	bool m_running;
	bool m_murder;

	int m_turn;
	unsigned int m_seed;
	std::vector<GOAP::Agent*>	m_agents;
	std::vector<GOAP::Agent*>	m_actors;
	std::vector<GOAP::Prop*>	m_objects;

	int m_timeOfDeath;
	Accuser* m_accuser;

	GOAP::Prop* m_murderWeapon;
	std::string m_murderWeaponType;
	std::string m_weaponExample1;
	std::string m_weaponExample2;
};

#endif
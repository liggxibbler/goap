#ifndef _GAME_H_
#define _GAME_H_

#include "RoomManager.h"
#include <vector>

namespace GOAP
{
	class Agent;
	class STUFF;
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
	void Accuse();

	bool Run(/*database class thing*/);
	
	void AssignRoles();
	void PopulateRooms();
	bool GeneratePlot();
	void MainLoop();

private:
	std::vector<GOAP::STUFF*> m_vecObject;
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
	std::vector<GOAP::STUFF*>	m_objects;
};

#endif
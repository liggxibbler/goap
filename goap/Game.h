#ifndef _GAME_H_
#define _GAME_H_

#include <vector>

namespace GOAP
{
	class Room;
	class Agent;
	class Object;
	class World;
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

private:
	std::vector<GOAP::Object*> m_vecObject;
	std::vector<GOAP::Agent*> m_vecAgent;
	std::vector<GOAP::Room*> m_vecRoom;

	/*databaseClassThing* m_database;*/

	GOAP::World* m_world;
	bool m_roam;
	GOAP::Room* m_currentRoom;
	GOAP::Agent* m_currentAgent;
	bool m_running;
};

#endif
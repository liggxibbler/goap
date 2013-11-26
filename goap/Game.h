#ifndef _GAME_H_
#define _GAME_H_

#include <map>

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

	bool Run(/*database class thing*/);

private:
	std::map<char, GOAP::Object*> m_objectMap;
	std::map<char, GOAP::Agent*> m_agentMap;
	std::map<char, GOAP::Room*> m_roomMap;

	/*databaseClassThing* m_database;*/

	GOAP::World* m_world;
	bool m_roam;
	GOAP::Room* m_currentRoom;
	GOAP::Agent* m_currentAgent;
	bool m_running;
};

#endif
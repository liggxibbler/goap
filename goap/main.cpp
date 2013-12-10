#include <iostream>
#include "Common.h"
#include "Operator.h"
#include "Object.h"
#include "Agent.h"
#include "OperatorManager.h"
#include "ActionManager.h"
#include "GoTo.h"
#include "Goal.h"
#include "Plan.h"
#include "Blade.h"

//#include "World.h"
#include "Room.h"
#include "Game.h"

#include <ctime>

using namespace std;
using namespace GOAP;

void InitObjs(Object* o1, Agent* o2);
void InitConds(Condition& cc_eq, Condition& cc_gt);

unsigned int seed;

int main()
{	
	//seed = (unsigned int)time(NULL);
	//srand(1386261647);

	Game* game = new Game();
	game->Initialize();
	game->Run();
	
	return 0;
}
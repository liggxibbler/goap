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

#include "World.h"
#include "Room.h"
#include "Game.h"

using namespace std;
using namespace GOAP;

void InitObjs(Object* o1, Agent* o2);
void InitConds(Condition& cc_eq, Condition& cc_gt);

int main()
{
	Agent a1, a2, a3;
	Object o1, o2, o3;

	//Object* obj = new Object("Kolang");
	Blade* obj = new Blade("Knife");

	obj->SetAttrib(ATTRIB_TYPE_POSX, 4);
	obj->SetAttrib(ATTRIB_TYPE_POSY, 2);
	/*obj->SetAttrib(ATTRIB_TYPE_HEIGHT, 10);
	obj->SetAttrib(ATTRIB_TYPE_WEIGHT, 20);
	obj->SetAttrib(ATTRIB_TYPE_ALIVE, true);*/

	/*cout << "obj has:" << endl;
	cout << "X: " << obj->GetAttrib(ATTRIB_TYPE_POSX) << endl;
	cout << "Y: " << obj->GetAttrib(ATTRIB_TYPE_POSY) << endl;*/

	GOAP::Agent* agent = new GOAP::Agent("Alborz");
	(*agent)[ATTRIB_TYPE_POSX] = 3;
	(*agent)[ATTRIB_TYPE_POSY] = 1;
	(*agent)[ATTRIB_TYPE_HEIGHT] = 30;
	(*agent)[ATTRIB_TYPE_WEIGHT] = 20;
	(*agent)[ATTRIB_TYPE_ALIVE] = true;

	GOAP::Agent* dysh = new GOAP::Agent("Dysh");
	(*dysh)[ATTRIB_TYPE_POSX] = 5;
	(*dysh)[ATTRIB_TYPE_POSY] = 1;
	(*dysh)[ATTRIB_TYPE_HEIGHT] = 30;
	(*dysh)[ATTRIB_TYPE_WEIGHT] = 20;
	(*dysh)[ATTRIB_TYPE_ALIVE] = true;

	/*cout << "agent has:" << endl;
	cout << "X: " << (*agent)[ATTRIB_TYPE_POSX] << endl;
	cout << "Y: " << (*agent)[ATTRIB_TYPE_POSY] << endl;
	cout << "Height: " << (*agent)[ATTRIB_TYPE_HEIGHT] << endl;
	cout << "Weight: " << (*agent)[ATTRIB_TYPE_WEIGHT] << endl;
	cout << "Alive: " << (*agent)[ATTRIB_TYPE_ALIVE] << endl;

	cin.get();

	cout << "Agent has ID " << agent->GetID() << endl;
	cout << "Object has ID " << obj->GetID() << endl;

	cin.get();*/

	GOAP::Op::OperatorManager* om = GOAP::Op::OperatorManager::Instance();

	Condition testCond(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_EQUAL);
	
	testCond[0].instance = dysh;
	testCond[0].type = OBJ_TYPE_AGENT | OBJ_TYPE_OBJECT;
	testCond[0].attrib = ATTRIB_TYPE_ALIVE;
	testCond[0].value = false;

	/*testCond[0].instance = agent;
	testCond[0].type = OBJ_TYPE_AGENT;
	testCond[0].value = false;
	testCond[0].strict = true;

	testCond[1].instance = obj;
	testCond[1].type = OBJ_TYPE_OBJECT;
	testCond[1].value = false;*/

	Goal* goal = new Goal();
	goal->AddCondition(testCond);
	
	ActionManager* am = ActionManager::Instance();

	agent->AddAction(ACTION_STAB);
	agent->AddAction(ACTION_TAKE);
	agent->AddAction(ACTION_GOTO);	

	agent->SetGoal(goal);
	
	agent->See(dysh);
	agent->See(agent);
	agent->See(obj);

	Plan* plan = NULL;
	plan = agent->GetPlan(am, om);

	if(plan->GetStatus() == PLAN_STAT_SUCCESS)
	{
		ActionStatus stat = ACT_STAT_UNKNOWN;
		while(plan->Execute() != ACT_STAT_DONE)
		{
		}
	}
	else
	{
		DUMP("Planning failed")
	}
	cin.get();
	delete agent;
	delete obj;
	
	Game* game = new Game();
	game->Initialize();
	game->Run();
	
	return 0;
}
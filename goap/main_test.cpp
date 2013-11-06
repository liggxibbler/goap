#include <iostream>
#include "Common.h"
#include "Operator.h"
#include "Object.h"
#include "Agent.h"
#include "OperatorManager.h"
#include "ActionManager.h"
#include "GoTo.h"
#include "Goal.h"

using namespace std;
using namespace GOAP;

void InitObjs(Object* o1, Agent* o2);
void InitConds(Condition& cc_eq, Condition& cc_gt);

int main()
{
	Agent a1, a2, a3;
	Object o1, o2, o3;

	Object* obj = new Object("Kolang");
	
	obj->SetAttrib(ATTRIB_TYPE_POSX, 4);
	obj->SetAttrib(ATTRIB_TYPE_POSY, 2);
	/*obj->SetAttrib(ATTRIB_TYPE_HEIGHT, 10);
	obj->SetAttrib(ATTRIB_TYPE_WEIGHT, 20);
	obj->SetAttrib(ATTRIB_TYPE_ALIVE, true);*/

	cout << "obj has:" << endl;
	cout << "X: " << obj->GetAttrib(ATTRIB_TYPE_POSX) << endl;
	cout << "Y: " << obj->GetAttrib(ATTRIB_TYPE_POSY) << endl;

	GOAP::Agent* agent = new GOAP::Agent("Alborz");
	(*agent)[ATTRIB_TYPE_POSX] = 3;
	(*agent)[ATTRIB_TYPE_POSY] = 1;
	(*agent)[ATTRIB_TYPE_HEIGHT] = 30;
	(*agent)[ATTRIB_TYPE_WEIGHT] = 20;
	(*agent)[ATTRIB_TYPE_ALIVE] = true;

	cout << "agent has:" << endl;
	cout << "X: " << (*agent)[ATTRIB_TYPE_POSX] << endl;
	cout << "Y: " << (*agent)[ATTRIB_TYPE_POSY] << endl;
	cout << "Height: " << (*agent)[ATTRIB_TYPE_HEIGHT] << endl;
	cout << "Weight: " << (*agent)[ATTRIB_TYPE_WEIGHT] << endl;
	cout << "Alive: " << (*agent)[ATTRIB_TYPE_ALIVE] << endl;

	cin.get();

	cout << "Agent has ID " << agent->GetID() << endl;
	cout << "Object has ID " << obj->GetID() << endl;

	cin.get();

	GOAP::Op::OperatorManager om;

	OperatorLayoutType a = OP_LAYOUT_TYPE_OOB;
	OperatorType b = OPER_TYPE_OWNS;

	Condition testCond(a, b);
	
	testCond[0].instance = agent;
	testCond[0].type = OBJ_TYPE_AGENT;
	
	testCond[1].instance = obj;
	testCond[1].type = OBJ_TYPE_OBJECT;

	Goal* goal = new Goal();
	goal->AddCondition(testCond);
	
	ActionManager* am = new ActionManager();

	agent->AddAction(ACTION_GOTO);
	agent->AddAction(ACTION_TAKE);

	agent->SetGoal(goal);
	agent->See(obj);

	Goal* plan = NULL;

	plan = agent->GetPlan(am, &om);

	cin.get();
	delete agent;
	delete obj;
	return 0;
}
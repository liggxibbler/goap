#include <iostream>
#include "Common.h"
#include "Operator.h"
#include "Object.h"
#include "Agent.h"
#include "OperatorManager.h"
#include "ActionManager.h"
#include "TestAction.h"
#include "Goal.h"

using namespace std;
using namespace GOAP;

void InitObjs(Object* o1, Agent* o2);
void InitConds(Condition& cc_eq, Condition& cc_gt);

int main()
{
	Object* obj = new Object();
	
	obj->SetAttrib(ATTRIB_TYPE_POSX, 4);
	obj->SetAttrib(ATTRIB_TYPE_POSY, 2);
	/*obj->SetAttrib(ATTRIB_TYPE_HEIGHT, 10);
	obj->SetAttrib(ATTRIB_TYPE_WEIGHT, 20);
	obj->SetAttrib(ATTRIB_TYPE_ALIVE, true);*/

	cout << "obj has:" << endl;
	cout << "X: " << obj->GetAttrib(ATTRIB_TYPE_POSX) << endl;
	cout << "Y: " << obj->GetAttrib(ATTRIB_TYPE_POSY) << endl;

	GOAP::Agent* agent = new GOAP::Agent;
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

	GOAP::Op::OperatorManager om;

	OperatorLayoutType a = OP_LAYOUT_TYPE_OAOAB;
	OperatorType b = OPER_TYPE_EQUAL;

	Condition testCond(a, b);
	
	testCond[0].instance = agent;
	testCond[0].type = OBJ_TYPE_AGENT;
	testCond[0].attrib = ATTRIB_TYPE_POSX;

	testCond[1].instance = obj;
	testCond[1].attrib = ATTRIB_TYPE_POSX;

	Goal* goal = new Goal();
	goal->AddCondition(testCond);
	
	ActionManager* am = new ActionManager();

	agent->AddAction(ACTION_TEST);
	agent->SetGoal(goal);

	Goal* plan = NULL;

	plan = agent->GetPlan(am, &om);

	cin.get();
	delete agent;
	delete obj;
	return 0;
}
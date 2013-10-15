#include <iostream>
#include "Common.h"
#include "ConcreteCondition.h"
#include "SemanticCondition.h"
#include "Operator.h"
#include "Object.h"
#include "Agent.h"

using namespace std;
using namespace GOAP;

int main()
{
	GOAP::Object* obj = new GOAP::Object;
	obj->SetAttrib(ATTRIB_TYPE_POSX, 4);
	obj->SetAttrib(ATTRIB_TYPE_POSY, 2);
	/*obj->SetAttrib(ATTRIB_TYPE_HEIGHT, 10);
	obj->SetAttrib(ATTRIB_TYPE_WEIGHT, 20);
	obj->SetAttrib(ATTRIB_TYPE_ALIVE, true);*/

	cout << "obj has:" << endl;
	cout << "X: " << obj->GetAttrib(ATTRIB_TYPE_POSX) << endl;
	cout << "Y: " << obj->GetAttrib(ATTRIB_TYPE_POSY) << endl;

	GOAP::Agent* agent = new GOAP::Agent;
	agent->SetAttrib(ATTRIB_TYPE_POSX, 3);
	agent->SetAttrib(ATTRIB_TYPE_POSY, 1);
	agent->SetAttrib(ATTRIB_TYPE_HEIGHT, 10);
	agent->SetAttrib(ATTRIB_TYPE_WEIGHT, 20);
	agent->SetAttrib(ATTRIB_TYPE_ALIVE, true);

	cout << "agent has:" << endl;
	cout << "X: " << (*agent)[ATTRIB_TYPE_POSX] << endl;
	cout << "Y: " << (*agent)[ATTRIB_TYPE_POSY] << endl;
	cout << "Height: " << (*agent)[ATTRIB_TYPE_HEIGHT] << endl;
	cout << "Weight: " << (*agent)[ATTRIB_TYPE_WEIGHT] << endl;
	cout << "Alive: " << (*agent)[ATTRIB_TYPE_ALIVE] << endl;

	ConcreteCondition cc(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_EQUAL);

	cin.get();
	return 0;
}
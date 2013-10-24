#include <iostream>
#include "Common.h"
#include "Operator.h"
#include "Object.h"
#include "Agent.h"
#include "OperatorManager.h"

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

	Condition cc_eq(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_EQUAL);
	//DUMP( "pre cc_eq >>> " << agent << ", " << ATTRIB_TYPE_HEIGHT << ", " << false << ", " << 9)
	cc_eq[0].instance = agent;
	cc_eq[0].attrib = ATTRIB_TYPE_HEIGHT;
	cc_eq.SetNegate(false);
	cc_eq[0].value = 30;
	//DUMP( "post cc_eq >>> " << cc_eq[0].instance << ", " << cc_eq[0].attrib << ", " << cc_eq.GetNegate() << ", " << cc_eq[0].value)
	bool bResult = cc_eq.Evaluate(&om);

	cout << "Agent.height == 30 is " << bResult << endl;

	Condition cc_gt(OP_LAYOUT_TYPE_OAVB, OPER_TYPE_GREATER_THAN);
	cc_gt[0].instance = agent;
	cc_gt[0].attrib = ATTRIB_TYPE_HEIGHT;
	cc_gt.SetNegate(true);
	cc_gt[0].value = 31;
	bResult = cc_gt.Evaluate(&om);

	cout << "Agent.height > 10 is " << bResult << endl;

	cin.get();
	
	delete agent;
	delete obj;

	return 0;
}
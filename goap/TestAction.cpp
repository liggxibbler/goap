#include "TestAction.h"

using namespace GOAP;

TestAction::TestAction()
{
}

TestAction::TestAction(const TestAction& other)
{
}

TestAction::~TestAction()
{
}

void TestAction::Execute()
{
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_TYPE_SUBJECT));
	ConditionParameter obj(*GetArgBySemantic(OP_SEMANTIC_TYPE_OBJECT0));

	sub.instance->SetAttrib(ATTRIB_TYPE_POSX, (*(obj.instance))[ATTRIB_TYPE_POSX]);
}

TestAction::operator ActionType()
{
	return ACTION_TEST;
}

TestAction* TestAction::Clone()
{
	TestAction* newTestAction = new TestAction();
	return newTestAction;
}

void TestAction::InitArgs()
{
	ConditionParameter sub, obj1;
	
	// SUBJECT
	sub.semantic = OP_SEMANTIC_TYPE_SUBJECT;
	sub.instance = NULL;
	sub.type = OBJ_TYPE_AGENT;
	m_args.push_back(sub);

	// OBJECT
	obj1.semantic = OP_SEMANTIC_TYPE_OBJECT0;
	obj1.instance = NULL;
	obj1.type = OBJ_TYPE_OBJECT;
	m_args.push_back(obj1);
}

void TestAction::InitEffects()
{
	Condition swapSubObj1(OP_LAYOUT_TYPE_OAOAB, OPER_TYPE_EQUAL);
	
	ConditionParameter sub(*GetArgBySemantic(OP_SEMANTIC_TYPE_SUBJECT));
	ConditionParameter obj0(*GetArgBySemantic(OP_SEMANTIC_TYPE_OBJECT0));
	
	swapSubObj1[0] = sub;
	swapSubObj1[0].attrib = ATTRIB_TYPE_POSX;
	
	swapSubObj1[1] = obj0;
	swapSubObj1[1].attrib = ATTRIB_TYPE_POSX;
	
	m_effects.push_back(swapSubObj1);	
}

void TestAction::InitPreconditions()
{
	// subject owns instrument
	Condition condTrue(OP_LAYOUT_TYPE_TRUE, OPER_TYPE_TRUE);
	m_preconds->AddCondition(condTrue);
}
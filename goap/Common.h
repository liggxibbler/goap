#ifndef _GOAP_COMMONS_H_
#define _GOAP_COMMONS_H_

#include <iostream>
#ifdef _DEBUG
#define DUMP(X) std::cout << std::endl << X << std::endl;
#else
#define DUMP(X)
#endif

namespace GOAP
{
	struct Position
	{
		int x;
		int y;
	};

	enum ObjectType
	{
		OBJ_TYPE_OBJECT		= 0x0001, // either inanimate objects
		OBJ_TYPE_BLADE		= 0x0002,
		OBJ_TYPE_CONTAINER	= 0x0004,
		
		OBJ_TYPE_AGENT		= 0x0100, // or living things
		OBJ_TYPE_PERSON		= 0x0200,
		OBJ_TYPE_LAST		= 0xf000
	};

	enum AttributeType
	{
		ATTRIB_TYPE_HEIGHT = 0x0000,
		ATTRIB_TYPE_WEIGHT,
		ATTRIB_TYPE_POSX,
		ATTRIB_TYPE_POSY,
		ATTRIB_TYPE_ALIVE,
		ATTRIB_TYPE_NONE,
		ATTRIB_TYPE_LAST = 0xffff
	};

	enum OperatorLayoutType
	{
		/*
		O for Object
		A for Attribute
		V for Value
		B indicates the boolean that can negate the result
		*/
		OP_LAYOUT_TYPE_OAVB,	// O has attrib A compared to V e.g. Dysh.height == 160
		OP_LAYOUT_TYPE_OAOAB,	// O1 has attrib A1, O2 has attrib A2, compared e.g. Al.strength > Dysh.weight
		OP_LAYOUT_TYPE_OOB,		// O1 and O2 have object level relationship e.g. Al owns Knife
		OP_LAYOUT_TYPE_TRUE,	// for true preconditions
		OP_LAYOUT_TYPE_UNDEFINED = 0xffff
	};

	enum OperandSemanticType
	{
		OP_SEMANTIC_TYPE_INSTRUMENT = 0x0000,
		
		OP_SEMANTIC_TYPE_OBJECT0,
		OP_SEMANTIC_TYPE_OBJECT1,
		
		OP_SEMANTIC_TYPE_DESTINATION,
		
		OP_SEMANTIC_TYPE_SUBJECT,
		
		OP_SEMANTIC_TYPE_NONE,
		OP_SEMANTIC_TYPE_UNDEFINED = 0xffff
	};

	enum OperatorType
	{
		OPER_TYPE_HAS_ATTIRB = 0x0000,
		
		OPER_TYPE_GREATER_THAN,
		OPER_TYPE_EQUAL,

		OPER_TYPE_PROXIMITY,

		OPER_TYPE_OWNS,

		OPER_TYPE_TRUE,

		OPER_TYPE_UNDEFINED = 0xffff
	};

	enum ActionType
	{
		ACTION_GOTO = 0x0000,
		ACTION_TAKE,
		ACTION_DROP,
		
		ACTION_CHOKE,
		ACTION_STAB,

		ACTION_TEST,
		ACTION_ACTION
	};

	enum ActionStatus
	{
		ACT_STAT_RUNNING,
		ACT_STAT_FAIL,
		ACT_STAT_SUCCESS,
		ACT_STAT_UNKNOWN,

		ACT_STAT_DONE		// mark the successful execution of a plan?
	};

	enum PlanStatus
	{
		PLAN_STAT_FAIL,
		PLAN_STAT_SUCCESS,
		PLAN_STAT_UNKNOWN
	};
}

#endif
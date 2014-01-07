#ifndef _GOAP_COMMONS_H_
#define _GOAP_COMMONS_H_

#include <iostream>

#ifdef _WIN32

#ifdef _DEBUG
#define _GOAP_DEBUG
#endif

#else

#ifndef NDEBUG
#define _GOAP_DEBUG
#endif

#endif

#ifdef _GOAP_DEBUG
#define DUMP(X) //std::cout << std::endl << X << std::endl;
#define DUMP_NL(X) //std::cout << X;
#else
#define DUMP(X)
#define DUMP_NL(X)
#endif

#ifdef _MSC_VER
#define _CPP_11_OVERRIDE override
#else
#define _CPP_11_OVERRIDE
#endif

#define NUMBER_OF_ROOMS 5

namespace GOAP
{
	struct Position
	{
		int x;
		int y;
	};

	enum ObjectType
	{
		OBJ_TYPE_NONE		= 0x0000,
		OBJ_TYPE_OBJECT		= 0x0001, // always and object
		OBJ_TYPE_BLADE		= 0x0002, // either inanimate objects
		OBJ_TYPE_BLUNT		= 0x0004,
		OBJ_TYPE_PROJECTILE = 0x0008,
		OBJ_TYPE_SQUEEZER	= 0x0010,
		OBJ_TYPE_CONTAINER	= 0x0020,
		OBJ_TYPE_ROOM		= 0x0040,
		OBJ_TYPE_PROP		= 0x0080,
		OBJ_TYPE_AGENT		= 0x0100, // or living things
		OBJ_TYPE_PERSON		= 0x0200,
		
		OBJ_TYPE_LAST		= 0xf000
	};

	enum AttributeType
	{
		ATTRIBUTE_HEIGHT = 0x0000,
		ATTRIBUTE_WEIGHT,
		ATTRIBUTE_ROOM,
		ATTRIBUTE_POSX,
		ATTRIBUTE_POSY,
		ATTRIBUTE_ALIVE,
		ATTRIBUTE_NONE,
		ATTRIBUTE_NUM_AGENTS,
		ATTRIBUTE_ID,
		ATTRIBUTE_INVENTORY,
		ATTRIBUTE_BEARER,
		ATTRIBUTE_LAST = 0xffff
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
		OP_LAYOUT_TYPE_TRUE,	// for actions with no preconditions
		OP_LAYOUT_TYPE_UNDEFINED = 0xffff
	};

	enum SemanticRole
	{
		SEMANTIC_ROLE_INSTRUMENT = 0x0000,

		SEMANTIC_ROLE_PATIENT,
		SEMANTIC_ROLE_PATIENT1,

		SEMANTIC_ROLE_GOAL,
		SEMANTIC_ROLE_LOCATIVE,

		SEMANTIC_ROLE_AGENT,

		SEMANTIC_ROLE_NONE,
		SEMANTIC_ROLE_UNDEFINED = 0xffff
	};

	enum OperatorType
	{
		OPERATOR_GREATER_THAN = 0x0000,

		OPERATOR_EQUAL,

		OPERATOR_PROXIMITY,

		OPERATOR_OWNS,
        OPERATOR_HAS,

		OPERATOR_TRUE,

		OPERATOR_UNDEFINED = 0xffff
	};

	enum ActionType
	{
		ACTION_GOTO		= 0x00,
		ACTION_WAITFOR	= 0x01,
		ACTION_WANDER	= 0x02,
		ACTION_TAKE		= 0x03,
		ACTION_DROP		= 0x04,

		ACTION_MURDER	= 0x10,	// murder
		ACTION_STAB		= 0x11,
		ACTION_BLUDGEON	= 0x12,
		ACTION_STRANGLE	= 0x13,
		ACTION_SHOOT	= 0x14,

		ACTION_TEST		= 0x20,
		ACTION_ACTION	= 0x40
	};

	enum ExecutionStatus
	{
		EXEC_STAT_INIT,
		EXEC_STAT_RUNNING,
		EXEC_STAT_FAIL,
		EXEC_STAT_SUCCESS,
		EXEC_STAT_SKIP,
		EXEC_STAT_PAUSED,
		EXEC_STAT_UNKNOWN,

		EXEC_STAT_MURDER,
		EXEC_STAT_NONE,

		EXEC_STAT_DONE		// mark the successful execution of a plan?
	};

	enum PlanStatus
	{
		PLAN_STAT_FAIL,
		PLAN_STAT_SUCCESS,
		PLAN_STAT_UNKNOWN
	};

	enum QuestionType
	{
		Q_POSITION,
		Q_POSSESSION,
		Q_ACTION
	};

	enum RoomName
	{
		ROOM_KITCHEN		= 0x01,
		ROOM_LIVING_ROOM	= 0x02,
		ROOM_DINING_ROOM	= 0x04,
		ROOM_BATHROOM		= 0x08,
		ROOM_BEDROOM		= 0x10
	};

	enum Gender
	{
		MALE,
		FEMALE
	};
}

#endif

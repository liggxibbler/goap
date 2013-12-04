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
		OBJ_TYPE_BLUNT		= 0x0004,
		OBJ_TYPE_PROJECTILE = 0x0008,
		OBJ_TYPE_SQUEEZER	= 0x0010,
		OBJ_TYPE_CONTAINER	= 0x0080,
		
		OBJ_TYPE_AGENT		= 0x0100, // or living things
		OBJ_TYPE_PERSON		= 0x0200,
		OBJ_TYPE_LAST		= 0xf000
	};

	enum EntityType
	{
		ENT_TYPE_ENTITY		= 0x0001, // always an entity

		ENT_TYPE_OBJECT		= 0x0002, // either inanimate object
		ENT_TYPE_BLADE		= 0x0004,
		ENT_TYPE_CONTAINER	= 0x0008,
		
		ENT_TYPE_AGENT		= 0x0100, // or living thing
		ENT_TYPE_PERSON		= 0x0200,
		
		ENT_TYPE_LAST		= 0xf000
	};

	enum AttributeType
	{
		ATTRIB_TYPE_HEIGHT = 0x0000,
		ATTRIB_TYPE_WEIGHT,
		ATTRIB_TYPE_ROOM,
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
		OP_LAYOUT_TYPE_TRUE,	// for actions with no preconditions
		OP_LAYOUT_TYPE_UNDEFINED = 0xffff
	};

	enum OperandSemanticRole
	{
		OP_SEMANTIC_ROLE_INSTRUMENT = 0x0000,
		
		OP_SEMANTIC_ROLE_PATIENT0,
		OP_SEMANTIC_ROLE_PATIENT1,
		
		OP_SEMANTIC_ROLE_DESTINATION,
		
		OP_SEMANTIC_ROLE_AGENT,
		
		OP_SEMANTIC_ROLE_NONE,
		OP_SEMANTIC_ROLE_UNDEFINED = 0xffff
	};

	enum OperatorType
	{
		OPER_TYPE_GREATER_THAN = 0x0000,		
		
		OPER_TYPE_EQUAL,

		OPER_TYPE_PROXIMITY,

		OPER_TYPE_OWNS,

		OPER_TYPE_TRUE,

		OPER_TYPE_UNDEFINED = 0xffff
	};

	enum ActionType
	{
		ACTION_GOTO,
		ACTION_WANDER,
		ACTION_TAKE,
		ACTION_DROP,
		
		ACTION_STAB,
		ACTION_BLUGEON,
		ACTION_STRANGLE,
		ACTION_SHOOT,

		ACTION_MURDER,

		ACTION_TEST,
		ACTION_ACTION
	};

	enum ActionStatus
	{
		ACT_STAT_INIT,
		ACT_STAT_RUNNING,
		ACT_STAT_FAIL,
		ACT_STAT_SUCCESS,
		//ACT_STAT_IDLE,
		ACT_STAT_UNKNOWN,		

		ACT_STAT_MURDER,
		ACT_STAT_NONE,

		ACT_STAT_DONE		// mark the successful execution of a plan?
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
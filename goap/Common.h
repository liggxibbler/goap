#ifndef _GOAP_COMMONS_H_
#define _GOAP_COMMONS_H_

#include <iostream>
#include <type_traits>

#ifdef _DEBUG
#define DUMP(X) std::cout << std::endl << X << std::endl;
#define DUMP_NL(X) std::cout << X;
#define GETKEY std::cin.get();
#else
#define DUMP(X)
#define DUMP_NL(X)
#define GETKEY
#endif

#define NUMBER_OF_ROOMS 5

namespace GOAP
{
	struct Position
	{
		int x;
		int y;
	};

	enum class ObjectType
	{
		NONE		= 0x0000,
		OBJECT		= 0x0001, // always and object
		BLADE		= 0x0002, // either inanimate objects
		BLUNT		= 0x0004,
		PROJECTILE = 0x0008,
		SQUEEZER	= 0x0010,
		CONTAINER	= 0x0020,
		ROOM		= 0x0040,
		PROP		= 0x0080,
		AGENT		= 0x0100, // or living things
		PERSON		= 0x0200,

		LAST		= 0xf000
	};

	inline ObjectType operator | (const ObjectType& lhs, const ObjectType& rhs)
	{
		return static_cast<ObjectType>(std::underlying_type<ObjectType>::type(lhs) |
			std::underlying_type<ObjectType>::type(rhs));
	}

	inline ObjectType operator & (const ObjectType& lhs, const ObjectType& rhs)
	{
		return static_cast<ObjectType>(std::underlying_type<ObjectType>::type(lhs) &
			std::underlying_type<ObjectType>::type(rhs));
	}

	enum class AttributeType
	{
		NONE,
		HEIGHT,
		WEIGHT,
		ROOM,
		POSX,
		POSY,
		ALIVE,
		NUM_AGENTS,
		ID,
		INVENTORY,
		BEARER,
		LAST = 0xffff
	};

	enum class OperatorLayoutType
	{
		/*
		O for Object
		A for Attribute
		V for Value
		B indicates the boolean that can negate the result
		*/
		OAVB,	// O has attrib A compared to V e.g. Dysh.height == 160
		OAOAB,	// O1 has attrib A1, O2 has attrib A2, compared e.g. Al.strength > Dysh.weight
		OOB,		// O1 and O2 have object level relationship e.g. Al owns Knife
		TRUE,	// for actions with no preconditions
		UNDEFINED = 0xffff
	};

	enum class SemanticRole
	{
		INSTRUMENT = 0x0000,

		PATIENT,
		PATIENT1,

		GOAL,
		LOCATIVE,

		AGENT,

		NONE,
		UNDEFINED = 0xffff
	};

	enum class OperatorType
	{
		NONE			= 0x0000,
		GREATER_THAN	= 0x0001,

		EQUAL,

		PROXIMITY,

		OWNS,
        HAS,

		TRUE,

		UNDEFINED		= 0xffff
	};

	enum class ActionType
	{
		NONE		= 0x00,
		GOTO		= 0x01,
		WAITFOR		= 0x02,
		WANDER		= 0x03,
		TAKE		= 0x04,
		DROP		= 0x05,

		MURDER		= 0x10,	// murder
		STAB		= 0x11,
		BLUDGEON	= 0x12,
		STRANGLE	= 0x13,
		SHOOT		= 0x14,

		TEST		= 0x20,
		ACTION		= 0x40
	};

	inline ActionType operator & (const ActionType& lhs, const ActionType& rhs)
	{
		return static_cast<ActionType>(std::underlying_type<ActionType>::type(lhs) &
			std::underlying_type<ActionType>::type(rhs));
	}

	inline ActionType operator | (const ActionType& lhs, const ActionType& rhs)
	{
		return static_cast<ActionType>(std::underlying_type<ActionType>::type(lhs) |
			std::underlying_type<ActionType>::type(rhs));
	}

	enum class ExecutionStatus
	{
		INIT,
		RUNNING,
		FAIL,
		SUCCESS,
		SKIP,
		PAUSED,
		UNKNOWN,

		MURDER,
		NONE,

		DONE		// mark the successful execution of a plan?
	};

	enum class PlanStatus
	{
		FAIL,
		SUCCESS,
		UNKNOWN
	};

	enum class QuestionType
	{
		POSITION,
		POSSESSION,
		ACTION
	};

	enum class RoomName
	{
		NONE           = 0x00,
		KITCHEN		= 0x01,
		LIVING_ROOM	= 0x02,
		DINING_ROOM	= 0x04,
		BATHROOM		= 0x08,
		BEDROOM		= 0x10
	};

	enum class Gender
	{
		MALE,
		FEMALE
	};
}

#endif

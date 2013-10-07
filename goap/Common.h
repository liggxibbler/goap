#ifndef _GOAP_COMMONS_H_
#define _GOAP_COMMONS_H_

namespace GOAP
{
	struct Position
	{
		int x;
		int y;
	};

	enum ObjectType
	{
		OBJ_TYPE_OBJECT = 0x0000, // either inanimate objects
		OBJ_TYPE_BLADE,
		OBJ_TYPE_AGENT = 0x8000, // or living things
		OBJ_TYPE_PERSON,
		OBJECT_TYPE_LAST = 0xffff
	};
};

#endif
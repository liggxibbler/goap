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
		OBJ_TYPE_CONTAINER,
		OBJ_TYPE_AGENT = 0x8000, // or living things
		OBJ_TYPE_PERSON,
		OBJ_TYPE_LAST = 0xffff
	};

	enum AttributeType
	{
		ATTRIB_TYPE_HEGIHT = 0x0000,
		ATTRIB_TYPE_WEIGHT,
		ATTRIB_TYPE_POSX,
		ATTRIB_TYPE_POSY,
		ATTRIB_TYPE_ALIVE,
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
		LAYOUT_TYPE_OAVB,	// O has attrib A compared to V e.g. Dysh.height == 160
		LAYOUT_TYPE_OOAB,	// O1 and O2 have attribute A compared e.g. Al.weight > Dysh.weight
		LAYOUT_TYPE_OAOAB,	// O1 has attrib A1, O2 has attrib A2, compared e.g. Al.strength > Dysh.weight
		LAYOUT_TYPE_OOB		// O1 and O2 have object level relationship e.g. Al owns Knife
	};

	enum OperandSemanticType
	{
		OP_SEMANTIC_TYPE_INSTRUMENT = 0x0000,
		OP_SEMANTIC_TYPE_OBJECT
	};
}

#endif
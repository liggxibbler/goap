#include "Argument.h"
#include "Object.h"

using namespace GOAP;

Argument::Argument() :
	type(OBJ_TYPE_NONE),
	semantic(SEMANTIC_ROLE_NONE),
	instance(NULL),
	attrib(ATTRIBUTE_NONE),
	value(0),
	strict(false)
{}

Argument::Argument(const Argument& other)
{
	attrib = other.attrib;
	instance = other.instance;
	semantic = other.semantic;
	type = other.type;
	value = other.value;
	strict = other.strict;
}

Argument& Argument::operator = (Argument& other)
{
	attrib = other.attrib;
	instance = other.instance;
	semantic = other.semantic;
	type = other.type;
	value = other.value;
	strict = other.strict;
	return *this;
}

bool Argument::MatchesTypeOf(const Argument& other)
{
	bool result = true;
	if(strict)
	{
		if( type != other.type )
		{
			result = false;
		}
	}
	else
	{
		if((type & OBJ_TYPE_OBJECT) == 0)
		{
			if( (type & other.type) == 0 )
			{
				result = false;
			}
		}
	}
	return result;
}

bool Argument::MatchesTypeOf(Object* other)
{
	bool result = true;
	int iType = type;
	if(strict)
	{
		if( iType != other->GetCompoundType() )
		{
			result = false;
		}
	}
	else
	{
		if((type & OBJ_TYPE_OBJECT) == 0)
		{
			if( (iType & other->GetCompoundType()) == 0 )
			{
				result = false;
			}
		}
	}
	return result;
}
#include "ConditionParameter.h"
#include "Object.h"

using namespace GOAP;

ConditionParameter::ConditionParameter() :
	type(OBJ_TYPE_NONE),
	semantic(SEMANTIC_ROLE_NONE),
	instance(NULL),
	attrib(ATTRIBUTE_NONE),
	value(0),
	strict(false)
{}

ConditionParameter::ConditionParameter(const ConditionParameter& other)
{
	attrib = other.attrib;
	instance = other.instance;
	semantic = other.semantic;
	type = other.type;
	value = other.value;
	strict = other.strict;
}

ConditionParameter& ConditionParameter::operator = (ConditionParameter& other)
{
	attrib = other.attrib;
	instance = other.instance;
	semantic = other.semantic;
	type = other.type;
	value = other.value;
	strict = other.strict;
	return *this;
}

bool ConditionParameter::MatchesTypeOf(const ConditionParameter& other)
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

bool ConditionParameter::MatchesTypeOf(Object* other)
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
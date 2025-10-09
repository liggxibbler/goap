#include "Argument.h"
#include "Object.h"

#include <iostream>

using namespace GOAP;

Argument::Argument() :
	type(ObjectType::NONE),
	semantic(SemanticRole::NONE),
	instance(nullptr),
	attrib(AttributeType::NONE),
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

bool Argument::MatchesTypeOf(const Argument& other) const
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
		if((type & ObjectType::OBJECT) == ObjectType::NONE)
		{
			if( (type & other.type) == ObjectType::NONE )
			{
				result = false;
			}
		}
	}
	return result;
}

bool Argument::MatchesTypeOf(const Object* other) const
{
	bool result = true;
	ObjectType iType = type;
	ObjectType otherCompoundType = other->GetCompoundType();
	if(strict)
	{
		if( iType != otherCompoundType)
		{
			std::cout << "strict " << (int)iType << std::endl;
			result = false;
		}
	}
	else
	{
		if((type & ObjectType::OBJECT) == ObjectType::NONE)
		{
			if( (iType & otherCompoundType) == ObjectType::NONE)
			{
				std::cout << (int)type << " " << (int)iType << " " << (int)otherCompoundType << std::endl;
				result = false;
			}
		}
	}
	return result;
}
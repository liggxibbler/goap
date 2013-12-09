#include "ConditionParameter.h"

using namespace GOAP;

ConditionParameter::ConditionParameter() :
type(OBJ_TYPE_OBJECT),
	semantic(SEMANTIC_ROLE_NONE),
	instance(NULL),
	attrib(ATTRIB_TYPE_NONE),
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
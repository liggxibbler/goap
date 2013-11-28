#ifndef _GOAP_CONDITIONPARAMETER_H_
#define _GOAP_CONDITIONPARAMETER_H_

#include "Common.h"

namespace GOAP
{
	class Object;
	struct ConditionParameter
	{
		ConditionParameter();		
		ConditionParameter(const ConditionParameter& other);
		ConditionParameter& operator = (ConditionParameter& other);
		
		//ObjectType			type;	// XIBB this should be an int, in order to allow multiple type flags
									// e.g. an object can be a blade >>> type = OBJECT | BLADE i.e. both
		int					type;
		OperandSemanticRole	semantic;
		Object*				instance;
		AttributeType		attrib;
		int					value;
		bool				strict;
	};
}

#endif
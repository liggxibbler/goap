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
		
		bool MatchesTypeOf(const ConditionParameter& other);
		bool MatchesTypeOf(Object* other);

		int					type;
		SemanticRole		semantic;
		Object*				instance;
		AttributeType		attrib;
		int					value;
		bool				strict;
	};
}

#endif
#ifndef _GOAP_Argument_H_
#define _GOAP_Argument_H_

#include "Common.h"

namespace GOAP
{
	class Object;
	struct Argument
	{
		Argument();		
		Argument(const Argument& other);
		Argument& operator = (Argument& other);
		
		bool MatchesTypeOf(const Argument& other);
		bool MatchesTypeOf(Object* other);

		ObjectType			type;
		SemanticRole		semantic;
		Object*				instance;
		AttributeType		attrib;
		int					value;
		bool				strict;
	};
}

#endif
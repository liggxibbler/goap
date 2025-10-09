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
		
		bool MatchesTypeOf(const Argument& other) const;
		bool MatchesTypeOf(const Object* other) const;

		ObjectType			type = ObjectType::NONE;
		SemanticRole		semantic = SemanticRole::NONE;
		Object*				instance = nullptr;
		AttributeType		attrib = AttributeType::NONE;
		int					value = -1;
		bool				strict = false;
	};
}

#endif
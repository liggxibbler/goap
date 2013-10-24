#ifndef _GOAP_CONDITION_H_
#define _GOAP_CONDITION_H_

#include "Common.h"
#include "Object.h"

namespace GOAP
{
	namespace Op
	{
		class OperatorManager;
	}
	struct ConditionParameter
	{
		ConditionParameter() :
		type(OBJ_TYPE_OBJECT),
		semantic(OP_SEMANTIC_TYPE_NONE),
		instance(NULL),
		attrib(ATTRIB_TYPE_NONE),
		value(0)
		{}
		
		ObjectType			type;	// XIBB this should be an int, in order to allow multiple type flags
									// e.g. an object can be a blade >>> type = OBJECT | BLADE i.e. both
		OperandSemanticType	semantic;
		Object*				instance;
		AttributeType		attrib;
		int					value;
	};

	class Condition
	{
	public:
		Condition();
		Condition(const Condition& other);
		~Condition();
		
		Condition(OperatorLayoutType layout, OperatorType oper);

		// == evaluates operand and attrib type equivalence,
		// does not take semantics or instances into account
		virtual bool operator == (Condition& other);
		

		OperatorLayoutType GetOperatorLayoutType();
		OperatorType GetOperatorType();
		ConditionParameter& operator [] (int index);
		
		const ConditionParameter* GetParams();
		int GetNumParams();

		void SetNegate(bool value);
		bool GetNegate();

		bool Evaluate(Op::OperatorManager* om);

		ConditionParameter* GetParamBySemantic(OperandSemanticType st);
		ConditionParameter* GetParamByType(ObjectType ot);
		ConditionParameter* GetParamByInstance(Object* obj);

	private:
		bool CreateArrays();

	protected:
		OperatorLayoutType m_layout;
		OperatorType m_operatorType;
		
		ConditionParameter* m_params;
		bool m_negate;

		int m_numParams;
		int m_topParam;
	};
}

#endif
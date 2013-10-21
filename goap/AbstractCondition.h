#ifndef _GOAP_ABSTRACT_CONDITION_H_
#define _GOAP_ABSTRACT_CONDITION_H_

#include "Common.h"
#include "Object.h"
#include "OperatorManager.h"

namespace GOAP
{
	struct ConditionParameter
	{
		ConditionParameter() :
		type(OBJ_TYPE_OBJECT),
		semantic(OP_SEMANTIC_TYPE_NONE),
		instance(NULL),
		attrib(ATTRIB_TYPE_NONE),
		value(0)
		{}
		
		ObjectType			type;
		OperandSemanticType	semantic;
		Object*				instance;
		AttributeType		attrib;
		int					value;
	};

	class AbstractCondition
	{
	public:
		AbstractCondition();
		AbstractCondition(const AbstractCondition& other);
		~AbstractCondition();
		
		AbstractCondition(OperatorLayoutType layout, OperatorType oper);

		// == evaluates operand and attrib type equivalence,
		// does not take semantics or instances into account
		virtual bool operator == (AbstractCondition& other);
		

		OperatorLayoutType GetOperatorLayoutType();
		OperatorType GetOperatorType();
		ConditionParameter& operator [] (int index);
		
		const ConditionParameter* GetParams();

		void SetNegate(bool value);
		bool GetNegate();

		bool Evaluate(Op::OperatorManger* om);

	private:
		bool CreateArrays();

	protected:
		OperatorLayoutType m_layout;
		OperatorType m_operatorType;
		
		ConditionParameter* m_params;
		bool m_negate;
		
		/*CappedStack<AttributeType>* m_objectTypeParams;
		CappedStack<ObjectType>* m_objectTypeParams;
		CappedStack<int>* m_objectTypeParams;*/

		int m_numParams;
		int m_topParam;
	};
}

#endif
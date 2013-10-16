#ifndef _GOAP_ABSTRACT_CONDITION_H_
#define _GOAP_ABSTRACT_CONDITION_H_

#include "Common.h"

namespace GOAP
{
	class AbstractCondition
	{
	public:
		AbstractCondition();
		AbstractCondition(const AbstractCondition& other);
		~AbstractCondition();
		
		AbstractCondition(OperatorLayoutType layout, OperatorType oper);

		bool operator == (AbstractCondition& other);

		bool AddObjectTypeParam(ObjectType ot);
		bool AddAttribParam(AttributeType at);
		bool AddValue(int value);
		void SetNegate(bool value);

		OperatorLayoutType GetOperatorLayoutType();
		OperatorType GetOperatorType();
		AttributeType* GetAttributes();
		int* GetValues();
		bool GetNegate();

	private:
		bool CreateArrays();

	protected:
		OperatorLayoutType m_layout;
		OperatorType m_operatorType;
		ObjectType* m_objectTypeParams;
		AttributeType* m_attribParams;
		int* m_values;
		bool m_negate;
		
		/*CappedStack<AttributeType>* m_objectTypeParams;
		CappedStack<ObjectType>* m_objectTypeParams;
		CappedStack<int>* m_objectTypeParams;*/

		int m_topObjectParams;
		int m_topAttribParams;
		int m_topValues;

		int m_numObjectParams;
		int m_numAttribParams;
		int m_numValues;
	};
}

#endif
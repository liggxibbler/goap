#ifndef _GOAP_CONDITION_H_
#define _GOAP_CONDITION_H_

#include "Common.h"
#include "ConditionParameter.h"
#include "Object.h"

namespace GOAP
{
	namespace Op
	{
		class OperatorManager;
	}
	
	class Condition
	{
	public:
		Condition();
		Condition(const Condition& other);
		~Condition();
		
		Condition(OperatorLayoutType layout, OperatorType oper);

		// == evaluates operand and attrib type equivalence,
		// does not take semantics or instances into account
		bool operator == (Condition& other);
		

		OperatorLayoutType GetOperatorLayoutType();
		OperatorType GetOperatorType();
		
		ConditionParameter& operator [] (int index);
		ConditionParameter& GetParamByIndex(int index);

		const ConditionParameter* GetParams();
		int GetNumParams();

		void SetNegate(bool value);
		bool GetNegate();

		bool Evaluate(Op::OperatorManager* om);

		ConditionParameter* GetParamBySemantic(OperandSemanticRole st);
		ConditionParameter* GetParamByType(ObjectType ot);
		ConditionParameter* GetParamByInstance(Object* obj);

		void CopySemantics(Condition& other);

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
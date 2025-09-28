#ifndef _GOAP_CONDITION_H_
#define _GOAP_CONDITION_H_

#include "Common.h"
#include "Argument.h"
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
		bool operator == (const Condition& other) const;
		bool EqualInstance(const Condition& other);

		OperatorLayoutType GetOperatorLayoutType() const;
		OperatorType GetOperatorType() const;
		
		const Argument& operator [] (int index) const;
		Argument& GetParamByIndex(int index);

		const Argument* GetParams() const;
		int GetNumParams() const;

		void SetNegate(bool value);
		bool GetNegate() const;

		bool Evaluate(Op::OperatorManager* om) const;

		Argument* GetParamBySemantic(SemanticRole st);
		Argument* GetParamByType(ObjectType ot);
		Argument* GetParamByInstance(Object* obj);

		void CopySemantics(const Condition& other) const;

	private:
		bool CreateArrays();

	protected:
		OperatorLayoutType m_layout;
		OperatorType m_operatorType;
		
		Argument* m_params;
		bool m_negate;

		int m_numParams;
		int m_topParam;
	};
}

#endif
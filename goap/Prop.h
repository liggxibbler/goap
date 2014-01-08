#ifndef _GOAP_PROP_H_
#define _GOAP_PROP_H_

#include "Object.h"
namespace GOAP
{
	class Prop : public Object
	{
	public:
		Prop();
		Prop(std::string name, Object* owner = NULL);
		Prop(const Prop& other);
		~Prop();

	public:
		//virtual operator ObjectType () _CPP_11_OVERRIDE;
		virtual bool Update(Op::OperatorManager* om, RoomManager* rm, int turn) _CPP_11_OVERRIDE;
		virtual int GetCompoundType() _CPP_11_OVERRIDE;
		virtual void Examine() _CPP_11_OVERRIDE;
		virtual Object* Clone() _CPP_11_OVERRIDE;

		void MayBeFoundIn(int);
		bool CanBeMurderWeapon();
		Object* GetBearer();
		void SetBearer(Object* bearer);

		virtual void IncreaseValue();
		virtual int GetValue();

		virtual int GetNumberOfInstances();
		
		std::string GetDescription();
		void SetDescription(std::string desc);

	protected:

		virtual void InitAttribMap() _CPP_11_OVERRIDE;
		Object* m_bearer;
		int	m_bearerID;
		int m_canBeFoundIn;
		std::string m_description;

	private:
		static int s_value;
		static int s_numInstances;
	};
}
#endif
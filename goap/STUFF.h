#ifndef _GOAP_STUFF_H_
#define _GOAP_STUFF_H_

#include "Object.h"
namespace GOAP
{
	class STUFF : public Object
	{
	public:
		STUFF();
		STUFF(std::string name, Object* owner = NULL);
		STUFF(const STUFF& other);
		~STUFF();

	public:
		virtual operator ObjectType () _CPP_11_OVERRIDE;
		virtual bool Update(Op::OperatorManager* om, RoomManager* rm, int turn) _CPP_11_OVERRIDE;
		virtual int GetCompoundType() _CPP_11_OVERRIDE;
		virtual void MayBeFoundIn(int) _CPP_11_OVERRIDE;
		virtual void Examine() _CPP_11_OVERRIDE;
		virtual bool CanBeMurderWeapon() _CPP_11_OVERRIDE;
		virtual Object* Clone() _CPP_11_OVERRIDE;

		Object* GetBearer();
		void SetBearer(Object* bearer);

	protected:

		virtual void InitAttribMap() _CPP_11_OVERRIDE;
		Object* m_bearer;
		int m_canBeFoundIn;

	};
}
#endif
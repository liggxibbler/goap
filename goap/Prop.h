#ifndef _GOAP_PROP_H_
#define _GOAP_PROP_H_

#include "Object.h"
namespace GOAP
{
	class Prop : public Object
	{
	public:
		Prop();
		Prop(std::string name, Object* owner = nullptr);
		Prop(const Prop& other);
		~Prop();

	public:
		//virtual operator ObjectType () override;
		virtual void Update(Planner & planner, int turn) override;

		virtual ObjectType GetCompoundType() const override;
		void SetCompoundType(ObjectType compundType);

		virtual void Examine() override;
		virtual Object* Clone() override;

		void MayBeFoundIn(RoomName);
		RoomName MayBeFoundIn();
		bool CanBeMurderWeapon();
		Object* GetBearer() const;
		void SetBearer(Object* bearer);

		virtual void IncreaseValue();
		virtual int GetValue();

		virtual int GetNumberOfInstances();

		std::string GetDescription();
		void SetDescription(std::string desc);

	protected:

		virtual void InitAttribMap() override;
		Object* m_bearer;
		int	m_bearerID;
		RoomName m_canBeFoundIn;
		std::string m_description;
		ObjectType m_type;

	private:
		static int s_value;
		static int s_numInstances;
	};
}
#endif

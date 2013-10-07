#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

namespace GOAP
{
	class Object;

	class Action
	{
	public:
		virtual void Execute() = 0;
	protected:
		Object* m_params;
	};
}
#endif
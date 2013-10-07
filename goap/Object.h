#ifndef _GOAP_OBJECT_H_
#define _GOAP_OBJECT_H_

namespace GOAP
{
	class Object
	{
	public:
		Object();
		Object(const Object& other);
		~Object();

	protected:
		Position m_position;
	};
}

#endif
#include "Object.h"

using namespace GOAP;

Object::Object()
{
	m_attribs[ATTRIB_TYPE_POSX] = &m_posx;
	m_attribs[ATTRIB_TYPE_POSY] = &m_posy;
}

Object::Object(const Object& other)
{
	// TBI
}

Object::~Object()
{
	// TBI
}
	
		
int Object::GetAttrib(AttributeType at)
{
	return *m_attribs[at];
}

void Object::SetAttrib(AttributeType at, int val)
{
	*m_attribs[at] = val;
}

Object::operator GOAP::ObjectType()
{
	return OBJ_TYPE_OBJECT;
}

int& Object::operator[] (AttributeType at)
{
	return *m_attribs[at];
}
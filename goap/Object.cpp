#include "Object.h"

using namespace GOAP;

int Object::s_numObjects = 0;

Object::Object()
{
	m_attribs[ATTRIB_TYPE_POSX] = &m_posx;
	m_attribs[ATTRIB_TYPE_POSY] = &m_posy;
	m_owner = NULL;
	m_name = "ANONYMOUS";
	m_id = s_numObjects++;
}


Object::Object(std::string name, Object* owner)
{
	m_attribs[ATTRIB_TYPE_POSX] = &m_posx;
	m_attribs[ATTRIB_TYPE_POSY] = &m_posy;
	m_owner = owner;
	m_name = name;
	m_id = s_numObjects++;
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
#include "Blade.h"

using namespace GOAP;

int Blade::s_value = 0;

Blade::Blade() : Prop()
{
}

Blade::Blade(std::string name) : Prop(name)
{
}

Blade::Blade(const Blade& other)
{
}

Blade::~Blade()
{
}

//Blade::operator GOAP::ObjectType()
//{
//	return OBJ_TYPE_BLADE;
//}

int Blade::GetCompoundType()
{
	return OBJ_TYPE_BLADE | OBJ_TYPE_OBJECT | OBJ_TYPE_PROP;
}

bool Blade::CanBeMurderWeapon()
{
	return true;
}

void Blade::IncreaseValue()
{
	s_value += 100;
}

int Blade::GetValue()
{
	return s_value;
}
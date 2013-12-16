#include "Blade.h"

using namespace GOAP;

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
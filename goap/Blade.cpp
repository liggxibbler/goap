#include "Blade.h"

using namespace GOAP;

Blade::Blade() : Object()
{
}

Blade::Blade(std::string name) : Object(name)
{
}

Blade::Blade(const Blade& other)
{
}

Blade::~Blade()
{
}

Blade::operator GOAP::ObjectType()
{
	return OBJ_TYPE_BLADE;
}

int Blade::GetCompoundType()
{
	return OBJ_TYPE_BLADE | OBJ_TYPE_OBJECT;
}

bool Blade::CanBeMurderWeapon()
{
	return true;
}
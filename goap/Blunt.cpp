#include "Blunt.h"

using namespace GOAP;

Blunt::Blunt() : Prop()
{
}

Blunt::Blunt(std::string name) : Prop(name)
{
}

Blunt::Blunt(const Blunt& other)
{
}

Blunt::~Blunt()
{
}

//Blunt::operator GOAP::ObjectType()
//{
//	return OBJ_TYPE_BLUNT;
//}

int Blunt::GetCompoundType()
{
	return OBJ_TYPE_BLUNT | OBJ_TYPE_OBJECT | OBJ_TYPE_PROP;
}

bool Blunt::CanBeMurderWeapon()
{
	return true;
}
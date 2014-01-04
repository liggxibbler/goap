#include "Projectile.h"

using namespace GOAP;

int Projectile::s_value = 0;

Projectile::Projectile() : Prop()
{
}

Projectile::Projectile(std::string name) : Prop(name)
{
}

Projectile::Projectile(const Projectile& other)
{
}

Projectile::~Projectile()
{
}

//Projectile::operator GOAP::ObjectType()
//{
//	return OBJ_TYPE_PROJECTILE;
//}

int Projectile::GetCompoundType()
{
	return OBJ_TYPE_PROJECTILE | OBJ_TYPE_OBJECT | OBJ_TYPE_PROP;
}

bool Projectile::CanBeMurderWeapon()
{
	return true;
}

void Projectile::IncreaseValue()
{
	s_value += 100;
}

int Projectile::GetValue()
{
	return s_value;
}
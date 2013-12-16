#include "Projectile.h"

using namespace GOAP;

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

Projectile::operator GOAP::ObjectType()
{
	return OBJ_TYPE_PROJECTILE;
}

int Projectile::GetCompoundType()
{
	return OBJ_TYPE_PROJECTILE | OBJ_TYPE_OBJECT | OBJ_TYPE_PROP;
}

bool Projectile::CanBeMurderWeapon()
{
	return true;
}
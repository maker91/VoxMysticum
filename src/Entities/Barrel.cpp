#include "Barrel.hpp"
#include "ResourceManager.hpp"
#include "Resources/TMD.hpp"
#include "EntityFlags.hpp"

Barrel::Barrel(GameState &gm, const sf::Vector2f &pos)
: Hurtable(gm, sf::Vector3f(pos.x, pos.y, 0.f), sf::Vector3f(64.f, 24.f, 56.f),
           ResourceManager::get<TMD>("barrel.tmd"), 1)
{
	setFlags(EntityFlags::COLLIDE);
}

void Barrel::onCollide(Entity &other)
{

}

void Barrel::tick(float dt)
{
	Hurtable::tick(dt);
}

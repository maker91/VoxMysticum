#include "Magic.hpp"
#include "ResourceManager.hpp"
#include "TMD.hpp"
#include "SoundEngine.hpp"
#include "GameState.hpp"
#include "EntityFlags.hpp"

#include <cmath>

Magic::Magic(GameState &gm, const sf::Vector2f &pos, const sf::Vector2f &vel,
	const sf::Vector2f &dir, float speed, float angle, float g)
	: g(g), direction(dir), hit(false),
	Entity(gm, sf::Vector3f(pos.x, pos.y, 32.f), sf::Vector3f(32.f, 24.f, 28.f),
	*ResourceManager::get<TMD>("magic_arcane.tmd"), 2)
{
	lob = speed*std::sin(3.1451f*angle / 180.f);
	velocity = vel + dir*speed*std::cos(3.1451f*angle / 180.f);
	anim.play("idle", true);

	light = std::static_pointer_cast<Light>(game.spawnLight(static_cast<IBaseEntity *>(this), 
		height, sf::Color(105, 0, 105), 0.8f, 100.f));
	setFlags(EntityFlags::GLOW | EntityFlags::COLLIDE);

	SoundEngine::playSound("arcane.wav");
}

void Magic::tick(float dt)
{
	Entity::tick(dt);

	lob -= g*dt;
	height += lob*dt;
	move(velocity*dt);

	light->setHeight(height);
	 
	if (!hit && height <= 12.f)
		destroy();
}

void Magic::onCollide(Entity &other)
{
	destroy();
	other.hurt(25);
}

void Magic::destroy()
{
	if (hasFlags(EntityFlags::REMOVE))
		return;

	g = 0.f;
	lob = 0.f;
	velocity = { 0.f, 0.f };

	SoundEngine::playSound("arcane_hit.wav");
	setFlags(EntityFlags::REMOVE);
	light->setParent(nullptr);
	light->setFlags(EntityFlags::REMOVE);
	game.spawnEffect(getPosition() - sf::Vector2f(0.f, height), 
		*ResourceManager::get<TMD>("magic_arcane.tmd"), "hit")->setFlags(EntityFlags::GLOW | EntityFlags::ABOVE);
}

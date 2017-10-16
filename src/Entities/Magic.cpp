#include "Magic.hpp"
#include "Config.hpp"
#include "ResourceManager.hpp"
#include "Resources/TMD.hpp"
#include "SoundEngine.hpp"
#include "States/GameState.hpp"
#include "EntityFlags.hpp"

#include <cmath>

Magic::Magic(GameState &gm, const sf::Vector2f &pos, const sf::Vector2f &vel,
	const sf::Vector2f &dir, float speed, float angle, int dmg, float g)
	: g(g), direction(dir), hit(false), dmg(dmg),
	Entity(gm, sf::Vector3f(pos.x, pos.y, 32.f), sf::Vector3f(32.f, 24.f, 28.f),
	*ResourceManager::get<TMD>(Config::config.get("magic-sprite", "magic_arcane.tmd").asString()), 2)
{
	lob = speed*std::sin(3.1451f*angle / 180.f);
	velocity = vel + dir*speed*std::cos(3.1451f*angle / 180.f);
	anim.play("idle", true);

	light = std::static_pointer_cast<Light>(game.spawnLight(static_cast<IBaseEntity *>(this), 
		height, sf::Color(105, 0, 0), 0.8f, 100.f));
	setFlags(EntityFlags::GLOW | EntityFlags::COLLIDE);
	setRotation(static_cast<float>(-180.f * std::atan2(velocity.y, -velocity.x) / M_PI));

	SoundEngine::playSound("arcane2.wav");
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
	other.hurt(dmg);
}

void Magic::destroy()
{
	if (hasFlags(EntityFlags::REMOVE))
		return;

	SoundEngine::playSound("arcane_hit.wav");
	setFlags(EntityFlags::REMOVE);
	light->setParent(nullptr);
	light->setFlags(EntityFlags::REMOVE);
	game.spawnEffect(getPosition() - sf::Vector2f(0.f, height), 
		*ResourceManager::get<TMD>("magic_arcane.tmd"), "hit")->setFlags(EntityFlags::GLOW | EntityFlags::ABOVE);

	// create two perpendicular magics
	//sf::Vector2f perp = sf::Vector2f(direction.y, direction.x);
	//game.spawnEntity("magic", getPosition(), perp*10.f, perp, 400.f, 3.5f, 100.f);
	//game.spawnEntity("magic", getPosition(), -perp*10.f, -perp, 400.f, 3.5f, 100.f);

	g = 0.f;
	lob = 0.f;
	velocity = { 0.f, 0.f };
}

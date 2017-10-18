#include "Bat.hpp"
#include "ResourceManager.hpp"
#include "Resources/TMD.hpp"
#include "EntityFlags.hpp"
#include "States/GameState.hpp"
#include "RNG.hpp"

Bat::Bat(GameState &gm, const sf::Vector2f &pos)
: Hurtable(gm, sf::Vector3f(pos.x, pos.y, 42.f), sf::Vector3f(48.f, 24.f, 32.f),
*ResourceManager::get<TMD>("bat.tmd").get(), 1), nextflap(1.0f)
{
	setFlags(EntityFlags::COLLIDE | EntityFlags::GLOW | EntityFlags::HURTFUL);
}

Bat::~Bat()
{
	
}

void Bat::onCollide(Entity &other)
{
	
}

void Bat::onHurt(int d)
{
	SoundEngine::playSound("bat_hit.wav", 100, 0.6f);
	if (getHealth() <= 0)
		remove();
}

void Bat::tick(float dt)
{
	nextflap -= dt;
	if (nextflap <= 0.f)
	{
		nextflap = 1.0f;
		SoundEngine::playSound("flap.wav", 50.f, 0.25f);
	}

	auto target = game.getPlayer();
	sf::Vector2f p = target->getPosition() - getPosition();
	float len = std::sqrt(p.x*p.x + p.y*p.y);
	float mag = RNG::unmanaged.generate(0.f, 100.f*dt);

	move(mag*p / len);
	Hurtable::tick(dt);
}

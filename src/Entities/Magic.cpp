#include "Magic.hpp"
#include "Config.hpp"
#include "ResourceManager.hpp"
#include "SoundEngine.hpp"
#include "States/GameState.hpp"
#include "EntityFlags.hpp"

#include <cmath>

Magic::Magic(GameState &gm, std::shared_ptr<const TMD> tex, const sf::Vector2f &pos, const sf::Vector2f &vel,
			 const sf::Vector2f &dir, const sf::Color &col, float speed, float angle, int dmg, float g)
        : g(g), direction(dir), hit(false), dmg(dmg),
          Entity(gm, sf::Vector3f(pos.x, pos.y, 32.f), sf::Vector3f(32.f, 24.f, 28.f), std::move(tex), 2)
{
	lob = speed*std::sin(3.1451f*angle / 180.f);
	velocity = vel + dir*speed*std::cos(3.1451f*angle / 180.f);
	anim.play("idle", true);

	light = std::static_pointer_cast<Light>(game.spawnLight(static_cast<BaseEntity *>(this),
		height, col, 0.8f, 100.f));
	setFlags(EntityFlags::GLOW | EntityFlags::COLLIDE);

	SoundEngine::playSound("arcane2.wav");
}

void Magic::tick(float dt)
{
	Entity::tick(dt);

	lob -= g*dt;
	height += lob*dt;
	move(velocity*dt);
    float absx;
    if (std::abs(direction.x) > 0.f)
        absx = direction.x/std::abs(direction.x);
    else
        absx = 0.f;
    setRotation(static_cast<float>(-absx*lob/4.f - 180.f*(std::atan2(velocity.y, -velocity.x))/M_PI));

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
	game.spawnEffect(getPosition() - sf::Vector2f(0.f, height), tmd, "hit")->setFlags(EntityFlags::GLOW | EntityFlags::ABOVE);

	g = 0.f;
	lob = 0.f;
	velocity = { 0.f, 0.f };
}

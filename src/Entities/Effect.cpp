#include "Effect.hpp"
#include "EntityFlags.hpp"
#include "States/GameState.hpp"


Effect::Effect(GameState &gm, const sf::Vector2f &pos, std::shared_ptr<const TMD> tex, const std::string &a, bool loop)
		: Entity(gm, sf::Vector3f(pos.x, pos.y, 0.f), sf::Vector3f(), tex)
{
	setFlags(EntityFlags::GLOW);
	anim.play(a, loop);
}

void Effect::tick(float dt)
{
	Entity::tick(dt);

	if (!anim.isPlaying() && !hasFlags(EntityFlags::REMOVE))
		remove();
}

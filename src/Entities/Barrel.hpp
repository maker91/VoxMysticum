#include "Hurtable.hpp"

class Barrel : public Hurtable
{
public:
	Barrel(GameState &game, const sf::Vector2f &pos);
	void tick(float dt);
	void onCollide(Entity &other);
};
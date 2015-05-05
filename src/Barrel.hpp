#include "Entity.hpp"

class Barrel : public Entity
{
public:
	Barrel(GameState &game, const sf::Vector2f &pos);
	void tick(float dt);
	void onCollide(Entity &other);
};
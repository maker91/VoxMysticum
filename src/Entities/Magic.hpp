#pragma once

#include <SFML/System/Vector2.hpp>
#include "Entity.hpp"
#include "Light.hpp"

class GameState;

class Magic : public Entity
{
public:
	Magic(GameState &, std::shared_ptr<const TMD>, const sf::Vector2f &pos, const sf::Vector2f &vel,
		  const sf::Vector2f &dir, const sf::Color &col, float speed = 600.f, float angle = 2.f,
          int dmg = 25, float g = 120.f);
	
	void tick(float dt);

	void onCollide(Entity &other);
	void destroy();

private:
	std::shared_ptr<Light> light;

	bool hit;
	sf::Vector2f velocity;
	sf::Vector2f direction;
	float lob;
	float g;
	int dmg;
};

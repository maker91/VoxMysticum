#pragma once

#include <SFML/System/Vector2.hpp>
#include "Entity.hpp"

class GameState;

class Player : public Entity
{
public:
	Player(GameState &game, const sf::Vector2f &pos = sf::Vector2f(0.f, 0.f), 
		float acceleration = 2500.f, float maxSpeed = 300.f, float friction = 6.f,
		float shootDelay = 0.6f);

	void tick(float dt);
	void shoot(const sf::Vector2f &vel, const sf::Vector2f &dir);
	void onCollide(Entity &other);

private:
	sf::Vector2f velocity;
	float acceleration;
	float maxSpeed;
	float friction;
	float shootDelay;
	float nextShoot;
};
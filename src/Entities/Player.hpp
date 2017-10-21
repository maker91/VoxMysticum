#pragma once

#include <SFML/System/Vector2.hpp>
#include "PAttributes.hpp"
#include "Hurtable.hpp"
#include "Characters/CharacterDef.hpp"

class GameState;

class Player : public Hurtable
{
public:
    Player(GameState &game, CharacterDef def, const sf::Vector2f &pos = sf::Vector2f(0.f, 0.f),
           float acceleration = 2500.f, float friction = 6.f);

    void onHurt(int d) override;

    void tick(float dt);
	void shoot(const sf::Vector2f &vel, const sf::Vector2f &dir);
	void onCollide(Entity &other);

public:
    PAttributes pAttrs;

private:
    CharacterDef cDef;
	sf::Vector2f velocity;
	float acceleration;
	float friction;
	float nextShoot;
};

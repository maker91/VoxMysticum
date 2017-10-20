#pragma once

#include <SFML/Graphics.hpp>
#include <Resources/TMD.hpp>
#include <AnimPlayer.hpp>
#include <TypeFactory.hpp>
#include "BaseTMDDrawable.hpp"


class GameState;

class Entity : public BaseTMDDrawable
{
public:
	Entity(GameState &game, const sf::Vector3f &pos, const sf::Vector3f &size,
		   std::shared_ptr<const TMD> tex, std::uint64_t mask = 0);

	void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;

    virtual bool hurt(int d) {return false;};
    virtual bool heal(int h) {};

	virtual float getHeight() const;
	virtual void setHeight(float);
	sf::IntRect getAABB() const;
	sf::IntRect getZAABB() const;

	virtual bool shouldCollide(const Entity& other) const;

protected:
	virtual void onCollide(Entity &other) {};

protected:
	GameState &game;

	float height;
	sf::Vector3f size;
	std::uint64_t collision_mask;

public:
	static void checkCollision(Entity &a, Entity &b);
};

using EntityFactory = TypeFactory<std::string, Entity>;

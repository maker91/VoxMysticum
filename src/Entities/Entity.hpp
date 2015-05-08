#pragma once

#include <SFML/Graphics.hpp>

#include "IBaseEntity.hpp"
#include "../Resources/TMD.hpp"
#include "../AnimPlayer.hpp"

class GameState;

class Entity : public IBaseEntity
{
public:
	Entity(GameState &game, const sf::Vector3f &pos, const sf::Vector3f size, 
		TMD &tex, std::uint64_t mask = 0, int health = 100);

	void setTexture(const TMD &);

	virtual void draw(sf::RenderTarget &rt, sf::RenderStates states) const;
	virtual void tick(float dt);
	virtual void render(sf::RenderTarget &diffuse, sf::RenderTarget &glow);

	float getHeight() const;
	void setHeight(float);
	sf::IntRect getAABB() const;
	sf::IntRect getZAABB() const;

	void hurt(int d);
	void setHealth(int h);
	int getHealth() const;

	virtual void onHurt(int d) {};

protected:
	virtual void onCollide(Entity &other) {};

protected:
	AnimPlayer anim;
	GameState &game;
	const TMD *tmd;

	float height;
	sf::Vector3f size;
	std::uint64_t collision_mask;

	int health;
	float hurtFlash;
public:
	static void checkCollision(Entity &a, Entity &b);
};

using EntityFactory = TypeFactory<std::string, Entity>;

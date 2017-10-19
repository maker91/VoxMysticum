#pragma once

#include <SFML/Graphics.hpp>

#include "IBaseEntity.hpp"
#include "../Resources/TMD.hpp"
#include "../AnimPlayer.hpp"

class GameState;

class Entity : public IBaseEntity
{
public:
	Entity(GameState &game, const sf::Vector3f &pos, const sf::Vector3f &size,
		TMD &tex, std::uint64_t mask = 0);

	void setTexture(const TMD &);

	void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;
	void tick(float dt) override;
	virtual void render(sf::RenderTarget &diffuse, sf::RenderTarget &glow);

    virtual bool hurt(int d) {return false;};
    virtual bool heal(int h) {};

	float getHeight() const;
	void setHeight(float);
	sf::IntRect getAABB() const;
	sf::IntRect getZAABB() const;

	virtual bool shouldCollide(const Entity& other) const;

protected:
	virtual void onCollide(Entity &other) {};

protected:
	AnimPlayer anim;
	GameState &game;
	const TMD *tmd;

	float height;
	sf::Vector3f size;
	std::uint64_t collision_mask;

public:
	static void checkCollision(Entity &a, Entity &b);
};

using EntityFactory = TypeFactory<std::string, Entity>;

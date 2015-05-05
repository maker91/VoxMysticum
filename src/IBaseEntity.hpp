#pragma once

#include <cstdint>
#include <memory>
#include <SFML/Graphics.hpp>

#include "IDFactory.hpp"
#include "TypeFactory.hpp"
#include "IBaseEntity.hpp"
#include "Texture.hpp"
#include "AnimPlayer.hpp"

class IBaseEntity : virtual public sf::Transformable, public sf::Drawable
{
public:
	IBaseEntity(const sf::Vector2f &pos);
	IBaseEntity(const sf::Vector2f &pos, const Texture &tex);

	bool hasFlags(std::uint64_t flag) const;
	std::uint64_t getFlags() const;
	void setFlags(std::uint64_t flag);
	void unsetFlags(std::uint64_t flag);
	void toggleFlags(std::uint64_t flag);

	void remove();

	void setParent(IBaseEntity *);
	IBaseEntity *getParent() const;
	uid getEntId() const;

	const Texture &getTexture() const;
	void setTexture(const Texture &, bool resetRect = true);
	void setTexture(const Texture &, const sf::IntRect &rect);

	const sf::IntRect &getTextureRect() const;
	void setTextureRect(const sf::IntRect &rect);
	const sf::Color &getColor() const;
	void setColor(const sf::Color &c);

	sf::Vector2f getAbsolutePosition() const;

	virtual void tick(float dt) = 0;

protected:
	virtual void draw(sf::RenderTarget &rt, sf::RenderStates states) const;

private:
	uid entId;
	std::uint64_t flags;
	IBaseEntity *parent;
	const Texture *tex;
	sf::IntRect rect;
	sf::Color col;
};
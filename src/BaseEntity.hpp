#pragma once

#include <cstdint>
#include <memory>
#include <SFML/Graphics.hpp>

#include "IDFactory.hpp"
#include "TypeFactory.hpp"
#include "Resources/Texture.hpp"
#include "AnimPlayer.hpp"


class BaseEntity : virtual public sf::Transformable
{
public:
	BaseEntity(const sf::Vector2f &pos);

	bool hasFlags(std::uint64_t flag) const;
	std::uint64_t getFlags() const;
	void setFlags(std::uint64_t flag);
	void unsetFlags(std::uint64_t flag);
	void toggleFlags(std::uint64_t flag);

	void remove();

	void setParent(BaseEntity *);
	BaseEntity *getParent() const;
	uid getEntId() const;

	sf::Vector2f getAbsolutePosition() const;

	virtual void tick(float dt) {};

private:
	uid entId;
	std::uint64_t flags;
	BaseEntity *parent;
};

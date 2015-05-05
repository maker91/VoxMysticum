#include "IBaseEntity.hpp"
#include "EntityFlags.hpp"

IBaseEntity::IBaseEntity(const sf::Vector2f &pos)
: entId(IDFactory::generate("entId")), flags(0), parent(nullptr), tex(nullptr)
{
	setPosition(pos);
}

IBaseEntity::IBaseEntity(const sf::Vector2f &pos, const Texture &t)
: entId(IDFactory::generate("entId")), flags(0), parent(nullptr), tex(&t)
{
	setPosition(pos);
}

bool IBaseEntity::hasFlags(std::uint64_t flag) const
{
	return ((flags&flag) == flag);
}

std::uint64_t IBaseEntity::getFlags() const
{
	return flags;
}

void IBaseEntity::setFlags(std::uint64_t flag)
{
	flags |= flag;
}

void IBaseEntity::unsetFlags(std::uint64_t flag)
{
	flags &= (~flag);
}

void IBaseEntity::toggleFlags(std::uint64_t flag)
{
	flags ^= flag;
}

std::uint32_t IBaseEntity::getEntId() const
{
	return entId;
}

void IBaseEntity::remove()
{
	setFlags(EntityFlags::REMOVE);
}

void IBaseEntity::setParent(IBaseEntity *p)
{
	parent = p;
}

IBaseEntity *IBaseEntity::getParent() const
{
	return parent;
}

const Texture &IBaseEntity::getTexture() const
{
	return *tex;
}

void IBaseEntity::setTexture(const Texture &t, bool resetRect)
{
	tex = &t;
	if (resetRect)
		rect = sf::IntRect({ 0, 0 }, static_cast<sf::Vector2i>(t.getSize()));
}

void IBaseEntity::setTexture(const Texture &t, const sf::IntRect &r)
{
	tex = &t;
	rect = r;
}

const sf::IntRect &IBaseEntity::getTextureRect() const
{
	return rect;
}

void IBaseEntity::setTextureRect(const sf::IntRect &r)
{
	rect = r;
}

const sf::Color &IBaseEntity::getColor() const
{
	return col;
}

void IBaseEntity::setColor(const sf::Color &c)
{
	col = c;
}

sf::Vector2f IBaseEntity::getAbsolutePosition() const
{
	auto pos = getPosition();
	auto parent = getParent();
	if (parent != nullptr)
		pos += parent->getAbsolutePosition();
	return pos;
}

void IBaseEntity::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
	sf::Sprite spr(*tex, rect);
	spr.setColor(col);
	if (getParent())
		states.transform.translate(getParent()->getAbsolutePosition());
	states.transform.combine(getTransform());
	rt.draw(spr, states);
}
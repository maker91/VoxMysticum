#include "BaseEntity.hpp"
#include "EntityFlags.hpp"

BaseEntity::BaseEntity(const sf::Vector2f &pos)
: entId(IDFactory::generate("entId")), flags(0), parent(nullptr)
{
	setPosition(pos);
}

bool BaseEntity::hasFlags(std::uint64_t flag) const
{
	return bool(flags&flag);
}

std::uint64_t BaseEntity::getFlags() const
{
	return flags;
}

void BaseEntity::setFlags(std::uint64_t flag)
{
	flags |= flag;
}

void BaseEntity::unsetFlags(std::uint64_t flag)
{
	flags &= (~flag);
}

void BaseEntity::toggleFlags(std::uint64_t flag)
{
	flags ^= flag;
}

std::uint32_t BaseEntity::getEntId() const
{
	return entId;
}

void BaseEntity::remove()
{
	setFlags(EntityFlags::REMOVE);
}

void BaseEntity::setParent(BaseEntity *p)
{
	parent = p;
}

BaseEntity *BaseEntity::getParent() const
{
	return parent;
}


sf::Vector2f BaseEntity::getAbsolutePosition() const
{
	auto pos = getPosition();
	auto parent = getParent();
	if (parent != nullptr)
		pos += parent->getAbsolutePosition();
	return pos;
}

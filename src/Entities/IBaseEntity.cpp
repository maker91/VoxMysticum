#include "IBaseEntity.hpp"
#include "EntityFlags.hpp"

IBaseEntity::IBaseEntity(const sf::Vector2f &pos)
: entId(IDFactory::generate("entId")), flags(0), parent(nullptr)
{
	setPosition(pos);
}

bool IBaseEntity::hasFlags(std::uint64_t flag) const
{
	return bool(flags&flag);
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


sf::Vector2f IBaseEntity::getAbsolutePosition() const
{
	auto pos = getPosition();
	auto parent = getParent();
	if (parent != nullptr)
		pos += parent->getAbsolutePosition();
	return pos;
}

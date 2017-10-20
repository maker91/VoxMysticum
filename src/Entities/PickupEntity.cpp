#include "PickupEntity.hpp"
#include "EntityFlags.hpp"


PickupEntity::PickupEntity(GameState &game, const sf::Vector2f &pos, const sf::Vector3f &size,
                           std::shared_ptr<const TMD> tex, uint64_t mask)
        : Entity(game, sf::Vector3f(pos.x, pos.y, 0.1f), size, tex, mask), active(true)
{
    setFlags(EntityFlags::PICKUP | EntityFlags::TRIGGER | EntityFlags::GLOW);
}

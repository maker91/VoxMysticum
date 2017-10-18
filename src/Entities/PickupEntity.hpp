#pragma once

#include "PAttributes.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"


class PickupEntity : public Entity
{
public:
    PickupEntity(GameState &game, const sf::Vector2f &pos, const sf::Vector3f &size, TMD &tex, uint64_t mask);

    virtual bool applyEffect(Player &, PAttributes &) const=0;
};
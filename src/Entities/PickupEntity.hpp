#pragma once

#include "PAttributes.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"


class PickupEntity : public Entity
{
public:
    PickupEntity(GameState &game, const sf::Vector2f &pos, const sf::Vector3f &size,
                 std::shared_ptr<const TMD> tex, uint64_t mask);

    void onPlayerCollide(Player &player) override;
    virtual bool applyEffect(Player &)=0;

protected:
    bool active;
};

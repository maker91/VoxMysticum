#pragma once

#include "Entities/PickupEntity.hpp"


class HealthPickup : public PickupEntity
{
public:
    HealthPickup(GameState &game, const sf::Vector2f &pos);

    bool applyEffect(Player &, PAttributes &attributes) override;

private:
    std::shared_ptr<BaseEntity> light;
};
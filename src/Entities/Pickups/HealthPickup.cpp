#include "HealthPickup.hpp"
#include "ResourceManager.hpp"


HealthPickup::HealthPickup(GameState &game, const sf::Vector2f &pos)
        : PickupEntity(game, pos, sf::Vector3f(30.f, 16.f, 30.f), *ResourceManager::get<TMD>("heart_pickup.tmd"), 32)
{

}


bool HealthPickup::applyEffect(Player &player, PAttributes &attributes) const
{
    return player.heal(1);
}

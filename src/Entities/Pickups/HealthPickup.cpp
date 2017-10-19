#include "HealthPickup.hpp"
#include "ResourceManager.hpp"
#include "SoundEngine.hpp"
#include "States/GameState.hpp"
#include "EntityFlags.hpp"


HealthPickup::HealthPickup(GameState &game, const sf::Vector2f &pos)
        : PickupEntity(game, pos, sf::Vector3f(30.f, 16.f, 30.f), *ResourceManager::get<TMD>("heart_pickup.tmd"), 32)
{
    light = game.spawnLight(this, 0.1, sf::Color(205, 105, 105), 0.5f, 15.f);
}


bool HealthPickup::applyEffect(Player &player, PAttributes &attributes)
{
    if (!active || !player.heal(1))
        return false;

    active = false;
    SoundEngine::playSound("gulp.wav", 60.f);
    std::shared_ptr<IBaseEntity> effect = game.spawnEffect(
            sf::Vector2f(0.f, 0.f), *ResourceManager::get<TMD>("heart_effect.tmd"), "idle", false);
    effect->setParent(&player);

    this->remove();
    light->remove();
}

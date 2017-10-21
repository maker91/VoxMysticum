#include "Heart.hpp"
#include "ResourceManager.hpp"
#include "EntityFlags.hpp"


Heart::Heart() : IBasePedestalItem(ResourceManager::get<const TMD>("health_up.tmd"))
{
    setFlags(EntityFlags::GLOW);
}

void Heart::applyEffect(Player &player) {
    player.pAttrs.maxHealth += 2;
    // TODO: fix this!
    player.setMaxHealth(player.pAttrs.maxHealth);
    player.setHealth(player.pAttrs.maxHealth);
}


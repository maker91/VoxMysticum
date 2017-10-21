#include "Wand.hpp"
#include "ResourceManager.hpp"
#include "EntityFlags.hpp"


Wand::Wand() : IBasePedestalItem(ResourceManager::get<const TMD>("wand.tmd"))
{
    setFlags(EntityFlags::GLOW);
}

void Wand::applyEffect(Player &player) {
    player.pAttrs.shootDelay -= 0.05;
}

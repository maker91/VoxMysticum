#include "EntityFlags.hpp"
#include "Pedestal.hpp"
#include "ResourceManager.hpp"
#include "States/GameState.hpp"
#include "SoundEngine.hpp"


Pedestal::Pedestal(GameState &game, const sf::Vector2f &pos)
        : Entity(game, sf::Vector3f(pos.x, pos.y, 0.f), sf::Vector3f(60.f, 20.f, 30.f),
                 ResourceManager::get<TMD>("pedestal.tmd"), 64)
{
    setFlags(EntityFlags::COLLIDE);
}

std::shared_ptr<IBasePedestalItem> Pedestal::getPedestalItem() const {
    return item;
}

void Pedestal::setPedestalItem(std::shared_ptr<IBasePedestalItem> i) {
    item = std::move(i);
    item->setParent(this);
    item->setPosition(0.f, -50.f);

    if (!light)
        light = game.spawnLight(this, 0.f, sf::Color(205, 205, 105));
}

void Pedestal::render(sf::RenderTarget &diffuse, sf::RenderTarget &glow, const sf::Color &ambient) {
    Entity::render(diffuse, glow, ambient);

    // draw the pedestal item
    if (item) {
        item->render(diffuse, glow, ambient);
    }
}

void Pedestal::onPlayerCollide(Player &player) {
    if (item) {
        item->applyEffect(player);
        item = nullptr;
        if (light)
            light->remove();
        SoundEngine::playSound("pedestal_pickup.wav");
    }
}

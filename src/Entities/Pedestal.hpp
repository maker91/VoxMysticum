#pragma once

#include "Entities/Entity.hpp"
#include "PedestalItems/IBasePedestalItem.hpp"


class Pedestal : public Entity
{
public:
    Pedestal(GameState &game, const sf::Vector2f &pos);

    std::shared_ptr<IBasePedestalItem> getPedestalItem() const;
    void setPedestalItem(std::shared_ptr<IBasePedestalItem>);

    void render(sf::RenderTarget &diffuse, sf::RenderTarget &glow, const sf::Color &ambient) override;
    void onPlayerCollide(Player &player) override;

private:
    std::shared_ptr<IBasePedestalItem> item;
    std::shared_ptr<BaseEntity> light;
};

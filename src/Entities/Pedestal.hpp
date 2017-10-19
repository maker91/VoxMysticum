#pragma once

#include "Entities/Entity.hpp"
#include "PedestalItems/IBasePedestalItem.hpp"


class Pedestal : public Entity
{
public:
    Pedestal(GameState &game, const sf::Vector2f &pos);

    std::shared_ptr<IBasePedestalItem> getPedestalItem() const;
    void setPedestalItem(std::shared_ptr<IBasePedestalItem>);

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;

private:
    std::shared_ptr<IBasePedestalItem> item;
};
#pragma once

#include <SFML/Graphics.hpp>
#include <Resources/Texture.hpp>
#include "BaseEntity.hpp"


class BaseDrawable : public BaseEntity, virtual public sf::Drawable
{
public:
    BaseDrawable(const sf::Vector2f &, std::shared_ptr<const Texture>);

    std::shared_ptr<const Texture> getTexture() const;
    void setTexture(std::shared_ptr<const Texture>, bool resetRect = true);
    void setTexture(std::shared_ptr<const Texture>, const sf::IntRect &rect);

    const sf::IntRect &getTextureRect() const;
    void setTextureRect(const sf::IntRect &rect);
    const sf::Color &getColor() const;
    void setColor(const sf::Color &c);

protected:
    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;

protected:
    std::shared_ptr<const Texture> tex;
    sf::IntRect rect;
    sf::Color col;
};

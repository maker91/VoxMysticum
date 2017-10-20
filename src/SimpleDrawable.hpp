#pragma once

#include <SFML/Graphics.hpp>
#include <Resources/Texture.hpp>


class SimpleDrawable : virtual sf::Transformable, virtual sf::Drawable
{
public:
    SimpleDrawable(const Texture &);

    const Texture &getTexture() const;
    void setTexture(const Texture &, bool resetRect = true);
    void setTexture(const Texture &, const sf::IntRect &rect);

    const sf::IntRect &getTextureRect() const;
    void setTextureRect(const sf::IntRect &rect);
    const sf::Color &getColor() const;
    void setColor(const sf::Color &c);

protected:
    virtual void draw(sf::RenderTarget &rt, sf::RenderStates states) const;

protected:
    Texture &tex;
    sf::IntRect rect;
    sf::Color col;
};
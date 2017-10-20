#include "SimpleDrawable.hpp"
#include <SFML/Graphics.hpp>


SimpleDrawable::SimpleDrawable(Texture &tex)
    : tex(tex)
{

}

const Texture &SimpleDrawable::getTexture() const {
    return tex;
}

void SimpleDrawable::setTexture(const Texture &t, bool resetRect) {
    tex = t;
    if (resetRect)
        rect = sf::IntRect({ 0, 0 }, static_cast<sf::Vector2i>(t.getSize()));
}

void SimpleDrawable::setTexture(const Texture &t, const sf::IntRect &r) {
    tex = t;
    rect = r;
}

const sf::IntRect &SimpleDrawable::getTextureRect() const {
    return rect;
}

void SimpleDrawable::setTextureRect(const sf::IntRect &r) {
    rect = r;
}

const sf::Color &SimpleDrawable::getColor() const {
    return col;
}

void SimpleDrawable::setColor(const sf::Color &c) {
    col = c;
}

void SimpleDrawable::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    sf::Sprite spr(tex, rect);
    spr.setColor(col);
    if (getParent())
        states.transform.translate(getParent()->getAbsolutePosition());
    states.transform.combine(getTransform());
    rt.draw(spr, states);
}

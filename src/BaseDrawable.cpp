#include "BaseDrawable.hpp"


BaseDrawable::BaseDrawable(const sf::Vector2f &pos, std::shared_ptr<const Texture> tex)
    : BaseEntity(pos), tex(std::move(tex))
{

}

std::shared_ptr<const Texture> BaseDrawable::getTexture() const {
    return tex;
}

void BaseDrawable::setTexture(std::shared_ptr<const Texture> t, bool resetRect) {
    tex = t;
    if (resetRect)
        rect = sf::IntRect({ 0, 0 }, static_cast<sf::Vector2i>(t->getSize()));
}

void BaseDrawable::setTexture(std::shared_ptr<const Texture> t, const sf::IntRect &r) {
    tex = t;
    rect = r;
}

const sf::IntRect &BaseDrawable::getTextureRect() const {
    return rect;
}

void BaseDrawable::setTextureRect(const sf::IntRect &r) {
    rect = r;
}

const sf::Color &BaseDrawable::getColor() const {
    return col;
}

void BaseDrawable::setColor(const sf::Color &c) {
    col = c;
}

void BaseDrawable::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    sf::Sprite spr(*tex, rect);
    spr.setColor(col);
    if (getParent())
        states.transform.translate(getParent()->getAbsolutePosition());
    states.transform.combine(getTransform());
    rt.draw(spr, states);
}

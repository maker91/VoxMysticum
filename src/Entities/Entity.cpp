#include "Entity.hpp"
#include "States/GameState.hpp"
#include "ResourceManager.hpp"


#define DEBUG_DRAW 0


Entity::Entity(GameState &game, const sf::Vector3f &pos, const sf::Vector3f &s, std::shared_ptr<const TMD> tex,
               std::uint64_t m)
    : BaseTMDDrawable(sf::Vector2f(pos.x, pos.y), std::move(tex)),
      game(game), height(pos.z), collision_mask(m), size(s)
{

}

void Entity::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    // draw the shadow
    if (height > 0.f)
    {
        std::shared_ptr<const TMD> shadowTex = ResourceManager::get<TMD>("shadow.tmd");
        sf::Sprite shadow(*shadowTex->getDiffuseTexture());
        shadow.setOrigin(shadowTex->getStaticOrigin());
        shadow.setPosition(getPosition());
        shadow.setScale(shadowTex->getStaticScale());
        rt.draw(shadow);
    }

    states.transform.translate(-sf::Vector2f(0.f, height));
    BaseTMDDrawable::draw(rt, states);

#if DEBUG_DRAW
    // draw the base bounding box
    auto aabb = getAABB();
    sf::RectangleShape r(sf::Vector2f(aabb.width, aabb.height));
    r.setPosition(aabb.left, aabb.top);
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineThickness(1.f);
    r.setOutlineColor(sf::Color::Red);
    rt.draw(r);

    // draw the vert bounding boc
    auto vaabb = getZAABB();
    sf::RectangleShape h(sf::Vector2f(vaabb.width, vaabb.height));
    h.setPosition(vaabb.left, vaabb.top);
    h.setFillColor(sf::Color::Transparent);
    h.setOutlineThickness(1.f);
    h.setOutlineColor(sf::Color::Green);
    rt.draw(h);
#endif
}


float Entity::getHeight() const
{
    return height;
}

void Entity::setHeight(float h)
{
    height = h;
}

sf::IntRect Entity::getAABB() const
{
    sf::Vector2f base_size {size.x, size.y};
    return { static_cast<sf::Vector2i>(BaseTMDDrawable::getPosition() - base_size / 2.f),
        static_cast<sf::Vector2i>(base_size)};
}

sf::IntRect Entity::getZAABB() const
{
    sf::Vector2f base_size{ size.x, -size.z };
    return{ static_cast<sf::Vector2i>(BaseTMDDrawable::getPosition() - sf::Vector2f(0.f, height)
        - sf::Vector2f(base_size.x / 2.f, 0.f)),
        static_cast<sf::Vector2i>(base_size) };
}

// static
void Entity::checkCollision(Entity &a, Entity &b)
{
    if (a.collision_mask & b.collision_mask)
        return;

    if (!a.shouldCollide(b) || !b.shouldCollide(a))
        return;

    sf::IntRect ab = a.getAABB();
    sf::IntRect azb = a.getZAABB();
    sf::IntRect bb = b.getAABB();
    sf::IntRect bzb = b.getZAABB();

    if (ab.intersects(bb) && azb.intersects(bzb))
    {
        a.onCollide(b);
        b.onCollide(a);
    }
}

bool Entity::shouldCollide(const Entity &other) const {
    return true;
}



#include "Hurtable.hpp"
#include "EntityFlags.hpp"
#include "ResourceManager.hpp"


Hurtable::Hurtable(GameState &game, const sf::Vector3f &pos, const sf::Vector3f &size, std::shared_ptr<const TMD> tex,
                   uint64_t mask, int health)
    : Entity(game, pos, size, tex, mask), health(health), maxHealth(health), hurtFlash(0.f)
{

}

void Hurtable::tick(float dt) {
    if (hurtFlash > 0.f)
        hurtFlash -= dt;

    Entity::tick(dt);
}

void Hurtable::draw(sf::RenderTarget &rt, sf::RenderStates states) const {
    if (hurtFlash > 0.f)
    {
        std::shared_ptr<Shader> sh = ResourceManager::get_noconst<Shader>("color_override.fsh");
        sh->setParameter("color", sf::Color::Red);
        states.shader = sh.get();
    }

    Entity::draw(rt, states);
}

bool Hurtable::hurt(int d)
{
    if (hasFlags(EntityFlags::INVUNERABLE) || hurtFlash > 0.f)
        return false;

    if (tmd->isAnimated() && tmd->hasAnimation("hurt"))
    {
        anim.play("hurt", [&]()
        {
            anim.play("idle");
        });
    }
    else
    {
        hurtFlash = 0.14f;
    }

    setHealth(getHealth() - d);
    onHurt(d);

    return true;
}

bool Hurtable::heal(int h)
{
    int curHealth = getHealth();
    int maxHealth = getMaxHealth();

    if (curHealth >= maxHealth)
        return false;

    setHealth(std::min(getMaxHealth(), getHealth() + h));
    return true;
}

void Hurtable::setHealth(int h)
{
    health = h;
}

int Hurtable::getHealth() const
{
    return health;
}

void Hurtable::setMaxHealth(int h)
{
    maxHealth = h;
}

int Hurtable::getMaxHealth() const
{
    return maxHealth;
}


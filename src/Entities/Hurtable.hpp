#pragma once


#include <SFML/Audio.hpp>
#include "Entity.hpp"

class Hurtable : public Entity
{
public:
    Hurtable(GameState &game, const sf::Vector3f &pos, const sf::Vector3f &size,
             std::shared_ptr<const TMD> tex, std::uint64_t mask=0, int health=100);

    void tick(float dt) override;
    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;

    bool hurt(int d) override;
    bool heal(int h) override;
    void setHealth(int h);
    int getHealth() const;
    void setMaxHealth(int h);
    int getMaxHealth() const;

    virtual void onHurt(int d) {};

protected:
    int maxHealth;
    int health;
    float hurtFlash;
};

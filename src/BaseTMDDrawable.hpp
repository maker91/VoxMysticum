#pragma once

#include "BaseDrawable.hpp"


class BaseTMDDrawable : public BaseDrawable
{
public:
    BaseTMDDrawable(const sf::Vector2f &, std::shared_ptr<const TMD> tex);

    void setTexture(std::shared_ptr<const TMD>);

    void tick(float dt) override;
    virtual void render(sf::RenderTarget &diffuse, sf::RenderTarget &glow, const sf::Color &ambient);

protected:
    AnimPlayer anim;
    std::shared_ptr<const TMD> tmd;
};

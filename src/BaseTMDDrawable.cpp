#include "BaseTMDDrawable.hpp"
#include "EntityFlags.hpp"
#include "ResourceManager.hpp"


BaseTMDDrawable::BaseTMDDrawable(const sf::Vector2f &pos, std::shared_ptr<const TMD> tex)
        : BaseDrawable(pos, tex->getDiffuseTexture()), anim(tex)
{
    setTexture(tex);
    if (!tmd->isAnimated()) {
        setOrigin(tex->getStaticOrigin());
        setScale(tex->getStaticScale());
        setColor(tex->getStaticColor());
    } else {
        anim.play("idle", true);
    }
}


void BaseTMDDrawable::setTexture(std::shared_ptr<const TMD> tex)
{
    tmd = tex;
    BaseDrawable::setTexture(tex->getDiffuseTexture());
    anim.setTexture(tex);
    if (!tex->isAnimated())
    {
        setOrigin(tex->getStaticOrigin());
        setScale(tex->getStaticScale());
    }
}

void BaseTMDDrawable::tick(float dt)
{
    if (tmd->isAnimated())
    {
        anim.tick(dt);

        sf::Vector2f orig;
        sf::Vector2f scale;
        sf::IntRect rect;
        sf::Color col;
        anim.getCurrentFrame(orig, scale, col, rect);

        setOrigin(orig);
        setScale(scale);
        setColor(col);
        setTextureRect(rect);
    }
}

void BaseTMDDrawable::render(sf::RenderTarget &diffuse, sf::RenderTarget &glow, const sf::Color &ambient)
{
    // draw the diffuse texture
    if (!hasFlags(EntityFlags::NODRAW))
    {
        if (tmd->getDiffuseShader() != nullptr)
            diffuse.draw(*this, tmd->getDiffuseShader().get());
        else
            diffuse.draw(*this);

        // draw occlusion to the lightmap to block lights behind us
        std::shared_ptr<Shader> sh = ResourceManager::get_noconst<Shader>("ambient.fsh");
        sh->setParameter("texture", sf::Shader::CurrentTexture);
        sh->setParameter("ambient", ambient);
        glow.draw(*this, sh.get());
    }

    // draw our glow to the light map
    std::shared_ptr<const Texture> glowTex = tmd->getGlowTexture();
    std::shared_ptr<const Shader> glowShader = tmd->getGlowShader();
    if (hasFlags(EntityFlags::GLOW) && glowTex != nullptr)
    {
        BaseDrawable::setTexture(glowTex, false);
        if (glowShader)
            glow.draw(*this, glowShader.get());
        else
            glow.draw(*this);
        BaseDrawable::setTexture(tmd->getDiffuseTexture(), false);
    }
}

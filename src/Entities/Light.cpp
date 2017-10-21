#include "Light.hpp"
#include "ResourceManager.hpp"
#include "EntityFlags.hpp"
#include "BaseDrawable.hpp"

#include <cmath>


Light::Light(GameState &gm, const sf::Vector3f &pos, const sf::Color &col, float intensity, float radius)
: intensity(intensity),  radius(radius),
  Entity(gm, pos, sf::Vector3f(), ResourceManager::get<TMD>("light.tmd"))
{
	setColor({ col.r, col.g, col.b, static_cast<sf::Uint8>(255 * intensity) });
	setFlags(EntityFlags::NODRAW | EntityFlags::GLOW);
	rescale();
}

Light::Light(GameState &gm, BaseEntity *parent, float height, const sf::Color &col, float intensity, float radius)
: Light(gm, { 0.f, 0.f, height }, col, intensity, radius)
{
	setParent(parent);
    rescale();
}

void Light::setHeight(float h)
{
	Entity::setHeight(h);
	rescale();
}

void Light::setIntensity(float i)
{
	intensity = i;
}

float Light::getIntensity() const
{
	return intensity;
}

void Light::setRadius(float r)
{
	radius = r;
	rescale();
}

float Light::getRadius() const
{
	return radius;
}

void Light::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
	
	states.blendMode = sf::BlendAdd;
    BaseDrawable::draw(rt, states);
}

void Light::rescale()
{
	float scale = 2.f*std::sqrt(radius*radius - height*height) / 256.f;
	setScale(tmd->getStaticScale()*scale);
}

#pragma once

#include "Entity.hpp"
#include "BaseEntity.hpp"

class Light : public Entity
{
public:
	Light(GameState &, const sf::Vector3f &pos, const sf::Color &col = sf::Color::White, 
		float intensity = 1.f, float radius = 100.f);
	Light(GameState &, BaseEntity *parent, float height, const sf::Color &col = sf::Color::White,
		float intensity = 1.f, float radius = 100.f);

	void setHeight(float height) override;
	void setIntensity(float i);
	void setRadius(float r);
	float getIntensity() const;
	float getRadius() const;

	void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;

private:
	void rescale();

private:
	float intensity;
	float radius;
};

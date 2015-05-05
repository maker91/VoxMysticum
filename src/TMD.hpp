#pragma once

#include <vector>
#include <map>
#include <memory>

#include "Texture.hpp"
#include "IBaseResource.hpp"
#include "Shader.hpp"

struct Animation
{
	sf::Vector2f origin;
	sf::Vector2f scale;
	sf::Color color;
	float frameTime;
	std::vector<sf::IntRect> frames;
};

class TMD : public IBaseResource
{
public:
	bool load(const std::string &name);
	void fallback();

	sf::Vector2f getStaticOrigin() const;
	sf::Vector2f getStaticScale() const;
	sf::Color getStaticColor() const;
	const Texture &getDiffuseTexture() const;
	const Texture &getGlowTexture() const;
	const Shader *getDiffuseShader() const;
	const Shader *getGlowShader() const;

	bool isAnimated() const;
	bool hasAnimation(const std::string &name) const;
	const Animation &getAnimation(const std::string &name) const;

private:
	std::string name;
	Texture *diffuse;
	Texture *glow;
	Shader *diffuse_shader;
	Shader *glow_shader;

	bool animated;
	sf::Vector2f origin;
	sf::Vector2f scale;
	sf::Color color;

	std::map<std::string, Animation> animations;
};
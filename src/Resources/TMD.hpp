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
	bool load(const std::string &name) override;
	void fallback() override;

	sf::Vector2f getStaticOrigin() const;
	sf::Vector2f getStaticScale() const;
	sf::Color getStaticColor() const;
	std::shared_ptr<const Texture> getDiffuseTexture() const;
	std::shared_ptr<const Texture> getGlowTexture() const;
	std::shared_ptr<Shader> getDiffuseShader() const;
	std::shared_ptr<Shader> getGlowShader() const;

	bool isAnimated() const;
	bool hasAnimation(const std::string &name) const;
	const Animation &getAnimation(const std::string &name) const;

private:
	std::string name;
	std::shared_ptr<const Texture> diffuse;
	std::shared_ptr<const Texture> glow;
	std::shared_ptr<Shader> diffuse_shader;
	std::shared_ptr<Shader> glow_shader;

	bool animated;
	sf::Vector2f origin;
	sf::Vector2f scale;
	sf::Color color;

	std::map<std::string, Animation> animations;
};

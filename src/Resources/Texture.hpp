#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "IBaseResource.hpp"

class Texture : public sf::Texture, public IBaseResource
{
public:
	bool load(const std::string &name);
	void fallback();
};
#pragma once

#include <SFML/Graphics/Shader.hpp>
#include "IBaseResource.hpp"

class Shader : public sf::Shader, public IBaseResource
{
public:
	bool load(const std::string &name);
};
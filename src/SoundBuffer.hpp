#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include "IBaseResource.hpp"

class SoundBuffer : public IBaseResource, public sf::SoundBuffer {
public:
	bool load(const std::string &name)
	{
		return loadFromFile("Resources/Sounds/" + name);
	}
};
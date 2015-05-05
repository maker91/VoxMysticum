#include "Texture.hpp"

bool Texture::load(const std::string &name)
{
	return loadFromFile("Resources/Textures/" + name);
}

void Texture::fallback()
{
	loadFromFile("Resources/Textures/error.png");
}
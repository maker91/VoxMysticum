#include "Shader.hpp"

bool Shader::load(const std::string &name)
{
	return loadFromFile("Resources/Shaders/" + name, sf::Shader::Fragment);
}
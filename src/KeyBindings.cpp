#include "KeyBindings.hpp"

void KeyBindings::bind(const std::string &name, sf::Keyboard::Key key)
{
	binds[name] = key;
}

bool KeyBindings::isBindPressed(const std::string &name)
{
	return sf::Keyboard::isKeyPressed(getBind(name));
}

sf::Keyboard::Key KeyBindings::getBind(const std::string &name)
{
	if (binds.count(name))
		return binds[name];
	return sf::Keyboard::Unknown;
}

std::map<std::string, sf::Keyboard::Key> KeyBindings::binds;
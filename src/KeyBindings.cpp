#include "KeyBindings.hpp"

void KeyBindings::bind(const std::string &name, sf::Keyboard::Key key)
{
    bind("default", name, key);
}

bool KeyBindings::isBindPressed(const std::string &name)
{
    return isBindPressed("default", name);
}

sf::Keyboard::Key KeyBindings::getBind(const std::string &name)
{
    return getBind("default", name);
}

void KeyBindings::bind(const std::string &context, const std::string &name, sf::Keyboard::Key key)
{
	binds[context][name] = key;
}

bool KeyBindings::isBindPressed(const std::string &context, const std::string &name)
{
	return sf::Keyboard::isKeyPressed(getBind(context, name));
}

sf::Keyboard::Key KeyBindings::getBind(const std::string &context, const std::string &name)
{
	if (!binds.count(context))
        binds[context] = std::map<std::string, sf::Keyboard::Key>();

    if (binds[context].count(name))
		return binds[context][name];
	return sf::Keyboard::Unknown;
}

std::map<std::string, std::map<std::string, sf::Keyboard::Key>> KeyBindings::binds;
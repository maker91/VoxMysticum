#pragma once

#include <string>
#include <map>
#include <stdexcept>

#include <SFML/Window/Keyboard.hpp>

class KeyBindings
{
public:
    static void bind(const std::string &, sf::Keyboard::Key);
    static bool isBindPressed(const std::string &);
    static sf::Keyboard::Key getBind(const std::string &);

    // context versions
	static void bind(const std::string &, const std::string &, sf::Keyboard::Key);
	static bool isBindPressed(const std::string &, const std::string &);
	static sf::Keyboard::Key getBind(const std::string &, const std::string &);

private:
	static std::map<std::string, std::map<std::string, sf::Keyboard::Key>> binds;
};
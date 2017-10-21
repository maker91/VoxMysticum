#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>
#include "PAttributes.hpp"


class CharacterDef
{
public:
    std::string name;
    std::string spriteTexture;
    std::string magicTexture;
    sf::Color magicColor;
    PAttributes pAttrs;
};

#pragma once

#include <string>
#include "PAttributes.hpp"


class CharacterDef
{
public:
    std::string name;
    std::string spriteTexture;
    std::string magicTexture;
    PAttributes pAttrs;
};

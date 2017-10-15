#pragma once

#include <SFML/Graphics/Font.hpp>
#include "IBaseResource.hpp"


class Font : public sf::Font, public IBaseResource
{
public:
    bool load(const std::string &name);
};
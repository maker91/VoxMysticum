#pragma once

#include <memory>
#include "Resources/Texture.hpp"


class IBasePedestalItem
{
public:
    IBasePedestalItem(const Texture &tex);

    const Texture &getTexture() const;

private:
    const Texture &tex;

};
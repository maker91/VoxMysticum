#pragma once

#include "IBasePedestalItem.hpp"


class Wand : public IBasePedestalItem
{
public:
    Wand();

    void applyEffect(Player &player) override;
};

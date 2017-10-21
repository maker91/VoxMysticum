#pragma once

#include "IBasePedestalItem.hpp"


class Heart : public IBasePedestalItem
{
public:
    Heart();

    void applyEffect(Player &player) override;
};

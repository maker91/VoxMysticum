#pragma once

#include <memory>
#include "BaseTMDDrawable.hpp"
#include "Entities/Player.hpp"


class IBasePedestalItem : public BaseTMDDrawable
{
public:
    explicit IBasePedestalItem(std::shared_ptr<const TMD>);
    virtual void applyEffect(Player &)=0;
};

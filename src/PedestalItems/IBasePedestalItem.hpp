#pragma once

#include <memory>
#include "BaseTMDDrawable.hpp"


class IBasePedestalItem : public BaseTMDDrawable
{
public:
    explicit IBasePedestalItem(std::shared_ptr<const TMD>);

};

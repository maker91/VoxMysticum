#include "IBasePedestalItem.hpp"


IBasePedestalItem::IBasePedestalItem(std::shared_ptr<const TMD> tex)
    : BaseTMDDrawable(sf::Vector2f(0.f, 0.f), std::move(tex))
{

}

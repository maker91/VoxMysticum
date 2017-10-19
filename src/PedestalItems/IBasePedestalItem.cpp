#include "IBasePedestalItem.hpp"


IBasePedestalItem::IBasePedestalItem(const Texture &tex)
    : tex(tex)
{

}

const Texture &IBasePedestalItem::getTexture() const {
    return tex;
}

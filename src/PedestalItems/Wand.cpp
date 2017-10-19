#include "Wand.hpp"
#include "ResourceManager.hpp"


Wand::Wand()
        : IBasePedestalItem(*ResourceManager::get<Texture>("wand.png"))
{

}

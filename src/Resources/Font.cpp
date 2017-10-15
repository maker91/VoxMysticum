#include "Resources/Font.hpp"


bool Font::load(const std::string &name) {
    return loadFromFile("Resources/Fonts/" + name);
}

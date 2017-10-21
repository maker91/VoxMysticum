#include "BaseState.hpp"
#include "Config.hpp"


BaseState::BaseState()
{
    screenWidth = Config::config.get("screen-width", 1600).asUInt();
    screenHeight = Config::config.get("screen-height", 1200).asUInt();
}


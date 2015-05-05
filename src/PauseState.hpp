#pragma once

#include "IBaseState.hpp"

class PauseState : public IBaseState
{
public:
	void tick(float dt);
	void handleEvent(const sf::Event &);
	void onEnter();
};
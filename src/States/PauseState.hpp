#pragma once

#include "IBaseState.hpp"

class PauseState : public IBaseState
{
public:
	PauseState();
	void tick(float dt);
	void draw(sf::RenderTarget &);
	void handleEvent(const sf::Event &);
};

#pragma once

#include "IBaseState.hpp"

class PauseState : public IBaseState
{
public:
	PauseState();
	void handleEvent(const sf::Event &);
	void draw(sf::RenderTarget &);
	void onEnter();
	void onExit();
};

#pragma once

#include "BaseState.hpp"

class PauseState : public BaseState
{
public:
	void handleEvent(const sf::Event &);
	void draw(sf::RenderTarget &);
	void onEnter();
	void onExit();
};

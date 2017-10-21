#pragma once

#include "BaseState.hpp"

class GameOverState : public BaseState
{
public:
	void handleEvent(const sf::Event &);
	void draw(sf::RenderTarget &);
	void onEnter();
	void onExit();
};

#pragma once

#include "IBaseState.hpp"

class GameOverState : public IBaseState
{
public:
	void handleEvent(const sf::Event &);
	void draw(sf::RenderTarget &);
	void onEnter();
	void onExit();
};

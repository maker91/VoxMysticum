#pragma once

#include <SFML/Graphics.hpp>

class IBaseState
{
public:
	virtual void tick(float dt) = 0;
	virtual void draw(sf::RenderTarget &) {};
	virtual void handleEvent(const sf::Event &) {};
	virtual void onEnter() {};
	virtual void onExit() {};
};
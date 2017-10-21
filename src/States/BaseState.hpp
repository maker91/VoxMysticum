#pragma once

#include <SFML/Graphics.hpp>

class BaseState
{
public:
    BaseState();

	virtual void tick(float dt) {};
	virtual void draw(sf::RenderTarget &) {};
	virtual void handleEvent(const sf::Event &) {};
	virtual void onEnter() {};
	virtual void onExit() {};

protected:
    int screenWidth;
    int screenHeight;
};

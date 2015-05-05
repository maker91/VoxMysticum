#include <cstdio>
#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "StateManager.hpp"
#include "GameState.hpp"
#include "SoundEngine.hpp"
#include "Config.hpp"


int main(int argc, char **argv)
{
	Config::config.loadFromFile("config.json");

	sf::RenderWindow window(sf::VideoMode(Config::config.get("screen-width", 800).asInt(), Config::config.get("screen-height", 600).asInt()), "Vox Mysticum");
	window.setVerticalSyncEnabled(true);

	StateManager::addState<GameState>("game");
	StateManager::pushState("game");

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		float dt = deltaClock.restart().asSeconds();

		SoundEngine::tick(dt);
		StateManager::getCurrentState()->tick(dt);

		sf::Event ev;
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				StateManager::getCurrentState()->handleEvent(ev);
			}
		}

		window.clear(sf::Color(205, 105, 105));
		StateManager::getCurrentState()->draw(window);
		window.display();
	}
}
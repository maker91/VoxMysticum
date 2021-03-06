#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "SoundEngine.hpp"
#include "Config.hpp"
#include "StateManager.hpp"
#include "States/GameState.hpp"
#include "States/PauseState.hpp"
#include "States/CharacterSelectState.hpp"


int main(int argc, char **argv)
{
	Config::config.loadFromFile("config.json");

	sf::RenderWindow window(sf::VideoMode(Config::config.get("screen-width", 800).asUInt(),
										  Config::config.get("screen-height", 600).asUInt()), "Vox Mysticum");
	window.setVerticalSyncEnabled(true);

//	StateManager::pushState<GameState>(false);
	StateManager::pushState<CharacterSelectState>(false);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		float dt = deltaClock.restart().asSeconds();

		SoundEngine::tick(dt);
		StateManager::tick(dt);

		sf::Event ev{};
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				StateManager::handleEvent(ev);
			}
		}

		window.clear(sf::Color(205, 105, 105));
		StateManager::draw(window);
		window.display();
	}
}

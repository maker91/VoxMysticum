#include <SFML/Window/Event.hpp>
#include "KeyBindings.hpp"
#include "StateManager.hpp"
#include "Logging.hpp"
#include "ResourceManager.hpp"
#include "Resources/Font.hpp"
#include "States/GameOverState.hpp"
#include "States/CharacterSelectState.hpp"


void GameOverState::onEnter() {
    Logging::Log->debug("Died");
}

void GameOverState::onExit() {
    Logging::Log->debug("Undied!?!?");
}

void GameOverState::draw(sf::RenderTarget &rt) {
    std::shared_ptr<const Font> font = ResourceManager::get<Font>("verdana.ttf");
    sf::Text text("YOU DIED", *font, 50);
    text.setPosition(300.f, 200.f);
    rt.draw(text);
}

void GameOverState::handleEvent(const sf::Event &ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        if (ev.key.code == KeyBindings::getBind("menu")) {
            StateManager::popState();
            StateManager::popState();
            StateManager::pushState<CharacterSelectState>(false);
        }
        break;

    default:
        break;
    }
}

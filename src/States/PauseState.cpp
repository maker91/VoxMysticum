#include <SFML/Window/Event.hpp>
#include "KeyBindings.hpp"
#include "StateManager.hpp"
#include "Logging.hpp"
#include "ResourceManager.hpp"
#include "Resources/Font.hpp"
#include "PauseState.hpp"


void PauseState::onEnter() {
    Logging::Log->debug("Pausing");
}

void PauseState::onExit() {
    Logging::Log->debug("Unpausing");
}

void PauseState::draw(sf::RenderTarget &rt) {
    std::shared_ptr<Font> font = ResourceManager::get<Font>("verdana.ttf");
    sf::Text text("PAUSED", *font, 50);
    text.setPosition(300.f, 200.f);
    rt.draw(text);
}

void PauseState::handleEvent(const sf::Event &ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        if (ev.key.code == KeyBindings::getBind("menu"))
            StateManager::popState();
        break;

    default:
        break;
    }
}

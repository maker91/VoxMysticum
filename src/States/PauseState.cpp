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
    std::shared_ptr<const Font> font = ResourceManager::get<Font>("verdana.ttf");
    sf::Text text("PAUSED", *font, 50);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(400.f, 300.f);
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

#include "StateManager.hpp"
#include "PauseState.hpp"
#include "KeyBindings.hpp"

PauseState::PauseState()
{
    KeyBindings::bind("menu", sf::Keyboard::Escape);
}

void PauseState::tick(float dt)
{
    // do some flashign effect or something?
}

void PauseState::draw(sf::RenderTarget &)
{

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

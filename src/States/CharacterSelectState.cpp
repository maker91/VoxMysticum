#include "CharacterSelectState.hpp"
#include "Logging.hpp"
#include "ResourceManager.hpp"
#include "Resources/Font.hpp"
#include "GameState.hpp"
#include "StateManager.hpp"
#include "KeyBindings.hpp"
#include "Characters/Blaze.hpp"
#include "Characters/Dexter.hpp"
#include "Characters/Brock.hpp"
#include "Characters/Oswald.hpp"
#include "Characters/Sparky.hpp"


CharacterList characters = {
    characterBlaze,
    characterDexter,
    characterBrock,
    characterOswald,
    characterSparky
};


CharacterSelectState::CharacterSelectState()
        : BaseState(), selectedCharDef(characters.cbegin())
{
    KeyBindings::bind("menu", "up", sf::Keyboard::Up);
    KeyBindings::bind("menu", "down", sf::Keyboard::Down);
    KeyBindings::bind("menu", "select", sf::Keyboard::Return);
}


void CharacterSelectState::onEnter() {
    Logging::Log->debug("Entering character select");
}


void CharacterSelectState::onExit() {
    Logging::Log->debug("Exiting character select");
}


void CharacterSelectState::draw(sf::RenderTarget &rt) {
    CharacterDef def = *selectedCharDef;

    std::shared_ptr<const Font> font = ResourceManager::get<Font>("verdana.ttf");
    sf::Text text(def.name, *font, 50);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(screenWidth/2.f, screenHeight/2.f);
    rt.draw(text);
}


void CharacterSelectState::handleEvent(const sf::Event &ev)
{
    switch (ev.type)
    {
        case sf::Event::KeyPressed:
            if (ev.key.code == KeyBindings::getBind("menu", "up")) {
                if (selectedCharDef == characters.cend()-1)
                    selectedCharDef = characters.cbegin();
                else
                    selectedCharDef++;
            } else if (ev.key.code == KeyBindings::getBind("menu", "down")) {
                if (selectedCharDef == characters.cbegin())
                    selectedCharDef = characters.cend()-1;
                else
                    selectedCharDef--;
            } else if (ev.key.code == KeyBindings::getBind("menu", "select")) {
                StateManager::popState();
                StateManager::pushState<GameState>(false, *selectedCharDef);
            }
            break;

        default:
            break;
    }
}

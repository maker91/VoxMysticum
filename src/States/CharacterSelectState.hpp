#pragma once

#include "BaseState.hpp"
#include "Characters/CharacterDef.hpp"


typedef std::vector<CharacterDef> CharacterList;


class CharacterSelectState : public BaseState
{
public:
    CharacterSelectState();

    void draw(sf::RenderTarget &target) override;

    void onExit() override;
    void onEnter() override;

    void handleEvent(const sf::Event &event) override;

private:
    CharacterList::const_iterator selectedCharDef;
};


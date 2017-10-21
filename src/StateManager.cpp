#include "StateManager.hpp"

StateInfo StateManager::popState()
{
	if (stateStack.empty())
		//EXCEPTION MATE
		return StateInfo{nullptr, false};

	StateInfo info = stateStack.back();
	info.state->onExit();
	stateStack.pop_back();

	if (!stateStack.empty())
		stateStack.back().state->onEnter();

	return info;
}

StateInfo StateManager::getCurrentState()
{
	return stateStack.back();
}


void StateManager::draw(sf::RenderTarget &window) {
    std::vector<std::shared_ptr<BaseState>> to_draw{};

    for (auto iter = stateStack.rbegin(); iter != stateStack.rend(); iter++)
    {
        StateInfo info = *iter;
        to_draw.push_back(info.state);
        if (!info.overlay)
            break;
    }

    for (auto iter = to_draw.rbegin(); iter != to_draw.rend(); iter++)
        (*iter)->draw(window);
}

void StateManager::handleEvent(const sf::Event &ev) {
	getCurrentState().state->handleEvent(ev);
}

void StateManager::tick(float dt) {
    getCurrentState().state->tick(dt);
}

std::deque<StateInfo> StateManager::stateStack;

#include "StateManager.hpp"

void StateManager::addState(const std::string &name, bool overlay, std::shared_ptr<IBaseState> state)
{
	stateMap[name] = StateInfo{std::move(state), overlay};
}

void StateManager::removeState(const std::string &name) {
    stateMap.erase(name);
}

bool StateManager::pushState(const std::string &name)
{
	if (!stateStack.empty())
		stateStack.back().state->onExit();
	
	if (stateMap.count(name))
	{
		auto info = stateMap[name];
		stateStack.push_back(info);
		info.state->onEnter();
		return true;
	}

	return false;
}

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

StateInfo StateManager::getState(const std::string &name)
{
	return stateMap.at(name);
}

void StateManager::draw(sf::RenderTarget &window) {
    std::vector<std::shared_ptr<IBaseState>> to_draw{};

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

std::map<std::string, StateInfo> StateManager::stateMap;
std::deque<StateInfo> StateManager::stateStack;
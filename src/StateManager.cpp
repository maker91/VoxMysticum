#include "StateManager.hpp"

void StateManager::addState(const std::string &name, std::shared_ptr<IBaseState> state)
{
	stateMap[name] = state;
}

bool StateManager::pushState(const std::string &name)
{
	if (!stateStack.empty())
		stateStack.back()->onExit();
	
	if (stateMap.count(name))
	{
		auto state = stateMap[name];
		stateStack.push_back(state);
		state->onEnter();
		return true;
	}

	return false;
}

std::shared_ptr<IBaseState> StateManager::popState()
{
	if (stateStack.empty())
		//EXCEPTION MATE
		return nullptr;

	auto state = stateStack.back();
	state->onExit();
	stateStack.pop_back();

	if (!stateStack.empty())
		stateStack.back()->onEnter();

	return state;
}

std::shared_ptr<IBaseState> StateManager::getCurrentState()
{
	return stateStack.back();
}

std::shared_ptr<IBaseState> StateManager::getState(const std::string &name)
{
	return stateMap.at(name);
}

void StateManager::tick(float dt)
{
	getCurrentState()->tick(dt);
}

void StateManager::draw(sf::RenderTarget &rt)
{
	for (auto state : stateStack) {
		state->draw(rt);
	}
}

void StateManager::handleEvent(const sf::Event &ev)
{
	getCurrentState()->handleEvent(ev);
}

std::map<std::string, std::shared_ptr<IBaseState>> StateManager::stateMap;
std::vector<std::shared_ptr<IBaseState>> StateManager::stateStack;
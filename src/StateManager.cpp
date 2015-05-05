#include "StateManager.hpp"

void StateManager::addState(const std::string &name, std::shared_ptr<IBaseState> state)
{
	stateMap[name] = state;
}

bool StateManager::pushState(const std::string &name)
{
	if (!stateStack.empty())
		stateStack.top()->onExit();
	
	if (stateMap.count(name))
	{
		auto state = stateMap[name];
		stateStack.push(state);
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

	auto state = stateStack.top();
	state->onExit();
	stateStack.pop();

	if (!stateStack.empty())
		stateStack.top()->onEnter();

	return state;
}

std::shared_ptr<IBaseState> StateManager::getCurrentState()
{
	return stateStack.top();
}

std::shared_ptr<IBaseState> StateManager::getState(const std::string &name)
{
	return stateMap.at(name);
}

std::map<std::string, std::shared_ptr<IBaseState>> StateManager::stateMap;
std::stack<std::shared_ptr<IBaseState>> StateManager::stateStack;
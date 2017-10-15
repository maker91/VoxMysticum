#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "States/IBaseState.hpp"

class StateManager
{
public:
	static void addState(const std::string &, std::shared_ptr<IBaseState>);
	static bool pushState(const std::string &);
	static std::shared_ptr<IBaseState> popState();
	static std::shared_ptr<IBaseState> getCurrentState();
	static std::shared_ptr<IBaseState> getState(const std::string &);

	static void tick(float dt);
	static void draw(sf::RenderTarget &);
	static void handleEvent(const sf::Event &);

	template <typename T, typename... Args>
	static std::shared_ptr<T> addState(const std::string &name, Args... args)
	{
		std::shared_ptr<T> state = std::make_shared<T>(args...);
		addState(name, state);
		return state;
	}

private:
	static std::map<std::string, std::shared_ptr<IBaseState>> stateMap;
	static std::vector<std::shared_ptr<IBaseState>> stateStack;
};

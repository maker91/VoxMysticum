#pragma once

#include <map>
#include <string>
#include <deque>
#include <memory>

#include "States/IBaseState.hpp"


struct StateInfo
{
    std::shared_ptr<IBaseState> state;
    bool overlay;
};


class StateManager
{
public:
	static void addState(const std::string &, bool, std::shared_ptr<IBaseState>);
    static void removeState(const std::string &);
	static bool pushState(const std::string &);
	static StateInfo popState();
	static StateInfo getCurrentState();
	static StateInfo getState(const std::string &);

	static void tick(float dt);
	static void draw(sf::RenderTarget &);
	static void handleEvent(const sf::Event &);

	template <typename T, typename... Args>
	static std::shared_ptr<T> addState(const std::string &name, bool overlay, Args... args)
	{
		std::shared_ptr<T> state = std::make_shared<T>(args...);
		addState(name, overlay, state);
		return state;
	}

	static void draw(sf::RenderTarget &);
    static void handleEvent(const sf::Event &);
    static void tick(float dt);

private:
	static std::map<std::string, StateInfo> stateMap;
	static std::deque<StateInfo> stateStack;
};

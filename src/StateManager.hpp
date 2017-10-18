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
	static StateInfo popState();
	static StateInfo getCurrentState();

	static void tick(float dt);
	static void draw(sf::RenderTarget &);
	static void handleEvent(const sf::Event &);

	template <typename T, typename... Args>
	static StateInfo pushState(bool overlay, Args... args)
	{
		if (!stateStack.empty())
			stateStack.back().state->onExit();

        std::shared_ptr<IBaseState> state = std::make_shared<T>(args...);
        state->onEnter();
        StateInfo info = {state, overlay};
        stateStack.push_back(info);

		return info;
	}

private:
	static std::deque<StateInfo> stateStack;
};

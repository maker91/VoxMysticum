#pragma once

#include "Entity.hpp"

class GameState;
class Effect : public Entity
{
public:
	Effect(GameState &, const sf::Vector2f &pos, std::shared_ptr<const TMD> tex,
		const std::string &anim = "idle", bool loop = false);
	
	void tick(float dt) override;
};

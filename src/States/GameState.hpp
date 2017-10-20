#pragma once

#include <list>
#include <SFML/Network.hpp>
#include <SFML/Audio/Music.hpp>

#include "IDFactory.hpp"
#include "IBaseState.hpp"

#include "Entities/Entity.hpp"
#include "Entities/Light.hpp"
#include "Entities/Player.hpp"

class GameState : public IBaseState
{
public:
	GameState();

	void tick(float dt);
	void draw(sf::RenderTarget &);
	void handleEvent(const sf::Event &);
	void onEnter();

	template <typename T, typename... Args>
	void registerEntity(std::string id)
	{
		EntityFactory::registerType<T, GameState &, Args...>(id);
	}

	template <typename... Args>
	std::shared_ptr<BaseEntity> spawnEntity(std::string id, Args... args)
	{
		std::shared_ptr<Entity> ent = EntityFactory::create<GameState &, Args...>(id, *this, args...);
		entities.push_back(ent);
		ent->tick(0.f);
		return ent;
	}

	std::shared_ptr<BaseEntity> spawnEffect(const sf::Vector2f &pos, std::shared_ptr<const TMD> tex,
											const std::string &anim, bool loop = false);
	std::shared_ptr<BaseEntity> spawnLight(const sf::Vector3f &pos, const sf::Color &col = sf::Color::White,
										   float intensity = 1.f, float radius=50.f);
	std::shared_ptr<BaseEntity> spawnLight(BaseEntity *parent, float height, const sf::Color &col = sf::Color::White,
										   float intensity = 1.f, float radius=50.f);

	const sf::Color &getAmbientColor() const;
	std::shared_ptr<Player> getPlayer() const;

private:
	std::list<std::shared_ptr<Entity>> entities;
	std::shared_ptr<Player> player;
	sf::RenderTexture lightmap;
	sf::Color ambient;
};

#include <ctime>

#include "StateManager.hpp"
#include "GameState.hpp"

#include "ResourceManager.hpp"
#include "Resources/Texture.hpp"
#include "Resources/Shader.hpp"

#include "SoundEngine.hpp"
#include "KeyBindings.hpp"
#include "Logging.hpp"
#include "Config.hpp"
#include "RNG.hpp"

#include "EntityFlags.hpp"
#include "TypeFactory.hpp"
#include "Entities/IBaseEntity.hpp"

#include "Entities/Magic.hpp"
#include "Entities/Effect.hpp"
#include "Entities/Barrel.hpp"
#include "Entities/Bat.hpp"

GameState::GameState()
{ 
	// set the seeds
	RNG::managed.seed(Config::config.get("seed", 100).asInt());
	RNG::unmanaged.seed(static_cast<unsigned long>(std::time(nullptr)));

	// register entities
	registerEntity<Player, sf::Vector2f>("localplayer");
	registerEntity<Barrel, sf::Vector2f>("barrel");
	registerEntity<Bat, sf::Vector2f>("bat");
	registerEntity<Magic, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, float, float>("magic");
	registerEntity<Effect, sf::Vector2f, TMD &, std::string, bool>("effect");
	registerEntity<Light, sf::Vector3f, sf::Color, float, float>("light");
	registerEntity<Light, IBaseEntity *, float, sf::Color, float, float>("light");
	
	// key bindings (move to config)
	KeyBindings::bind("move_up", sf::Keyboard::W);
	KeyBindings::bind("move_right", sf::Keyboard::D);
	KeyBindings::bind("move_down", sf::Keyboard::S);
	KeyBindings::bind("move_left", sf::Keyboard::A);
	KeyBindings::bind("shoot_up", sf::Keyboard::Up);
	KeyBindings::bind("shoot_right", sf::Keyboard::Right);
	KeyBindings::bind("shoot_down", sf::Keyboard::Down);
	KeyBindings::bind("shoot_left", sf::Keyboard::Left);
	KeyBindings::bind("activate", sf::Keyboard::Space);
	KeyBindings::bind("reload", sf::Keyboard::R);
	KeyBindings::bind("bomb", sf::Keyboard::LShift);

	// spawn player
	player = std::static_pointer_cast<Player>(spawnEntity<sf::Vector2f>("localplayer", { 100.f, 100.f }));

	// create the lightmap
	lightmap.create(800, 600);
	ambient = sf::Color(35, 35, 35);
}

void GameState::tick(float dt)
{
	// tick the entities
	for (auto ent : entities)
		ent->tick(dt);

	// check for collision
	for (auto itr = entities.begin(); itr != entities.end(); ++itr)
	{
		auto a = *itr;
		if (a->hasFlags(EntityFlags::COLLIDE))
		{
			for (auto nitr = itr; nitr != entities.end(); ++nitr)
			{
				auto b = *nitr;
				if (a != b && b->hasFlags(EntityFlags::COLLIDE))
					Entity::checkCollision(*a, *b);
			}
		}
	}

	// check for removes
	for (auto itr = entities.begin(); itr != entities.end();)
	{
		auto ent = *itr;
		if (ent->hasFlags(EntityFlags::REMOVE))
			entities.erase(itr++);
		else
			++itr;
	}
}

void GameState::draw(sf::RenderTarget &rt)
{
	lightmap.clear(ambient);

	// draw the floor
	rt.draw(sf::Sprite(*ResourceManager::get<Texture>("floor.png")));

	// sort the entities
	entities.sort([](std::shared_ptr<Entity> &a, std::shared_ptr<Entity> &b) -> bool
	{
		return a->getAbsolutePosition().y < b->getAbsolutePosition().y;
	});

	// draw things in order!
	for (auto ent : entities)
		if (ent->hasFlags(EntityFlags::BELOW))
			ent->render(rt, lightmap);
	for (auto ent : entities)
		if (!ent->hasFlags(EntityFlags::BELOW) && !ent->hasFlags(EntityFlags::ABOVE))
			ent->render(rt, lightmap);
	for (auto ent : entities)
		if (ent->hasFlags(EntityFlags::ABOVE))
			ent->render(rt, lightmap);

	// draw the lightmap
	lightmap.display();
	rt.draw(sf::Sprite(lightmap.getTexture()), sf::BlendMultiply);
	//rt.draw(sf::Sprite(lightmap.getTexture()));

	// draw the UI on top
	int health = player->getHealth();
	int healthmod = health % 2;
	sf::Sprite heart = sf::Sprite(*ResourceManager::get<Texture>("heart.png"));
	sf::Sprite half_heart = sf::Sprite(*ResourceManager::get<Texture>("half_heart.png"));
	heart.setScale(0.5f, 0.5f);
	half_heart.setScale(0.5f, 0.5f);
	for (int i=0; i<(health/2); i++) {
		heart.setPosition(sf::Vector2f(10.f + i*34.f, 10.f));
		rt.draw(heart);
	}
	if (healthmod != 0) {
		half_heart.setPosition(sf::Vector2f(10.f + (health/2)*34.f, 10.f));
		rt.draw(half_heart);
	}
}

void GameState::handleEvent(const sf::Event &ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (ev.key.code == KeyBindings::getBind("activate"))
			spawnEntity("bat", sf::Vector2f(
				RNG::managed.generate(100.f, 700.f), RNG::managed.generate(100.f, 500.f))
			);
		else if (ev.key.code == KeyBindings::getBind("reload"))
			spawnEntity("barrel", sf::Vector2f(
				RNG::managed.generate(100.f, 700.f), RNG::managed.generate(100.f, 500.f))
			);
		else if (ev.key.code == KeyBindings::getBind("bomb"))
			player->hurt(1);
		break;

	default:
		break;
	}
}

void GameState::onEnter()
{
	Logging::Log->debug("Entering GameState");
}

std::shared_ptr<IBaseEntity> GameState::spawnEffect(const sf::Vector2f &pos, TMD &t, const std::string &anim, bool loop)
{
	return spawnEntity<sf::Vector2f, TMD &, std::string, bool>("effect", pos, t, anim, loop);
}

std::shared_ptr<IBaseEntity> GameState::spawnLight(const sf::Vector3f &pos, const sf::Color &col, float intensity, float radius)
{
	return spawnEntity<sf::Vector3f, sf::Color, float, float>("light", pos, col, intensity, radius);
}

std::shared_ptr<IBaseEntity> GameState::spawnLight(IBaseEntity *parent, float height, const sf::Color &col, float intensity, float radius)
{
	return spawnEntity<IBaseEntity *, float, sf::Color, float, float>("light", parent, height, col, intensity, radius);
}

const sf::Color &GameState::getAmbientColor() const
{
	return ambient;
}

std::shared_ptr<Player> GameState::getPlayer() const
{
	return player;
}
#include <cmath>

#include "Player.hpp"
#include "ResourceManager.hpp"
#include "States/GameState.hpp"
#include "KeyBindings.hpp"
#include "Config.hpp"
#include "EntityFlags.hpp"
#include "PickupEntity.hpp"
#include "SoundEngine.hpp"


Player::Player(GameState &gm, CharacterDef cDef, const sf::Vector2f &pos, float acceleration, float friction)
		: acceleration(acceleration), friction(friction), pAttrs(cDef.pAttrs), cDef(cDef), nextShoot(0.f),
          Hurtable(gm, sf::Vector3f(pos.x, pos.y, 0.f), sf::Vector3f(48.f, 24.f, 54.f),
                   ResourceManager::get<TMD>(cDef.spriteTexture), 2, 6)
{
	setFlags(EntityFlags::GLOW | EntityFlags::COLLIDE);
	game.spawnLight(this, 10.f, sf::Color(105, 105, 70), 1.f, 300.f);
	setMaxHealth(pAttrs.maxHealth);
}

void Player::tick(float dt)
{
	Hurtable::tick(dt);

	// movement
	sf::Vector2f acc;
	if (KeyBindings::isBindPressed("player", "move_up"))
		acc.y -= 1.f;
	if (KeyBindings::isBindPressed("player", "move_left"))
		acc.x -= 1.f;
	if (KeyBindings::isBindPressed("player", "move_down"))
		acc.y += 1.f;
	if (KeyBindings::isBindPressed("player", "move_right"))
		acc.x += 1.f;

	float norm = acc.x*acc.x + acc.y*acc.y;
	if (norm > 0.f)
	{
		norm = std::sqrt(norm);
		velocity += acceleration*acc*dt/norm;
	}
	
	float speed = std::sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
    if (speed > pAttrs.maxSpeed)
        velocity = pAttrs.maxSpeed*velocity/speed;
	if (speed > 0.f)
		velocity -= velocity*friction*dt;
    if (speed > 50.f) {
        if (!anim.isPlaying("walk"))
            anim.play("walk", true);
    } else {
        if (!anim.isPlaying("idle"))
            anim.play("idle");
    }

	move(velocity*dt);

	// shooting and direction
	if (nextShoot > 0.f)
		nextShoot -= dt;

	sf::Vector2f shootDir;
	if (KeyBindings::isBindPressed("player", "shoot_up"))
		shootDir = sf::Vector2f(0.f, -1.f);
	else if (KeyBindings::isBindPressed("player", "shoot_right"))
		shootDir = sf::Vector2f(1.f, 0.f);
	else if (KeyBindings::isBindPressed("player", "shoot_down"))
		shootDir = sf::Vector2f(0.f, 1.f);
	else if (KeyBindings::isBindPressed("player", "shoot_left"))
		shootDir = sf::Vector2f(-1.f, 0.f);

	if (shootDir.x*shootDir.x + shootDir.y*shootDir.y > 0.f)
	{
		if (shootDir.x != 0.f)
			setScale(-shootDir.x, 1.f);
		shoot(velocity, shootDir);
	}
	else
	{
		if (velocity.x > 0.f)
			setScale(-1.f, 1.f);
		else
			setScale(1.f, 1.f);
	}
}

void Player::onCollide(Entity &other)
{
	auto mAABB = getAABB();
	auto mzAABB = getZAABB();
	auto tAABB = other.getAABB();
	auto tzAABB = other.getZAABB();

	// check base overlaps
	int x, y;
	if (tAABB.left > mAABB.left)
		x = tAABB.left - (mAABB.left + mAABB.width) - 1;
	else
		x = (tAABB.left + tAABB.width) - mAABB.left + 1;
	if (tAABB.top > mAABB.top)
		y = tAABB.top - (mAABB.top + mAABB.height) - 1;
	else
		y = (tAABB.top + tAABB.height) - mAABB.top + 1;

	// check Z overlaps
	int zx, zy;
	if (tzAABB.left > mzAABB.left)
		zx = tzAABB.left - (mzAABB.left + mzAABB.width) - 1;
	else
		zx = (tzAABB.left + tzAABB.width) - mzAABB.left + 1;
	if (tzAABB.top > mzAABB.top)
		zy = tzAABB.top - (mzAABB.top + mzAABB.height) - 1;
	else
		zy = (tzAABB.top + tzAABB.height) - mzAABB.top + 1;

	if (std::abs(zx) < std::abs(x))
		x = zx;
	if (std::abs(zy) < std::abs(y))
		y = zy;

    if (!other.hasFlags(EntityFlags::TRIGGER)) {
        if (std::abs(x) > std::abs(y))
            move(0.f, static_cast<float>(y));
        else
            move(static_cast<float>(x), 0.f);
    }

    if (other.hasFlags(EntityFlags::HURTFUL)) {
        hurt(1);
        velocity += 10.f*(getPosition() - other.getPosition());
    }

	other.onPlayerCollide(*this);
}

void Player::shoot(const sf::Vector2f &vel, const sf::Vector2f &dir)
{
	if (nextShoot <= 0.0f)
	{
        std::shared_ptr<const TMD> tex = ResourceManager::get<TMD>(cDef.magicTexture);
		game.spawnEntity("magic", tex, getPosition() + 25.f*dir, 0.7f*vel, dir, cDef.magicColor,
                         pAttrs.projectileSpeed, 3.5f, pAttrs.damage, 100.f);
		nextShoot = pAttrs.shootDelay;
	}
}

void Player::onHurt(int d) {
	Hurtable::onHurt(d);
	SoundEngine::playSound("hurt.wav");
    if (getHealth() <= 0)
        game.playerDeath();
}

#include "Entity.hpp"
#include "EntityFlags.hpp"
#include "States/GameState.hpp"
#include "ResourceManager.hpp"

Entity::Entity(GameState &game, const sf::Vector3f &pos, const sf::Vector3f s, TMD &tex, 
	std::uint64_t m, int h)
	: IBaseEntity(sf::Vector2f(pos.x, pos.y)), anim(tex), game(game), height(pos.z), collision_mask(m),
	size(s), health(h), hurtFlash(0.f)
{
	setTexture(tex);
	if (!tmd->isAnimated())
	{
		setOrigin(tex.getStaticOrigin());
		setScale(tex.getStaticScale());
		setColor(tex.getStaticColor());
	} 
	else
	{
		anim.play("idle", true);
	}
}

void Entity::tick(float dt)
{
	if (tmd->isAnimated())
	{
		anim.tick(dt);

		sf::Vector2f orig;
		sf::Vector2f scale;
		sf::IntRect rect;
		sf::Color col;
		anim.getCurrentFrame(orig, scale, col, rect);

		setOrigin(orig);
		setScale(scale);
		setColor(col);
		setTextureRect(rect);
	}

	if (hurtFlash > 0.f)
		hurtFlash -= dt;
}

void Entity::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
	// draw the shadow
	if (height > 0.f)
	{
		std::shared_ptr<TMD> shadowTex = ResourceManager::get<TMD>("shadow.tmd");
		sf::Sprite shadow(shadowTex->getDiffuseTexture());
		shadow.setOrigin(shadowTex->getStaticOrigin());
		shadow.setPosition(getPosition());
		shadow.setScale(shadowTex->getStaticScale());
		rt.draw(shadow);
	}

	//// draw the base bounding box
	//auto aabb = getAABB();
	//sf::RectangleShape r(sf::Vector2f(aabb.width, aabb.height));
	//r.setPosition(aabb.left, aabb.top);
	//r.setFillColor(sf::Color::Transparent);
	//r.setOutlineThickness(1.f);
	//r.setOutlineColor(sf::Color::Red);
	//rt.draw(r);

	//// draw the vert bounding boc
	//auto vaabb = getZAABB();
	//sf::RectangleShape h(sf::Vector2f(vaabb.width, vaabb.height));
	//h.setPosition(vaabb.left, vaabb.top);
	//h.setFillColor(sf::Color::Transparent);
	//h.setOutlineThickness(1.f);
	//h.setOutlineColor(sf::Color::Green);
	//rt.draw(h);

	if (hurtFlash > 0.f)
	{
		auto sh = ResourceManager::get<Shader>("color_override.fsh");
		sh->setParameter("color", sf::Color::Red);
		states.shader = sh.get();
	}

	states.transform.translate(-sf::Vector2f(0.f, height));
	IBaseEntity::draw(rt, states);
}

void Entity::render(sf::RenderTarget &diffuse, sf::RenderTarget &glow)
{
	// draw the diffuse texture
	if (!hasFlags(EntityFlags::NODRAW))
	{
		if (tmd->getDiffuseShader() != nullptr)
			diffuse.draw(*this, tmd->getDiffuseShader());
		else
			diffuse.draw(*this);

		// draw occlusion to the lightmap to block lights behind us
		std::shared_ptr<Shader> sh = ResourceManager::get<Shader>("ambient.fsh");
		sh->setParameter("texture", sf::Shader::CurrentTexture);
		sh->setParameter("ambient", game.getAmbientColor());
		glow.draw(*this, sh.get());
	}

	// draw our glow to the light map
	if (hasFlags(EntityFlags::GLOW))
	{
		IBaseEntity::setTexture(tmd->getGlowTexture(), false);
		if (tmd->getGlowShader() != nullptr)
			glow.draw(*this, tmd->getGlowShader());
		else
			glow.draw(*this);
		IBaseEntity::setTexture(tmd->getDiffuseTexture(), false);
	}
}

void Entity::setTexture(const TMD &tex)
{
	tmd = &tex;
	IBaseEntity::setTexture(tex.getDiffuseTexture());
	anim.setTexture(tex);
	if (!tex.isAnimated())
	{
		setOrigin(tex.getStaticOrigin());
		setScale(tex.getStaticScale());
	}
}

float Entity::getHeight() const
{
	return height;
}

void Entity::setHeight(float h)
{
	height = h;
}

sf::IntRect Entity::getAABB() const
{
	sf::Vector2f base_size {size.x, size.y};
	return { static_cast<sf::Vector2i>(IBaseEntity::getPosition() - base_size / 2.f), 
		static_cast<sf::Vector2i>(base_size)};
}

sf::IntRect Entity::getZAABB() const
{
	sf::Vector2f base_size{ size.x, -size.z };
	return{ static_cast<sf::Vector2i>(IBaseEntity::getPosition() - sf::Vector2f(0.f, height)
		- sf::Vector2f(base_size.x / 2.f, 0.f)),
		static_cast<sf::Vector2i>(base_size) };
}

void Entity::hurt(int d)
{
	if (hasFlags(EntityFlags::INVUNERABLE))
		return;

	if (tmd->isAnimated() && tmd->hasAnimation("hurt"))
	{
		anim.play("hurt", [&]()
		{
			anim.play("idle");
		});
	}
	else
	{
		hurtFlash = 0.14f;
	}

	setHealth(getHealth() - d);
	onHurt(d);
}

void Entity::setHealth(int h)
{
	health = h;
}

int Entity::getHealth() const
{
	return health;
}

// static
void Entity::checkCollision(Entity &a, Entity &b)
{
	if (a.collision_mask & b.collision_mask)
		return;

	sf::IntRect ab = a.getAABB();
	sf::IntRect azb = a.getZAABB();
	sf::IntRect bb = b.getAABB();
	sf::IntRect bzb = b.getZAABB();

	if (ab.intersects(bb) && azb.intersects(bzb))
	{
		a.onCollide(b);
		b.onCollide(a);
	}
}

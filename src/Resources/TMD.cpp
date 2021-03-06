#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "json/json.h"

#include "Logging.hpp"
#include "ResourceManager.hpp"
#include "TMD.hpp"
#include "IBaseResource.hpp"


/*
	TMD parsing methods
*/
template <typename T>
bool readVector2(const Json::Value &root, const std::string &n, sf::Vector2<T> &v)
{
	const Json::Value node = root[n];
	if (node.isNull())
		return false;
	std::istringstream stream(node.asString());
	stream >> v.x >> v.y;
	return true;
}

bool readColor(const Json::Value &root, const std::string &n, sf::Color &c)
{
	const Json::Value node = root[n];
	if (node.isNull())
		return false;
	int r, g, b, a;
	std::istringstream stream(node.asString());
	stream >> r >> g >> b;
	if (!stream.str().empty())
		stream >> a;
	else
		a = 255;
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return true;
}

bool readString(const Json::Value &root, const std::string &n, std::string &s)
{
	const Json::Value node = root[n];
	if (node.isNull())
		return false;
	s.assign(node.asCString());
	return true;
}

bool readTexture(const Json::Value &root, const std::string &n, std::shared_ptr<const Texture> &t,
                 std::shared_ptr<Shader> &s)
{
	const Json::Value node = root[n];
	if (node.isNull())
		return false;
	if (node.isObject())
	{
		std::string tex;
		if (!readString(node, "texture", tex))
			return false;
		t = ResourceManager::get<Texture>(tex);

		std::string sh;
		if (!readString(node, "shader", sh))
			s = nullptr;
		else
			s = ResourceManager::get_noconst<Shader>(sh);
	}
	else
	{
		t = ResourceManager::get<Texture>(node.asString());
		s = nullptr;
	}
	return true;
}


/*
	TMD class methods
*/
bool TMD::load(const std::string &n)
{
	name = n;

	// open the metadata file
	std::ifstream tmd(("Resources/Textures/" + name).c_str());
	if (!tmd.is_open())
	{
		Logging::Log->error("Can't open TMD file: %s", name.c_str());
		return false;
	}
	std::string content((std::istreambuf_iterator<char>(tmd)), (std::istreambuf_iterator<char>()));

	// parse json
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(content, root))
	{
		Logging::Log->error("Failed to parse TMD file: %s\n%s", name.c_str(), reader.getFormattedErrorMessages().c_str());
		return false;
	}

	// load the diffuse texture
	if (!readTexture(root, "diffuse", diffuse, diffuse_shader))
	{
		Logging::Log->error("TMD file '%s' does not specifiy diffuse texture!", name.c_str());
		return false;
	}

	// load the glow texture
	if (!readTexture(root, "glow", glow, glow_shader))
	{
		glow = nullptr;
		glow_shader = nullptr;
	}

	// get the default origin
	if (!readVector2<float>(root, "origin", origin))
		origin = static_cast<sf::Vector2f>(diffuse->getSize()) / 2.f;

	// get the base scale
	if (!readVector2<float>(root, "scale", scale))
		scale = sf::Vector2f(1.f, 1.f);

	// get the default color override
	if (!readColor(root, "color", color))
		color = sf::Color::White;

	// load the animation information
	const Json::Value anims = root["animation"];
	if (!anims.isNull())
	{
		if (anims.empty())
		{
			Logging::Log->error("Animated TMD file: '%s' must contain atleast one animation!", name.c_str());
			return false;
		}

		animated = true;
		for (auto animData : anims) {
            // load the name
			std::string animName;
			if (!readString(animData, "name", animName))
			{
				Logging::Log->error("Animated TMD file: '%s' contains an animation with no name!", name.c_str());
				return false;
			}

			// load the animation data
			Animation anim;
			anim.frameTime = animData.get("frametime", 0.05).asFloat();

			// origin override
			if (!readVector2<float>(animData, "origin", anim.origin))
				anim.origin = origin;

			// scale multiplier
			if (!readVector2<float>(animData, "scale", anim.scale))
			{
				anim.scale = scale;
			}
			else
			{
				anim.scale.x *= scale.x;
				anim.scale.y *= scale.y;
			}

			// animation color modulation
			if (!readColor(animData, "color", anim.color))
				anim.color = sf::Color::White;
			else
				anim.color = color*anim.color;

			// frames
			const Json::Value frameData = animData["frames"];
			for (const auto &frameIndex : frameData) {
				sf::IntRect frame;
				std::istringstream frameSs(frameIndex.asString());
				frameSs >> frame.left >> frame.top >> frame.width >> frame.height;
				anim.frames.push_back(frame);
			}

			if (anim.frames.empty())
				anim.frames.emplace_back(0, 0, 0, 0);

			animations[animName] = anim;
		}

		// check that an idle animation is present
		if (!animations.count("idle"))
		{
			Logging::Log->error("Animated TMD file: '%s' must contain an idle animation!", name.c_str());
			return false;
		}
	}
	else
	{
		animated = false;
		Animation anim;
		anim.scale = scale;
		anim.origin = origin;
		anim.frameTime = 0.f;
		anim.frames.emplace_back(sf::Vector2i(0, 0), static_cast<sf::Vector2i>(diffuse->getSize()));
		animations["idle"] = anim;
	}

	return true;
}

void TMD::fallback()
{
	diffuse = ResourceManager::get<const Texture>("error.png");
	diffuse_shader = nullptr;
	glow = diffuse;
	glow_shader = ResourceManager::get_noconst<Shader>("white.fsh");
	origin = { 64.f, 64.f };
	scale = { 0.5f, 0.5f };
    color = sf::Color::White;
	animated = false;

	Animation anim;
	anim.scale = scale;
	anim.origin = origin;
	anim.frameTime = 0.f;
	anim.frames.emplace_back(sf::Vector2i(0, 0), static_cast<sf::Vector2i>(diffuse->getSize()));
	animations["idle"] = anim;
}

bool TMD::isAnimated() const
{
	return animated;
}

sf::Vector2f TMD::getStaticOrigin() const
{
	return origin;
}

sf::Vector2f TMD::getStaticScale() const
{
	return scale;
}

sf::Color TMD::getStaticColor() const
{
	return color;
}

bool TMD::hasAnimation(const std::string &name) const
{
	return animations.count(name) > 0;
}

const Animation &TMD::getAnimation(const std::string &n) const
{
	if (!animated)
		return animations.at("idle");

	if (!hasAnimation(n))
	{
		Logging::Log->error("Unknown animation '%s' for TMD: %s", n.c_str(), name.c_str());
		return animations.at("idle");
	}

	return animations.at(n);
}

std::shared_ptr<const Texture> TMD::getDiffuseTexture() const
{
	return diffuse;
}

std::shared_ptr<const Texture> TMD::getGlowTexture() const
{
	return glow;
}

std::shared_ptr<Shader> TMD::getDiffuseShader() const
{
	return diffuse_shader;
}

std::shared_ptr<Shader> TMD::getGlowShader() const
{
	return glow_shader;
}

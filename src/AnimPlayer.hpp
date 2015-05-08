#pragma once

#include <functional>
#include "Resources/TMD.hpp"

class AnimPlayer
{
public:
	AnimPlayer(const TMD &);

	void setTexture(const TMD &);

	void tick(float dt);
	void play(const std::string &anim, bool loop = false);
	void play(const std::string &anim, std::function<void()>);
	void stop();
	void pause();

	bool isPlaying() const;
	bool isPlaying(const std::string &anim) const;

	void getCurrentFrame(sf::Vector2f &origin, sf::Vector2f &scale, sf::Color &col, sf::IntRect &rect) const;

private:
	const TMD *tex;
	const Animation *curAnim;
	std::string curAnimName;
	float curTime;
	unsigned int curFrame;
	bool running;
	bool looping;
	std::function<void()> callback;
};

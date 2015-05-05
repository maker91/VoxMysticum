#include "AnimPlayer.hpp"

AnimPlayer::AnimPlayer(const TMD &tex)
: tex(&tex), curTime(0.f), curFrame(0u), running(false), looping(false),
  curAnimName("idle"), curAnim(&tex.getAnimation("idle"))
{

}

void AnimPlayer::setTexture(const TMD &t)
{
	stop();
	tex = &t;
}

void AnimPlayer::tick(float dt)
{
	if (running)
	{
		curTime += dt;
		if (curTime >= curAnim->frameTime)
		{
			curFrame += 1;
			curTime -= curAnim->frameTime;

			if (curFrame >= curAnim->frames.size())
			{
				curFrame -= 1;
				if (looping)
				{
					curFrame = 0u;
				}
				else
				{
					pause();
					if (callback)
						callback();
				}
			}
		}
	}
}

void AnimPlayer::play(const std::string &anim, bool loop)
{
	if (curAnimName != anim)
	{
		stop();
		curAnimName = anim;
		curAnim = &tex->getAnimation(anim);
	}
	running = true;
	looping = loop;
}

void AnimPlayer::play(const std::string &anim, std::function<void()> clb)
{
	callback = clb;
	play(anim, false);
}

void AnimPlayer::stop()
{
	curAnimName = "";
	curTime = 0.f;
	curFrame = 0u;
	running = false;
	callback = std::function<void()>();
}

void AnimPlayer::pause()
{
	running = false;
}

bool AnimPlayer::isPlaying() const
{
	return running;
}

bool AnimPlayer::isPlaying(const std::string &anim) const
{
	return (running && curAnimName == anim);
}

void AnimPlayer::getCurrentFrame(sf::Vector2f &origin, sf::Vector2f &scale, sf::Color &col, sf::IntRect &rect) const
{
	sf::IntRect r = curAnim->frames[curFrame];
	sf::Vector2f s = curAnim->scale;
	sf::Vector2f o = curAnim->origin;
	sf::Color c = curAnim->color;

	origin.x = o.x;
	origin.y = o.y;
	scale.x = s.x;
	scale.y = s.y;
	col.r = c.r;
	col.g = c.g;
	col.b = c.b;
	col.a = c.a;
	rect.left = r.left;
	rect.top = r.top;
	rect.width = r.width;
	rect.height = r.height;
}
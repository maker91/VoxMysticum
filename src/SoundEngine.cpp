#include <stdexcept>

#include "SoundEngine.hpp"
#include "ResourceManager.hpp"
#include "Logging.hpp"

#include <cmath>

sf::Sound SoundEngine::sounds[MAX_SOUNDS];
sf::Music SoundEngine::music;
bool SoundEngine::fading = false;
float SoundEngine::fadeTarget;
float SoundEngine::fadeRate;

sf::Sound &SoundEngine::playSound(SoundBuffer *buffer, float volume, float pitch, bool loop) {
	sf::Sound &snd = requestSoundObject();
	snd.setBuffer(*buffer);
	snd.setVolume(volume);
	snd.setPitch(pitch);
	snd.setLoop(loop);

	snd.play();
	return snd;
}

sf::Sound &SoundEngine::playSound(const std::string &name, float volume, float pitch, bool loop) {
	sf::Sound &snd = requestSoundObject();
	snd.setBuffer(*ResourceManager::get<SoundBuffer>(name));
	snd.setVolume(volume);
	snd.setPitch(pitch);
	snd.setLoop(loop);

	snd.play();
	return snd;
}

void SoundEngine::tick(float dt)
{
	if (fading)
	{
		float volume = music.getVolume();
		if (std::abs(fadeTarget - volume) <= std::abs(fadeRate*dt))
		{
			music.setVolume(fadeTarget);
			fading = false;
			if (fadeTarget == 0.f)
				music.stop();
		}
		else
		{
			music.setVolume(volume + fadeRate*dt);
		}
	}
}

void SoundEngine::playMusic(const std::string &name, bool loop, float volume, float pitch)
{
	stopMusic();
	music.openFromFile("Resources/Music/" + name);
	music.setVolume(volume);
	music.setPitch(pitch);
	music.play();
}

void SoundEngine::stopMusic()
{
	if (isMusicPlaying())
		music.stop();
}

void SoundEngine::fadeMusicIn(const std::string &name, float t, bool loop, float volume, float picth)
{
	fading = true;
	fadeTarget = volume;
	fadeRate = volume/t;
	playMusic(name, loop, 0.f, picth);
}

void SoundEngine::fadeMusicOut(float t)
{
	fading = true;
	fadeTarget = 0.f;
	fadeRate = -music.getVolume()/t;
}

bool SoundEngine::isMusicPlaying()
{
	return (music.getStatus() == sf::Music::Playing);
}

// optimize
sf::Sound &SoundEngine::requestSoundObject() {
	for (auto &sound : sounds) {
		if (sound.getStatus() == sf::Sound::Status::Stopped) {
			return sound;
		}
	}

	throw std::runtime_error("OUT OF SOUND OBJECTS");
}

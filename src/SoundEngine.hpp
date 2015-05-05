#pragma once

#include <SFML/Audio.hpp>
#include "SoundBuffer.hpp"

#define MAX_SOUNDS 250

class SoundEngine {
private:
	static sf::Sound sounds[MAX_SOUNDS];
	static sf::Music music;

public:
	static sf::Sound &playSound(SoundBuffer *buffer, float volume = 100.f, float pitch = 1.f, bool loop = false);
	static sf::Sound &playSound(const std::string &name, float volume = 100.f, float pitch = 1.f, bool loop = false);

	static void playMusic(const std::string &name, bool loop = true, float volume = 100.f, float pitch = 1.f);
	static void stopMusic();
	static void fadeMusicIn(const std::string &name, float t, bool loop = true, float volume = 100.f, float picth = 1.f);
	static void fadeMusicOut(float t);

	static bool isMusicPlaying();

	static void tick(float dt);

private:
	static sf::Sound &requestSoundObject();
	static bool fading;
	static float fadeTarget;
	static float fadeRate;
};
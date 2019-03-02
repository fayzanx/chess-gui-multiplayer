#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#define NUM_AUD 3

class Signal
{
private:
	//sf::SoundBuffer sound_file[NUM_AUD];
	sf::Music mTracks[NUM_AUD];
	sf::Sound playtrk[NUM_AUD];
public:
	static int sounds;
	Signal();
	~Signal();
};



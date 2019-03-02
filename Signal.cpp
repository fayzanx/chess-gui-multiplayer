#include "Signal.h"



Signal::Signal()
{
	for (int i = 0; i < 10; i++) {
		
		mTracks[0].openFromFile("audio/blip3.ogg");
		mTracks[0].play();
		std::cin.get();
		//mTracks[0].setLoop(true);
		mTracks[0].stop();
	}


}


Signal::~Signal()
{
}

int Signal::sounds = 0;
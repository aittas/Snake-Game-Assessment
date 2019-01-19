#include "SoundManager.h"



SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	//delete memory
	for(SoundListing listing : sounds)
	{
		Mix_FreeChunk(listing.sound);
	}
}

void SoundManager::loadSound(string name, string file)
{
	SoundListing listing;
	listing.name = name;
	listing.sound = Mix_LoadWAV(file.c_str());

	if (listing.sound != NULL)
	{
		sounds.push_back(listing);
	}
}

void SoundManager::playSound(string name)
{
	//loop through list, if match name, play sound
	for(SoundListing listing : sounds)
	{
		if (listing.name == name)
		{
			//play sound we matched by name
			Mix_PlayChannel(-1, listing.sound, 0);
			break;
		}
	}
}

SoundManager SoundManager::soundManager;

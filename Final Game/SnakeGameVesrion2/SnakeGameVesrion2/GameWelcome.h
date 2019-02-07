#pragma once

#include <SDL.h> //main sdl lib
#include <SDL_ttf.h> //sdl lib for text using
#include<SDL_image.h> //sdl lib for image

#include<string>
#include<iostream>

#include<fstream> //to read the high score from file

#include "SoundManager.h"

using namespace std;

class GameWelcome
{

private:

	//the levels of game (snake move faster in harder level)
	int levelEasy = 3; 
	int levelNormal = 2;
	int levelHard = 1;


	//surfaces and textures for the rendering (background image, texts for title, levels, show high score, exit game)
	SDL_Texture* backImgTexture;

	SDL_Surface* titleSurface;
	SDL_Texture* titleTexture;

	SDL_Surface* levelEasySurface;
	SDL_Texture* levelEasyTexture;

	SDL_Surface* levelNormalSurface;
	SDL_Texture* levelNormalTexture;

	SDL_Surface* levelHardSurface;
	SDL_Texture* levelHardTexture;

	SDL_Surface* highScoreSurface;
	SDL_Texture* highScoreTexture;

	SDL_Surface* exitGameSurface;
	SDL_Texture* exitGameTexture;
	

	//function displaying a pop up window with the all time highest score
	int PopUpHighScore(int windowSize);


	//our event for key pressing
	SDL_Event event;

	//some background music
	Mix_Music* welcoming;

public:
	GameWelcome();
	~GameWelcome();

	int ShowScreen(SDL_Renderer* renderer, int windowSize);
};


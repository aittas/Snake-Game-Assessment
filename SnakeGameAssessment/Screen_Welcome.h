#pragma once
#include <SDL.h> //main sdl lib
#include <SDL_ttf.h> //sdl lib for text using
#include<SDL_image.h> //sdl lib for image
#include<string>
#include<iostream>
#include<fstream> //tto read the score from file
using namespace std;

class Screen_Welcome
{
private:
	int windowWidth, windowHeight; //the width and height of the welcoming window
	SDL_Window* window; //to create our window
	SDL_Renderer* renderer; //to create our renderer
	
	int levelEasy, levelNormal, levelHard; //the levels of game(snake move faster in harder level)
	
	TTF_Font* font; //to load our font we will use
	const char* fontPath; //the path of the font
	SDL_Color fontColor; //the color we will use for our font

	//for title text rendering
	SDL_Surface* titleSurface;
	SDL_Texture* titleTexture;
	SDL_Rect titleRect;

	//for backgroung image rendering
	SDL_Texture* backImgTexture;
	SDL_Rect backImgRect;

	//for easy mode option text rendering
	SDL_Surface* levelEasySurface;
	SDL_Texture* levelEasyTexture;
	SDL_Rect levelEasyRect;

	//for normal mode option text rendering
	SDL_Surface* levelNormalSurface;
	SDL_Texture* levelNormalTexture;
	SDL_Rect levelNormalRect;

	//for hard mode option text rendering
	SDL_Surface* levelHardSurface;
	SDL_Texture* levelHardTexture;
	SDL_Rect levelHardRect;

	//for high scores option text rendering
	SDL_Surface* highScoreSurface;
	SDL_Texture* highScoreTexture;
	SDL_Rect highScoreRect;

	//for exit game option text rendering
	SDL_Surface* exitGameSurface;
	SDL_Texture* exitGameTexture;
	SDL_Rect exitGameRect;

	//our event for key pressing
	SDL_Event event;

	//for showing highest score
	void showHighestScore();

public:
	Screen_Welcome(); //constructor
	~Screen_Welcome(); //destructor
	int draw(); //to draw our welcoming screen (returns the level taht user has chosen)
};


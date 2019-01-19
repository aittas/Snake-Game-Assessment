#pragma once

#include <SDL.h> //main sdl lib
#include <SDL_ttf.h> //sdl lib for text using

#include <iostream>
#include <string>
#include <vector>
#include <fstream>//to read/write on file

#include "SoundManager.h"

using namespace std;

class GameRenders
{
public:
	GameRenders();
	~GameRenders();

	//Set the background
	void PrepareWindow(SDL_Renderer* renderer, SDL_Texture* texture, int blockScale, int windowSize);

	//Render Score
	int DrawScore(SDL_Renderer* renderer, int snakeTail_Length, int windowSize);

	//Render Food
	void DrawFood(SDL_Renderer* renderer, SDL_Texture* texture, int snakeFood_X, int snakeFood_Y, int blockScale);

	//Render Snake
	void DrawSnake(SDL_Renderer* renderer, SDL_Texture* textureHead, SDL_Texture* textureTail, int snakeHead_X, int snakeHead_Y, vector<int> snakeTail_X, vector<int> snakeTail_Y, int snakeTail_Length, int blockScale);
	
	//Render Game Over Screen
	int DisplayGameOverScreen(SDL_Renderer* renderer, SDL_Event event, int snakeTail_Length, int windowSize);
};


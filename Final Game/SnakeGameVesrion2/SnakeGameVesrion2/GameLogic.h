#pragma once

#include <iostream>
#include <string>


#include <SDL.h> //Main SDL library
#include <SDL_ttf.h> //Optional SDL library used to display text using renderers
#include <SDL_image.h> //SDL library used for images rendering
#include <SDL_mixer.h> //for sounds

#include <vector>
#include <ctime>

#include "GameRenders.h"

using namespace std;

class GameLogic
{

private:

	//BLOCK FOR SNAKE'S HEAD
	int snakeHead_X; //the current poosition  x  of the snake's head
	int snakeHead_Y; //the current poosition  y  of the snake's head
	int snakeHead_prevX; //the previous poosition  x  of the snake's head
	int snakeHead_prevY; //the previous poosition  y  of the snake's head


	//BLOCKS FOR SNAKE'S TAIL
	int snakeTail_Length = 0; //the length, in blocks, of snake's tail
	vector<int> snakeTail_X; //to hold the positions  x  for the blocks in snake's tail
	vector<int> snakeTail_Y; //to hold the positions  y  for the blocks in snake's tail


	//BLOCK FOR SNAKE'S FOOD
	int snakeFood_X; //the  x  position of snake's food
	int snakeFood_Y; //the  y  position of snake's food
	pair<int, int> snakeFood_XY; // to positions x and y for snake's food in "pair" type
	pair<int, int> GetRandom_snakeFood_XY(int snakeHead_X, int snakeHead_Y, vector<int> snakeTail_X, vector<int> snakeTail_Y, int snakeTail_Length, int blockScale, int windowScale); //function to get randomly new cordinates for snake's food


	//SNAKE MOVEMENTS
	bool moveUp = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool moveDown = false;



	//function to check for collision
	bool IsCollision(int snakeHead_X, int snakeHead_Y, int snakeFood_X, int snakeFood_Y);

	//our event for key pressing
	SDL_Event event;

	//is the speed at which the blocks are updated
	int snakeSpeed;

	//to exit game if any error
	int gameOverValue; //if -1 exiting the game

	

public:
	GameLogic();
	~GameLogic();

	//the game's logic
	void RunGame(SDL_Renderer* renderer, int blockScale, int windowScale, int windowSize, int gameLevel);

};


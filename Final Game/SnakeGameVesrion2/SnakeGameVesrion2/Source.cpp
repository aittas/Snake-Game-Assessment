#include <iostream>
#include <string>

#include <SDL.h> //main sdl lib
#include <SDL_ttf.h> //sdl lib for text using
#include <SDL_image.h> //sdl lib for image
#include <SDL_mixer.h> //for sounds

#include "GameWelcome.h"
#include "GameLogic.h"

using namespace std;


int main(int argc, char* argv[])
{

	/* - INITIALIZE STUFF - */

	//if everything is good to go (inits, window, renderer  )
	bool SDL_Success = true;



	//init everything... sdl2, ttf, sdl image, sdl mixer 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "FAILED SDL INIT ! ";
		SDL_Success = false;
	}

	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & IMG_INIT_PNG | IMG_INIT_JPG))
	{
		cout << "\n FAILED SDL IMAGE INIT ! ";
		SDL_Success = false;
	}

	if (TTF_Init() < 0)
	{
		cout << "\n FAILED TTF INIT ! ...ERROR: " << TTF_GetError() << endl;
		SDL_Success = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == 1)
	{
		cout << "\n FAILED SDL MIXER OPEN ! ...ERROR: " << Mix_GetError() << endl;
		SDL_Success = false;
	}



	//our fullscreen window and renderer (for background and welcoming)
	SDL_DisplayMode dm;//to get the desktop width and height
	if (SDL_GetDesktopDisplayMode(0, &dm))
	{
		cout << "\n FAILED TO GET DESKTOP DISPLAY MODE";
		SDL_Success = false;
	}
	cout <<  "\n dm.w: "<< dm.w <<" dm.h: " <<dm.h;

	SDL_Window* windowBACK = SDL_CreateWindow("SnakeBack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_SHOWN);
	if (windowBACK == NULL)
	{
		cout << "\n FAILED TO CREATE WINDOW BACK ! ";
		SDL_Success = false;
	}

	SDL_Renderer* rendererBACK = SDL_CreateRenderer(windowBACK, -1, SDL_RENDERER_ACCELERATED);
	if (rendererBACK == NULL)
	{
		cout << "\n RENDERER BACK FAILED !";
		SDL_Success = false;
	}

	int w, h; //some output to check window's width and height
	SDL_GetWindowSize(windowBACK, &w, &h);
	cout << "\n W: " << w << " H: " << h;
	


	//our game's window and renderer (according to desktop's height)
	int blockScale = 30; //the size or our blocks (food, snake head, snake tails blocks, etc..) 
	
	int windowScale = static_cast<int>(dm.h / blockScale); //the window scale ,.. is to be used during the game loop with the blockScale for different calculation
	cout << "\n window scale (static_cast<int>(dm.h / blockScale)) :   " << windowScale; //some output to check 
	
	int windowSize = windowScale * blockScale; //we mutiply 'windowScale' with the 'blockScale' to get the size of our window (width will be equal to height)
	
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize, windowSize, SDL_WINDOW_BORDERLESS | SDL_WINDOW_HIDDEN); //dont want to show it yet
	if (window == NULL)
	{
		cout << "\n FAILED TO CREATE WINDOW ! ";
		SDL_Success = false;
	}
	
	SDL_Renderer* renderer = renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		cout << "\n RENDERER FAILED !";
		SDL_Success = false;
	}



	//If initializing went wrong..
	if (SDL_Success == false)
	{
		IMG_Quit(); //shuts down sdl image sub system
		SDL_Quit(); //shuts down all sdl sub systems
		TTF_Quit(); //de-initialize TTF engine
		Mix_CloseAudio(); //close audio

		cout << endl << "EXITING PROGRAM . . .\n";
		system("pause");
		
		return 0;
	}







	/* - GAME - */


	// load all game-sound relevant
	SoundManager::soundManager.loadSound("buttonPressed", "assets/effect.wav"); //when user choose an option
	SoundManager::soundManager.loadSound("food", "assets/eatapple.wav"); //when snake ate its apple
	SoundManager::soundManager.loadSound("gameover", "assets/gameover.wav"); //when game is over



	//welcome screen
	GameWelcome* welcome = new GameWelcome();
	int gameLevel = welcome->ShowScreen(rendererBACK, w); // returns the game level according to user's selection (3->Easy, 2->Normal, 1-> Hard)
	cout << "\n Game Level Value: " << gameLevel <<"\n";

	

	// run game
	SDL_ShowWindow(window); //now, show our game's window (dont remove the background)
	GameLogic* game = new GameLogic();
	if (gameLevel != -1)//if user did not exit (did not close the window or press 'Esc')
		game->RunGame(renderer, blockScale, windowScale, windowSize, gameLevel);	
	
	





	/* - EXITING - */

	//EXITING
	cout << " \n\n\n EXITING PROGRAM . . . \n";
	


	//free memory

	welcome->~GameWelcome();
	delete welcome;
	
	delete game;

	SDL_DestroyWindow(windowBACK);
	SDL_DestroyRenderer(rendererBACK);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	IMG_Quit(); //shuts down sdl image sub system
	SDL_Quit(); //shuts down all sdl sub systems
	TTF_Quit(); //de-initialize TTF engine
	Mix_CloseAudio(); //close audio


	cout << endl;
	system("pause");
	
	return 0;
}

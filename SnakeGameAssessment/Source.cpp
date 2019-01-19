#include <iostream>
#include <SDL.h> //main sdl lib
#include <SDL_ttf.h> //sdl lib for text using
#include<SDL_image.h> //sdl lib for image
#include "Screen_Welcome.h"

using namespace std;

int main(int argc, char* argv[])
{
	
	//init everything... sdl2, ttf, sdl image
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		cout << "FAILED SDL INIT ! ";
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & IMG_INIT_PNG | IMG_INIT_JPG))
		cout << "FAILED SDL IMAGE INIT ! ";
	if (TTF_Init() < 0)
		cout << "FAILED TTF INIT ! ...ERROR: " << TTF_GetError() << endl;


	

	//welcome screen
	Screen_Welcome* sw = new Screen_Welcome();
	int gameLevel = sw->draw();
	
	sw->~Screen_Welcome();
	delete sw;


	// *** RUN GAME ***
	cout << " \n Game to start running at " <<gameLevel <<" speed level ! \n";
	system("pause");


	cout << " \n\n\n EXIT PROGRAM . . . \n";
	system("pause");
	SDL_Quit(); //shuts down all sdl sub systems
	TTF_Quit(); //de-initialize TTF engine
	return 0;
}
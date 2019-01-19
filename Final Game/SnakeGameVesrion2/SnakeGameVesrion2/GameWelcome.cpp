#include "GameWelcome.h"



int GameWelcome::PopUpHighScore(int windowSize)
{
	//create a new window and renderer
	int width = windowSize / 4;
	int height = windowSize / 4;

	SDL_Window* scoreWindow = SDL_CreateWindow("HIGHEST SCORE !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer* scoreRenderer = SDL_CreateRenderer(scoreWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int w, h;
	SDL_GetWindowSize(scoreWindow, &w, &h);
	cout << "\n W: " << w << " H: " << h;



	//Get the font
	TTF_Font* myFont = TTF_OpenFont((char*)"assets/arial.ttf", 50);
	if (myFont == NULL)
	{
		//font not loaded? print an error and return
		cout << "\n HIGH SCORE WINDOW - error loading my font" << endl;
		//return;
	}



	//Set a color for the font
	SDL_Color whiteFontColor = { 255, 255, 255};



	//Get current highest scor from file
	int scoreFromFile;
	ifstream InputFile("assets/HighestScore.txt");
	if (InputFile.is_open())
	{
		InputFile >> scoreFromFile;
		cout << " Hihest score is: " << scoreFromFile;
		InputFile.close();
	}



	//Create the surfaces and textures
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(myFont, (string("Highest Score: " + to_string(scoreFromFile))).c_str(), whiteFontColor);
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(scoreRenderer, scoreSurface);
	SDL_FreeSurface(scoreSurface);//free memory
	
	SDL_Surface* gobackSurface = TTF_RenderText_Solid(myFont, (string(" press 'B' to go back . . . ")).c_str(), whiteFontColor);
	SDL_Texture* gobackTexture = SDL_CreateTextureFromSurface(scoreRenderer, gobackSurface);
	SDL_FreeSurface(gobackSurface);//free memory



	//Close the font
	TTF_CloseFont(myFont);



	//Create rectangles
	SDL_Rect scoreRect;
	scoreRect.w = width / 1.5;
	scoreRect.h = height / 4;
	scoreRect.x = (width / 2) - (scoreRect.w / 2);
	scoreRect.y = (height / 2) - scoreRect.h;

	SDL_Rect gobackRect;
	gobackRect.w = width / 2;
	gobackRect.h = height / 6;
	gobackRect.x = (width / 2) - (gobackRect.w / 2);
	gobackRect.y = height / 2;



	//Rendering
	SDL_SetRenderDrawColor(scoreRenderer, 0, 64, 0, 255); //'army/dark green'

	SDL_RenderClear(scoreRenderer);

	SDL_RenderCopy(scoreRenderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(scoreRenderer, gobackTexture, NULL, &gobackRect);

	SDL_RenderPresent(scoreRenderer);



	//controls
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			//User closes window or press 'Esc'
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				SoundManager::soundManager.playSound("buttonPressed");//play some sound
				return -1;
			}
			//User press 'B'
			else if (event.key.keysym.scancode == SDL_SCANCODE_B)
			{
				SoundManager::soundManager.playSound("buttonPressed");//play some sound

				// destroy window, renderer and free pointers
				SDL_DestroyWindow(scoreWindow);
				SDL_DestroyRenderer(scoreRenderer);
				SDL_DestroyTexture(scoreTexture);
				SDL_DestroyTexture(gobackTexture);

				return 1;
			}
		}
	}

}



GameWelcome::GameWelcome()
{
}



GameWelcome::~GameWelcome()
{
	//free all pointers textures, as  well !
	SDL_DestroyTexture(backImgTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(levelEasyTexture);
	SDL_DestroyTexture(levelNormalTexture);
	SDL_DestroyTexture(levelHardTexture);
	SDL_DestroyTexture(highScoreTexture);
	SDL_DestroyTexture(exitGameTexture);
}



int GameWelcome::ShowScreen(SDL_Renderer * renderer, int windowSize)
{
	//Get the font
	TTF_Font* myFont = TTF_OpenFont((char*)"assets/trashco.ttf", 100);
	if (myFont == NULL)
	{
		//font not loaded? print an error and return
		cout << "\n WELCOME SCREEN - error loading my font" << endl;
		//return;
	}



	//Set a color for the font
	SDL_Color blackFontColor = { 0,0,0 };



	//Create the surfaces and textures
	backImgTexture = IMG_LoadTexture(renderer, "assets/snakeBack.png");

	titleSurface = TTF_RenderText_Solid(myFont, (string(" Snake Game ")).c_str(), blackFontColor);
	titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
	SDL_FreeSurface(titleSurface);

	levelEasySurface = TTF_RenderText_Solid(myFont, (string(" E - Easy Mode ")).c_str(), blackFontColor);
	levelEasyTexture = SDL_CreateTextureFromSurface(renderer, levelEasySurface);
	SDL_FreeSurface(levelEasySurface);

	levelNormalSurface = TTF_RenderText_Solid(myFont, (string(" N - Normal Mode ")).c_str(), blackFontColor);
	levelNormalTexture = SDL_CreateTextureFromSurface(renderer, levelNormalSurface);
	SDL_FreeSurface(levelNormalSurface);

	levelHardSurface = TTF_RenderText_Solid(myFont, (string(" H - Hard Mode ")).c_str(), blackFontColor);
	levelHardTexture = SDL_CreateTextureFromSurface(renderer, levelHardSurface);
	SDL_FreeSurface(levelHardSurface);
	
	highScoreSurface = TTF_RenderText_Solid(myFont, (string(" S - Highest Score ")).c_str(), blackFontColor);
	highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
	SDL_FreeSurface(highScoreSurface);
	
	exitGameSurface = TTF_RenderText_Solid(myFont, (string(" Esc - Exit Game ")).c_str(), blackFontColor);
	exitGameTexture = SDL_CreateTextureFromSurface(renderer, exitGameSurface);
	SDL_FreeSurface(exitGameSurface);



	//Close the font
	TTF_CloseFont(myFont);



	//Create rectangles
	SDL_Rect backImgRect;
	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm))
		cout << "\n FAILED TO GET DESKTOP DISPLAY MODE in game welcome .cpp";
	backImgRect = { 0, 0, dm.w, dm.h };

	SDL_Rect titleRect;
	titleRect.w = windowSize / 2;
	titleRect.h = 100;
	titleRect.x = (windowSize / 2) - (titleRect.w / 2);
	titleRect.y = 130;

	SDL_Rect levelEasyRect;
	levelEasyRect.w = windowSize / 3;
	levelEasyRect.h = 75;
	levelEasyRect.x = (windowSize / 2) - (levelEasyRect.w / 2);
	levelEasyRect.y = titleRect.y + 200;

	SDL_Rect levelNormalRect;
	levelNormalRect = { levelEasyRect.x, levelEasyRect.y + 75,	 levelEasyRect.w, 75 };

	SDL_Rect levelHardRect;
	levelHardRect = { levelEasyRect.x, levelNormalRect.y + 75, levelEasyRect.w, 75 };
	
	SDL_Rect highScoreRect;
	highScoreRect = { levelEasyRect.x, levelHardRect.y + 75,	 levelEasyRect.w, 75 };
	
	SDL_Rect exitGameRect;
	exitGameRect = { levelEasyRect.x, highScoreRect.y + 75,	 levelEasyRect.w, 75 };



	//Rendering
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, backImgTexture, NULL, &backImgRect);
	SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(renderer, levelEasyTexture, NULL, &levelEasyRect);
	SDL_RenderCopy(renderer, levelNormalTexture, NULL, &levelNormalRect);
	SDL_RenderCopy(renderer, levelHardTexture, NULL, &levelHardRect);
	SDL_RenderCopy(renderer, highScoreTexture, NULL, &highScoreRect);
	SDL_RenderCopy(renderer, exitGameTexture, NULL, &exitGameRect);

	SDL_RenderPresent(renderer);



	//Controls
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			//User closes window or press 'Esc'
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				SoundManager::soundManager.playSound("buttonPressed");//play some sound
				return -1;
			}
			//Options...
			else
			{
				//User press 'E'
				if (event.key.keysym.scancode == SDL_SCANCODE_E)
				{
					SoundManager::soundManager.playSound("buttonPressed");//play some sound
					return levelEasy;
				}

				//User press 'N'
				else if (event.key.keysym.scancode == SDL_SCANCODE_N) 
				{
					SoundManager::soundManager.playSound("buttonPressed");//play some sound
					return levelNormal;
				}	

				//User press 'H'
				else if (event.key.keysym.scancode == SDL_SCANCODE_H)
				{
					SoundManager::soundManager.playSound("buttonPressed");//play some sound
					return levelHard;
				}

				//User press 'S'
				else if (event.key.keysym.scancode == SDL_SCANCODE_S)
				{
					SoundManager::soundManager.playSound("buttonPressed");//play some sound
					if (PopUpHighScore(windowSize) == -1)
					{
						return -1;
					}
				}
					
			}
		}
	}


}

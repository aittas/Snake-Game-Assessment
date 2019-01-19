#include "Screen_Welcome.h"



void Screen_Welcome::showHighestScore()
{
	//get font
	string pathString = "Fonts/arial.ttf";
	const char* fontPath = pathString.c_str();
	TTF_Font* fontScore = TTF_OpenFont(fontPath, 50);
	if (fontScore == NULL)
		cout << "ERROR LOADING FONT(score screen) ";

	SDL_Color whiteColor = { 255,255,255 };

	int scoreFromFile;
	ifstream InputFile ("HighestScore.txt");
	if (InputFile.is_open())
	{
		InputFile >> scoreFromFile;
		cout << " Hihest score is: " << scoreFromFile;
		InputFile.close();
	}
	
	SDL_Window* scoreWindow = SDL_CreateWindow("SCORES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth/2, windowHeight/2, SDL_WINDOW_SHOWN);
	SDL_Renderer* scoreRenderer = SDL_CreateRenderer(scoreWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* scoreSurface = TTF_RenderText_Solid(fontScore, (string("Highest Score: " + to_string(scoreFromFile))).c_str(), whiteColor);
	SDL_Surface* gobackSurface = TTF_RenderText_Solid(fontScore, (string(" press 'B' to go back . . . ")).c_str(), whiteColor);

	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(scoreRenderer, scoreSurface);
	SDL_Texture* gobackTexture = SDL_CreateTextureFromSurface(scoreRenderer, gobackSurface);

	SDL_Rect scoreRect = {25,30,200,70};
	SDL_Rect gobackRect = { 5,150,250,30 };

	SDL_SetRenderDrawColor(scoreRenderer, 0, 64, 0, 255);
	SDL_RenderClear(scoreRenderer);
	
	SDL_RenderCopy(scoreRenderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(scoreRenderer, gobackTexture, NULL, &gobackRect);
	SDL_RenderPresent(scoreRenderer);

	//controls
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_B)
			{
				SDL_DestroyWindow(scoreWindow);
				SDL_DestroyRenderer(scoreRenderer);
				SDL_FreeSurface(scoreSurface);
				SDL_FreeSurface(gobackSurface);
				SDL_DestroyTexture(scoreTexture);
				SDL_DestroyTexture(gobackTexture);
				TTF_CloseFont(fontScore);
				return;
			}
		}
	}
}



Screen_Welcome::Screen_Welcome()
{
	//set the width and height for the window
	windowWidth = windowHeight = 30 * 24;

	//create the window
	window = SDL_CreateWindow("Welcome to Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	//create our renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//levels
	levelEasy = 120; //slow speed
	levelNormal = 80; //normal speed
	levelHard = 40; //fast
}

Screen_Welcome::~Screen_Welcome()
{
	//free all pointers as well
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_DestroyTexture(titleTexture);
	SDL_FreeSurface(titleSurface);

	SDL_DestroyTexture(backImgTexture);

	SDL_DestroyTexture(levelEasyTexture);
	SDL_FreeSurface(levelEasySurface);

	SDL_DestroyTexture(levelNormalTexture);
	SDL_FreeSurface(levelNormalSurface);

	SDL_DestroyTexture(levelHardTexture);
	SDL_FreeSurface(levelHardSurface);

	SDL_DestroyTexture(highScoreTexture);
	//SDL_FreeSurface(highScoreSurface);

	SDL_DestroyTexture(exitGameTexture);
	//SDL_FreeSurface(exitGameSurface);

	//delete font;
	//delete fontPath;
}



int Screen_Welcome::draw()
{
	//get font
	string pathString = "Fonts/trashco.ttf";
	fontPath = pathString.c_str();
	font = TTF_OpenFont(fontPath, 100);
	if (font == NULL)
		cout << "ERROR LOADING FONT(welcome screen) ";

	//set color to font
	fontColor = { 0,0,0 }; //black


	//surfaces
	titleSurface = TTF_RenderText_Solid(font, (string(" Snake Game ")).c_str(), fontColor);
	levelEasySurface = TTF_RenderText_Solid(font, (string(" E - Easy Mode ")).c_str(), fontColor);
	levelNormalSurface = TTF_RenderText_Solid(font, (string(" N - Normal Mode ")).c_str(), fontColor);
	levelHardSurface = TTF_RenderText_Solid(font, (string(" H - Hard Mode ")).c_str(), fontColor);
	highScoreSurface = TTF_RenderText_Solid(font, (string(" S - Highest Score ")).c_str(), fontColor);
	exitGameSurface = TTF_RenderText_Solid(font, (string(" Esc - Exit Game ")).c_str(), fontColor);

	//close font
	TTF_CloseFont(font);


	//textures
	titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
	backImgTexture = IMG_LoadTexture(renderer, "Images/snakeBack.png");
	levelEasyTexture = SDL_CreateTextureFromSurface(renderer, levelEasySurface);
	levelNormalTexture = SDL_CreateTextureFromSurface(renderer, levelNormalSurface);
	levelHardTexture = SDL_CreateTextureFromSurface(renderer, levelHardSurface);
	highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
	exitGameTexture = SDL_CreateTextureFromSurface(renderer, exitGameSurface);


	//rectangles
	titleRect.w = windowWidth / 2;
	titleRect.h = 100;
	titleRect.x = (windowWidth / 2) - (titleRect.w / 2);
	titleRect.y = 70;

	backImgRect = { 0,0,windowWidth,windowHeight };

	levelEasyRect.w = windowWidth / 3;
	levelEasyRect.h = 75;
	levelEasyRect.x = (windowWidth / 2) - (levelEasyRect.w / 2);
	levelEasyRect.y = windowHeight / 4;

	levelNormalRect = { levelEasyRect.x, levelEasyRect.y + 75,	 levelEasyRect.w, 75 };
	levelHardRect = { levelEasyRect.x, levelNormalRect.y + 75, levelEasyRect.w, 75 };
	highScoreRect = { levelEasyRect.x, levelHardRect.y + 75,	 levelEasyRect.w, 75 };
	exitGameRect = { levelEasyRect.x, highScoreRect.y + 75,	 levelEasyRect.w, 75 };


	//rendering
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, backImgTexture, NULL, &backImgRect);
	SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
	SDL_RenderCopy(renderer, levelEasyTexture, NULL, &levelEasyRect);
	SDL_RenderCopy(renderer, levelNormalTexture, NULL, &levelNormalRect);
	SDL_RenderCopy(renderer, levelHardTexture, NULL, &levelHardRect);
	SDL_RenderCopy(renderer, highScoreTexture, NULL, &highScoreRect);
	SDL_RenderCopy(renderer, exitGameTexture, NULL, &exitGameRect);

	SDL_RenderPresent(renderer);


	//controls
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				SDL_Quit(); //shuts down all sdl sub systems
				TTF_Quit(); //de-initialize TTF engine

				//exit
				exit(0);
			}
			else
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_E)
					return levelEasy;
				else if (event.key.keysym.scancode == SDL_SCANCODE_N)
					return levelNormal;
				else if (event.key.keysym.scancode == SDL_SCANCODE_H)
					return levelHard;
				else if (event.key.keysym.scancode == SDL_SCANCODE_S)
					showHighestScore();
			}
		}
	}


	
}

#include "GameRenders.h"



GameRenders::GameRenders()
{
}



GameRenders::~GameRenders()
{
}



void GameRenders::PrepareWindow(SDL_Renderer * renderer, SDL_Texture * texture, int blockScale, int windowSize)
{
	for (int y = 0; y <= windowSize - blockScale; y = y + blockScale)
	{
		for (int x = 0; x <= windowSize - blockScale; x = x + blockScale)
		{
			SDL_Rect rect = { x, y, blockScale, blockScale };
			SDL_RenderCopy(renderer, texture, NULL, &rect);
		}
	}
}



int GameRenders::DrawScore(SDL_Renderer* renderer, int snakeTail_Length, int windowSize)
{
	//Get the font
	TTF_Font* myFont = TTF_OpenFont((char*)"assets/arial.ttf", 50);
	if (myFont == NULL)
	{
		cout << "\n *************************************";
		cout << "\n *** SCORE - error loading my font ***";
		cout << "\n *************************************";
		return -1;
	}
		
	

	//Set a color for the font
	SDL_Color myFontColor = { 255,255,255 };



	//Create the surfaces and textures
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(myFont, (string("Score: ") + to_string(snakeTail_Length * 10)).c_str(), myFontColor);
	SDL_Texture* score = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_FreeSurface(scoreSurface); //free memory

	TTF_CloseFont(myFont); //Close the font



	//Create rectangles
	SDL_Rect scoreRect;
	scoreRect.w = 350;
	scoreRect.h = 100;
	scoreRect.x = (windowSize / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;


	
	//Rendering
	SDL_RenderCopy(renderer, score, NULL, &scoreRect);



	//destroy score
	SDL_DestroyTexture(score);
}



void GameRenders::DrawFood(SDL_Renderer * renderer, SDL_Texture * texture, int snakeFood_X, int snakeFood_Y, int blockScale)
{
	//Create the rectangle
	SDL_Rect foodRect;
	foodRect.x = snakeFood_X;
	foodRect.y = snakeFood_Y;
	foodRect.w = blockScale - 4;
	foodRect.h = blockScale - 4;

	//rendering
	SDL_RenderCopy(renderer, texture, NULL, &foodRect);
}



void GameRenders::DrawSnake(SDL_Renderer * renderer, SDL_Texture * textureHead, SDL_Texture * textureTail, int snakeHead_X, int snakeHead_Y, vector<int> snakeTail_X, vector<int> snakeTail_Y, int snakeTail_Length, int blockScale)
{
	/* SNAKE'S HEAD */

	//Create the rectangle (we can use it for both of head and tail)
	SDL_Rect snakeRect;
	snakeRect.x = snakeHead_X;
	snakeRect.y = snakeHead_Y;
	snakeRect.w = blockScale - 5;
	snakeRect.h = blockScale - 2;

	//rendering the SNAKE'S HEAD
	SDL_RenderCopy(renderer, textureHead, NULL, &snakeRect);



	/* SNAKE'S TAIL */

	for (int i = 0; i < snakeTail_Length; i++)
	{
		snakeRect.x = snakeTail_X[i];
		snakeRect.y = snakeTail_Y[i];;
		snakeRect.w = blockScale;
		snakeRect.h = blockScale;

		//rendering the SNAKE'S TAIL
		SDL_RenderCopy(renderer, textureTail, NULL, &snakeRect);
	}
}



int GameRenders::DisplayGameOverScreen(SDL_Renderer * renderer, SDL_Event event, int snakeTail_Length, int windowSize)
{
	//update score in file - if we have higher score
	int currentScore = snakeTail_Length * 10;
	int scoreFromFile;
	
	ifstream InputFile("assets/HighestScore.txt");
	if (InputFile.is_open())
	{
		InputFile >> scoreFromFile;
		InputFile.close();
	}

	if (currentScore>scoreFromFile)
	{
		ofstream myfile("assets/HighestScore.txt");
		if (myfile.is_open())
		{
			myfile << currentScore;
			cout << "\n Highest score was: " << scoreFromFile;
			cout << "\n  New Highscore is: " << currentScore;
			myfile.close();
		}
	}
	


	//Get the font
	TTF_Font* myFont = TTF_OpenFont((char*)"assets/arial.ttf", 10);
	if (myFont == NULL)
	{
		cout << "\n ************************************************";
		cout << "\n *** GAME OVER SCREEN - error loading my font ***";
		cout << "\n ************************************************";

		return -1;
	}



	//Set a color for the font
	SDL_Color myFontColor_Black = { 0,0,0 }; //for score & retry texts
	SDL_Color myFontColor_White = { 255,255,255 }; //for game over text



	//Create the surfaces and textures (score, game over and retry)
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(myFont, (string("Score: ") + to_string(currentScore)).c_str(), myFontColor_Black);
	SDL_Texture* score = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_FreeSurface(scoreSurface); //free memory

	SDL_Surface* gameoverSurface = TTF_RenderText_Solid(myFont, "Game Over", myFontColor_White);
	SDL_Texture* gameover = SDL_CreateTextureFromSurface(renderer, gameoverSurface);
	SDL_FreeSurface(gameoverSurface); //free memory

	SDL_Surface* retrySurface = TTF_RenderText_Solid(myFont, "Press Enter to retry. . .", myFontColor_Black);
	SDL_Texture* retry = SDL_CreateTextureFromSurface(renderer, retrySurface);
	SDL_FreeSurface(retrySurface); //free memory

	TTF_CloseFont(myFont);//Close the font



	//Create rectangles
	SDL_Rect scoreRect; //score
	scoreRect.w = 300;
	scoreRect.h = 100;
	scoreRect.x = (windowSize / 2) - (scoreRect.w / 2);
	scoreRect.y = 50;

	SDL_Rect gameoverRect; //game over
	gameoverRect.w = 550;
	gameoverRect.h = 200;
	gameoverRect.x = (windowSize / 2) - (gameoverRect.w / 2);
	gameoverRect.y = scoreRect.y + scoreRect.h + 100;

	SDL_Rect retryRect; //retry
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = (windowSize / 2) - (retryRect.w / 2);
	retryRect.y = gameoverRect.y + gameoverRect.h + 100;

	SDL_Rect backRect;//background
	backRect.w = windowSize;
	backRect.h = windowSize;
	backRect.x = 0;
	backRect.y = 0;
	


	//Rendering
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//red
	SDL_RenderFillRect(renderer, &backRect);

	SDL_RenderCopy(renderer, score, NULL, &scoreRect);
	SDL_RenderCopy(renderer, gameover, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retry, NULL, &retryRect);
	


	//destroy - free memory
	SDL_DestroyTexture(score);
	SDL_DestroyTexture(gameover);
	SDL_DestroyTexture(retry);


	
	//Show game over screen until user...........
	while (true)
	{
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) //close or the 'Esc' key
			{
				SoundManager::soundManager.playSound("buttonPressed");//play some sound
				return -1;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) //the 'Enter' key
			{
				SoundManager::soundManager.playSound("buttonPressed");//play some sound
				return 1;
			}
		}
	}


}

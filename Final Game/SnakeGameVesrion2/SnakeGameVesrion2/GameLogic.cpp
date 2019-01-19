#include "GameLogic.h"
#include "SoundManager.h"



pair<int, int> GameLogic::GetRandom_snakeFood_XY(int snakeHead_X, int snakeHead_Y, vector<int> snakeTail_X, vector<int> snakeTail_Y, int snakeTail_Length, int blockScale, int windowScale)
{
	/*	DESC.:
	Finds a vaild location for the food.
	Location should Not be the same with snake's head
	Location should Not be the same with any of the blocks of snake's tail
	*/

	int x = 0; //random  x  position on screen to put food's block 
	int y = 0; //random  y  position on screen to put food's block 


	bool valid = false;
	while (!valid)
	{
		/*
		*	Random Location: 
		*	Remember width & height of our window('windowSize') equal to  'blockScale' times 'windowScale'. (**Declared in Source.cpp)
		*	So, using 'blockScale' and 'windowScale' we can generate a location inside the window!  )
		*/
		srand(time(0));
		x = blockScale * (rand() % windowScale);
		y = blockScale * (rand() % windowScale);

		//make valid true
		valid = true;

		//check for any possible collision between the random generated positions(x,y) and snake's blocks(head & tail)
		for (int i = 0; i < snakeTail_Length; i++)
		{
			if ((x == snakeTail_X[i] && y == snakeTail_Y[i]) || (x == snakeHead_X && y == snakeHead_Y))
			{
				valid = false;//if so, food location is not valid
			}
		}
	}


	//Create and return a pair of the two position values
	pair <int, int> FoodLocation = make_pair(x, y);

	return FoodLocation;
}



bool GameLogic::IsCollision(int snakeHead_X, int snakeHead_Y, int snakeFood_X, int snakeFood_Y)
{
	//checks the x and y positions for snake and food's block
	if (snakeHead_X == snakeFood_X && snakeHead_Y == snakeFood_Y)
	{
		//if they are same we have collision
		return true;
	}

	return false;
}



GameLogic::GameLogic()
{
}



GameLogic::~GameLogic()
{
}



void GameLogic::RunGame(SDL_Renderer* renderer, int blockScale, int windowScale, int windowSize, int gameLevel)
{
	//load up music & play
	Mix_Music* music = Mix_LoadMUS("assets/playscreen.ogg");
	if (music == NULL)
	{
		cout << "\n ***************************";
		cout << "\n *** ERROR LOADING MUSIC (in game logic ,first call)***";
		cout << "\n ***************************";
	}
	Mix_PlayMusic(music, -1);



	//TEXTURES - images for backgound blocks, snake and food
	SDL_Texture* blocksImage = IMG_LoadTexture(renderer, "assets/block.png"); //a white blocks for the background

	SDL_Texture* snakeHeadImage_faceUP = IMG_LoadTexture(renderer, "assets/faceUP.png"); //snake faces up
	SDL_Texture* snakeHeadImage_faceLEFT = IMG_LoadTexture(renderer, "assets/faceLEFT.png"); //snake faces left
	SDL_Texture* snakeHeadImage_faceRIGHT = IMG_LoadTexture(renderer, "assets/faceRIGHT.png"); //snake faces right
	SDL_Texture* snakeHeadImage_faceDOWN = IMG_LoadTexture(renderer, "assets/faceDOWN.png"); //snake faces down
	SDL_Texture* snakeHeadImage = IMG_LoadTexture(renderer, "assets/faceDOWN.png"); //set as default to face down 

	SDL_Texture* snakeTailImage = IMG_LoadTexture(renderer, "assets/tailSnake.png"); //snake's tail

	SDL_Texture* foodImage = IMG_LoadTexture(renderer, "assets/food.png"); //an apple for snake's food



	//snake first position (left top corner)
	snakeHead_X = 0; 
	snakeHead_Y = 0;



	//snake's food random position
	snakeFood_XY = GetRandom_snakeFood_XY(snakeHead_X, snakeHead_Y, snakeTail_X, snakeTail_Y, snakeTail_Length, blockScale, windowScale);
	snakeFood_X = snakeFood_XY.first;
	snakeFood_Y = snakeFood_XY.second;



	// - GAME - 
	GameRenders* gr = new GameRenders();
	snakeSpeed = gameLevel * 40; //set the speed
	float lastT = SDL_GetTicks() / 100;//Used for delaying movement of blocks
	bool GameLoop = true;

	while (GameLoop)
	{
		//TIME MANAGEMENT
		float newT = SDL_GetTicks() / snakeSpeed; 
		float DT = newT - lastT;
		lastT = newT;



		//CONTROLS
		if (SDL_PollEvent(&event))
		{
			//Exit Game when window / screen closed OR 'Esc' pressed
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				SoundManager::soundManager.playSound("buttonPressed");//play some sound

				Mix_PausedMusic();//stop music from playing
				Mix_FreeMusic(music);//delete song from memory

				GameLoop = false;
			}

			//Set directions for the snake's movements
			if (event.type == SDL_KEYDOWN)//when a key is pressed....
			{
				//UP - cant go up when is moving down, so bool down should be false
				if (event.key.keysym.scancode == SDL_SCANCODE_UP && moveDown == false)
				{
					moveUp = true;

					moveLeft = false;
					moveRight = false;
					moveDown = false;
				}

				//LEFT - cant go left when is moving right, so bool right should be false
				else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT && moveRight == false)
				{
					moveLeft = true;

					moveUp = false;
					moveRight = false;
					moveDown = false;
				}

				//RIGHT - cant go right when is moving left, so bool left should be false
				else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT && moveLeft == false)
				{
					moveRight = true;

					moveUp = false;
					moveLeft = false;	
					moveDown = false;
				}

				//DOWN - cant go down when is moving up, so bool up should be false
				else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && moveUp == false)
				{
					moveDown = true;

					moveUp = false;
					moveLeft = false;
					moveRight = false;				
				}
			}
		}



		//The previous position of the snake block, these are used so tail blocks will never be on the snake block's position
		snakeHead_prevX = snakeHead_X;
		snakeHead_prevY = snakeHead_Y;



		//Set image for snake head and also make it move at the same speed regardless of framerate (otherwise snake will move too fast)
		if (moveUp)
		{
			snakeHead_Y -= DT * blockScale;
			snakeHeadImage = snakeHeadImage_faceUP;
		}
		else if (moveLeft)
		{
			snakeHead_X -= DT * blockScale;
			snakeHeadImage = snakeHeadImage_faceLEFT;
		}
		else if (moveRight)
		{
			snakeHead_X += DT * blockScale;
			snakeHeadImage = snakeHeadImage_faceRIGHT;
		}
		else if (moveDown)
		{
			snakeHead_Y += DT * blockScale;
			snakeHeadImage = snakeHeadImage_faceDOWN;
		}



		//COLLISSION DETECTION (when snake has eaten the food)
		if (IsCollision(snakeHead_X, snakeHead_Y, snakeFood_X, snakeFood_Y))
		{
			cout << "\n Snake ate its food";

			//play some sound
			SoundManager::soundManager.playSound("food");

			//Get new food location 
			snakeFood_XY = GetRandom_snakeFood_XY(snakeHead_X, snakeHead_Y, snakeTail_X, snakeTail_Y, snakeTail_Length, blockScale, windowScale);
			snakeFood_X = snakeFood_XY.first;
			snakeFood_Y = snakeFood_XY.second;

			//Tail becomes one block longer
			snakeTail_Length++;
		}

		

		//Only runs in the frames where the snake block has moved
		if (DT*blockScale == blockScale) 
		{
			//Update tail size and position
			//If the size of the tail isn't equal to the actual size, add another block to the tail (this needs to be first)
			//If this is not first the program will later attempt to check and move an amount of tail blocks equal to the snakeTail_Length -
			//(which is constantly updated), although the extra tail block hasn't been added, causing a crash
			if (snakeTail_X.size() != snakeTail_Length) 
			{
				snakeTail_X.push_back(snakeHead_prevX);
				snakeTail_Y.push_back(snakeHead_prevY);
			}

			//Loop through every tail block, move all blocks to the nearest block in front
			//This updates the blocks from end (farthest from snake head block) to the start (nearest to snake head block)
			for (int i = 0; i < snakeTail_Length; i++)
			{
				if (i > 0) 
				{
					snakeTail_X[i - 1] = snakeTail_X[i];
					snakeTail_Y[i - 1] = snakeTail_Y[i];
				}
			}

			//If the tail has grown, change the nearest tail block position to the snake head block position (needs to be last, otherwise, the 2 first blocks stack)
			//The tail blocks will stack because the 2nd block will always have an updated position to the first block
			//While the third block and the rest have an outdated position to the block infront
			if (snakeTail_Length > 0)
			{
				snakeTail_X[snakeTail_Length - 1] = snakeHead_prevX;
				snakeTail_Y[snakeTail_Length - 1] = snakeHead_prevY;
			}
		}

		

		//GAME OVER 1 (if snake head hits tail)
		for (int i = 0; i < snakeTail_Length; i++)  
		{
			if (snakeHead_X == snakeTail_X[i] && snakeHead_Y == snakeTail_Y[i])
			{
				cout << "\n Snake hit its tail";

				Mix_PausedMusic();//stop music from playing
				Mix_FreeMusic(music);//delete song from memory

				SoundManager::soundManager.playSound("gameover");//play some sound


				//***GAME OVER RENDERING********
				gameOverValue = gr->DisplayGameOverScreen(renderer, event, snakeTail_Length, windowSize); 
				if (gameOverValue == -1)
					GameLoop = false;


				//reseting....
				music = Mix_LoadMUS("assets/playscreen.ogg");
				if (music == NULL)
				{
					cout << "\n ***************************";
					cout << "\n *** ERROR LOADING MUSIC (in game loop)***";
					cout << "\n ***************************";
				}
				Mix_PlayMusic(music, 1);

				snakeHead_X = 0;
				snakeHead_Y = 0;

				snakeTail_Length = 0;

				snakeTail_X.clear();
				snakeTail_Y.clear();

				snakeFood_XY = GetRandom_snakeFood_XY(snakeHead_X, snakeHead_Y, snakeTail_X, snakeTail_Y, snakeTail_Length, blockScale, windowScale);
				snakeFood_X = snakeFood_XY.first;
				snakeFood_Y = snakeFood_XY.second;
				
				moveUp = false;
				moveLeft = false;
				moveRight = false;
				moveDown = false;

				snakeHeadImage = snakeHeadImage_faceDOWN;
			}
		}

		//GAME OVER 2 (if snake hits the boundaries)
		if (snakeHead_X < 0 || snakeHead_Y < 0 || snakeHead_X > windowSize - blockScale || snakeHead_Y > windowSize - blockScale)
		{
			cout << "\n Snake hit on boundaries";

			Mix_PausedMusic();//stop music from playing
			Mix_FreeMusic(music);//delete song from memory

			SoundManager::soundManager.playSound("gameover");//play some sound


			//***GAME OVER RENDERING********
			gameOverValue = gr->DisplayGameOverScreen(renderer,event,snakeTail_Length,windowSize); 
			if (gameOverValue == -1)
				GameLoop = false;


			//reseting....
			music = Mix_LoadMUS("assets/playscreen.ogg");
			if (music == NULL)
			{
				cout << "\n ***************************";
				cout << "\n *** ERROR LOADING MUSIC (in game loop)***";
				cout << "\n ***************************";
			}
			Mix_PlayMusic(music, 1);

			snakeHead_X = 0;
			snakeHead_Y = 0;

			snakeTail_Length = 0;

			snakeTail_X.clear();
			snakeTail_Y.clear();			

			snakeFood_XY = GetRandom_snakeFood_XY(snakeHead_X, snakeHead_Y, snakeTail_X, snakeTail_Y, snakeTail_Length, blockScale, windowScale);
			snakeFood_X = snakeFood_XY.first;
			snakeFood_Y = snakeFood_XY.second;

			moveUp = false;
			moveLeft = false;
			moveRight = false;
			moveDown = false;

			snakeHeadImage = snakeHeadImage_faceDOWN;
		}



		//RENDERING (background, score, food, and snake) 
		gr->PrepareWindow(renderer, blocksImage, blockScale, windowSize);
		gameOverValue = gr->DrawScore(renderer, snakeTail_Length, windowSize);
		if (gameOverValue == -1)
			GameLoop = false;
		gr->DrawFood(renderer, foodImage, snakeFood_X, snakeFood_Y, blockScale);
		gr->DrawSnake(renderer, snakeHeadImage, snakeTailImage, snakeHead_X, snakeHead_Y, snakeTail_X, snakeTail_Y, snakeTail_Length, blockScale);
		
		SDL_RenderPresent(renderer);

		SDL_RenderClear(renderer); //clear render before the next frame
	}



	//Free Memory
	if (music != NULL)
		Mix_FreeMusic(music);

	SDL_DestroyTexture(blocksImage);

	SDL_DestroyTexture(snakeHeadImage_faceUP);
	SDL_DestroyTexture(snakeHeadImage_faceLEFT);
	SDL_DestroyTexture(snakeHeadImage_faceRIGHT);
	SDL_DestroyTexture(snakeHeadImage_faceDOWN);
	SDL_DestroyTexture(snakeHeadImage);

	SDL_DestroyTexture(snakeTailImage);

	SDL_DestroyTexture(foodImage);	

	delete gr;
}

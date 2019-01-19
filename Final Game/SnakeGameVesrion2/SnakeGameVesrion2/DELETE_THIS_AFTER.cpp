#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SDL_image.h>
#include <SDL.h> //Main SDL library
#include <SDL_ttf.h> //Optional SDL library used to display text using renderers

using namespace std;

void prepareWindow(SDL_Renderer* renderer, SDL_Texture* texture)
{

	for (int y = 0; y <= (30 * 24) - 30; y = y + 30)
	{
		for (int x = 0; x <= (30 * 24) - 30; x = x + 30)
		{
			SDL_Rect rect = { x,y,30,30 };
			SDL_RenderCopy(renderer, texture, NULL, &rect);
		}
	}
}

void renderPlayer(SDL_Renderer* renderer, SDL_Texture* textureHead, SDL_Texture* textureTail, SDL_Rect player, int x, int y, int scale, vector<int> tailX, vector<int> tailY, int tailLength)
{
	player.w = scale - 5;
	player.h = scale - 2;
	player.x = x;
	player.y = y;
	SDL_RenderCopy(renderer, textureHead, NULL, &player);



	for (int i = 0; i < tailLength; i++)
	{
		player.x = tailX[i];
		player.y = tailY[i];;
		player.w = scale;
		player.h = scale;

		//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //0, 255, 0 same with food
		//SDL_RenderFillRect(renderer, &snakeRect);

		SDL_RenderCopy(renderer, textureTail, NULL, &player);
	}



	////Setting color before rendering, needs to be set first each time or the block could get a color from another block
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//player.w = scale;
	//player.h = scale;

	////Gets x and y of all tail blocks and renders them
	//for (int i = 0; i < tailLength; i++) {
	//	player.x = tailX[i];
	//	player.y = tailY[i];
	//	SDL_RenderFillRect(renderer, &player);
	//}

	//player.x = x;
	//player.y = y;

	//SDL_RenderFillRect(renderer, &player);
}

void renderFood(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect food)
{

	food.w = 30 - 4;
	food.h = 30 - 4;
	SDL_RenderCopy(renderer, texture, NULL, &food);


	/*SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &food);*/
}

void renderScore(SDL_Renderer* renderer,  int tailLength, int scale, int wScale)
{
	SDL_Color myColor = { 0, 100, 0 };

	//Get the font used for displaying text
	TTF_Font* font = TTF_OpenFont((char*)"assets/arial.ttf", 50);
	if (font == NULL) {
		//font not loaded? print an error and return
		cout << "SCORE SECTION - Font loading error" << endl;
		return;
	}

	//c_str() allows normal strings to be rendered here, otherwise the rendered text would have to be a const char* type
	//Const char* values cannot be changed after initialization, but we need dynamic text here
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), myColor);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect scoreRect;
	scoreRect.w = 270;
	scoreRect.h = 90;
	scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;

	/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect bb;
	bb.w = scoreRect.w;
	bb.h = scoreRect.h;
	bb.x = scoreRect.x;
	bb.y = 0;
	SDL_RenderFillRect(renderer, &bb);*/


	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	//Close font before finishing so this font doesn't collide with any other function's font
	TTF_CloseFont(font);


	////////c_str() allows normal strings to be rendered here, otherwise the rendered text would have to be a const char* type
	////////Const char* values cannot be changed after initialization, but we need dynamic text here
	//////score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), myColor);
	//////if (score == NULL)
	//////{
	//////	cout << "\n\n SURFACE  null";
	//////	if ( font == NULL)
	//////	{
	//////		cout << "/n FONT: null ";
	//////	}
	//////	if ((string("Score: ") + to_string(tailLength * 10)).c_str() == NULL)
	//////	{
	//////		cout << "\n TEXT: " << (string("Score: ") + to_string(tailLength * 10)).c_str();
	//////	}
	//////}

	//////scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	//////if (scoreMessage == NULL)
	//////{
	//////	cout << "\n\n TEXTURE  null";
	//////}
	//////	
	//////
	//////SDL_Rect scoreRect;
	//////scoreRect.w = 150; //100;  //(30 * 24) / 2;
	//////scoreRect.h = 30; //30*2;
	//////scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	//////scoreRect.y = 0;

	//////SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//////SDL_Rect bb;
	//////bb.w = scoreRect.w;
	//////bb.h = scoreRect.h;
	//////bb.x = scoreRect.x;
	//////bb.y = 0;
	//////SDL_RenderFillRect(renderer, &bb);


	//////SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	////////Close font before finishing so this font doesn't collide with any other function's font
	//////TTF_CloseFont(font);
}

bool checkCollision(int foodx, int foody, int playerx, int playery) {
	//Very simple, if x and y of the player block is the same as a food block
	if (playerx == foodx && playery == foody) {
		//Then return true
		return true;
	}
	return false;
}

pair <int, int> getFoodSpawn(vector <int> tailX, vector <int> tailY, int playerX, int playerY, int scale, int wScale, int tailLength) {
	//Get a valid spawn for the food which is not on top of a tail or player block
	bool valid = false;
	int x = 0;
	int y = 0;

	while (!valid) 
	{
		srand(time(0));
		x = scale * (rand() % wScale);
		y = scale * (rand() % wScale);

		valid = true;

		//Check all tail blocks and player block
		for (int i = 0; i < tailLength; i++)
		{
			if ((x == tailX[i] && y == tailY[i]) || (x == playerX && y == playerY)) 
			{
				valid = false;
			}
		}

	}

	//Create and return a pair of the two position values
	pair <int, int> foodLoc;
	foodLoc = make_pair(x, y);

	return foodLoc;
}

int gameOver(SDL_Renderer* renderer, SDL_Event event, int scale, int wScale, int tailLength)
{
	SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };


	//Get the font used for displaying text
	TTF_Font* font = TTF_OpenFont((char*)"assets/arial.ttf", 10);
	if (font == NULL) {
		//font not loaded? print an error and return
		cout << "GAME OEVR SCREEN - Font loading error" << endl;
		return 1;
	}


	//c_str() allows normal strings to be rendered here, otherwise the rendered text would have to be a const char* type
	//Const char* values cannot be changed after initialization, but we need dynamic text here
	//We re-render the score in the game over screen so the player can still see their score
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(tailLength * 10)).c_str(), Black);
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over", White);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to retry", Black);

	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);


	SDL_Rect scoreRect;
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;

	scoreRect.w = 300;
	scoreRect.h = 100;
	scoreRect.x = ((scale*wScale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 50;

	gameoverRect.w = 550;
	gameoverRect.h = 200;
	gameoverRect.x = ((scale*wScale) / 2) - (gameoverRect.w / 2);
	gameoverRect.y = ((scale*wScale) / 2) - (gameoverRect.h / 2) - 50;

	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((scale*wScale) / 2) - ((retryRect.w / 2));
	retryRect.y = (((scale*wScale) / 2) - ((retryRect.h / 2)) + 150);


	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//red
	SDL_Rect bb;
	bb.w = scale * wScale;
	bb.h = scale * wScale;
	bb.x = 0;
	bb.y = 0;
	SDL_RenderFillRect(renderer, &bb);

	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);


	//Close font before finishing so this font doesn't collide with any other function's font
	TTF_CloseFont(font);



	//Show game over screen while space has not been pressed
	while (true)
	{
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				return -1;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) //ENTER
			{
				return 1;
			}
		}
	}
}




int AAAAAAAAAAAAAAAAAmain(int argc, char* argv[]) {

	//Init everything so we have everything
	SDL_Init(SDL_INIT_EVERYTHING);

	//Init TTF and check for any errors
	if (TTF_Init() < 0) {
		cout << "Error: " << TTF_GetError() << endl;
	}

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	//This is the player rectangle, set all values to 0
	SDL_Rect player;
	player.x = 0;
	player.y = 0;
	player.h = 0;
	player.w = 0;

	//tailLength is incremented every time the snake eats food
	//Used in for loops to determine how many times they have to run
	int tailLength = 0;

	//Vectors for storage of tail block positions
	//Vectors are used because they don't need to have a fixed size, unlike normal arrays
	vector<int> tailX;
	vector<int> tailY;

	//These values change scale of blocks and scale of window (wScale)
	//They are later multiplied with eachother to allow easy change of window size according to block size
	int scale = 30;
	int wScale = 24;

	//Default values of player position values
	int x = 30;
	int y = 30;
	int prevX = 0;
	int prevY = 0;

	//Booleans to control the movement
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	//This is the food rectangle, set all values to 0
	//Except for the x and y coordinates, which will be set to something random inside the window area
	SDL_Rect food;
	food.w = scale;
	food.h = scale;
	food.x = 0;
	food.y = 0;

	pair <int, int> foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
	food.x = foodLoc.first;
	food.y = foodLoc.second;

	//Show the window with these settings and apply a renderer to it
	//The renderer is responsible for all graphics being displayed
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scale*wScale, scale*wScale, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Used for delaying movement of blocks
	float time = SDL_GetTicks() / 100;


	//textures
	SDL_Texture* blocksImage = IMG_LoadTexture(renderer, "assets/white.png");

	SDL_Texture* snakeHeadImage_faceUP = IMG_LoadTexture(renderer, "assets/faceUP.png");
	SDL_Texture* snakeHeadImage_faceLEFT = IMG_LoadTexture(renderer, "assets/faceLEFT.png");
	SDL_Texture* snakeHeadImage_faceRIGHT = IMG_LoadTexture(renderer, "assets/faceRIGHT.png");
	SDL_Texture* snakeHeadImage_faceDOWN = IMG_LoadTexture(renderer, "assets/faceDOWN.png");
	SDL_Texture* snakeHeadImage_default = IMG_LoadTexture(renderer, "assets/faceDOWN.png");
	SDL_Texture* snakeHeadImage = snakeHeadImage_default;

	SDL_Texture* snakeTailImage = IMG_LoadTexture(renderer, "assets/tailSnake.png");
	SDL_Texture* foodImage = IMG_LoadTexture(renderer, "assets/food.png");


	////Get the font used for displaying text
	//TTF_Font* myFont = TTF_OpenFont((char*)"arial.ttf", 50);
	//if (myFont == NULL) {
	//	//font not loaded? print an error and return
	//	cout << "My Font loading error" << endl;
	//	//return;
	//}
	//SDL_Color RandomColor = { 10, 24, 254 };

	////SCORE
	//SDL_Surface* ScoreSurface = TTF_RenderText_Solid(myFont, (string("RANDOM-TEXT")).c_str(), RandomColor );
	//SDL_Texture* ScoreTexture = SDL_CreateTextureFromSurface(renderer, ScoreSurface);

	////GAME OVER
	//SDL_Surface* GameOverSurface = TTF_RenderText_Solid(myFont, (string("RANDOM-TEXT")).c_str(), RandomColor);
	//SDL_Texture* GameOverTexture = SDL_CreateTextureFromSurface(renderer, GameOverSurface);

	//TTF_CloseFont(myFont);

	int exitValue = -1;





	//Main game loop, this constantly runs and keeps everything updated
	bool GameLoop = true;
	while (GameLoop)
	{
		//Used to delay the movement of blocks
		float newTime = SDL_GetTicks() / 75; //This value (75) is the speed at which the blocks are updated
		float delta = newTime - time;
		time = newTime;


		//Controls
		if (SDL_PollEvent(&event))
		{
			//If user tries to exit window, exit program
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				GameLoop = false;
			}
			//If a key is pressed
			if (event.type == SDL_KEYDOWN)
			{
				//Then check for the key being pressed and change direction accordingly
				if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
					up = true;
					left = false;
					right = false;
					down = false;
				}
				else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					up = false;
					left = true;
					right = false;
					down = false;
				}
				else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					up = false;
					left = false;
					right = false;
					down = true;
				}
				else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					up = false;
					left = false;
					right = true;
					down = false;
				}
			}
		}


		//The previous position of the player block, these are used so tail blocks will never be on the player block's position
		prevX = x;
		prevY = y;


		//delta*xMovementPerTick
		//This makes the player move at the same speed regardless of framerate
		//Without this the player would move way too fast
		if (up)
		{
			y -= delta * scale;
			snakeHeadImage = snakeHeadImage_faceUP;
		}
		else if (left)
		{
			x -= delta * scale;
			snakeHeadImage = snakeHeadImage_faceLEFT;
		}
		else if (right)
		{
			x += delta * scale;
			snakeHeadImage = snakeHeadImage_faceRIGHT;
		}
		else if (down)
		{
			y += delta * scale;
			snakeHeadImage = snakeHeadImage_faceDOWN;
		}


		//Collision detection, has played collided with food?
		if (checkCollision(food.x, food.y, x, y)) {

			//Spawn new food after it has been eaten
			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			tailLength++;
		}


		//Only runs in the frames where the player block has moved
		if (delta*scale == scale) {
			//Update tail size and position
			//If the size of the tail isn't equal to the actual size, add another block to the tail (this needs to be first)
			//If this is not first the program will later attempt to check and move an amount of tail blocks equal to the tailLength -
			//(which is constantly updated), although the extra tail block hasn't been added, causing a crash
			if (tailX.size() != tailLength) {
				tailX.push_back(prevX);
				tailY.push_back(prevY);
			}

			//Loop through every tail block, move all blocks to the nearest block in front
			//This updates the blocks from end (farthest from player block) to the start (nearest to player block)
			for (int i = 0; i < tailLength; i++) {
				if (i > 0) {
					tailX[i - 1] = tailX[i];
					tailY[i - 1] = tailY[i];
				}
			}

			//If the tail has grown, change the nearest tail block position to the player block position (needs to be last, otherwise, the 2 first blocks stack)
			//The tail blocks will stack because the 2nd block will always have an updated position to the first block
			//While the third block and the rest have an outdated position to the block infront
			if (tailLength > 0) {
				tailX[tailLength - 1] = prevX;
				tailY[tailLength - 1] = prevY;
			}
		}


		//Game over if player has collided with a tail block, also reset everything
		for (int i = 0; i < tailLength; i++)
		{
			if (x == tailX[i] && y == tailY[i])
			{
				exitValue = gameOver(renderer, /*GameOverSurface, GameOverSurface, GameOverSurface, GameOverTexture, GameOverTexture, GameOverTexture,*/ event, scale, wScale, tailLength);
				if (exitValue == -1)
					GameLoop = false;

				x = 0;
				y = 0;
				up = false;
				left = false;
				right = false;
				down = false;
				tailX.clear();
				tailY.clear();
				tailLength = 0;

				foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
				food.x = foodLoc.first;
				food.y = foodLoc.second;

				snakeHeadImage = snakeHeadImage_default;
			}
		}


		//Game over if player out of bounds, also reset everything
		if (x < 0 || y < 0 || x > scale*wScale - scale || y > scale*wScale - scale)
		{
			exitValue = gameOver(renderer, /*GameOverSurface, GameOverSurface, GameOverSurface, GameOverTexture, GameOverTexture, GameOverTexture,*/ event, scale, wScale, tailLength);
			if (exitValue == -1)
				GameLoop = false;

			x = 0;
			y = 0;
			up = false;
			left = false;
			right = false;
			down = false;
			tailX.clear();
			tailY.clear();
			tailLength = 0;

			foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
			food.x = foodLoc.first;
			food.y = foodLoc.second;

			snakeHeadImage = snakeHeadImage_default;
		}



		//Render everything
		prepareWindow(renderer, blocksImage);
		renderScore(renderer, tailLength, scale, wScale);
		renderFood(renderer, foodImage, food);
		renderPlayer(renderer, snakeHeadImage, snakeTailImage, player, x, y, scale, tailX, tailY, tailLength);


		//Put everything on screen
		//Nothing is actually put on screen until this is called
		SDL_RenderPresent(renderer);

		//Choose a color and fill the entire window with it, this resets everything before the next frame
		//It also creates the background color
		//SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
		SDL_RenderClear(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyTexture(blocksImage);
	SDL_DestroyTexture(snakeHeadImage);
	SDL_DestroyTexture(snakeTailImage);
	SDL_DestroyTexture(foodImage);

	/*SDL_FreeSurface(ScoreSurface);
	SDL_DestroyTexture(ScoreTexture);

	SDL_FreeSurface(GameOverSurface);
	SDL_DestroyTexture(GameOverTexture);*/


	TTF_Quit();

	SDL_Quit();



	cout << "/n/n/n exit";
	system("pause");


	return 0;
}
#include <SDL.h>

#include <iostream>
#include <sstream>

#include "vec2D.h"
#include "map.h"
#include "player.h"
#include "InputManager.h"

bool upimageLoaded = false, downimageLoaded = false, rightimageLoaded = false, leftimageLoaded = false; // Very naughty, Bradley, you shouldn't be using evil globals.
int upcheckLoad = 0, downcheckLoad = 0, rightcheckLoad = 0, leftcheckload = 0; // Very naughty, such globals, much evil.

//Functions

int moveMap_Left();
void moveMap_Right(int counter_x, int counter_y, int moveMap_x, int moveMap_y, map earth[], player Player, SDL_Renderer *renderer);
int moveMap_Up();
int moveMap_Down();

int main(int argc, char *argv[])
{
	// This is our initialisation phase
	// SDL_Init is the main initialisation function for SDL
	// It takes a 'flag' parameter which we use to tell SDL what systems we're going to use
	// Here, we want to use SDL's video system, so we give it the flag for this
	// Incidentally, this also initialises the input event system
	// This function also returns an error value if something goes wrong
	// So we can put this straight in an 'if' statement to check and exit if need be
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "Something went very wrong, cannot initialise SDL!" << std::endl;
		return -1;
	}

	// Now we have got SDL initialised, we are ready to create a window!
	// These are some variables to help show you what the parameters are for this function
	// You can experiment with the numbers to see what they do

	const int winWidth = 720;
	const int winHeight = 640;

	int mapWidth = 73;
	int mapHeight = 37;

	SDL_Rect camera = { 0, 0, winWidth, winHeight };

	Uint32 SDL_GetMouseState(int* x, int* y);

	SDL_Window *window = SDL_CreateWindow("Fallout 2.5 - Return To The Wasteland!",  // The first parameter is the window title
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_OPENGL);

	// The last parameter lets us specify a number of options
	// Here, we tell SDL that we want the window to be shown and that it can be resized
	// You can learn more about SDL_CreateWindow here: https://wiki.libsdl.org/SDL_CreateWindow?highlight=%28\bCategoryVideo\b%29|%28CategoryEnum%29|%28CategoryStruct%29
	// The flags you can pass in for the last parameter are listed here: https://wiki.libsdl.org/SDL_WindowFlags

	// The SDL_CreateWindow function returns an SDL_Window
	// This is a structure which contains all the data about our window (size, position, etc)
	// We will also need this when we want to draw things to the window
	// This is therefore quite important we don't lose it!

	// The SDL_Renderer is a structure that handles rendering
	// It will store all of SDL's internal rendering related settings
	// When we create it we tell it which SDL_Window we want it to render to
	// That renderer can only be used for this window
	// (yes, we can have multiple windows - feel free to have a play sometime)

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	vec2D vec2d;

	//INSTANCIATION

	InputManager *Input = new InputManager();

	map *earth[1000];
	for (int i = 0; i < 1000; i++)
	{
		earth[i] = new map();
	}
	for (int i = 0; i < 1000; i++)
	{
		earth[i]->LoadFromPNG("../Assets/earth.png", renderer);
	}
	for (int i = 0; i < 1000; i++)
	{
		earth[i]->setMapPosition_x(73);
		earth[i]->setMapPosition_y(18.5);
	}

	player *Player = new player();
	Player->LoadFromPNG("../Assets/player_full.png", renderer);
	Player->setPlayerPosition_x(100);
	Player->setPlayerPosition_y(100);
	Player->SetDestination(100, 100);
	Player->setID(1);

	//Setting Up FPS

	unsigned int lastTime = SDL_GetTicks();
	Uint32 startTime = SDL_GetTicks();
	int numFrames = 0;


	std::cerr << "checkload:" << upcheckLoad;
	std::cerr << "imageLoaded:" << upimageLoaded;

	bool first_run = false;

	int moveMap_x = 1;
	int moveMap_y = 1;

	int mouse_x = 0;
	int mouse_y = 0;


	int counter_x = 0;
	int counter_y = 0;

	bool go = false;

	bool walking = false;

	while (!first_run)
	{
		bool first = true;
		for (int i = 0; i < 1000; i++)
		{
			int ran = rand() % 10;
			switch (ran)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				earth[i]->setID(0);
				break;
			case 7:
				earth[i]->setID(1);
				break;
			case 8:
				earth[i]->setID(2);
				break;
			case 9:
				earth[i]->setID(3);
				break;
			}

			earth[i]->update(2);

			if (counter_x == 25)
			{
				counter_x = 0;
				counter_y++;
				first = true;
			}

			if (counter_y % 2)
			{
				earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5)), ((earth[i]->getMapPosition_y() * counter_y)), 7, 8, renderer);
				counter_x++;

				if (first)
				{
					earth[i]->setMapPosition_x(-36.5);
					first = false;
				}
				else
				{
					earth[i]->setMapPosition_x(earth[i-1]->getMapPosition_x() + 73);
				}
				earth[i]->setMapPosition_y(earth[i]->getMapPosition_y() * counter_y);
			}
			else
			{				
				earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x)), ((earth[i]->getMapPosition_y() * counter_y)), 7, 8, renderer);
				counter_x++;

				if (first)
				{
					earth[i]->setMapPosition_x(0);
					first = false;
				}
				else
				{
					earth[i]->setMapPosition_x(earth[i-1]->getMapPosition_x() + 73);
				}
				earth[i]->setMapPosition_y(earth[i]->getMapPosition_y() * counter_y);
			}
		}

		SDL_RenderPresent(renderer);
		first_run = true;
		go = true;

	}

	bool cmd_forwards, cmd_backwards, cmd_left, cmd_right, cmd_space, cmd_mouseleft;
	cmd_forwards = cmd_backwards = cmd_left = cmd_right = cmd_space = cmd_mouseleft = false;


	//Main Game Loop
	while (go)
	{
		Input->InputUpdate();

		numFrames++;

		std::stringstream ss;

		int fps = (numFrames / (float)(SDL_GetTicks() - startTime)) * 1000;
		ss << fps;

		unsigned int current = SDL_GetTicks();

		float deltaTs = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		if (deltaTs < (1.0f / 50.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
		}

		bool adjust_x = false;
		int adjustcounter = 1;
		bool finished = true;

		// bind camera

		if (camera.x < 50)
		{
			camera.x = 49;
		}
		if (camera.y < 18)
		{ 
			camera.y = 17;
		}
		if (camera.x > 1785 - camera.w)
		{
			camera.x = 1785 - camera.w;
		}
		if (camera.y > 1517 - camera.h)
		{
			camera.y = 1517 - camera.h;
		}


		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{
			case SDL_QUIT:
				go = false;
				break;

				//When a key is lifted
			case SDL_KEYUP:
				switch (incomingEvent.key.keysym.sym)
				{
				case SDLK_LEFT:
					cmd_left = false;
					break;
				case SDLK_RIGHT:
					cmd_right = false;
					break;
				case SDLK_UP:
					cmd_forwards = false;
					break;
				case SDLK_DOWN:
					cmd_backwards = false;
					break;
				}
				break;
				//When a key is pressed
			case SDL_KEYDOWN:
				switch (incomingEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					go = false;
					break;
				case SDLK_LEFT:
					cmd_left = true;
					break;
				case SDLK_RIGHT:
					cmd_right = true;
					break;
				case SDLK_UP:
					cmd_forwards = true;
					break;
				case SDLK_DOWN:
					cmd_backwards = true;
					break;
				}
				break;
			}

			if (incomingEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (incomingEvent.button.button == SDL_BUTTON_LEFT)
				{
					std::cout << "Left Mouse Button has been pressed! \n";
					cmd_mouseleft = true;
				}

				if (incomingEvent.type == SDL_MOUSEBUTTONUP)
				{
					std::cout << "Left Mouse Button was lifted! \n";
					if (incomingEvent.button.button == SDL_BUTTON_LEFT)
					{
						cmd_mouseleft = false;
					}
				}
			}
		}

		if (cmd_forwards)
		{
			Player->setID(1);
		}
		if (cmd_right)
		{
			Player->setID(2);
		}
		if (cmd_backwards)
		{
			Player->setID(5);
		}
		if (cmd_left)
		{
			Player->setID(6);
		}

		// Draw our world

		// Start by clearing what was drawn before
		// Set the colour for drawing
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		// Clear the entire screen to our selected colour
		SDL_RenderClear(renderer);

		//Mouse Control for movement of the map
		//When the mouse is moved to the side of the screen, it moves the map in the direction.
		SDL_PumpEvents();
		if (SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&mouse_x, &mouse_y);
			if (mouse_x <= 720 && mouse_x >= 670)	//Move screen to the right
			{
				camera.x += 1;
				//moveMap_Right(counter_x, counter_y, moveMap_x, moveMap_x, earth[0], *Player, renderer);
				for (int i = 0; i < 1000; i++)
				{
					if (counter_x == 25)
					{
						counter_x = 0;
						counter_y++;
					}

					if (counter_y % 2)
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() + camera.x, earth[i]->getMapPosition_y() + camera.y, 7, 8, renderer);
						counter_x++;
					}
					else
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() + camera.x, earth[i]->getMapPosition_y() + camera.y, 7, 8, renderer);
						counter_x++;
					}
				}
				//Player->setPlayerPosition_x(-3);
			}
			else
			{
				for (int i = 0; i < 1000; i++)
				{
					if (counter_x == 25)
					{
						counter_x = 0;
						counter_y++;
					}

					if (counter_y % 2)
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
					else
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
				}
			}
			if (mouse_x >= 0 && mouse_x <= 50)	//Move screen to the left
			{
				camera.x -= 1;
				for (int i = 0; i < 1000; i++)
				{
					if (counter_x == 25)
					{
						counter_x = 0;
						counter_y++;
					}

					if (counter_y % 2)
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
					else
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y - moveMap_y)), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}

				}
				//Player->setPlayerPosition_x(3);
			}
			else
			{
				for (int i = 0; i < 1000; i++)
				{
					if (counter_x == 25)
					{
						counter_x = 0;
						counter_y++;
					}

					if (counter_y % 2)
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
					else
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
				}
			}
			if (mouse_y >= 0 && mouse_y <= 50)	//Move screen up
			{
				camera.y -= 1;
				for (int i = 0; i < 1000; i++)
				{
					if (counter_x == 25)
					{
						counter_x = 0;
						counter_y++;
					}

					if (counter_y % 2)
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
					else
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
				}
				//Player->setPlayerPosition_y(3);
			}
			else
			{
				for (int i = 0; i < 1000; i++)
				{
					if (counter_x == 25)
					{
						counter_x = 0;
						counter_y++;
					}

					if (counter_y % 2)
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
					else
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
				}
			}

			if (mouse_y <= 640 && mouse_y >= 590)	//Move screen down
			{
				camera.y += 1;
				for (int i = 0; i < 1000; i++)
				{
					if (counter_x == 25)
					{
						counter_x = 0;
						counter_y++;
					}

					if (counter_y % 2)
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
					else
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
				}
				//Player->setPlayerPosition_y(-3);
			}
			else
			{
				for (int i = 0; i < 1000; i++)
				{
					if (counter_x == 25)
					{
						counter_x = 0;
						counter_y++;
					}

					if (counter_y % 2)
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
					else
					{
						//earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						earth[i]->AnimDraw(earth[i]->getMapPosition_x() - camera.x, earth[i]->getMapPosition_y() - camera.y, 7, 8, renderer);
						counter_x++;
					}
				}
			}
		}
		int frametime = 0;

		if (cmd_mouseleft)
		{
			Player->SetDestination(camera.x + mouse_x, camera.y + mouse_y);
			//Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 29, 67, renderer);
			//Player->setID(7);
			/*
			if (Player->getPlayerPosition_x() < mouse_x && finished) //Player movement to the right on the x axis
			{
			Player->setID(2);
			for (int i = Player->getPlayerPosition_x(); i < mouse_x; i+=5)
			{
			finished = false;
			if (deltaTs < (1.0f / 30.0f))
			{
			SDL_Delay((unsigned int)(((1.0f / 30.0f) - deltaTs)*1000.0f));
			}

			SDL_RenderClear(renderer);

			counter_x = 0;
			counter_y = 0;

			for (int i = 0; i < 1000; i++)
			{
			if (counter_x == 25)
			{
			counter_x = 0;
			counter_y++;
			}

			if (counter_y % 2)
			{
			earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
			counter_x++;
			}
			else
			{
			earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
			counter_x++;
			}
			}

			Player->setPlayerPosition_x(5);
			Player->update_idle(2);
			Player->AnimDraw(Player->getPlayerPosition_x(), Player->getPlayerPosition_y(), 36, 69, renderer);

			SDL_RenderPresent(renderer);
			}
			//finished = true;
			}
			if (Player->getPlayerPosition_x() > mouse_x && finished)		//Player movement to the left on the x axis
			{
			Player->setID(5);
			for (int i = Player->getPlayerPosition_x(); i > mouse_x; i-=5)
			{
			finished = false;
			if (deltaTs < (1.0f / 30.0f))
			{
			SDL_Delay((unsigned int)(((1.0f / 30.0f) - deltaTs)*1000.0f));
			}

			SDL_RenderClear(renderer);

			counter_x = 0;
			counter_y = 0;

			for (int i = 0; i < 1000; i++)
			{
			if (counter_x == 25)
			{
			counter_x = 0;
			counter_y++;
			}

			if (counter_y % 2)
			{
			earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
			counter_x++;
			}
			else
			{
			earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
			counter_x++;
			}
			}

			Player->setPlayerPosition_x(-5);
			Player->update_idle(2);
			Player->AnimDraw(Player->getPlayerPosition_x(), Player->getPlayerPosition_y(), 36, 69, renderer);

			SDL_RenderPresent(renderer);
			}
			finished = false;
			}
			cmd_mouseleft = false;
			*/
			cmd_mouseleft = false;
			walking = true;
		}

		Player->MoveToDest();
		
		if (walking)
		{
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 29, 67, renderer);
 			Player->setID(7);
			Player->update_idle(2);
		}
		else
		{
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 36, 69, renderer);
		}
		std::cout << Player->getPlayerPosition_x() << ", " << Player->getPlayerPosition_y() << std::endl;
		Player->update_idle(2);
		//Player->update_walking(2);
		SDL_RenderPresent(renderer);
	}


	//DELETING MEMORY LOCATIONS
	for (int i = 0; i < 1000; i++)
	{
		delete earth[i];
	}
	delete Player;

	SDL_DestroyWindow(window); // Destroy the window
	SDL_Quit(); // Terminate SDL

	return 0;
}
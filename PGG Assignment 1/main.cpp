#include <SDL.h>

#include <iostream>
#include <sstream>

#include "vec2D.h"
#include "map.h"
#include "player.h"
#include "InputManager.h"

bool upimageLoaded = false, downimageLoaded = false, rightimageLoaded = false, leftimageLoaded = false; // Very naughty, Bradley, you shouldn't be using evil globals.
int upcheckLoad = 0, downcheckLoad = 0, rightcheckLoad = 0, leftcheckload = 0; // Very naughty, such globals, much evil.

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

	int winWidth = 720;
	int winHeight = 640;

	int mapWidth = 73;
	int mapHeight = 37;

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
	Player->LoadFromPNG("../Assets/player_idle.png", renderer);
	Player->setPlayerPosition_x(30);
	Player->setPlayerPosition_y(30);
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

	//int counter_x = 0;
	//int counter_y = 0;

	/*while (!first_run)
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
				earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
				counter_x++;
				earth[i]->setMapPosition_x(earth[i]->getMapPosition_x() * counter_x + 36.5);
				earth[i]->setMapPosition_y(earth[i]->getMapPosition_y() * counter_x + 36.5);
			}
			else
			{
				earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
				counter_x++;
				earth[i]->setMapPosition_x(earth[i]->getMapPosition_x() * counter_x + 36.5);
				earth[i]->setMapPosition_y(earth[i]->getMapPosition_y() * counter_x + 36.5);
			}
		}
		first_run = true;
		go = true;

	}*/

	//Main Game Loop
	while (Input->go)
	{
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

		int counter_x = 0;
		int counter_y = 0;
		bool adjust_x = false;
		int adjustcounter = 1;
		//Added keyboard input		
		
		if (Input->cmd_forwards)
		{
			Player->setID(1);
		}
		if (Input->cmd_right)
		{
			Player->setID(2);
		}
		if (Input->cmd_backwards)
		{
			Player->setID(5);
		}
		if (Input->cmd_left)
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
			if (mouse_x <= 720 && mouse_x >= 670)
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
						earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						counter_x++;
					}
					else
					{
						earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
						counter_x++;
					}
				}
				moveMap_x++;
				moveMap_x++;
				moveMap_x++;
				Player->setPlayerPosition_x(-3);
			}
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
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
				else
				{
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
			}
		}
		if (mouse_x >= 0 && mouse_x <= 50)
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
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
				else
				{
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y - moveMap_y)), 7, 8, renderer);
					counter_x++;
				}
				
			}
			moveMap_x--;
			moveMap_x--;
			moveMap_x--;
			Player->setPlayerPosition_x(3);
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
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
				else
				{
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
			}
		}
		if (mouse_y >= 0 && mouse_y <= 50)
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
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
				else
				{
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
			}
			moveMap_y--;
			moveMap_y--;
			moveMap_y--;
			Player->setPlayerPosition_y(3);
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
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
				else
				{
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
			}
		}
		if (mouse_y <= 640 && mouse_y >= 590)
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
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
				else
				{
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
			}
			moveMap_y++;
			moveMap_y++;
			moveMap_y++;
			Player->setPlayerPosition_y(-3);
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
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x + 36.5) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
				else
				{
					earth[i]->AnimDraw(((earth[i]->getMapPosition_x() * counter_x) - moveMap_x), ((earth[i]->getMapPosition_y() * counter_y) - moveMap_y), 7, 8, renderer);
					counter_x++;
				}
			}
		}
		int frametime = 0;
		if (Input->cmd_mouseleft)
		{
			bool done = false;
			if (Player->getPlayerPosition_x() < mouse_x)
			{
				Player->setID(2);
				for (int i = Player->getPlayerPosition_x(); i < mouse_x; i++)
				{
					if (deltaTs < (1.0f / 50.0f))
					{
						SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
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

					Player->setPlayerPosition_x(1);
					Player->AnimDraw(Player->getPlayerPosition_x(), Player->getPlayerPosition_y(), 36, 69, renderer);
				
					SDL_RenderPresent(renderer);
						
				}
			}
			Input->cmd_mouseleft = false;
		}

		Player->AnimDraw(Player->getPlayerPosition_x(), Player->getPlayerPosition_y(), 36, 69, renderer);

		Player->update_idle(2);
	
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

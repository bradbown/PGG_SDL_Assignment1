#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <sstream>

#include "vec2D.h"
#include "map.h"

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

	bool go = true;
	
	//INSTANCIATION

	//Create new sprites

	map *earth = new map();

	//Load images for sprites

	earth->LoadFromPNG("G:Year 2/Programming for Graphics and Games/PGG_SDL_Assignment1/Assets/earth.png", renderer);

	//Set the starting position of sprites

	earth->setMapPosition_x(0);
	earth->setMapPosition_y(0);

	//Setting Up FPS

	unsigned int lastTime = SDL_GetTicks();
	Uint32 startTime = SDL_GetTicks();
	int numFrames = 0;


	//Main Game Loop
	while (go)
	{
		//Added keyboard input
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
				}
				break;
			//When a key is pressed
			case SDL_KEYDOWN:
				switch (incomingEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					go = false;
					break;
				}
				break;
			}
		}
		//std::cout << "in game loop";
		//Setting up FPS
		numFrames++;

		std::stringstream ss;

		int fps = (numFrames / (float)(SDL_GetTicks() - startTime)) * 1000;
		ss << fps;

		//Event Handling For Control Systems
		unsigned int current = SDL_GetTicks();

		float deltaTs = (float)(current - lastTime) / 1000.0f;
		lastTime = current;



		if (deltaTs < (1.0f / 50.0f))
		{
			SDL_Delay((unsigned int)(((1.0f / 50.0f) - deltaTs)*1000.0f));
		}

		
		earth->Draw(earth->getMapPosition_x(), earth->getMapPosition_y(), earth->getTextureWidth(), earth->getTextureHeight(), renderer);
	}


	//DELETING MEMORY LOCATIONS

	delete earth;
	SDL_DestroyWindow(window); // Destroy the window
	SDL_Quit(); // Terminate SDL
	
	return 0;
}
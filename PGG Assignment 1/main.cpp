#include <SDL.h>

#include <iostream>
#include <sstream>

#include "vec2D.h"
#include "map.h"
#include "player.h"
#include "InputManager.h"
#include "menu.h"

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

	menu *mainmenu = new menu();
	menu *play_button = new menu();
	menu *help_button = new menu();
	menu *quit_button = new menu();

	menu *menu_cursor = new menu();
	menu *ingame_cursor = new menu();

	mainmenu->LoadFromPNG("../Assets/mainmenu_bg.png", renderer);
	mainmenu->setPosition_x(0);
	mainmenu->setPosition_y(0);

	play_button->LoadFromPNG("../Assets/play_button_sheet.png", renderer);
	play_button->setPosition_x(424);
	play_button->setPosition_y(158);

	help_button->LoadFromPNG("../Assets/button_readme.png", renderer);
	help_button->setPosition_x(424);
	help_button->setPosition_y(198);

	quit_button->LoadFromPNG("../Assets/button_quit.png", renderer);
	quit_button->setPosition_x(424);
	quit_button->setPosition_y(238);

	SDL_ShowCursor(0);
	menu_cursor->LoadFromPNG("../Assets/cursor.png", renderer);
	menu_cursor->setPosition_x(Input->mouse_x);
	menu_cursor->setPosition_y(Input->mouse_y);

	ingame_cursor->LoadFromPNG("../Assets/cursor_sheet.png", renderer);
	ingame_cursor->setPosition_x(Input->mouse_x);
	ingame_cursor->setPosition_y(Input->mouse_y);
	
	bool menu_active = true;
	bool first_run = false;
	bool go = false;

	bool play_pressed = false;
	bool help_pressed = false;
	bool quit_pressed = false;

	while (menu_active)
	{
		if (Input->first)
		{
			Input->cmd_mouseleft = false;
			Input->first = false;
		}
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(renderer);

		Input->InputUpdate();

		if (Input->cmd_escape)
		{
			menu_active = false;
		}

		mainmenu->Draw(mainmenu->getPosition_x(), mainmenu->getPosition_y(), renderer);
		play_button->AnimDraw(play_button->getPosition_x(), play_button->getPosition_y(), 3, 1, renderer);
		help_button->AnimDraw(help_button->getPosition_x(), help_button->getPosition_y(), 3, 1, renderer);
		quit_button->AnimDraw(quit_button->getPosition_x(), quit_button->getPosition_y(), 3, 1, renderer);
		
		if (Input->cmd_mouseleft && Input->mouse_x >= 424 && Input->mouse_x <= 754 && Input->mouse_y >= 158 && Input->mouse_y <= 188)
		{
			play_button->setID(2);
			play_pressed = true;
		}
		
		else if (Input->mouse_x >= 424 && Input->mouse_x <= 754 && Input->mouse_y >= 158 && Input->mouse_y <= 188)
		{
			play_button->setID(1);
		}

		else
		{
			play_button->setID(0);
		}

		if (Input->cmd_mouseleft && Input->mouse_x >= 424 && Input->mouse_x <= 754 && Input->mouse_y >= 198 && Input->mouse_y <= 228)
		{
			help_button->setID(2);
			help_pressed = true;
		}

		else if (Input->mouse_x >= 424 && Input->mouse_x <= 754 && Input->mouse_y >= 198 && Input->mouse_y <= 228)
		{
			help_button->setID(1);
		}

		else
		{
			help_button->setID(0);
		}

		if (Input->cmd_mouseleft && Input->mouse_x >= 424 && Input->mouse_x <= 754 && Input->mouse_y >= 238 && Input->mouse_y <= 288)
		{
			quit_button->setID(2);
			quit_pressed = true;
		}

		else if (Input->mouse_x >= 424 && Input->mouse_x <= 754 && Input->mouse_y >= 238 && Input->mouse_y <= 268)
		{
			quit_button->setID(1);
		}

		else
		{
			quit_button->setID(0);
		}

		if (Input->cmd_mouseleft_up && play_pressed)
		{
			menu_active = false;
		}

		if (Input->cmd_mouseleft_up && quit_pressed)
		{
			menu_active = false;
			first_run = true;
			go = false;

		}

		menu_cursor->setPosition_x(Input->mouse_x);
		menu_cursor->setPosition_y(Input->mouse_y);
		menu_cursor->Draw(menu_cursor->getPosition_x(), menu_cursor->getPosition_y(), renderer);

		menu_cursor->update(1);
		play_button->update(1);
		help_button->update(1);
		quit_button->update(1);
		SDL_RenderPresent(renderer);
	}

	menu *ui = new menu();
	ui->LoadFromPNG("../Assets/ui.png", renderer);
	ui->setPosition_x(0);
	ui->setPosition_y(540);

	map *earth[1000];
	for (int i = 0; i < 1000; i++)
	{
		earth[i] = new map();
		earth[i]->LoadFromPNG("../Assets/earth.png", renderer);
		earth[i]->setMapPosition_x(73);
		earth[i]->setMapPosition_y(18.5);
	}

	map *boxes = new map;
	boxes->LoadFromPNG("../Assets/boxes.png", renderer);

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

	bool transition = false;

	int moveMap_x = 1;
	int moveMap_y = 1;

	int mouse_x = 0;
	int mouse_y = 0;

	int counter_x = 0;
	int counter_y = 0;

	bool walking = false;
	bool walking_NE = false;
	bool walking_NW = false;
	bool walking_E = false;
	bool walking_W = false;
	bool walking_SE = false;
	bool walking_SW = false;
	bool walking_S = false;
	bool walking_N = false;

	bool interact = false;
	bool over_box = false;
	bool moveto_box = false;

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

		for (int i = 0; i < 25; i++)
		{
			boxes->setID(0);
			boxes->setMapPosition_x(350);
			boxes->setMapPosition_y(400);
			boxes->Draw(boxes->getMapPosition_x(), boxes->getMapPosition_y(), renderer);
		}

		SDL_RenderPresent(renderer);
		first_run = true;
		go = true;
		ingame_cursor->setID(0);
	}

	bool cmd_forwards, cmd_backwards, cmd_left, cmd_right, cmd_space, cmd_mouseleft;
	cmd_forwards = cmd_backwards = cmd_left = cmd_right = cmd_space = cmd_mouseleft = false;

	//Main Game Loop
	while (go)
	{
		Input->InputUpdate();

		ingame_cursor->setPosition_x(Input->mouse_x);
		ingame_cursor->setPosition_y(Input->mouse_y);

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
			if (incomingEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				if (incomingEvent.button.button == SDL_BUTTON_LEFT)
				{
					std::cout << "Left Mouse Button has been pressed! \n";
					cmd_mouseleft = true;
				}
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

		if (Input->cmd_escape)
		{
			go = false;;
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

			//&& Input->mouse_x >= 424 && Input->mouse_x <= 754 && Input->mouse_y >= 238 && Input->mouse_y <= 288)
			if (mouse_x >= boxes->getMapPosition_x() - camera.x && mouse_x <= boxes->getMapPosition_x() + 36 - camera.x && mouse_y >= boxes->getMapPosition_y() - camera.y && mouse_y <= boxes->getMapPosition_y() + 21 - camera.y)
			{
				ingame_cursor->setID(1);
				ingame_cursor->update_cursor(1);
				//interact_cursor->Draw(interact_cursor->getPosition_x(), interact_cursor->getPosition_y(), renderer);
				over_box = true;
				std::cout << "Over Box\n";
			}
			else if (mouse_y >= ui->getPosition_y())
			{
				ingame_cursor->setID(2);
				ingame_cursor->update_cursor(1);
			}
			else
			{
				ingame_cursor->setID(0);
				ingame_cursor->update_cursor(1);
				over_box = false;
				//	ingame_cursor->Draw(ingame_cursor->getPosition_x(), ingame_cursor->getPosition_y(), renderer);
			}

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

				boxes->Draw(boxes->getMapPosition_x() + camera.x, boxes->getMapPosition_y() + camera.y, renderer);
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

				boxes->Draw(boxes->getMapPosition_x() - camera.x, boxes->getMapPosition_y() - camera.y, renderer);
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

				boxes->Draw(boxes->getMapPosition_x() - camera.x, boxes->getMapPosition_y() - camera.y, renderer);
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

				boxes->Draw(boxes->getMapPosition_x() - camera.x, boxes->getMapPosition_y() - camera.y, renderer);

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

				boxes->Draw(boxes->getMapPosition_x() - camera.x, boxes->getMapPosition_y() - camera.y, renderer);
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

				boxes->Draw(boxes->getMapPosition_x() - camera.x, boxes->getMapPosition_y() - camera.y, renderer);
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

				boxes->Draw(boxes->getMapPosition_x() - camera.x, boxes->getMapPosition_y() - camera.y, renderer);

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

				boxes->Draw(boxes->getMapPosition_x() - camera.x, boxes->getMapPosition_y() - camera.y, renderer);
			}
		}
		int frametime = 0;

		if (cmd_mouseleft && !over_box && mouse_y <= ui->getPosition_y())
		{
			Player->SetDestination(camera.x + mouse_x, camera.y + mouse_y - 60);
			cmd_mouseleft = false;
			walking = true;
			Player->first = true;
		}

		if (cmd_mouseleft && over_box && mouse_y <= ui->getPosition_y())
		{
			Player->SetDestination(camera.x + mouse_x - 30, camera.y + mouse_y - 40);
			cmd_mouseleft = false;
			walking = true;
			Player->first = true;
			moveto_box = true;
		}

		if (ingame_cursor->getID() == 0 || ingame_cursor->getID() == 1)
		{
			ingame_cursor->AnimDraw(ingame_cursor->getPosition_x(), ingame_cursor->getPosition_y(), 3, 1, renderer);
		}

		if (moveto_box && !Player->finished)
		{
			Player->MoveToDest();
			if (Player->getPlayerPosition_x() == Player->GetDestX() && Player->getPlayerPosition_y() == Player->GetDestY())
			{
				if (transition)
				{
					Player->first = true;
					transition = false;
				}
				interact = true;
				Player->setID(13);
				Player->update_idle(2);
				Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 28, 64, renderer);
				if (Player->finished)
				{
					Player->finished = false;
					interact = false;
					Player->setID(3);
					moveto_box = false;
					Player->update_idle(2);
				}
			}
		}
		else
		{
			Player->MoveToDest();
		}

		//Transitioning~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if (walking_N && Player->getPlayerPosition_y() == Player->GetDestY())	//transition from North
		{
			transition = true;
			walking_N = false;
		}

		if (walking_S && Player->getPlayerPosition_y() == Player->GetDestY())	//transition from South
		{
			transition = true;
			walking_S = false;
		}

		if (walking_NE && Player->getPlayerPosition_x() == Player->GetDestX() || walking_NE && Player->getPlayerPosition_y() == Player->GetDestY())	//transition from North East
		{
			transition = true;
			walking_NE = false;
		}

		if (walking_E && Player->getPlayerPosition_x() == Player->GetDestX())	//transition from East
		{
			transition = true;
			walking_E = false;
		}

		if (walking_SE && Player->getPlayerPosition_x() == Player->GetDestX() || walking_SE && Player->getPlayerPosition_y() == Player->GetDestY())	//transition from South East
		{
			transition = true;
			walking_SE = false;
		}
	
		if (walking_SW && Player->getPlayerPosition_x() == Player->GetDestX() || walking_SW && Player->getPlayerPosition_y() == Player->GetDestY())	//transition from South West
		{
			transition = true;
			walking_SW = false;
		}

		if (walking_W && Player->getPlayerPosition_x() == Player->GetDestX())	//transition from West
		{
			transition = true;
			walking_W = false;
		}

		if (walking_NW && Player->getPlayerPosition_x() == Player->GetDestX() || walking_NW && Player->getPlayerPosition_y() == Player->GetDestY())	//transition from North West
		{
			transition = true;
			walking_NW = false;
		}

		//Walking Animation Selection~~~~~~~~~~~~~~~~~~~~



		if (walking && Player->getPlayerPosition_x() == Player->GetDestX() && Player->getPlayerPosition_y() > Player->GetDestY()) //if walking north
		{
			if (transition)
			{
				Player->first = true;
				transition = false;
			}

			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 29, 67, renderer);
			Player->setID(7);
			Player->update_idle(2);
			walking_N = true;
		}

		if (walking && Player->getPlayerPosition_x() == Player->GetDestX() && Player->getPlayerPosition_y() < Player->GetDestY()) //if walking south
		{
			if (transition)
			{
				Player->first = true;
				transition = false;
			}

			Player->setID(9);
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 30, 66, renderer);
			Player->update_idle(2);
			walking_S = true;
		}

		if (walking && Player->getPlayerPosition_x() < Player->GetDestX() && Player->getPlayerPosition_y() > Player->GetDestY()) //if walking north east
		{
			if (transition)
			{
				Player->first = true;
				transition = false;
			}

			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 29, 67, renderer);
 			Player->setID(7);
			Player->update_idle(2);
			walking_NE = true;
		}

		if (walking && Player->getPlayerPosition_x() < Player->GetDestX() && Player->getPlayerPosition_y() == Player->GetDestY()) //if walking east
		{
			if (transition)
			{
				Player->first = true;
				Player->setFrametime(20);
				transition = false;
			}
			
			Player->setID(8);
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 43, 63, renderer);
			Player->update_idle(2);
			walking_E = true;
		}

		if (walking && Player->getPlayerPosition_x() < Player->GetDestX() && Player->getPlayerPosition_y() < Player->GetDestY()) //if walking south east
		{
			if (transition)
			{
				Player->first = true;
				Player->setFrametime(20);
				transition = false;
			}

			Player->setID(9);
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 30, 66, renderer);
			Player->update_idle(2);
			walking_SE = true;
		}

		if (walking && Player->getPlayerPosition_x() > Player->GetDestX() && Player->getPlayerPosition_y() < Player->GetDestY()) //if walking south west
		{
			if (transition)
			{
				Player->first = true;
				Player->setFrametime(20);
				transition = false;
			}

			Player->setID(10);
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 30, 66, renderer);
			Player->update_idle(2);
			walking_SW = true;
		}

		if (walking && Player->getPlayerPosition_x() > Player->GetDestX() && Player->getPlayerPosition_y() == Player->GetDestY()) //if walking west
		{
			if (transition)
			{
				Player->first = true;
				Player->setFrametime(20);
				transition = false;
			}

			Player->setID(11);
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 43, 63, renderer);
			Player->update_idle(2);
			walking_W = true;
		}

		if (walking && Player->getPlayerPosition_x() > Player->GetDestX() && Player->getPlayerPosition_y() > Player->GetDestY()) //if walking north west
		{
			if (transition)
			{
				Player->first = true;
				Player->setFrametime(20);
				transition = false;
			}

			Player->setID(12);
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 30, 67, renderer);
			Player->update_idle(2);
			walking_NW = true;
		}

		if (!interact && Player->getPlayerPosition_x() == Player->GetDestX() && Player->getPlayerPosition_y() == Player->GetDestY())//else idling
		{
			walking = false;
			
			if (Player->getID() == 7)
			{
				Player->setID(1);
			}

			if (Player->getID() == 8)
			{
				Player->setID(2);
			}

			if (Player->getID() == 9)
			{
				Player->setID(3);
			}

			if (Player->getID() == 10)
			{
				Player->setID(4);
			}

			if (Player->getID() == 11)
			{
				Player->setID(5);
			}

			if (Player->getID() == 12)
			{
				Player->setID(6);
			}
			Player->AnimDraw(Player->getPlayerPosition_x() - camera.x, Player->getPlayerPosition_y() - camera.y, 36, 69, renderer);
			Player->update_idle(2);
		}
		ui->Draw(ui->getPosition_x(), ui->getPosition_y(), renderer);
		if (ingame_cursor->getID() == 2)
		{
			ingame_cursor->AnimDraw(ingame_cursor->getPosition_x(), ingame_cursor->getPosition_y(), 3, 1, renderer);
		}
		SDL_RenderPresent(renderer);
	}


	//DELETING MEMORY LOCATIONS
	for (int i = 0; i < 1000; i++)
	{
		delete earth[i];
	}
	delete boxes;
	
	delete Player;
	delete mainmenu;
	delete Input;

	delete menu_cursor;
	delete ingame_cursor;

	SDL_DestroyWindow(window); // Destroy the window
	SDL_Quit(); // Terminate SDL

	return 0;
}
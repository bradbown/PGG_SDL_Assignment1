#include "InputManager.h"
#include <iostream>

InputManager::InputManager()
{
	go = true;
}

InputManager::~InputManager()
{

}

void InputManager::InputUpdate()
{
	cmd_forwards = cmd_backwards = cmd_left = cmd_right = cmd_space, cmd_mouseleft, cmd_escape = false;


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
				cmd_escape = true;
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

	SDL_PumpEvents();
	if (SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&mouse_x, &mouse_y);
	}

}
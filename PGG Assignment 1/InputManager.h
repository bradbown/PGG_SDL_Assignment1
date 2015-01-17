#pragma once
#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <SDL.h>

class InputManager
{
public:

	InputManager();
	~InputManager();

	void InputUpdate();

	bool go;

	bool cmd_forwards, cmd_backwards, cmd_left, cmd_right, cmd_space, cmd_mouseleft, cmd_escape;
		
protected:

private:

	
};

#endif;
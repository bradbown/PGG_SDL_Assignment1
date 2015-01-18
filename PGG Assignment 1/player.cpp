#include "player.h"
#include <iostream>

player::player()
{
	// This is the constructor
	// Don't forget to initialise those member variables!
	_texture = NULL;
	PlayerPosition_x = 0;
	PlayerPosition_y = 0;
}

player::~player()
{
	// This is the destructor
	// Use SDL to clean up our texture 
	if (_texture)
	{
		SDL_DestroyTexture(_texture);
	}
}

bool player::LoadFromPNG(std::string filename, SDL_Renderer *renderer)
{
	// Just check we're not being given garbage :P
	if (filename.empty())
	{
		std::cerr << "ERROR: Sprite::LoadFromBMP - Empty filename given." << std::endl;
		return false;
	}

	// First we load it to what SDL calls a 'surface'
	// This is just a raw collection of pixels
	SDL_Surface * image = IMG_Load(filename.c_str());
	if (!image)
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		std::cerr << "ERROR: Sprite::LoadFromPNG - Can't find the image file." << std::endl;
		return false;
	}

	// Next we convert the SDL_Surface into what it calls a 'texture'
	// This is kinda similar, but because it's bound to a renderer, SDL can make some useful optimisations behind the scenes
	// This will make it draw to the screen faster
	_texture = SDL_CreateTextureFromSurface(renderer, image);

	// We've now finished with our raw pixel data, so we can get rid of it
	SDL_FreeSurface(image);

	return true;
}

void player::Draw(int SPosition_x, int SPosition_y, SDL_Renderer *renderer)
{
	// This will specify where to draw the sprite
	SDL_Rect destRect;
	// SDL has (0,0) at the top left corner - check this by playing about with the numbers!
	destRect.x = SPosition_x;
	destRect.y = SPosition_y;

	// Query the texture to get its original width and height
	SDL_QueryTexture(_texture, NULL, NULL, &destRect.w, &destRect.h);

	// Here we are telling the renderer to copy the texture memory to our screen,
	// at the position of the rectangle we specify
	// The parameter that's currently NULL can be used to specify another rectangle that's a sub-region of the whole image
	// This is for doing sprite ReadSprite type effects
	SDL_RenderCopy(renderer, _texture, NULL, &destRect);

}

void player::AnimDraw(int positionX, int positionY, int hoz,int vert, SDL_Renderer *renderer)
{
	/* // This will specify where to draw the sprite
	SDL_Rect destRect;
	// SDL has (0,0) at the top left corner - check this by playing about with the numbers!
	destRect.x = positionX;
	destRect.y = positionY;
	*/

	ReadSprite.dstrect.x = positionX;
	ReadSprite.dstrect.y = positionY;

	// std::cout << srcrect.x << "\n";

	// Query the texture to get its original width and height
	SDL_QueryTexture(_texture, NULL, NULL, &ReadSprite.textureWidth, &ReadSprite.textureHeight);


	ReadSprite.spriteWidth = hoz;
	ReadSprite.spriteHeight = vert;

	ReadSprite.srcrect.w = ReadSprite.spriteWidth;
	ReadSprite.srcrect.h = ReadSprite.spriteHeight;

	ReadSprite.dstrect.w = ReadSprite.spriteWidth;
	ReadSprite.dstrect.h = ReadSprite.spriteHeight;


	// Here we are telling the renderer to copy the texture memory to our screen,
	// at the position of the rectangle we specify
	// The parameter that's currently NULL can be used to specify another rectangle that's a sub-region of the whole image
	// This is for doing sprite ReadSprite type effects
	SDL_RenderCopy(renderer, _texture, &ReadSprite.srcrect, &ReadSprite.dstrect);

}

void player::update_idle(int in_speed)
{
	ReadSprite.frametime++;

	if (ID == 0)
	{
		ReadSprite.frametime = 1;
	}


	if (FPS / ReadSprite.frametime == in_speed)
	{
		ReadSprite.frametime = 0;

		switch (ID)
		{

		//IDLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		case 1:		//Idle North East
		{
			ReadSprite.srcrect.y = 0;
			ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			if (ReadSprite.srcrect.x >= (ReadSprite.spriteWidth * 12))
			{
				ReadSprite.srcrect.x = 0;
			}
		}
			break;

		case 2:		//Idle East
		{
			ReadSprite.srcrect.y = 70;
			ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			if (ReadSprite.srcrect.x >= (ReadSprite.spriteWidth * 12))
			{
				ReadSprite.srcrect.x = 0;
			}
		}
			break;

		case 3:		//Idle South East
		{
			ReadSprite.srcrect.y = 140;
			ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			if (ReadSprite.srcrect.x >= (ReadSprite.spriteWidth * 12))
			{
				ReadSprite.srcrect.x = 0;
			}
		}
			break;

		case 4:		//Idle South West
		{
			ReadSprite.srcrect.y = 210;
			ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			if (ReadSprite.srcrect.x >= (ReadSprite.spriteWidth * 12))
			{
				ReadSprite.srcrect.x = 0;
			}
		}
			break;

		case 5:		//Idle West
		{
				  ReadSprite.srcrect.y = 280;
				  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
				  if (ReadSprite.srcrect.x >= (ReadSprite.spriteWidth * 12))
				  {
					  ReadSprite.srcrect.x = 0;
				  }
		}
			break;

		case 6:		//Idle North West
		{
				  ReadSprite.srcrect.y = 350;
				  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
				  if (ReadSprite.srcrect.x >= (ReadSprite.spriteWidth * 12))
				  {
					  ReadSprite.srcrect.x = 0;
				  }
		}
			break;

		//WALKING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		case 7:	//Walking North Eest
		{
				  if (first)
				  {
					  ReadSprite.srcrect.x = 441;
					  first = false;
				  }
				  ReadSprite.srcrect.y = 0;
				  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
				  if (ReadSprite.srcrect.x >= (441 + (ReadSprite.spriteWidth * 8)))
				  {
					  ReadSprite.srcrect.x = 441;
				  }
		}
			break;
		case 8:	//Walking East
		{
				  if (first)
				  {
					  ReadSprite.srcrect.x = 441;
					  first = false;
				  }
				  ReadSprite.srcrect.y = 73;
				  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
				  if (ReadSprite.srcrect.x >= (441 + (ReadSprite.spriteWidth * 8)))
				  {
					  ReadSprite.srcrect.x = 441;
				  }
		}
			break;
		case 9:	//Walking South East
		{
				  if (first)
				  {
					  ReadSprite.srcrect.x = 441;
					  first = false;
				  }
				  ReadSprite.srcrect.y = 138;
				  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
				  if (ReadSprite.srcrect.x >= (441 + (ReadSprite.spriteWidth * 8)))
				  {
					  ReadSprite.srcrect.x = 441;
				  }
		}
			break;
		case 10:	//Walking South East
		{
					if (first)
					{
						ReadSprite.srcrect.x = 441;
						first = false;
					}
					ReadSprite.srcrect.y = 206;
					ReadSprite.srcrect.x += ReadSprite.spriteWidth;
					if (ReadSprite.srcrect.x >= (441 + (ReadSprite.spriteWidth * 8)))
					{
						ReadSprite.srcrect.x = 441;
					}
		}
			break;
	
		case 11:	//Walking West
		{
					if (first)
					{
						ReadSprite.srcrect.x = 441;
						first = false;
					}
					ReadSprite.srcrect.y = 277;
					ReadSprite.srcrect.x += ReadSprite.spriteWidth;
					if (ReadSprite.srcrect.x >= (441 + (ReadSprite.spriteWidth * 8)))
					{
						ReadSprite.srcrect.x = 441;
						first = true;
					}
		}
			break;

		case 12:	//Walking North West
		{
					if (first)
					{
						ReadSprite.srcrect.x = 441;
						first = false;
					}
					ReadSprite.srcrect.y = 340;
					ReadSprite.srcrect.x += ReadSprite.spriteWidth;
					if (ReadSprite.srcrect.x >= (441 + (ReadSprite.spriteWidth * 8)))
					{
						ReadSprite.srcrect.x = 441;
						first = true;
					}
		}
			break;

		//INTERACT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		case 13:
		{
				if (first)
			{
				ReadSprite.srcrect.x = 1071;
				first = false;
			}
			ReadSprite.srcrect.y = 134;
			ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			if (ReadSprite.srcrect.x >= (1071 + (ReadSprite.spriteWidth * 9)))
			{
				ReadSprite.srcrect.x = 1071;
				first = true;
				finished = true;
			}
		}
			break;

		} // end of switch
	} // end of FPS
}

void player::setFrametime(int frametime)
{
	ReadSprite.frametime = frametime;
}

float player::GetDestX()
{
	return Goal_x;
}

float player::GetDestY()
{
	return Goal_y;
}

void player::MoveToDest()
{
	moving = 0;
	if (PlayerPosition_x < Goal_x)
	{
		// move right
		setPlayerPosition_x(1);
		// bool right = true
		moving++;
	}
	else if (PlayerPosition_x > Goal_x)
	{
		// move left
		setPlayerPosition_x(-1);
		moving++;
	}

	if (PlayerPosition_y < Goal_y)
	{
		// move down
		setPlayerPosition_y(1);
		moving++;
	}
	else if (PlayerPosition_y > Goal_y)
	{
		// move up
		setPlayerPosition_y(-1);
		moving++;
	}
}

bool player::hasMoved()
{
	//	if moved > 0, return true, else return false
	return (moving > 0 ? true : false);
}

void player::setMoved(bool moved)
{
	moved;
}

void player::setMoved_False(bool moved)
{
	moved = false;
}

bool player::getMoved()
{
	return moved;
}

void player::SetDestination(float x, float y)
{
	Goal_x = x;
	Goal_y = y;
}

void player::setPlayerPosition_x(float playerPositionX)
{
	PlayerPosition_x += playerPositionX;
}

float player::getPlayerPosition_x() const
{
	return PlayerPosition_x;
}

void player::setPlayerPosition_y(float playerPositionY)
{
	PlayerPosition_y += playerPositionY;
}

float player::getPlayerPosition_y() const
{
	return PlayerPosition_y;
}

void player::changePos_x(float playerPositionX)
{
	PlayerPosition_x = playerPositionX;
}

void player::changePos_y(float playerPositionY)
{
	PlayerPosition_y = playerPositionY;
}

int player::getTextureWidth() const
{
	return ReadSprite.textureWidth;
}

int player::getTextureHeight() const
{
	return ReadSprite.textureHeight;
}

void player::setID(int IDNum)
{
	ID = IDNum;
}

int player::getID() const
{
	return ID;
}
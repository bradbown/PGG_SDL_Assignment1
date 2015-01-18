#include "enemy.h"
#include <iostream>

enemy::enemy()
{
	// This is the constructor
	// Don't forget to initialise those member variables!
	_texture = NULL;
	EnemyPosition_x = 0;
	EnemyPosition_y = 0;
}

enemy::~enemy()
{
	// This is the destructor
	// Use SDL to clean up our texture 
	if (_texture)
	{
		SDL_DestroyTexture(_texture);
	}
}

bool enemy::LoadFromPNG(std::string filename, SDL_Renderer *renderer)
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
		std::cerr << "ERROR: enemy::LoadFromPNG - Can't find the image file." << std::endl;
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

void enemy::AnimDraw(int positionX, int positionY, int hoz, int vert, SDL_Renderer *renderer)
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

void enemy::update(int in_speed)
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

		//WALKING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		case 1:		//Walking North East
		{
						if (first)
						{
							ReadSprite.srcrect.x = 3;
							first = false;
						}

						ReadSprite.srcrect.y = 209;
						ReadSprite.srcrect.x += ReadSprite.spriteWidth;
						if (ReadSprite.srcrect.x >= (3 + (ReadSprite.spriteWidth * 11)))
						{
							ReadSprite.srcrect.x = 3;
						}
		}
			break;

		case 2:		//Walking East
		{
						if (first)
						{
							ReadSprite.srcrect.x = 3;
							first = false;
						}

						ReadSprite.srcrect.y = 246;
						ReadSprite.srcrect.x += ReadSprite.spriteWidth;
						if (ReadSprite.srcrect.x >= (3 + (ReadSprite.spriteWidth * 11)))
						{
							ReadSprite.srcrect.x = 3;
						}
		}
			break;

		case 3:		//Walking South East
		{
						if (first)
						{
							ReadSprite.srcrect.x = 3;
							first = false;
						}

						ReadSprite.srcrect.y = 273;
						ReadSprite.srcrect.x += ReadSprite.spriteWidth;
						if (ReadSprite.srcrect.x >= (3 + (ReadSprite.spriteWidth * 11)))
						{
							ReadSprite.srcrect.x = 3;
						}
		}
			break;

		case 4:		//Walking South West
		{
						if (first)
						{
							ReadSprite.srcrect.x = 3;
							first = false;
						}

						ReadSprite.srcrect.y = 305;
						ReadSprite.srcrect.x += ReadSprite.spriteWidth;
						if (ReadSprite.srcrect.x >= (3 + (ReadSprite.spriteWidth * 11)))
						{
							ReadSprite.srcrect.x = 3;
						}
		}
			break;

		case 5:		//Walking West
		{
						if (first)
						{
							ReadSprite.srcrect.x = 3;
							first = false;
						}

						ReadSprite.srcrect.y = 345;
						ReadSprite.srcrect.x += ReadSprite.spriteWidth;
						if (ReadSprite.srcrect.x >= (3 + (ReadSprite.spriteWidth * 11)))
						{
							ReadSprite.srcrect.x = 3;
						}
		}
			break;

		case 6:		//Walking North West
		{
						if (first)
						{
							ReadSprite.srcrect.x = 3;
							first = false;
						}

						ReadSprite.srcrect.y = 372;
						ReadSprite.srcrect.x += ReadSprite.spriteWidth;
						if (ReadSprite.srcrect.x >= (3 + (ReadSprite.spriteWidth * 11)))
						{
							ReadSprite.srcrect.x = 3;
						}
		}
			break;

		

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

void enemy::setFrametime(int frametime)
{
	ReadSprite.frametime = frametime;
}

float enemy::GetDestX()
{
	return Goal_x;
}

float enemy::GetDestY()
{
	return Goal_y;
}

void enemy::MoveToDest()
{
	moving = 0;
	if (EnemyPosition_x < Goal_x)
	{
		// move right
		setEnemyPosition_x(0.5);
		// bool right = true
		moving++;
	}
	else if (EnemyPosition_x > Goal_x)
	{
		// move left
		setEnemyPosition_x(-0.5);
		moving++;
	}

	if (EnemyPosition_y < Goal_y)
	{
		// move down
		setEnemyPosition_y(0.5);
		moving++;
	}
	else if (EnemyPosition_y > Goal_y)
	{
		// move up
		setEnemyPosition_y(-0.5);
		moving++;
	}
}

bool enemy::hasMoved()
{
	//	if moved > 0, return true, else return false
	return (moving > 0 ? true : false);
}

void enemy::setMoved(bool moved)
{
	moved;
}

void enemy::setMoved_False(bool moved)
{
	moved = false;
}

bool enemy::getMoved()
{
	return moved;
}

void enemy::SetDestination(float x, float y)
{
	Goal_x = x;
	Goal_y = y;
}

void enemy::setEnemyPosition_x(float enemyPositionX)
{
	EnemyPosition_x += enemyPositionX;
}

float enemy::getEnemyPosition_x() const
{
	return EnemyPosition_x;
}

void enemy::setEnemyPosition_y(float enemyPositionY)
{
	EnemyPosition_y += enemyPositionY;
}

float enemy::getEnemyPosition_y() const
{
	return EnemyPosition_y;
}

void enemy::changePos_x(float enemyPositionX)
{
	EnemyPosition_x = enemyPositionX;
}

void enemy::changePos_y(float enemyPositionY)
{
	EnemyPosition_y = enemyPositionY;
}

int enemy::getTextureWidth() const
{
	return ReadSprite.textureWidth;
}

int enemy::getTextureHeight() const
{
	return ReadSprite.textureHeight;
}

void enemy::setID(int IDNum)
{
	ID = IDNum;
}

int enemy::getID() const
{
	return ID;
}
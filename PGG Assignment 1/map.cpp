#include <iostream>
#include "map.h"

map::map()
{
	// This is the constructor
	// Don't forget to initialise those member variables!
	_texture = NULL;
	MapPosition_x = 0;
	MapPosition_y = 0;
}

map::~map()
{
	// This is the destructor
	// Use SDL to clean up our texture 
	if (_texture)
	{
		SDL_DestroyTexture(_texture);
	}
}

bool map::LoadFromPNG(std::string filename, SDL_Renderer *renderer)
{
	// Just check we're not being given garbage :P
	if( filename.empty() )
	{
		std::cerr<<"ERROR: Sprite::LoadFromBMP - empty filename given"<<std::endl;
		return false;
	}

	// First we load it to what SDL calls a 'surface'
	// This is just a raw collection of pixels
	SDL_Surface * image = IMG_Load( filename.c_str() );
	if( !image )
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		std::cerr<<"ERROR: Sprite::LoadFromBMP - Oh dear, sorry but I can't find your image file. This brings me great sadness :("<<std::endl;
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

void map::Draw(int SPosition_x, int SPosition_y, SDL_Renderer *renderer)
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
	// This is for doing sprite animation type effects
	SDL_RenderCopy(renderer, _texture, NULL, &destRect);

}

void map::AnimDraw(int positionX, int positionY, int vert, int hoz, SDL_Renderer *renderer)
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


	ReadSprite.spriteWidth = ReadSprite.textureWidth / hoz;
	ReadSprite.spriteHeight = ReadSprite.textureHeight / vert;

	ReadSprite.srcrect.w = ReadSprite.spriteWidth;
	ReadSprite.srcrect.h = ReadSprite.spriteHeight;

	ReadSprite.dstrect.w = ReadSprite.spriteWidth;
	ReadSprite.dstrect.h = ReadSprite.spriteHeight;


	// Here we are telling the renderer to copy the texture memory to our screen,
	// at the position of the rectangle we specify
	// The parameter that's currently NULL can be used to specify another rectangle that's a sub-region of the whole image
	// This is for doing sprite animation type effects
	SDL_RenderCopy(renderer, _texture, &ReadSprite.srcrect, &ReadSprite.dstrect);

}

void map::update(int in_speed)
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

		case 1:
		{
			ReadSprite.srcrect.y = 0;
			ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
			{
				ReadSprite.srcrect.x = 0;
			}
		}
			break;

		case 2:
		{
			ReadSprite.srcrect.y = 0;
			ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
			{
				ReadSprite.srcrect.x = 0;
			}
		}
			break;

		} // end of switch
	} // end of FPS
}

void map::setMapPosition_x(float mapPositionX)
{
	MapPosition_x += mapPositionX;
}

float map::getMapPosition_x() const
{
	return MapPosition_x;
}

void map::setMapPosition_y(float mapPositionY)
{
	MapPosition_y += mapPositionY;
}

float map::getMapPosition_y() const
{
	return MapPosition_y;
}

void map::changePos_x(float mapPositionX)
{
	MapPosition_x = mapPositionX;
}

void map::changePos_y(float mapPositionY)
{
	MapPosition_y = mapPositionY;
}

void map::scrollingMapPosX(int MapPositionX)
{
	//ReadSprite.dstrect.x -= 1;
	MapPosition_x += MapPositionX;
}

int map::getTextureWidth() const
{
	return ReadSprite.textureWidth;
}

int map::getTextureHeight() const
{
	return ReadSprite.textureHeight;
}
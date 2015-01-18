#include <iostream>
#include "menu.h"

menu::menu()
{
	_texture = NULL;
	Position_x = 0;
	Position_y = 0;
}

menu::~menu()
{
	if (_texture)
	{
		SDL_DestroyTexture(_texture);
	}
}

bool menu::LoadFromPNG(std::string filename, SDL_Renderer *renderer)
{
	if (filename.empty())
	{
		std::cerr << "ERROR: menu::LoadFromPNG - empty filename given" << std::endl;
		return false;
	}

	SDL_Surface * image = IMG_Load(filename.c_str());

	if (!image)
	{
		std::cerr << "ERROR: Sprite::LoadFromPNG - Can't find the image file" << std::endl;
		return false;
	}

	_texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);

	return true;
}

void menu::Draw(int SPosition_x, int SPosition_y, SDL_Renderer *renderer)
{
	SDL_Rect destRect;

	destRect.x = SPosition_x;
	destRect.y = SPosition_y;

	SDL_QueryTexture(_texture, NULL, NULL, &destRect.w, &destRect.h);

	SDL_RenderCopy(renderer, _texture, NULL, &destRect);
}

void menu::AnimDraw(int positionX, int positionY, int vert, int hoz, SDL_Renderer *renderer)
{
	ReadSprite.dstrect.x = positionX;
	ReadSprite.dstrect.y = positionY;

	SDL_QueryTexture(_texture, NULL, NULL, &ReadSprite.textureWidth, &ReadSprite.textureHeight);

	ReadSprite.spriteWidth = ReadSprite.textureWidth / hoz;
	ReadSprite.spriteHeight = ReadSprite.textureHeight / vert;

	ReadSprite.srcrect.w = ReadSprite.spriteWidth;
	ReadSprite.srcrect.h = ReadSprite.spriteHeight;

	ReadSprite.dstrect.w = ReadSprite.spriteWidth;
	ReadSprite.dstrect.h = ReadSprite.spriteHeight;

	SDL_RenderCopy(renderer, _texture, &ReadSprite.srcrect, &ReadSprite.dstrect);

}

void menu::update(int in_speed)
{
	switch (ID)
	{

		case 0:
		{
				  ReadSprite.srcrect.y = 0;
				  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
				  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
				  {
					  ReadSprite.srcrect.x = 0;
				  }
		}
			break;

		case 1:
		{
				  ReadSprite.srcrect.y = 30;
				  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
				  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
				  {
					  ReadSprite.srcrect.x = 0;
				  }
		}
			break;

		case 2:
		{
				  ReadSprite.srcrect.y = 60;
				  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
				  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
				  {
					  ReadSprite.srcrect.x = 0;
				  }
		}
			break;
	}

}

void menu::update_cursor(int in_speed)
{
	switch (ID)
	{

	case 0:
	{
			  ReadSprite.srcrect.y = 0;
			  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
			  {
				  ReadSprite.srcrect.x = 0;
			  }
	}
		break;

	case 1:
	{
			  ReadSprite.srcrect.y = 28;
			  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
			  {
				  ReadSprite.srcrect.x = 0;
			  }
	}
		break;

	case 2:
	{
			  ReadSprite.srcrect.y = 56;
			  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
			  {
				  ReadSprite.srcrect.x = 0;
			  }
	}
		break;
	}
}

void menu::update_text(int in_speed)
{
	switch (ID)
	{

	case 0:
	{
			  ReadSprite.srcrect.y = 0;
			  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
			  {
				  ReadSprite.srcrect.x = 0;
			  }
	}
		break;

	case 1:
	{
			  ReadSprite.srcrect.y = 23;
			  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
			  {
				  ReadSprite.srcrect.x = 0;
			  }
	}
		break;

	case 2:
	{
			  ReadSprite.srcrect.y = 46;
			  ReadSprite.srcrect.x += ReadSprite.spriteWidth;
			  if (ReadSprite.srcrect.x >= ReadSprite.textureWidth)
			  {
				  ReadSprite.srcrect.x = 0;
			  }
	}
		break;
	}
}

void menu::setID(int IDNum)
{
	ID = IDNum;
}

int menu::getID() const
{
	return ID;
}

void menu::setPosition_x(float position_x)
{
	Position_x = position_x;
}

float menu::getPosition_x() const
{
	return Position_x;
}

void menu::setPosition_y(float position_y)
{
	Position_y = position_y;
}

float menu::getPosition_y() const
{
	return Position_y;
}


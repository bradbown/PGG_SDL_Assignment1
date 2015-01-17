#pragma once
#ifndef __menu_H__
#define __menu_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class menu
{
public:
	
	menu();
	~menu();

	void setPosition_x(float position_x);
	void setPosition_y(float position_y);

	float getPosition_x() const;
	float getPosition_y() const;

	void update(int in_speed);

	void setID(int IDNum);
	int getID() const;

	bool LoadFromPNG(std::string filename, SDL_Renderer *renderer);

	void Draw(int SPosition_x, int SPosition_y, SDL_Renderer *renderer);
	void AnimDraw(int positionX, int positionY, int vert, int hoz, SDL_Renderer *renderer);

protected:

	SDL_Texture *_texture;

private:

	char ID = 0;

	const int FPS = 60;

	float Position_x, Position_y;

	struct
	{
		int spriteWidth;
		int spriteHeight;

		int textureWidth;
		int textureHeight;

		int frametime;

		SDL_Rect srcrect;
		SDL_Rect dstrect;
	}ReadSprite;
};

#endif
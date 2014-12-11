#pragma once
#ifndef __MAP_H__
#define __MAP_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

class map
{
public:

	map();

	void setMapPosition_x(int MapPosition_x);
	int getMapPosition_x() const;

	void setMapPosition_y(int MapPosition_y);
	int getMapPosition_y() const;

	void changePos_x(int MapPosition_x);
	void changePos_y(int MapPosition_y);

	~map();

	bool LoadFromPNG(std::string filename, SDL_Renderer *renderer);

	void Draw(int SPosition_x, int SPosition_y, SDL_Renderer *renderer);

protected:

	// This variable will be our handle for the texture
	SDL_Texture *_texture;


private:

	int MapPosition_x, MapPosition_y;

	struct
	{
		float spriteWidth;
		float spriteHeight;

		float textureWidth;
		float textureHeight;

		float frametime;

		SDL_Rect srcrect;
		SDL_Rect dstrect;
	};

};

#endif
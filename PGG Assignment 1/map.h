#pragma once
#ifndef __MAP_H__
#define __MAP_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class map
{
public:

	map();
	~map();

	void setMapPosition_x(float MapPositionX);
	float getMapPosition_x() const;

	void setMapPosition_y(float MapPositionY);
	float getMapPosition_y() const;

	void changePos_x(float MapPositionX);
	void changePos_y(float MapPositionY);

	void scrollingMapPosX(int MapPositionX);

	int getTextureWidth() const;
	int getTextureHeight() const;

	void update(int in_speed);
	void TileSelect(int in_speed);

	//Loads a .png file
	bool LoadFromPNG(std::string filename, SDL_Renderer *renderer);

	//void Draw(int SPosition_x, int SPosition_y, int TileWidth, int TileHeight, SDL_Renderer *renderer);
	void Draw(int SPosition_x, int SPosition_y, SDL_Renderer *renderer);
	void AnimDraw(int positionX, int positionY, int vert, int hoz, SDL_Renderer *renderer);
	
protected:

	// This variable will be our handle for the texture
	SDL_Texture *_texture;


private:

	char ID = 0;

	const int FPS = 60;

	float MapPosition_x, MapPosition_y;

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
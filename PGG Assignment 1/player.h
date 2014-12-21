#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class player
{
public:

	player();
	~player();

	void setPlayerPosition_x(float PlayerPositionX);
	float getPlayerPosition_x() const;

	void setPlayerPosition_y(float PlayerPositionY);
	float getPlayerPosition_y() const;

	void changePos_x(float PlayerPositionX);
	void changePos_y(float PlayerPositionY);

	int getTextureWidth() const;
	int getTextureHeight() const;

	void update(int in_speed);
	void TileSelect(int in_speed);

	void setID(int IDNum);
	int getID() const;

	//Loads a .png file
	bool LoadFromPNG(std::string filename, SDL_Renderer *renderer);

	//void Draw(int SPosition_x, int SPosition_y, int TileWidth, int TileHeight, SDL_Renderer *renderer);
	void Draw(int SPosition_x, int SPosition_y, SDL_Renderer *renderer);
	void AnimDraw(int positionX, int positionY, int vert, int hoz, SDL_Renderer *renderer);

protected:

	// This variable will be our handle for the texture
	SDL_Texture *_texture;

private:

	int ID = 0;

	const int FPS = 60;

	float PlayerPosition_x, PlayerPosition_y;

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
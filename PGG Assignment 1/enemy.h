#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class enemy
{
public:

	enemy();
	~enemy();

	void setEnemyPosition_x(float EnemyPositionX);
	float getEnemyPosition_x() const;

	void setEnemyPosition_y(float EnemyPositionY);
	float getEnemyPosition_y() const;

	void changePos_x(float EnemyPositionX);
	void changePos_y(float EnemyPositionY);

	int getTextureWidth() const;
	int getTextureHeight() const;

	void update(int in_speed);

	void setID(int IDNum);
	int getID() const;

	//Loads a .png file
	bool LoadFromPNG(std::string filename, SDL_Renderer *renderer);

	void AnimDraw(int positionX, int positionY, int hoz, int vert, SDL_Renderer *renderer);

	void SetDestination(float x, float y);
	float GetDestX();
	float GetDestY();

	void MoveToDest();

	void setMoved(bool moved);
	void setMoved_False(bool moved);
	bool getMoved();
	bool hasMoved();

	bool finished;

	bool first = true;

	void setFrametime(int frametime);

protected:

	// This variable will be our handle for the texture
	SDL_Texture *_texture;


private:

	int ID = 0;

	const int FPS = 60;

	float EnemyPosition_x, EnemyPosition_y;

	float Goal_x, Goal_y;

	bool moved = true;
	int moving;

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

	SDL_Texture *idle;
	SDL_Texture *walk;
};

#endif
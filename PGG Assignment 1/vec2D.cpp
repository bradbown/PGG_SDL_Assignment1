#include "vec2D.h"
#include <iostream>

using namespace std;


vec2D::vec2D()
{
	velocity_x = 0.0f;
	velocity_y = 0.0f;

}


vec2D::~vec2D()
{
}


void vec2D::setvelocity_x(float velocityX)
{
	velocity_x += velocityX;
}

float vec2D::getvelocityX() const
{
	return velocity_x;

}


void vec2D::setvelocity_y(float velocityY)
{
	velocity_y += velocityY;
}

float vec2D::getvelocityY() const
{
	return velocity_y;

}

void vec2D::changeVelocityX(float velocityX)
{
	velocity_x = velocityX;
}

void vec2D::changeVelocityY(float velocityY)
{
	velocity_y = velocityY;
}


#pragma once

#include <iostream>

class vec2D
{

public:
	vec2D();

	void setvelocity_x(float velocityX);
	float getvelocityX() const;

	void setvelocity_y(float velocityY);
	float getvelocityY() const;


	void changeVelocityY(float velocityY);
	void changeVelocityX(float velocityX);

	~vec2D();


private:

	float velocity_x, velocity_y;





};


#ifndef PURPLEMUSHROOM_H
#define PURPLEMUSHROOM_H

#include "Platform.h"

class Purplemushroom 
{
public:
	C2D_Sprite purple;
	double x;
	double y;
	double w;
	double h;
	double speedX;
	double velocityY;
	double gravity;
	double speedY;
	bool onGround;
	int done;

	C2D_SpriteSheet purpleSpriteSheet;

	Purplemushroom(double x, double y);
	~Purplemushroom();
	void update(std::vector<Platform>& platList);
	void render();
};

#endif // PURPLEMUSHROOM_H
#ifndef BLUEMUSHROOM_H
#define BLUEMUSHROOM_H

#include "Platform.h"

class Bluemushroom 
{
public:
	C2D_Sprite blue;
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

	C2D_SpriteSheet blueSpriteSheet;

	Bluemushroom(double x, double y);
	~Bluemushroom();
	void update(std::vector<Platform>& platList);
	void render();
};

#endif // BLUEMUSHROOM_H
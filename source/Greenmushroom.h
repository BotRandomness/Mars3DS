#ifndef GREENMUSHROOM_H
#define GREENMUSHROOM_H

#include "Platform.h"

class Greenmushroom 
{
public:
	C2D_Sprite green;
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

	C2D_SpriteSheet greenSpriteSheet;

	Greenmushroom(double x, double y);
	~Greenmushroom();
	void update(std::vector<Platform>& platList);
	void render();
};

#endif // GREENMUSHROOM_H
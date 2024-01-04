#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "Platform.h"
#include "Enebullet.h"

class Enemy 
{
public:
	C2D_Sprite parasite;
	double x;
	double y;
	double w;
	double h;
	double speedX;
	double velocityY;
	double gravity;
	double speedY;
	int direction;
	bool onGround;
	int health;

	int flip;

	int anim;
	int framesCounter;
	int frameSpeed;
	int currentFrame;
	std::chrono::steady_clock::time_point incoming;

	std::vector<Enebullet*> enebullList;

	C2D_SpriteSheet paraSpriteSheet;
	C2D_SpriteSheet warnSpriteSheet;

	Enemy(double x, double y, int anim);
	void movement(std::vector<Platform>& platList);
	void collision(std::vector<Platform>& platList);
	void shoot(double pX);
	void render();
	void update(std::vector<Platform>& platList, double pX);
};

#endif // ENEMY_H
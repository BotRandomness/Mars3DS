#ifndef ASTRO_H
#define ASTRO_H

#include<vector>
#include "Platform.h"
#include "Bullet.h"

class Astro 
{
public:
	C2D_Sprite astro;
	C2D_Sprite healthBar;
	double x;
	double y;
	double w;
	double h;
	double velocityX;
	double acc;
	double friction;
	double speedX;
	double velocityY;
	double gravity;
	double jumpForce;
	double speedY;
	bool onGround;
	int health;

	int flip;

	std::vector<Bullet*> bullList;

	C2D_SpriteSheet astroSpriteSheet;
	C2D_SpriteSheet healthSpriteSheet;

	Astro(double x, double y);
	void movement();
	void collision(std::vector<Platform>& platList);
	void shoot();
	void render();
	void update(std::vector<Platform>& platList);
};

#endif // ASTRO_H
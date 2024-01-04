#include <citro2d.h>
#include "Bullet.h"

Bullet::Bullet(double x, double y, int flip) 
{
	this->x = x;
	this->y = y;
	this->flip = flip;
	speed = 5.5;
	done = 0;

	bulletSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/bullet.t3x");
	C2D_SpriteFromSheet(&bullet, bulletSpriteSheet, 0);
	C2D_SpriteSetPos(&bullet, x, y);
}

Bullet::~Bullet() 
{
	C2D_SpriteSheetFree(bulletSpriteSheet);
}

void Bullet::enemyHit(double eX, double eY) 
{

}

void Bullet::update() 
{
	if (flip == 0) 
	{
		C2D_SpriteFromSheet(&bullet, bulletSpriteSheet, 0);
		this->x += speed;
	}
	else if (flip == 1) 
	{
		C2D_SpriteFromSheet(&bullet, bulletSpriteSheet, 1);
		this->x -= speed;
	}

	C2D_SpriteSetPos(&bullet, x, y);
}

void Bullet::render() 
{
	C2D_DrawSprite(&bullet);
	C2D_SpriteSetPos(&bullet, x, y);
}
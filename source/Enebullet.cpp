#include <citro2d.h>
#include "Enebullet.h"

Enebullet::Enebullet(double x, double y, int flip) 
{
	this->x = x;
	this->y = y;
	this->flip = flip;
	speed = 5.5;
	done = 0;

	eneBulletSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/parabullet.t3x");
	C2D_SpriteFromSheet(&eneBullet, eneBulletSpriteSheet, 0);
	C2D_SpriteSetPos(&eneBullet, x, y);
}

Enebullet::~Enebullet() 
{
	C2D_SpriteSheetFree(eneBulletSpriteSheet);
}

void Enebullet::playerHit() 
{

}

void Enebullet::update() 
{
	if (flip == 0) 
	{
		this->x += speed;
	}
	else if (flip == 1) 
	{
		this->x -= speed;
	}

	C2D_SpriteSetPos(&eneBullet, x, y);
}

void Enebullet::render() 
{
	C2D_DrawSprite(&eneBullet);
}
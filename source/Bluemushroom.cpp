#include <citro2d.h>
#include <vector>
#include "Bluemushroom.h"
#include "Platform.h"

Bluemushroom::Bluemushroom(double x, double y) 
{
	this->x = x;
	this->y = y;
	w = 17.0;
	h = 16.0;
	speedX = 1.5;
	velocityY = 0;
	gravity = 0.30;
	speedY = 11.0;
	onGround = false;
	done = 0;

	blueSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/bluemushroom.t3x");
	C2D_SpriteFromSheet(&blue, blueSpriteSheet, 0);
}

Bluemushroom::~Bluemushroom() 
{
	C2D_SpriteSheetFree(blueSpriteSheet);
}

void Bluemushroom::update(std::vector<Platform>& platList) 
{
	onGround = false;

	for(std::size_t i = 0; i < platList.size(); i++) 
	{
		if ((x + w/2) >= platList[i].x && (x + w/2) <= (platList[i].x + platList[i].w) && (y + h) <= (platList[i].y + platList[i].h) && (y + h) >= platList[i].y) 
		{
			//printf("COLLISION!");
			velocityY = 0;
			y = platList[i].y - h;
			onGround = true;
		}
	}

	if (onGround == false) 
	{
		velocityY += gravity;
		y += velocityY;

		if (velocityY >= speedY) 
		{
			velocityY = speedY;
		}
	}

	C2D_SpriteSetPos(&blue, x, y);
}

void Bluemushroom::render() 
{
	C2D_DrawSprite(&blue);
}
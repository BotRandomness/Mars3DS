#include <citro2d.h>
#include <vector>
#include <cmath>
#include <chrono>
#include "Enemy.h"
#include "Platform.h"

Enemy::Enemy(double x, double y, int anim) 
{
	this->x = x;
	this->y = y;
	this->anim = anim;
	w = 29.0;
	h = 25.0;
	speedX = 1.5;
	velocityY = 0;
	gravity = 0.30;
	speedY = 11.0;
	direction = 1;
	onGround = false;
	health = 3;

	flip = 0;

	framesCounter = 0;
	frameSpeed = 5;
	currentFrame = 0;

	incoming = std::chrono::steady_clock::now();

	paraSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/para.t3x");
	warnSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/warning.t3x");
	C2D_SpriteFromSheet(&parasite, warnSpriteSheet, 0);
	C2D_SpriteSetPos(&parasite, x, y);
}

void Enemy::movement(std::vector<Platform>& platList) 
{
	if (onGround == false) 
	{
		velocityY += gravity;
		y += velocityY;

		if (velocityY >= speedY) 
		{
			velocityY = speedY;
		}
	}

	if (onGround == true) 
	{
		speedX *= 1;
	}

	x += speedX;

	C2D_SpriteFromSheet(&parasite, paraSpriteSheet, 0);
	C2D_SpriteSetPos(&parasite, x, y);
}

void Enemy::collision(std::vector<Platform>& platList) 
{
	onGround = false;

	for(std::size_t i = 0; i < platList.size(); i++) 
	{
		bool center = (x + w/2) >= platList[i].x && (x + w/2) <= (platList[i].x + platList[i].w) && (y + h) <= (platList[i].y + platList[i].h) && (y + h) >= platList[i].y;
		bool right = x >= platList[i].x && x <= (platList[i].x + platList[i].w) &&  (y + h) >= platList[i].y && y <= (platList[i].y + platList[i].h);
		bool left = (x + w) >= platList[i].x && (x + w) <= (platList[i].x + platList[i].w) &&  (y + h) >= platList[i].y && y <= (platList[i].y + platList[i].h);

		if (center) 
		{
			//printf("COLLISION!");
			velocityY = 0;
			y = platList[i].y - h;
			onGround = true;
		}
		if (right && !center && !left) 
		{
			speedX *= -1;
			y = platList[i].y - h;
			velocityY = 0;
			onGround = true;
		}
		else if (left && !center && !right) 
		{
			speedX *= -1;
			y = platList[i].y - h;
			velocityY = 0;
			onGround = true;
		}
	}
}

void Enemy::shoot(double pX) 
{
	if (enebullList.size() >= 0) 
	{
		for (std::size_t i = 0; i < enebullList.size(); i++) 
		{
			if ((enebullList[i]->x >= 400 || enebullList[i]->x <= 0 || enebullList[i]->done == 1))
			{
				delete enebullList[i];
				enebullList.erase(enebullList.begin() + i);
				//printf("delE\n");
			}
			else 
			{
				enebullList[i]->update();
			}

			//printf("EnebullList: %d\n", enebullList.size());
		}
	}

	if (x >= pX) 
	{
		flip = 1;
	}
	else if (x <= pX) 
	{
		flip = 0;
	}

	if (enebullList.size() != 1) 
	{
		if (std::abs(pX - x) <= 100) 
		{
			enebullList.push_back(new Enebullet((x + w/2), (y + h/3), flip));
		}
	}
}

void Enemy::update(std::vector<Platform>& platList, double pX) 
{
	if (anim == 0) 
	{
		//Get the current time
		auto currentTime = std::chrono::steady_clock::now();

		//Calculate the elapsed time in seconds
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - incoming).count();

		if (elapsedTime <= 0.2) 
		{
			framesCounter++;

			if (framesCounter >= frameSpeed) 
			{

				framesCounter = 0;
	            currentFrame++;

	            if(currentFrame >= C2D_SpriteSheetCount(warnSpriteSheet))
	            {
	                currentFrame = 0;
	            }

				C2D_SpriteFromSheet(&parasite, warnSpriteSheet, currentFrame);
				C2D_SpriteSetPos(&parasite, x, y);
			}
		}
		else if (elapsedTime > 0.2) 
		{
			anim = 1;
			C2D_SpriteFromSheet(&parasite, paraSpriteSheet, currentFrame);
			C2D_SpriteSetPos(&parasite, x, y);
		}		
	}

	if (anim == 1) 
	{
		collision(platList);
		movement(platList);
		shoot(pX);
	}
}

void Enemy::render() 
{
	C2D_DrawSprite(&parasite);

	for (std::size_t i = 0; i < enebullList.size(); i++) 
	{
		enebullList[i]->render();
	}
}
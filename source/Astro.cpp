#include <citro2d.h>
#include <vector>
#include "Astro.h"
#include "Platform.h"
#include "Bullet.h"

Astro::Astro(double x, double y) 
{
	this->x = x;
	this->y = y;
	w = 22.0;
	h = 27.0;
	velocityX = 0;
	acc = 0.2;
	friction = 0.90;
	speedX = 4.3;
	velocityY = 0;
	gravity = 0.50;
	jumpForce = 8.7;
	speedY = 8.0;
	onGround = false;
	health = 5;

	flip = 0;

	astroSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/astro.t3x");
	C2D_SpriteFromSheet(&astro, astroSpriteSheet, 0);
	healthSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/health.t3x");
	C2D_SpriteFromSheet(&healthBar, healthSpriteSheet, 0);
}

void Astro::movement() 
{
	if (hidKeysHeld() & KEY_RIGHT) 
	{
		velocityX += acc;
		if (velocityX >= speedX) 
		{
			velocityX = speedX;
		}

		if (hidKeysDown() & KEY_RIGHT) 
		{
			C2D_SpriteFromSheet(&astro, astroSpriteSheet, 0);
			flip = 0;
		}

		C2D_SpriteSetPos(&astro, x, y);

	}
	else if (hidKeysHeld() & KEY_LEFT) 
	{
		velocityX -= acc;
		if (velocityX <= -speedX) 
		{
			velocityX = -speedX;
		}

		if (hidKeysDown() & KEY_LEFT) 
		{
			C2D_SpriteFromSheet(&astro, astroSpriteSheet, 1);
			flip = 1;
		}

		C2D_SpriteSetPos(&astro, x, y);
	}
	else 
	{
		velocityX *= friction;
	}
	x += velocityX;
	
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
		if (hidKeysDown() & KEY_B) 
		{
			velocityY += -jumpForce;
			y += velocityY;
		}
	}
	

	/*
	if (y >= 197) 
	{
		y = 197;
		velocityY = 0;
		onGround = true;
	}
	else 
	{
		onGround = false;
	*/

	if (x > 400) 
	{
		x = 0;
	}
	if((x + w) < 0) 
	{
		x = 400;
	}
	/*
	if (y > 240) 
	{
		y = 0;
	}
	*/

	C2D_SpriteSetPos(&astro, x, y);

	if(hidKeysHeld()) 
	{
		//printf("X: %f, Y: %f\n", x, y);
		//printf("OnGround Stat: %d\n", onGround);
	}
}

void Astro::collision(std::vector<Platform>& platList)
{
	onGround = false;

	for(std::size_t i = 0; i < platList.size(); i++) 
	{
		/*
		//Box collision
		if (x >= platList[i].x && x <= (platList[i].x + platList[i].w) &&  (y + h) >= platList[i].y && y <= (platList[i].y + platList[i].h)) 
		{
			//printf("COLLISION!\n");
			//velocityY = 0;
			//y = platList[i].y - h;
			//onGround = true;
		}
		*/

		if ((x + w/2) >= platList[i].x && (x + w/2) <= (platList[i].x + platList[i].w) && (y + h) <= (platList[i].y + platList[i].h) && (y + h) >= platList[i].y) 
		{
			//printf("COLLISION!");
			velocityY = 0;
			y = platList[i].y - h;
			onGround = true;
		}

		if ((x + w/2) >= platList[i].x && (x + w/2) <= (platList[i].x + platList[i].w) && y <= (platList[i].y + platList[i].h) && y >= platList[i].y) 
		{
			//printf("BOTTOM!");
			y += speedY - 2;
		}

		if (x >= platList[i].x && x <= (platList[i].x + platList[i].w) && (y + h/2) <= (platList[i].y + platList[i].h) && (y + h/2) >= platList[i].y) 
		{
			//printf("RIGHT-SIDE!");
			x += speedX * 2;
		}

		if ((x + w) >= platList[i].x && (x + w) <= (platList[i].x + platList[i].w) && (y + h/2) <= (platList[i].y + platList[i].h) && (y + h/2) >= platList[i].y) 
		{
			//printf("LEFT-SIDE!");
			x -= speedX * 2;
		}
	}

}

void Astro::shoot() 
{
	if (bullList.size() >= 0) 
	{
		for (std::size_t i = 0; i < bullList.size(); i++) 
		{
			if ((bullList[i]->x >= 400 || bullList[i]->x <= 0 || bullList[i]->done == 1))
			{
				delete bullList[i];
				bullList.erase(bullList.begin() + i);
				//printf("delP\n");
			}
			else 
			{
				bullList[i]->update();
			}

			//printf("BullList: %d\n", bullList.size());
		}
	}

	if (hidKeysDown() & KEY_A) 
	{
		bullList.push_back(new Bullet((x + w/2), (y + h/3), flip));
	}	
}

void Astro::update(std::vector<Platform>& platList) 
{
	if (health >= 1) 
	{
		collision(platList);
		movement();
		shoot();
    }

	if (health == 5) 
	{
		C2D_SpriteFromSheet(&healthBar, healthSpriteSheet, 0);
		C2D_SpriteSetPos(&healthBar, 3, 3);
	}
	else if (health == 4) 
	{
		C2D_SpriteFromSheet(&healthBar, healthSpriteSheet, 1);
		C2D_SpriteSetPos(&healthBar, 3, 3);
	}
	else if (health == 3) 
	{
		C2D_SpriteFromSheet(&healthBar, healthSpriteSheet, 2);
		C2D_SpriteSetPos(&healthBar, 3, 3);
	}
	else if (health == 2) 
	{
		C2D_SpriteFromSheet(&healthBar, healthSpriteSheet, 3);
		C2D_SpriteSetPos(&healthBar, 3, 3);
	}
	else if (health == 1) 
	{
		C2D_SpriteFromSheet(&healthBar, healthSpriteSheet, 4);
		C2D_SpriteSetPos(&healthBar, 3, 3);
	}
	else if (health == 0) 
	{
		C2D_SpriteFromSheet(&healthBar, healthSpriteSheet, 5);
		C2D_SpriteSetPos(&healthBar, 3, 3);
	}
}

void Astro::render() 
{
	if (health >= 1) 
	{
		C2D_DrawSprite(&astro);
	}
	
	C2D_DrawSprite(&healthBar);

	for (std::size_t i = 0; i < bullList.size(); i++) 
	{
		bullList[i]->render();
	}
}
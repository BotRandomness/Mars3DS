#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include <vector>
#include <random>
#include <chrono>
#include "Astro.h"
#include "Platform.h"
#include "Enemy.h"
#include "Bluemushroom.h"
#include "Greenmushroom.h"
#include "Purplemushroom.h"

template <typename RNG>
void spawnEnemy(std::vector<Enemy*>& paraList, RNG& gen, int minX, int maxX, int minY, int maxY, std::chrono::steady_clock::time_point& startTime) 
{
	if (paraList.size() < 7) 
	{
	    auto currentTime = std::chrono::steady_clock::now();
	    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

	    if (elapsedTime >= 1.9) 
	    {
	        std::uniform_int_distribution<int> distributionX(minX, maxX);
	        std::uniform_int_distribution<int> distributionY(minY, maxY);

	        int randomX = distributionX(gen);
	        int randomY = distributionY(gen);

	        paraList.push_back(new Enemy(randomX, randomY, 0));

	        startTime = std::chrono::steady_clock::now();
	    }
    }
}

void enemyHit(std::vector<Enemy*>& paraList, Astro& astro, std::vector<Platform>& platList) 
{
	for (int i = 0; i < paraList.size(); i++) 
	{
		paraList[i]->update(platList, astro.x);

		for (int j = 0; j < astro.bullList.size(); j++) 
		{
			int hit = 0;

			if (astro.bullList[j]->x >= paraList[i]->x && astro.bullList[j]->x <= (paraList[i]->x + paraList[i]->w) &&  (astro.bullList[j]->y + 9.0) >= paraList[i]->y && astro.bullList[j]->y <= (paraList[i]->y + paraList[i]->h)) 
			{
				hit += 1;

				if (hit == 1) 
				{
					paraList[i]->health -= 1;
					astro.bullList[j]->done = 1;
				}

				if (paraList[i]->health <= 0) 
				{
					//astro.bullList[j]->done = 1;
					delete paraList[i];
					paraList.erase(paraList.begin() + i);
				}
			}
		}

		if(paraList[i]->y >= 240) 
		{
			delete paraList[i];
			paraList.erase(paraList.begin() + i);
		}
	}
}

template <typename RNG>
void playerHit(std::vector<Enemy*>& paraList, Astro& astro, RNG& gen, std::chrono::steady_clock::time_point& sT, int& scene, int& score) 
{
	auto cT = std::chrono::steady_clock::now();
	auto eT = std::chrono::duration_cast<std::chrono::seconds>(cT - sT).count();

	for (int i = 0; i < paraList.size(); i++) 
	{
		int hitP = 0;

		for (int j = 0; j < paraList[i]->enebullList.size(); j++) 
		{
			if (paraList[i]->enebullList[j]->x >= astro.x && paraList[i]->enebullList[j]->x <= (astro.x + astro.w) && (paraList[i]->enebullList[j]->y + 15.0) >= astro.y && paraList[i]->enebullList[j]->y <= (astro.y + astro.h)) 
			{
				hitP += 1;

				if (hitP == 1 && eT >= 1.8) 
				{
					astro.health -= 1;
					paraList[i]->enebullList[j]->done = 1;
					sT = std::chrono::steady_clock::now();
					//printf("HIT!");
				}

				if (astro.health <= 0) 
				{
					//printf("DEAD!");
					for (int k = 0; k < astro.bullList.size(); k++) 
					{
						delete astro.bullList[k]; 
					}
					astro.bullList.clear();

					for (int k = 0; k < paraList.size(); k++) 
					{
						for (int l = 0; l < paraList[k]->enebullList.size(); l++) 
						{
							delete paraList[k]->enebullList[l];
						}
						paraList[k]->enebullList.clear();

						delete paraList[k];
					}
					paraList.clear();

					//score = 0;
					scene = 2;
				}
			}
		}
	}
}

template <typename RNG>
void scoreBlue(int& score, std::vector<Bluemushroom*>& blueList, Astro& astro, std::vector<Platform>& platList, RNG& gen, std::chrono::steady_clock::time_point& blueTime, int minX, int maxX, int minY, int maxY, int minS, int maxS) 
{
	//printf("%d", score);

	auto blueCurrentTime = std::chrono::steady_clock::now();

	auto blueElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(blueCurrentTime - blueTime).count();

	if (blueElapsedTime >= minS) 
	{
	    
		if (blueList.size() == 0 && blueElapsedTime - minS <= 0) 
		{
			std::uniform_int_distribution<int> distributionX(30, 260);
	    	std::uniform_int_distribution<int> distributionY(minY, maxY);

	    	int blueRandomX = distributionX(gen);
	    	int blueRandomY = distributionY(gen);

	    	blueList.push_back(new Bluemushroom(blueRandomX, blueRandomY));
	    	//printf("Make!");
		}

		if (blueElapsedTime >= maxS) 
		{
			for (int i = 0; i < blueList.size(); i++) 
			{
				delete blueList[i];
			}
			blueList.clear();

	        blueTime = std::chrono::steady_clock::now();
	        //printf("Reset/Del");
		}
		if (blueElapsedTime > minS && blueElapsedTime < maxS) 
		{
			for (int i = 0; i < blueList.size(); i++) 
			{
				if (blueList[i]->x >= astro.x && blueList[i]->x <= (astro.x + astro.w) && (blueList[i]->y + 16.0) >= astro.y && blueList[i]->y <= (astro.y + astro.h)) 
				{
					score += 1;
					delete blueList[i];
					blueList.erase(blueList.begin() + i);
				}
				
				if(blueList.size() > 0) 
				{
					blueList[i]->update(platList);
	    			blueList[i]->render();
					//printf("GO!");
				}
			}
		}
	}
}

template <typename RNG>
void heal(std::vector<Greenmushroom*>& greenList, Astro& astro, std::vector<Platform>& platList, RNG& gen, std::chrono::steady_clock::time_point& greenTime, int minX, int maxX, int minY, int maxY, int minS, int maxS) 
{
	//printf("%d", score);

	auto greenCurrentTime = std::chrono::steady_clock::now();

	auto greenElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(greenCurrentTime - greenTime).count();

	if (greenElapsedTime >= minS) 
	{
	    
		if (greenList.size() == 0 && greenElapsedTime - minS <= 0) 
		{
			std::uniform_int_distribution<int> distributionX(minX, maxX);
	    	std::uniform_int_distribution<int> distributionY(minY, maxY);

	    	int greenRandomX = distributionX(gen);
	    	int greenRandomY = distributionY(gen);

	    	greenList.push_back(new Greenmushroom(greenRandomX, greenRandomY));
	    	//printf("Make!");
		}

		if (greenElapsedTime >= maxS) 
		{
			for (int i = 0; i < greenList.size(); i++) 
			{
				delete greenList[i];
			}
			greenList.clear();

	        greenTime = std::chrono::steady_clock::now();
	        //printf("Reset/Del");
		}
		if (greenElapsedTime > minS && greenElapsedTime < maxS) 
		{
			for (int i = 0; i < greenList.size(); i++) 
			{
				if (greenList[i]->x >= astro.x && greenList[i]->x <= (astro.x + astro.w) && (greenList[i]->y + 16.0) >= astro.y && greenList[i]->y <= (astro.y + astro.h)) 
				{
					if (astro.health < 5) 
					{
						astro.health += 1;
					}

					delete greenList[i];
					greenList.erase(greenList.begin() + i);
				}
				
				if(greenList.size() > 0) 
				{
					greenList[i]->update(platList);
	    			greenList[i]->render();
					//printf("GO!");
				}
			}
		}
	}
}

template <typename RNG>
void antiGravityPower(int& antiGravity, std::vector<Purplemushroom*>& purpleList, Astro& astro, std::vector<Platform>& platList, RNG& gen, std::chrono::steady_clock::time_point& purpleTime, int minX, int maxX, int minY, int maxY, int minS, int maxS) 
{
	//printf("%d", score);

	auto purpleCurrentTime = std::chrono::steady_clock::now();

	auto purpleElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(purpleCurrentTime - purpleTime).count();

	if (purpleElapsedTime >= minS) 
	{
	    
		if (purpleList.size() == 0 && purpleElapsedTime - minS <= 0) 
		{
			std::uniform_int_distribution<int> distributionX(minX, maxX);
	    	std::uniform_int_distribution<int> distributionY(minY, maxY);

	    	int purpleRandomX = distributionX(gen);
	    	int purpleRandomY = distributionY(gen);

	    	purpleList.push_back(new Purplemushroom(purpleRandomX, purpleRandomY));
	    	//printf("Make!");
		}

		if (purpleElapsedTime >= maxS) 
		{
			for (int i = 0; i < purpleList.size(); i++) 
			{
				delete purpleList[i];
			}
			purpleList.clear();

	        purpleTime = std::chrono::steady_clock::now();
	        //printf("Reset/Del");
		}
		if (purpleElapsedTime > minS && purpleElapsedTime < maxS) 
		{
			for (int i = 0; i < purpleList.size(); i++) 
			{
				if (purpleList[i]->x >= astro.x && purpleList[i]->x <= (astro.x + astro.w) && (purpleList[i]->y + 16.0) >= astro.y && purpleList[i]->y <= (astro.y + astro.h)) 
				{
					if (antiGravity < 3) 
					{
						antiGravity += 1;
					}

					delete purpleList[i];
					purpleList.erase(purpleList.begin() + i);
				}
				
				if(purpleList.size() > 0) 
				{
					purpleList[i]->update(platList);
	    			purpleList[i]->render();
					//printf("GO!");
				}
			}
		}
	}
}

void fall(int& antiGravity, Astro& astro, std::vector<Enemy*>& paraList, int& score, int& scene)
{
	if (astro.y >= 240) 
	{
		antiGravity -= 1;

		if (antiGravity < 0) 
		{
			//printf("DEAD!");
			for (int k = 0; k < astro.bullList.size(); k++) 
			{
				delete astro.bullList[k]; 
			}
			astro.bullList.clear();

			for (int k = 0; k < paraList.size(); k++) 
			{
				for (int l = 0; l < paraList[k]->enebullList.size(); l++) 
				{
					delete paraList[k]->enebullList[l];
				}
				paraList[k]->enebullList.clear();

				delete paraList[k];
			}
			paraList.clear();

			//score = 0;
			scene = 2;			
		}
		else 
		{
			astro.y = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	romfsInit();
	gfxInitDefault();
	cfguInit();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	//consoleInit(GFX_BOTTOM, NULL);
	
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT); //Top Screen ready for graphics
	C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT); //Bottom Screen ready for graphics

	int scene = 3;

	Astro astro(195.0, 50.0);

	std::vector<Enemy*> paraList;

	std::vector<Bluemushroom*> blueList;
	int score = 0;
	int highScore = 0;

	std::vector<Greenmushroom*> greenList;

	std::vector<Purplemushroom*> purpleList;
	int antiGravity = 0;

	std::vector<Platform> platList;
	platList.push_back(Platform(30, 139, 90, 9));
	platList.push_back(Platform(250, 139, 90, 9));
	platList.push_back(Platform(20, 90, 90, 9));
	platList.push_back(Platform(260, 90, 90, 9));
	platList.push_back(Platform(60, 220, 280, 9));

	std::random_device rd;
    std::mt19937 gen(rd());
    auto startTime = std::chrono::steady_clock::now();
    auto sT = std::chrono::steady_clock::now();
    auto blueTime = std::chrono::steady_clock::now();
    auto greenTime = std::chrono::steady_clock::now();
    auto purpleTime = std::chrono::steady_clock::now();
    int minX = 1;
    int maxX = 250;
    int minY = 95;
    int maxY = 210;

	C2D_TextBuf g_staticBuf;
	C2D_Text g_staticText;
	C2D_TextBuf g2_staticBuf;
	C2D_Text g2_staticText;
	C2D_TextBuf g3_staticBuf;
	C2D_Text g3_staticText;
	C2D_TextBuf g4_staticBuf;
	C2D_Text g4_staticText;
	C2D_TextBuf g5_staticBuf;
	C2D_Text g5_staticText;
	C2D_TextBuf g6_staticBuf;
	C2D_Text g6_staticText;
	C2D_TextBuf g7_staticBuf;
	C2D_Text g7_staticText;
	C2D_TextBuf g8_staticBuf;
	C2D_Text g8_staticText;
	g_staticBuf  = C2D_TextBufNew(4096);
	g2_staticBuf  = C2D_TextBufNew(4096);
	g3_staticBuf  = C2D_TextBufNew(4096);
	g4_staticBuf  = C2D_TextBufNew(4096);
	g5_staticBuf  = C2D_TextBufNew(4096);
	g6_staticBuf  = C2D_TextBufNew(4096);
	g7_staticBuf  = C2D_TextBufNew(4096);
	g8_staticBuf  = C2D_TextBufNew(4096);
	C2D_Font font = C2D_FontLoad("romfs:/nokiafc22.bcfnt");
	C2D_TextFontParse(&g3_staticText, font, g3_staticBuf, "Press (A) or TOUCH screen to Play");
	C2D_TextOptimize(&g3_staticText);
	C2D_TextFontParse(&g4_staticText, font, g4_staticBuf, "GAME OVER!");
	C2D_TextOptimize(&g4_staticText);
	C2D_TextFontParse(&g5_staticText, font, g5_staticBuf, "Score");
	C2D_TextOptimize(&g5_staticText);
	C2D_TextFontParse(&g6_staticText, font, g6_staticBuf, "High Score");
	C2D_TextOptimize(&g6_staticText);
	C2D_TextFontParse(&g7_staticText, font, g7_staticBuf, "Press (A) or TOUCH screen to Continue");
	C2D_TextOptimize(&g7_staticText);

	C2D_Sprite purpHud;
	C2D_SpriteSheet purpHudSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/purplecount.t3x");
	C2D_SpriteFromSheet(&purpHud, purpHudSpriteSheet, 0);

	C2D_Sprite background;
	C2D_SpriteSheet backgroundSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/background.t3x");
	C2D_SpriteFromSheet(&background, backgroundSpriteSheet, 0);

	C2D_Sprite logo;
	C2D_SpriteSheet logoSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/logo.t3x");
	C2D_SpriteFromSheet(&logo, logoSpriteSheet, 0);

	C2D_Sprite splash;
	C2D_SpriteSheet splashSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/splash.t3x");
	C2D_SpriteFromSheet(&splash, splashSpriteSheet, 0);
	auto splashTime = std::chrono::steady_clock::now();
	double splashX = 98;
	double splashY = -95;

	C2D_Sprite instru;
	C2D_SpriteSheet instruSpriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/instru.t3x");
	C2D_SpriteFromSheet(&instru, instruSpriteSheet, 0);

	touchPosition touch;

	//Main game loop
	while(aptMainLoop()) 
	{
		//Update
		hidScanInput();
		hidTouchRead(&touch);

		if (hidKeysDown() & KEY_START) break; //Back to Homebrew Menu

		if (scene == 0) 
		{
			astro.update(platList);

	    	spawnEnemy(paraList, gen, minX, maxX, minY, maxY, startTime);

			enemyHit(paraList, astro, platList);

			playerHit(paraList, astro, gen, sT, scene, score);

			fall(antiGravity, astro, paraList, score, scene);

			C2D_TextFontParse(&g_staticText, font, g_staticBuf, std::to_string(score).c_str());
			C2D_TextFontParse(&g2_staticText, font, g2_staticBuf, std::to_string(antiGravity).c_str());

			C2D_TextOptimize(&g_staticText);
			C2D_TextOptimize(&g2_staticText);

			C2D_SpriteSetPos(&purpHud, 330.0, 4.5);

			//printf("%d\n", paraList.size());
			//printf("%d\n", astro.health);
		}
		else if (scene == 1) 
		{
			if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH)) 
			{
				scene = 4;
			}
		}
		else if (scene == 2) 
		{
			C2D_TextFontParse(&g_staticText, font, g_staticBuf, std::to_string(score).c_str());
			C2D_TextOptimize(&g_staticText);

			if (score > highScore) 
			{
				highScore = score;
			}

			C2D_TextFontParse(&g8_staticText, font, g8_staticBuf, std::to_string(highScore).c_str());
			C2D_TextOptimize(&g8_staticText);

			if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH)) 
			{
				scene = 0;
				score = 0;
				astro.x = 195.0;
				astro.y = 95.0;
				astro.health = 5;
				antiGravity = 0;

				paraList.push_back(new Enemy(120.0, 50.0, 1));
				paraList.push_back(new Enemy(50.0, 0.0, 1));
				paraList.push_back(new Enemy(60.0, 90.0, 1));
				paraList.push_back(new Enemy(300.0, 10.0, 1));
			}
		}
		else if (scene == 3) 
		{
			auto splashCurrentTime = std::chrono::steady_clock::now();
			auto splashElapsedTime = std::chrono::duration_cast<std::chrono::seconds>(splashCurrentTime - splashTime).count();
			
			if (splashY < 67) 
			{
				splashY += 2.0;
			}

			C2D_SpriteSetPos(&splash, splashX, splashY);

			if (splashElapsedTime >= 2.4) 
			{
				scene = 1;
			}
		}
		else if (scene == 4) 
		{
			if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH)) 
			{
				scene = 0;
				score = 0;
				astro.x = 195.0;
				astro.y = 95.0;
				astro.health = 5;
				antiGravity = 0;

				paraList.push_back(new Enemy(120.0, 50.0, 1));
				paraList.push_back(new Enemy(50.0, 0.0, 1));
				paraList.push_back(new Enemy(60.0, 90.0, 1));
				paraList.push_back(new Enemy(300.0, 10.0, 1));
			}
		}

		//Render
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		
		C2D_SceneBegin(top);
		C2D_TargetClear(top, C2D_Color32(0.0f, 0.0f, 0.0f, 0.0f)); //Background color

		if (scene == 0) 
		{
			C2D_DrawSprite(&background);

			astro.render();

			for (int i = 0; i < platList.size(); i++) 
			{
				platList[i].render();
			}

			for (int i = 0; i < paraList.size(); i++) 
			{
				paraList[i]->render();
			}

			scoreBlue(score, blueList, astro, platList, gen, blueTime, minX, maxX, minY, maxY, 2, 7);
			heal(greenList, astro, platList, gen, greenTime, minX, maxX, minY, maxY, 5, 10);
			antiGravityPower(antiGravity, purpleList, astro, platList, gen, purpleTime, minX, maxX, minY, maxY, 2, 6);

			C2D_DrawText(&g_staticText, C2D_WithColor, 190.0f, 2.0f, 0.5f, 1.2f, 1.2f, C2D_Color32(255, 255, 255, 255));
			C2D_DrawText(&g2_staticText, C2D_WithColor, 359.0f, 2.0f, 0.0f, 0.8f, 0.8f, C2D_Color32(255, 255, 255, 255));

			C2D_DrawSprite(&purpHud);
		}
		else if (scene == 1) 
		{
			C2D_DrawSprite(&logo);
		}
		else if (scene == 2) 
		{
			C2D_DrawSprite(&background);
			C2D_DrawText(&g4_staticText, C2D_WithColor, 78.0f, 8.0f, 0.5f, 1.5f, 1.4f, C2D_Color32(255, 255, 255, 255));
			C2D_DrawText(&g5_staticText, C2D_WithColor, 155.0f, 60.0f, 0.5f, 1.0f, 1.0f, C2D_Color32(255, 255, 255, 255));
			C2D_DrawText(&g_staticText, C2D_WithColor, 183.0f, 90.0f, 0.5f, 1.3f, 1.3f, C2D_Color32(255, 255, 255, 255));
			C2D_DrawText(&g6_staticText, C2D_WithColor, 120.0f, 150.0f, 0.5f, 1.0f, 1.0f, C2D_Color32(255, 255, 255, 255));
			C2D_DrawText(&g8_staticText, C2D_WithColor, 183.0f, 190.0f, 0.5f, 1.3f, 1.3f, C2D_Color32(255, 255, 255, 255));

		}
		else if (scene == 3) 
		{
			C2D_DrawSprite(&background);
			C2D_DrawSprite(&splash);
		}
		else if (scene == 4) 
		{
			C2D_DrawSprite(&instru);
		}

		C2D_SceneBegin(bot);
		C2D_TargetClear(bot, C2D_Color32(219.0f, 95.0f, 27.0f, 0.0f));
		
		if (scene == 0) 
		{
			C2D_DrawSprite(&background);
		}
		else if (scene == 1) 
		{
			C2D_DrawSprite(&background);
			C2D_DrawText(&g3_staticText, C2D_WithColor, 45.0f, 120.0f, 0.5f, 0.5f, 0.5f, C2D_Color32(255, 255, 255, 255));

		}
		else if (scene == 2) 
		{
			C2D_DrawSprite(&background);
			C2D_DrawText(&g7_staticText, C2D_WithColor, 30.0f, 120.0f, 0.5f, 0.5f, 0.5f, C2D_Color32(255, 255, 255, 255));

		}
		else if (scene == 3) 
		{
			C2D_DrawSprite(&background);
		}
		else if (scene == 4) 
		{
			C2D_DrawSprite(&background);
			C2D_DrawText(&g7_staticText, C2D_WithColor, 30.0f, 120.0f, 0.5f, 0.5f, 0.5f, C2D_Color32(255, 255, 255, 255));

		}

		C3D_FrameEnd(0);
	}

	//Done
	C2D_SpriteSheetFree(astro.astroSpriteSheet);
	C2D_SpriteSheetFree(astro.healthSpriteSheet);
	C2D_SpriteSheetFree(logoSpriteSheet);
	C2D_SpriteSheetFree(backgroundSpriteSheet);
	C2D_SpriteSheetFree(splashSpriteSheet);
	C2D_SpriteSheetFree(instruSpriteSheet);
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	cfguExit();
	return 0;
}
#ifndef BULLET_H
#define BULLET_H

class Bullet 
{
public:
	C2D_Sprite bullet;
	double x;
	double y;
	double speed;
	int flip;
	int done;

	C2D_SpriteSheet bulletSpriteSheet;

	Bullet(double x, double y, int flip);
	~Bullet();
	void enemyHit(double eX, double eY);
	void update();
	void render();
};

#endif // BULLET_H
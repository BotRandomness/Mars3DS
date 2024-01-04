#ifndef ENEBULLET_H
#define ENEBULLET_H

class Enebullet 
{
public:
	C2D_Sprite eneBullet;
	double x;
	double y;
	double speed;
	int flip;
	int done;

	C2D_SpriteSheet eneBulletSpriteSheet;

	Enebullet(double x, double y, int flip);
	~Enebullet();
	void playerHit();
	void update();
	void render();
};

#endif // ENEBULLET_H
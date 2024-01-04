#ifndef PLATFORM_H
#define PLATFORM_H

class Platform 
{
public:
	double x;
	double y;
	double w;
	double h;

	Platform(double x, double y, double w, double h);
	void update();
	void render();
};

#endif // PLATFORM_H
#include <citro2d.h>
#include "Platform.h"

Platform::Platform(double x, double y, double w, double h) 
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void Platform::update() 
{

}

void Platform::render() 
{
	C2D_DrawRectSolid(x, y, 0, w, h, C2D_Color32(251.6f, 168.2f, 52.4f, 255.0f));
}
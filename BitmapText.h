#ifndef BITMAPTEXT_H
#define BITMAPTEXT_H

#include <GL/glut.h>
#include "MathStructs.h"

class BitmapText  
{
public:
	BitmapText();
	BitmapText(Point, void *);

	void raster(char *);

private:
	Point location;
	void *font;
	

};

#endif


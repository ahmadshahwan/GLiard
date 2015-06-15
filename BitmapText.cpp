#include "BitmapText.h"

BitmapText::BitmapText(Point pos, void *fnt)
	: location(pos), font(fnt)
{
}

BitmapText::BitmapText()
{
	BitmapText(Point(0.0, 0.0, 0.0), GLUT_BITMAP_8_BY_13);
}

void BitmapText::raster(char *str)
{
	char *c;
	// set position to start drawing fonts
	glRasterPos3f(location.getX(), location.getY(), location.getZ());
	// loop all the characters in the string
	for (c=str; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}


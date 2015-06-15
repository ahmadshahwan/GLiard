#ifndef POCKET_H
#define POCKET_H

#include "Ball.h"

class Pocket: public PhysicalObject
{
public:
	// constructors
	Pocket();
	Pocket(Point, double);

	// getters
	double getRadius() const;

	// other member functions
	bool draw(Ball &);

	static void renderCurvePart(Point, double, double, double);
	static void renderSharpPart(Point, double, double, double);

	void render();

private:
	double radius;
};

#endif


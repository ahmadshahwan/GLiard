#ifndef TABLE_H
#define TABLE_H

#include "MathStructs.h"
#include "Ball.h"
#include "Pocket.h"
#include "PhysicalObject.h"

class Table: public PhysicalObject
{
public:
	// constructors
	Table(Point, double, double);
	Table();

	static const double BORDER;				// borders' thickness

	double getHeight();
	double getWidth();
	double getLeft();
	double getRight();
	double getTop();
	double getBottom();

	// checks the position of the ball according to the table,
	// and applies the proper forces
	bool checkBorders(Ball &);
	// applies the proper friction
	void applyFriction(Ball &);

	void render();

private:
	static const double FRICTION_FACTOR;	// friction factor
	static const double RADIUS;				// pockets' radius

	// checks the position of the ball according to the table holes
	bool checkHoles(Ball &);
	// checks the position of the ball according to the table borders
	bool checkCollision(Ball &);

	double height;
	double width;
	Pocket pocket[6];
};

#endif

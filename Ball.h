#ifndef BALL_H
#define BALL_H

#include "MathStructs.h"
#include "PhysicalObject.h"

class Ball: public PhysicalObject
{
public:
	enum Color
	{
		WHITE,
		BLACK
	};

	// constructors
	Ball(Point, double, double, Color);
	Ball();

	// getters
	double getRadius() const;
	double getMass() const;
	Vector getVelocity() const;
	Color getColor() const;
	bool isStatic() const;
	bool isPocketed() const;


	// modifiers
	void updateLocation();
	void applyImpulse(Vector);
	void pocket();
	void resetAt(Point);

	void render();

private:
	double radius;
	double mass;
	Color color;
	Vector velocity;
	bool pocketed;
};

#endif

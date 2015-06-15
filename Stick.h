#ifndef STICK_H
#define STICK_H

#include "Ball.h"
#include "PhysicalObject.h"

class Stick: public PhysicalObject
{
public:
	// constructors
	Stick(double);
	Stick();

	// getters
	int getPower() const;
	double getImpulse() const;
	double getAngle() const;

	// shifts power up till it reaches the maximus, the resets it
	int shiftPower();
	// resets power to the minimum
	void resetPower();
	// set stick angle
	void setAngle(double);
	// hit a ball
	void hit(Ball &);
	
	void render();

private:
	static const double IMPULSE_FACTOR;		// impulse factor to be mutiplied by power
	static const int POWER_GRADES;			// power incrementation
	static const int MIN_POWER;				// minimus power
	static const double JUMP;				// distance between two contiguous states

	double itsLength;
	double angle;
	int power;
};

#endif
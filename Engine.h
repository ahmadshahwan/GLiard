#ifndef ENGINE_H
#define ENGINE_H

#include <math.h>
#include "MathStructs.h"
#include "Ball.h"
#include "Table.h"
#include "Stick.h"

class Engine
{
public:
	// enumeration represents game state
	enum State
	{
		GAME_OVER,
		YOU_WIN,
		GAME_ON,
		INITIAL
	};

	// constructor
	Engine();

	// class member getters
	Table &getTable();
	Ball &getCue();
	Ball &getEight();
	Stick &getStick();

	// sets the eight ball at its initial position
	bool setEightBallAt(Point);
	// sets the eight ball at the default position
	bool setEightBallAt();
	// progresses the game to the next step, returning the game's new state
	State nextStep();
	// directs the stick from the cue ball toward a certain point
	void directStick(Point);
	// hits the cue ball with the stick, only if the balls are static
	bool hit(Point);
	// changes the power of the stick
	int shiftPower();
	// resets the whole game all over
	void reset();

	// denotes whether the balls on the table are static or not
	bool isStatic() const;
	// denotes whether the balls have just been stabilized
	bool isStabilized() const;
	// returns the game's current state
	State getState() const;
	// returns how far is the eight ball from the cue one
	double howFar() const;
	// returns the value of the velocity to be applied on the cue ball
	double cueInitialVelocity() const;
	// estimates the time needed for the cue ball to hit the eight on, in case of head on collision only
	int estimateHeadOnTime() const;
	// returns information about the game
	char *infoString(int, char *) const;
	// returns time interval between two consecutive scenes, in ms
	int timeInterval() const;
		
private:
	static const double STICK_LENGTH;
	static const double BALL_MASS;
	static const double BALL_RADIUS;
	static const double TABLE_HEIGHT;
	static const double TABLE_WIDTH;
	static const int TIME_INTERVAL;

	Ball cueBall;
	Ball eightBall;
	Table table;
	Stick stick;
	bool initial;

	void nextStep(Ball &);
	void collideBalls();
};

#endif

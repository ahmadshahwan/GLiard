#include <string.h>
#include <stdio.h>
#include "MathStructs.h"
#include "Table.h"
#include "Ball.h"
#include "Engine.h"

const double Engine::STICK_LENGTH = 1.25;
const double Engine::BALL_MASS = 1;
const double Engine::TABLE_HEIGHT = 1;
const double Engine::TABLE_WIDTH = 1.5;
const double Engine::BALL_RADIUS = 0.05;
const int Engine::TIME_INTERVAL = 40;

Engine::Engine():
	table(Point(-0.75, -0.5, 0), TABLE_HEIGHT, TABLE_WIDTH),
	cueBall(
		Point(
			-0.75 + (TABLE_WIDTH/6),
			-0.50 + (TABLE_HEIGHT/2),
			BALL_RADIUS
		), 
		BALL_RADIUS,
		BALL_MASS, 
		Ball::WHITE
	),
	eightBall(
		Point(
			-0.75 + (TABLE_WIDTH/6),
			-0.50 + (5*TABLE_HEIGHT/2),
			BALL_RADIUS
		),
		BALL_RADIUS,
		BALL_MASS,
		Ball::BLACK
	),
	stick(STICK_LENGTH),
	initial(true)
{
	directStick(Point(0.0, 0.0, 0.0));
	eightBall.hide();
}

Table &Engine::getTable()
{
	return table;
}

Ball &Engine::getCue()
{
	return cueBall;
}

Ball &Engine::getEight()
{
	return eightBall;
}

Stick &Engine::getStick()
{
	return stick;
}

void Engine::nextStep(Ball &ball)
{
	if (!ball.isPocketed()) // case the ball is not already in the hole
	{
		// check whether ball collide with borders or fit in a hole,
		// and apply the proper forces
		table.checkBorders(ball);
		// update position according to the current velocity
		ball.updateLocation();
		// apply frictional impulse on the ball
		table.applyFriction(ball);
	}
}

Engine::State Engine::nextStep()
{
	collideBalls();
	nextStep(cueBall);
	nextStep(eightBall);
	if (isStatic() && (getState() != GAME_OVER))
		stick.show();
	if (isStabilized())
		directStick(eightBall.getLocation());
	return getState();
}

bool Engine::isStatic() const
{
	return (cueBall.isStatic() && eightBall.isStatic());
}

bool Engine::isStabilized() const
{
	static bool state = false;
	bool oldState = state;
	state = isStatic();
	return ((state != oldState) && (state));
}

bool Engine::hit(Point dest)
{
	if (initial)
		setEightBallAt(dest);
	else if (isStatic() /*&& (getState() == GAME_ON)*/)
	{
		directStick(dest);
		stick.hit(cueBall);
		stick.resetPower();
	}
	else
		return false;
	return true;
}

int Engine::shiftPower()
{
	// return zero in case of initial state
	if (initial)
		return (int) !setEightBallAt();
	else
		return stick.shiftPower();	
}

void Engine::collideBalls()
{
	Vector dPos = ((Vector) cueBall.getLocation() + cueBall.getVelocity()) - ((Vector) eightBall.getLocation() + eightBall.getVelocity());
	double xSpace = dPos.length() - (cueBall.getRadius() + eightBall.getRadius());
	// if the two balls collide
	if (xSpace <= 0)
	{
		// normal to the surface of the collision, toward the cue ball
		Vector n = dPos.unit();		// unit vector
		// calculate impulses applied on each ball
		double impFactor = 2 * (cueBall.getMass() * eightBall.getMass()) / (cueBall.getMass() + eightBall.getMass());
		double imp = impFactor * ((eightBall.getVelocity() - cueBall.getVelocity()).dot(n));
		cueBall.applyImpulse(n * (+imp));
		eightBall.applyImpulse(n * (-imp));
	}
}

void Engine::directStick(Point p)
{

	// calculate the inclination angle of the stick
	double angle = ((Vector) p - (Vector) cueBall.getLocation()).inclination2D();
	// direct the stick
	stick.setAngle(angle);
	// now put the stick at the right place
	stick.putAt((Vector) cueBall.getLocation());
}

void Engine::reset()
{
	initial = true;
	cueBall.resetAt(Point(
		table.getLeft() + (table.getWidth()/6),
		table.getBottom() + (table.getHeight()/2),
		eightBall.getRadius()
	));
	cueBall.show();
	eightBall.resetAt(Point(
		table.getRight() - (table.getWidth()/6),
		table.getBottom() + (table.getHeight()/2),
		eightBall.getRadius()
	));
	eightBall.hide();
}

Engine::State Engine::getState() const
{
	if (initial)
		return INITIAL;
	else if (cueBall.isPocketed())
		return GAME_OVER;
	else if (eightBall.isPocketed())
		return YOU_WIN;
	else
		return GAME_ON;
}

double Engine::howFar() const
{
	return ((Vector) cueBall.getLocation() - (Vector) eightBall.getLocation()).length();
}

double Engine::cueInitialVelocity() const
{
	return stick.getImpulse() / cueBall.getMass();
}

int Engine::estimateHeadOnTime() const
{
	// regardless the friction
	return (int) (howFar() / cueInitialVelocity()) * timeInterval();
}

char *Engine::infoString(int line, char *out) const
{
	switch (line)
	{
	case 1:
		switch (getState())
		{
		case GAME_ON:
			strcpy(out, "Game On.");
			break;
		case GAME_OVER:
			strcpy(out, "Game Over.");
			break;
		case YOU_WIN:
			strcpy(out, "You Win.");
			break;
		case INITIAL:
			strcpy(out, "Initial Stage.");
			break;
		}
		break;
	case 2:
		if (initial)
			sprintf(out, "");
		else
			sprintf(out, "Current stick power level: %d.", stick.getPower());
		break;
	case 3:
		if (initial)
			sprintf(out, "");
		else
			sprintf(out, "Initial Speed: %.2f.", cueInitialVelocity());
		break;
	case 4:
		if (initial)
			sprintf(out, "Left Click: Put The Eight Ball.");
		else
			sprintf(out, "Distance between tow balls: %.2f.", howFar());
		break;
	case 5:
		if (initial)
			sprintf(out, "Right Click: Default Place.");
		else
			sprintf(out, "Estimated time: %d ms.", estimateHeadOnTime());
		break;
	case 6:
		if (initial)
			sprintf(out, "");
		else
			sprintf(out, "(in case of head on collision)");
		break;
	default:
		sprintf(out, "");
		break;
	}
	return out;
}

bool Engine::setEightBallAt(Point pos)
{
	// insure its the initial state
	if (getState() != INITIAL)
		return false;
	eightBall.putAt(pos);
	eightBall.show();
	initial = false;
	return true;
}

bool Engine::setEightBallAt()
{
	return setEightBallAt(Point(
		table.getRight() - (table.getWidth()/6),
		table.getBottom() + (table.getHeight()/2),
		eightBall.getRadius()
	));
}

int Engine::timeInterval() const
{
	return TIME_INTERVAL;
}

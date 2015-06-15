#include <math.h>
#include <GL/glut.h>
#include "Stick.h"
#include "Color.h"

const double Stick::IMPULSE_FACTOR = 0.04;
const int Stick::POWER_GRADES = 7;
const int Stick::MIN_POWER = 1;
const double Stick::JUMP = 0.05;

Stick::Stick(double length)
	: angle(0), power(MIN_POWER), itsLength(length)
{}

Stick::Stick()
{
	Stick(1.0);
}

void Stick::setAngle(double a)
{
	angle = a;
}

int Stick::shiftPower()
{
	return power = MIN_POWER + power % POWER_GRADES;
}

void Stick::resetPower()
{
	power = MIN_POWER;
}

void Stick::hit(Ball &ball)
{
	ball.applyImpulse(Vector(cos(angle), sin(angle), 0.0) * (power * IMPULSE_FACTOR));
	hide();
}

int Stick::getPower() const
{
	return power;
}

double Stick::getImpulse() const
{
	return power * IMPULSE_FACTOR;
}

double Stick::getAngle() const
{
	return angle;
}

void Stick::render()
{
	if (isVisible())
	{
		GLUquadricObj *qObj;
		qObj = gluNewQuadric();
		//glMaterialfv(GL_FRONT, GL_AMBIENT, Color(Color::WHITE).toArray());
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, Color(Color::WHITE).toArray());
		glColor3f(0.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(getLocation().getX(), getLocation().getY(), getLocation().getZ() + 0.0002);
		glRotatef((180.0 / PI) * angle - 90, 0, 0, 1);
		glTranslatef(0.0, -JUMP * (power + 1), 0.0);
		glRotatef(88, 1, 0, 0);
		gluCylinder(qObj, 0.01, 0.02, itsLength, 16, 16);
		
		
		/*
		glBegin(GL_LINES);
			glVertex2f(-0.01, 0.0);			// left top
			glVertex2f(-0.02, -itsLength);	// left bottom
			glVertex2f(+0.02, -itsLength);	// right bottom
			glVertex2f(+0.01, 0.0);			// right top
		glEnd();
		glBegin(GL_POLYGON);
			//glColor3f(0.0, 0.0, 0.0);
			glVertex2f(+0.01, 0.0);			// right top
			glVertex2f(-0.01, 0.0);			// left top
			//glColor3f(0.5, 0.5, 0.5);
			glVertex2f(-0.02, -itsLength);	// left bottom
			glVertex2f(+0.02, -itsLength);	// right bottom
		glEnd();*/
		glPopMatrix();
	}
}

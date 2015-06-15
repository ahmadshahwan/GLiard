#include <stdio.h>
#include <GL/glut.h>
#include "Ball.h"

Ball::Ball(Point p, double r, double m, Color c):
	PhysicalObject(p),
	radius(r),
	mass(m),
	color(c),
	pocketed(false),
	velocity(0, 0, 0)
{
}

Ball::Ball()
{}

double Ball::getRadius() const
{
	return radius;
}

double Ball::getMass() const
{
	return mass;
}

Vector Ball::getVelocity() const
{
	return velocity;
}

Ball::Color Ball::getColor() const
{
	return color;
}

void Ball::updateLocation()
{
	putAt((Vector) this->getLocation() + velocity);
}

void Ball::applyImpulse(Vector imp)
{
	Vector dVel =  imp / this->mass;
	velocity = (velocity + dVel).nullify();
	dVel = velocity;
}

void Ball::render()
{
	float white[] = {1.0, 1.0, 1.0, 1.0};
	float black[] = {0.0, 0.0, 0.0, 1.0};
	float gray[]  = {0.5, 0.5, 0.5, 1.0};
	float specular[4];
	float shininess;
	glGetMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
	glGetMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	switch (color)
	{
	case WHITE:
		//glMaterialfv(GL_FRONT, GL_AMBIENT, white);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
		glColor3f(1.0, 1.0, 1.0);
		break;
	case BLACK:
		//glMaterialfv(GL_FRONT, GL_AMBIENT, black);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
		glColor3f(0.0, 0.0, 0.0);
		break;
	}
	if (isVisible())
	{
		glPushMatrix();
		glTranslatef(getLocation().getX(), getLocation().getY(), getLocation().getZ());
		glutSolidSphere(radius, 16, 16);
		glPopMatrix();
	}
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

bool Ball::isStatic() const
{
	return velocity.isNull();
}

void Ball::resetAt(Point p)
{
	pocketed = false;
	putAt(p);
	velocity = Vector(0.0, 0.0, 0.0);
	this->show();
}

bool Ball::isPocketed() const
{
	return pocketed;
}

void Ball::pocket()
{
	pocketed = true;
	velocity = Vector(0.0, 0.0, 0.0);
	putAt(Point(POS_ZERO, POS_ZERO, -getRadius()));
	this->hide();
}

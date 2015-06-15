#include <math.h>
#include <GL/glut.h>
#include "Table.h"
#include "Color.h"

const double Table::FRICTION_FACTOR = 0.07;
const double Table::BORDER = 0.1;
const double Table::RADIUS = 0.075;

Table::Table(Point p, double h, double w):
	PhysicalObject(p),
	height(h),
	width(w)
{
	double lft = getLeft();
	double rit = getRight();
	double mdl = (getLeft() + getRight()) / 2;
	double top = getTop();
	double btm = getBottom();
	pocket[0] = Pocket(Point(lft, top, 0.0), RADIUS);
	pocket[1] = Pocket(Point(lft, btm, 0.0), RADIUS);
	pocket[2] = Pocket(Point(mdl, btm, 0.0), RADIUS);
	pocket[3] = Pocket(Point(rit, btm, 0.0), RADIUS);
	pocket[4] = Pocket(Point(rit, top, 0.0), RADIUS);
	pocket[5] = Pocket(Point(mdl, top, 0.0), RADIUS);
	
	/**Pockets Distribution**

	      0-----5-----4
	      |           |
	      |  O     O  |
	      |           |
	      1-----2-----3
	
	*************************/
}

Table::Table()
{
	Table(Point(0, 0, 0), 0, 0);
}

double Table::getHeight()
{
	return height;
}

double Table::getWidth()
{
	return width;
}

double Table::getLeft()
{
	return getLocation().getX();
}

double Table::getRight()
{
	return getLocation().getX() + width;
}

double Table::getTop()
{
	return getLocation().getY() + height;
}

double Table::getBottom()
{
	return getLocation().getY();
}

bool Table::checkBorders(Ball &ball)
{
	if (!ball.isPocketed())	// if ball is not already in hole
		// checks whether the ball in hole, if not (and only if not), checks whether it collides
		return (checkHoles(ball) || checkCollision(ball));
	return false;	// otherwise
}

bool Table::checkHoles(Ball &ball)
{
	for (int i=0; i<6; i++)
		if (pocket[i].draw(ball))
			return true;
	// if non of the pockets draw the ball
	return false;
}

bool Table::checkCollision(Ball &ball)
{
	double impulse = 0;
	if ((ball.getLocation().getX() - ball.getRadius()) < getLeft())
	{
		ball.putAt(Point(getLeft() + ball.getRadius(), ball.getLocation().getY(), ball.getLocation().getZ()));
		impulse = -2 * ball.getMass() * ball.getVelocity().getX();
		ball.applyImpulse(Vector(impulse, 0.0, 0.0));
		return true;
	}
	if ((ball.getLocation().getX() + ball.getRadius()) > getRight())
	{
		ball.putAt(Point(getRight() - ball.getRadius(), ball.getLocation().getY(), ball.getLocation().getZ()));
		impulse = -2 * ball.getMass() * ball.getVelocity().getX();
		ball.applyImpulse(Vector(impulse, 0.0, 0.0));
		return true;
	}
	if ((ball.getLocation().getY() + ball.getRadius()) > getTop())
	{
		ball.putAt(Point(ball.getLocation().getX(), getTop() - ball.getRadius(), ball.getLocation().getZ()));
		impulse = -2 * ball.getMass() * ball.getVelocity().getY();
		ball.applyImpulse(Vector(0.0, impulse, 0.0));
		return true;
	}
	if ((ball.getLocation().getY() - ball.getRadius()) < getBottom())
	{
		ball.putAt(Point(ball.getLocation().getX(), getBottom() + ball.getRadius(), ball.getLocation().getZ()));
		impulse = -2 * ball.getMass() * ball.getVelocity().getY();
		ball.applyImpulse(Vector(0.0, impulse, 0.0));
		return true;
	}
	return false;
}

void Table::applyFriction(Ball &ball)
{
	ball.applyImpulse((ball.getVelocity() * (-1 * FRICTION_FACTOR)) * ball.getMass());
}

void Table::render()
{
	double outerLeft = getLeft() - BORDER;
	double outerRight = getRight() + BORDER;
	double outerTop = getTop() + BORDER;
	double outerBottom = getBottom() - BORDER;
	double innerLeft = getLeft();
	double innerRight = getRight();
	double innerTop = getTop();
	double innerBottom = getBottom();
	float pktPart1Angle[] = {0.0, 90.0, 180.0, 180.0, 270.0, 0.0};
	float pktPart2Angle[] = {180.0, 270.0, 270.0, 0.0, 90.0, 90.0};
	float pktPart3Angle[] = {90.0, 180.0, 0.0, 270.0, 0.0, 0.0 };
	bool pktIsCorner[] = {true, true, false, true, true, false};
	//double clipPlane1[4] = {1.0, 0.0, 0.0, -width/2};
	//double clipPlane2[4] = {-1.0, 0.0, 0.0, -width/2};
	//double clipPlane3[4] = {0.0, 1.0, 0.0, -height/2};
	//double clipPlane4[4] = {0.0, -1.0, 0.0, -height/2};
	//double x, y, z;
	int i, j;
	int fragFactor;		// larger this number is, closer the scene to reality
	GLUquadricObj *qObj = gluNewQuadric();
	
	//glClipPlane(GL_CLIP_PLANE1, clipPlane1);
	//glClipPlane(GL_CLIP_PLANE2, clipPlane2);
	//glClipPlane(GL_CLIP_PLANE3, clipPlane3);
	//glClipPlane(GL_CLIP_PLANE4, clipPlane4);
	

	
	// RENDER BORDERS
	//setting borders color
	glColor3f(0.5, 0.4, 0.2);

	// rendering boundaries
	fragFactor = 8;		// fragment each border into 3 pieces
	glPushMatrix();
		glTranslatef(innerLeft + BORDER, innerTop, 0.0);
		glScalef(width / 2 - 2 * BORDER, BORDER, BORDER);
		glTranslatef(0.5, 0.5, 0.0);
		// fragment the border into smaller pieces to increase lighting effect
		glScalef(1.0 / fragFactor, 1.0, 1.0);
		for (i = 0; i<fragFactor; i++)
		{
			glPushMatrix();
				glTranslatef(-(fragFactor - 1) / 2.0 + 1.0 * i, 0.0, 0.0);
				glutSolidCube(1.0);
			glPopMatrix();
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(innerLeft + (width / 2) + BORDER, innerTop, 0.0);
		glScalef(width / 2 - 2 * BORDER, BORDER, BORDER);
		glTranslatef(0.5, 0.5, 0.0);
		// fragment the border into smaller pieces to increase lighting effect
		glScalef(1.0 / fragFactor, 1.0, 1.0);
		for (i = 0; i<fragFactor; i++)
		{
			glPushMatrix();
				glTranslatef(-(fragFactor - 1) / 2.0 + 1.0 * i, 0.0, 0.0);
				glutSolidCube(1.0);
			glPopMatrix();
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(innerLeft + BORDER, outerBottom, 0.0);
		glScalef(width / 2 - 2 * BORDER, BORDER, BORDER);
		glTranslatef(0.5, 0.5, 0.0);
		// fragment the border into smaller pieces to increase lighting effect
		glScalef(1.0 / fragFactor, 1.0, 1.0);
		for (i = 0; i<fragFactor; i++)
		{
			glPushMatrix();
				glTranslatef(-(fragFactor - 1) / 2.0 + 1.0 * i, 0.0, 0.0);
				glutSolidCube(1.0);
			glPopMatrix();
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(innerLeft + (width / 2) + BORDER, outerBottom, 0.0);
		glScalef(width / 2 - 2 * BORDER, BORDER, BORDER);
		glTranslatef(0.5, 0.5, 0.0);
		// fragment the border into smaller pieces to increase lighting effect
		glScalef(1.0 / fragFactor, 1.0, 1.0);
		for (i = 0; i<fragFactor; i++)
		{
			glPushMatrix();
				glTranslatef(-(fragFactor - 1) / 2.0 + 1.0 * i, 0.0, 0.0);
				glutSolidCube(1.0);
			glPopMatrix();
		}
	glPopMatrix();

	glPushMatrix();
		glTranslatef(outerLeft, innerBottom + BORDER, 0.0);
		glScalef(BORDER, height - 2 * BORDER, BORDER);
		glTranslatef(0.5, 0.5, 0.0);
		// fragment the border into smaller pieces to increase lighting effect
		glScalef(1.0, 1.0 / fragFactor, 1.0);
		for (i = 0; i<fragFactor; i++)
		{
			glPushMatrix();
				glTranslatef(0.0, -(fragFactor - 1) / 2.0 + 1.0 * i, 0.0);
				glutSolidCube(1.0);
			glPopMatrix();
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(innerRight, innerBottom + BORDER, 0.0);
		glScalef(BORDER, height - 2 * BORDER, BORDER);
		glTranslatef(0.5, 0.5, 0.0);
		// fragment the border into smaller pieces to increase lighting effect
		glScalef(1.0, 1.0 / fragFactor, 1.0);
		for (i = 0; i<fragFactor; i++)
		{
			glPushMatrix();
				glTranslatef(0.0, -(fragFactor - 1) / 2.0 + 1.0 * i, 0.0);
				glutSolidCube(1.0);
			glPopMatrix();
		}
	glPopMatrix();

	//Pocket::renderSharpPart(Point(-0.75, +0.50, 0.0), 0.0, BORDER, RADIUS);
	
	// rendering corners

	for (i= 0; i<6; i++)
	{
		glColor3f(0.5, 0.4, 0.2);
		Pocket::renderSharpPart(pocket[i].getLocation(), pktPart1Angle[i], RADIUS, BORDER);
		Pocket::renderSharpPart(pocket[i].getLocation(), pktPart2Angle[i], RADIUS, BORDER);
		if (pktIsCorner[i])
			Pocket::renderCurvePart(pocket[i].getLocation(), pktPart3Angle[i], RADIUS, BORDER);
		glColor3f(0.0, 0.0, 0.0);
		glPushMatrix();
			glTranslatef(pocket[i].getLocation().getX(), pocket[i].getLocation().getY(), pocket[i].getLocation().getZ() + 0.1E-3);
			gluDisk(qObj, 0.0, RADIUS, 16, 16);
		glPopMatrix();
	}


	// RENDER BOARD
	fragFactor = 25;	//fragment the board into 9 pieces
	// fragment the board into smaller pieces to increase lighting effect
	glColor3f(0.0, 0.7, 0.0);
	for (i=0; i<fragFactor; i++)
		for (j=0; j<fragFactor; j++)
		{
			glBegin(GL_POLYGON);
				glVertex3f(innerLeft + j * width / fragFactor, innerBottom + i * height / fragFactor, 0.0);
				glVertex3f(innerLeft + (j + 1) * width / fragFactor, innerBottom + i * height / fragFactor, 0.0);
				glVertex3f(innerLeft + (j + 1) * width / fragFactor, innerBottom + (i + 1) * height / fragFactor, 0.0);
				glVertex3f(innerLeft + j * width / fragFactor, innerBottom + (i + 1) * height / fragFactor, 0.0);
			glEnd();
		}

	// render the white line
	glColor3f(0.7, 1.0, 0.7);
	glBegin(GL_LINES);
		glVertex2f((innerLeft + (getWidth()/6)), innerTop);
		glVertex2f((innerLeft + (getWidth()/6)), innerBottom);
	glEnd();
	glPushMatrix();
	glTranslatef((innerLeft + (getWidth()/6)), innerBottom + (getHeight()/2), 0.0);
	gluDisk(qObj, 0.0, 0.02, 8, 1);
	glPopMatrix();

}

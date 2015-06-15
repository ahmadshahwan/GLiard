#include <GL/glut.h>
#include "Pocket.h"
#include "Color.h"
#include "Table.h"

Pocket::Pocket()
{
	Pocket(Point(0.0, 0.0, 0.0), 0.0);
}

Pocket::Pocket(Point p, double r)
	: PhysicalObject(p), radius(r)
{}

double Pocket::getRadius() const
{
	return radius;
}

bool Pocket::draw(Ball &ball)
{
	Vector dPos = (Vector) this->getLocation() - (Vector) ball.getLocation();
	// if pocket draws the ball
	if (dPos.length() < ball.getRadius() + this->getRadius())
	{
		Vector vFinal = dPos.unit() * 0.02;
		Vector dVel = vFinal - ball.getVelocity();
		ball.applyImpulse(dVel * ball.getMass());
		// if ball is pocketed
		if (dPos.length() < 0.01)
			ball.pocket();
		return true;
	}
	return false;	// otherwise
}

void Pocket::render()
{
	GLUquadricObj *qObj;
	if (isVisible())
	{
		qObj = gluNewQuadric();
		gluQuadricDrawStyle(qObj, GLU_FILL);
		glColor3f (0.1, 0.1, 0.1);
		//glMaterialfv(GL_FRONT, GL_AMBIENT, Color(Color::RED).toArray());
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, Color(Color::RED).toArray());
		glPushMatrix();
		glTranslatef (getLocation().getX(), getLocation().getY(), -Table::BORDER / 2 + POS_ZERO);
		//glutSolidSphere(radius, 16, 16);
		gluCylinder(qObj, radius, radius, Table::BORDER, 16, 16);
		gluDisk(qObj, radius, radius, 16, 16);
		glTranslatef (0.0, 0.0, Table::BORDER);
		gluDisk(qObj, 0.0, radius, 16, 16);
		glPopMatrix();
		gluDeleteQuadric(qObj);
	}
}

void Pocket::renderSharpPart(Point p, double a, double radius, double border)
{
	double clipPlane1[] = {0.0, 1.0, 0.0, 0.0};
	double clipPlane2[] = {1.0, 0.0, 0.0, 0.0};
	double clipPlane3[] = {0.0, -1.0, 0.0, border};
	double clipPlane4[] = {-1.0, 0.0, 0.0, border};
	double clipPlane0[] = { 0.0, 0.0, -1.0, +border/2};
	float specular[4];
	float shininess;
	glGetMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	glGetMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	GLUquadricObj *qObj;
	glPushMatrix();
		glTranslatef(p.getX(), p.getY(), p.getZ());
		glRotatef(a, 0.0, 0.0, 1.0);
		qObj = gluNewQuadric();
		glClipPlane(GL_CLIP_PLANE1, clipPlane1);
		glClipPlane(GL_CLIP_PLANE2, clipPlane2);
		glClipPlane(GL_CLIP_PLANE3, clipPlane3);
		glClipPlane(GL_CLIP_PLANE4, clipPlane4);
		glClipPlane(GL_CLIP_PLANE0, clipPlane0);
		glPushMatrix();
			glEnable(GL_CLIP_PLANE1);
			glEnable(GL_CLIP_PLANE2);
			glTranslatef(0.0, 0.0, -border / 2);
			gluCylinder(qObj, radius, radius, border, 16, 16);
			
			glPushMatrix();
				glTranslatef(0.0, 0.0, border);
				glEnable(GL_CLIP_PLANE0);
				glutSolidCube(2 * border);
				glDisable(GL_CLIP_PLANE0);
			glPopMatrix();

			
			glDisable(GL_CLIP_PLANE1);
			glDisable(GL_CLIP_PLANE2);
		
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 0.0, -border / 2);
			
			glBegin(GL_POLYGON);
				glVertex3f(radius, 0.0, border);
				glVertex3f(radius, 0.0, 0.0);
				glVertex3f(border, 0.0, 0.0);
				glVertex3f(border, 0.0, border);
			glEnd();

			glBegin(GL_POLYGON);
				glVertex3f(0.0, border, border);
				glVertex3f(0.0, border, 0.0);
				glVertex3f(0.0, radius, 0.0);
				glVertex3f(0.0, radius, border);
			glEnd();


			glEnable(GL_CLIP_PLANE1);
			glEnable(GL_CLIP_PLANE2);
			glEnable(GL_CLIP_PLANE3);
			glEnable(GL_CLIP_PLANE4);			

			glTranslatef(0.0, 0.0, border);
			gluDisk(qObj, radius, 2 * border, 16, 16);

			glDisable(GL_CLIP_PLANE1);
			glDisable(GL_CLIP_PLANE2);
			glDisable(GL_CLIP_PLANE3);
			glDisable(GL_CLIP_PLANE4);
		glPopMatrix();
	glPopMatrix();
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void Pocket::renderCurvePart(Point p, double a, double radius, double border)
{
	double clipPlane1[] = {0.0, 1.0, 0.0, 0.0};
	double clipPlane2[] = {1.0, 0.0, 0.0, 0.0};
	//double clipPlane3[] = {0.0, -1.0, 0.0, border};
	//double clipPlane4[] = {-1.0, 0.0, 0.0, border};
	GLUquadricObj *qObj;
	glPushMatrix();
		glTranslatef(p.getX(), p.getY(), p.getZ());
		glRotatef(a, 0.0, 0.0, 1.0);
		qObj = gluNewQuadric();
		glClipPlane(GL_CLIP_PLANE1, clipPlane1);
		glClipPlane(GL_CLIP_PLANE2, clipPlane2);
		//glClipPlane(GL_CLIP_PLANE3, clipPlane3);
		//glClipPlane(GL_CLIP_PLANE4, clipPlane4);
		glEnable(GL_CLIP_PLANE1);
		glEnable(GL_CLIP_PLANE2);
		//glEnable(GL_CLIP_PLANE3);
		//glEnable(GL_CLIP_PLANE4);
		glPushMatrix();
			glTranslatef(0.0, 0.0, -border / 2);
			gluCylinder(qObj, radius, radius, border, 16, 16);
			gluCylinder(qObj, border, border, border, 16, 16);
			glTranslatef(0.0, 0.0, border);
			gluDisk(qObj, radius, border, 16, 16);
		glPopMatrix();
		glDisable(GL_CLIP_PLANE1);
		glDisable(GL_CLIP_PLANE2);
		//glDisable(GL_CLIP_PLANE3);
		//glDisable(GL_CLIP_PLANE4);
	glPopMatrix();
}

	


#include "GLLayer.h"
#include <GL/glut.h>
#include <stdio.h>

const char GLLayer::LAMP1 = 0x1;
const char GLLayer::LAMP2 = 0x2;

GLLayer::GLLayer(Engine *engine)
	: game(engine), lightZ(1.0)
{
}

void GLLayer::renderScene() const
{
	game->getTable().render();
	game->getCue().render();
	game->getEight().render();
	game->getStick().render();
}

void GLLayer::centerViewPoint() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, +1.0, -1.0, +1.0, -2.0, +4.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(
		0.0, 0.0, 2.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);
	glMatrixMode(GL_MODELVIEW);
}

void GLLayer::closeViewPoint(Eye e) const
{
	Point eye = setEye();
	double xX = game->getCue().getLocation().getX();
	double xY = game->getCue().getLocation().getY();
	double xZ = game->getCue().getLocation().getZ();
	double iX = eye.getX() + ((e == GLLayer::LEFT) ? -.5 : +.5);
	double iY = eye.getY();
	double iZ = eye.getZ();
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble) viewport[2] / (GLdouble) viewport[3], 0.25, 4);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(
		iX, iY, iZ,
		xX, xY, xZ,
		0.0, 0.0, 1.0
	);
	glMatrixMode(GL_MODELVIEW);
}

Point GLLayer::setEye() const
{
	Point eye;
	eye.setX(-game->getEight().getLocation().getX());
	eye.setY(-game->getEight().getLocation().getY());
	eye.setZ(0.0);
	eye = ((Vector) eye).unit() * 1.6;
	eye.setZ(0.50);
	return eye;
}

void GLLayer::setViewPoint(Eye e)
{
	glLoadIdentity();
	if (orthographic = game->isStatic())
		centerViewPoint();
	else
		closeViewPoint(e);
}

void GLLayer::initLights() const
{
	float ambient[] = { 1.0, 1.0, 1.0, 0.1 };
	float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float position1[] = { +0.5, 0.0, lightZ, 1.0 };
	float position2[] = { -0.5, 0.0, lightZ, 1.0 };
	float direction[] = { 0.0, 0.0, -1.0 };
	float shininess[] = { 10.0 };
	float constant_attenuation[] = { 1.25 };
	float linear_attenuation[] = { 0.25 };
	float quadratic_attenuation[] = { 0.0 };
	float cutoff[] = { 30.0 };
	//float lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	//float local_view[] = { 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_SHININESS, shininess);
	glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, constant_attenuation);
	glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, linear_attenuation);
	glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);


	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
	glLightfv(GL_LIGHT2, GL_SHININESS, shininess);
	glLightfv(GL_LIGHT2, GL_CONSTANT_ATTENUATION, constant_attenuation);
	glLightfv(GL_LIGHT2, GL_LINEAR_ATTENUATION, linear_attenuation);
	glLightfv(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);

	
	
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
}

void GLLayer::turnOn(char lights) const
{
	if (lights & LAMP1)
		glEnable(GL_LIGHT1);
	if (lights & LAMP2)
		glEnable(GL_LIGHT2);

}

void GLLayer::turnOff(char lights) const
{
	if (lights & LAMP1)
		glDisable(GL_LIGHT1);
	if (lights & LAMP2)
		glDisable(GL_LIGHT2);
}

void GLLayer::lightsUp()
{
	float position1[] = { +0.5, 0.0, lightZ, 1.0 };
	float position2[] = { -0.5, 0.0, lightZ, 1.0 };
	lightZ += 0.5;
	position1[2] += 0.5;
	position2[2] += 0.5;
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
}

void GLLayer::lightsDown()
{
	float position1[] = { +0.5, 0.0, lightZ, 1.0 };
	float position2[] = { -0.5, 0.0, lightZ, 1.0 };
	lightZ -= 0.5;
	position1[2] -= 0.5;
	position2[2] -= 0.5;
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
}

char *GLLayer::infoString(int line, char *out) const
{
	switch (line)
	{
	case 1:
		sprintf(out, (orthographic)  ? "Active Stage." : "Passive Stage.");
		break;
	case 2:
		sprintf(out, "Projection Mode: %s.", (orthographic)  ? "Orthographic" : "Perspective"); 
		break;
	default:
		sprintf(out, "");
		break;
	}
	return out;
}

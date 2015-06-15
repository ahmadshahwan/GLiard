#ifndef GLLAYER_H
#define GLLAYER_H

#include "Engine.h"

class GLLayer
{
public:
	enum Eye
	{
		LEFT,
		RIGHT
	};

	GLLayer(Engine *);

	void setViewPoint(Eye);
	void renderScene() const;
	void initLights() const;
	void turnOn(char) const;
	void turnOff(char) const;
	char *infoString(int, char *) const;
	void lightsUp();
	void lightsDown();

	static const char LAMP1;
	static const char LAMP2;

private:
	Engine *game;
	Point eye;
	double lightZ;
	bool orthographic;

	Point setEye() const;
	void centerViewPoint() const;
	void closeViewPoint(Eye) const;
};

#endif

	

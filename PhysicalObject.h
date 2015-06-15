#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "MathStructs.h"
#include "Shapeable.h"

class PhysicalObject: public Shapeable
{
public:
	// constructors
	PhysicalObject();
	PhysicalObject(Point);

	// getters
	Point getLocation() const;
	bool isVisible() const;

	// non-constant member functions
	void putAt(Point);
	void hide();
	void show();

private:
	Point itsLocation;
	bool visible;
};

#endif

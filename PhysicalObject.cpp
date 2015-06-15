#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(Point p)
	: itsLocation(p), visible(true)
{}

PhysicalObject::PhysicalObject()
	: itsLocation(Point(0, 0, 0)), visible(true)
{}

Point PhysicalObject::getLocation() const
{
	return itsLocation;
}

bool PhysicalObject::isVisible() const
{
	return visible;
}

void PhysicalObject::hide()
{
	visible = false;
}

void PhysicalObject::show()
{
	visible = true;
}

void PhysicalObject::putAt(Point p)
{
	itsLocation = p;
}

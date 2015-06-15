#include <math.h>
#include "MathStructs.h"

Point::Point(double x, double y, double z)
	: itsX(x), itsY(y), itsZ(z)
{}

Point::Point()
{
	Point(0.0, 0.0, 0.0);
}

void Point::setX(double x)
{
	itsX = x;
}

void Point::setY(double y)
{
	itsY = y;
}

void Point::setZ(double z)
{
	itsZ = z;
}

double Point::getX() const
{
	return itsX;
}

double Point::getY() const
{
	return itsY;
}

double Point::getZ() const
{
	return itsZ;
}

Vector::Vector(double x, double y, double z)
	: Point(x, y, z)
{}

Vector::Vector(Point lhs)
	: Point(lhs)
{}

Vector::Vector()
	: Point()
{}

double Vector::length() const
{
	return sqrt(pow(itsX, 2) + pow(itsY, 2) + pow(itsZ, 2));
}

double Vector::inclination2D() const
{
	return atan(getY() / getX()) + ((itsX < 0) ? PI : 0);
}

Vector Vector::add(Vector other) const
{
	double x = this->getX() + other.getX();
	double y = this->getY() + other.getY();
	double z = this->getZ() + other.getZ();
	return (Vector(x, y, z));
}

Vector Vector::sub(Vector other) const
{
	double x = this->getX() - other.getX();
	double y = this->getY() - other.getY();
	double z = this->getZ() - other.getZ();
	return (Vector(x, y, z));
}

Vector Vector::cross(Vector other) const
{
	double x = this->getY() * other.getZ() - other.getY() * this->getZ();
	double y = this->getZ() * other.getX() - other.getZ() * this->getX();
	double z = this->getX() * other.getY() - other.getX() * this->getY();
	return (Vector(x, y, z));
}

double Vector::dot(Vector other) const
{

	return (getX() * other.getX()) + (getY() * other.getY()) + (getZ() * other.getZ());
}

Vector Vector::operator+(Vector other) const
{
	return this->add(other);
}

Vector Vector::operator-(Vector other) const
{
	return this->sub(other);
}

Vector Vector::operator*(double f) const
{
	return Vector(itsX * f, itsY * f, itsZ * f);
}

Vector Vector::operator/(double f) const
{
	return Vector(itsX / f, itsY / f, itsZ / f);
}

Vector Vector::operator+=(Vector other)
{
	*this = *this + other;
	return *this;
}

Vector Vector::operator-=(Vector other)
{
	*this = *this - other;
	return *this;
}


Vector &Vector::nullify()
{
	if (fabs(getX()) < POS_ZERO)
		itsX = 0;
	if (fabs(getY()) < POS_ZERO)
		itsY = 0;
	if (fabs(getZ()) < POS_ZERO)
		itsZ = 0;
	return *this;
}

Vector Vector::unit() const
{
	return (*this / this->length());
}

bool Vector::isNull() const
{
	return (
		(fabs(itsX) < POS_ZERO) &&
		(fabs(itsY) < POS_ZERO) &&
		(fabs(itsZ) < POS_ZERO));
}

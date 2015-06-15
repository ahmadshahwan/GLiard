#ifndef MATHSTRUCTS_H
#define MATHSTRUCTS_H

const double PI = 3.14159265358979323846;		// mathimatical Pi
const double POS_ZERO = +0.1E-2;			// positive zero
const double NEG_ZERO = -0.1E-2;			// negative zero

class Point
{
public:
	// constructors
	Point(double, double, double);
	Point();

	// setters
	virtual void setX(double);
	virtual void setY(double);
	virtual void setZ(double);

	// getters
	virtual double getX() const;
	virtual double getY() const;
	virtual double getZ() const;


protected:
	double itsX;
	double itsY;
	double itsZ;
};


class Vector: public Point
{
public:
	// constructors
	Vector(double, double, double);
	Vector(Point);
	Vector();

	// methods
	// returns the length of the vector
	double length() const;
	// returns inclination angle between vector's projection on x-y plane, and x-axle
	double inclination2D() const;
	// adds two vectors
	Vector add(Vector) const;
	// subtract two vectors
	Vector sub(Vector) const;
	// cross product this vector with another one
	Vector cross(Vector) const;
	// return the unit vector (directive vector)
	Vector unit() const;
	// dot product this vector with another one
	double dot(Vector) const;
	// check whether vector in null or not
	bool isNull() const;
	
	// nullify vector's component when it comes too tinny
	Vector &nullify();

	// operators
	// add operation
	Vector operator+(Vector) const;
	// subtract operation
	Vector operator-(Vector) const;
	// mutiply by a real
	Vector operator*(double) const;
	// divide by a real
	Vector operator/(double) const;

	// increment by
	Vector operator+=(Vector);
	// decrement by
	Vector operator-=(Vector);
};

#endif

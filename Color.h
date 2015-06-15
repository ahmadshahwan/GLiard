#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	Color();
	Color(double, double, double);
	Color(int, int, int);
	Color(int);

	float *toArray() const;

	enum 
	{
		WHITE	= 0,
		BLACK	= 1,
		RED		= 2,
		GREEN	= 3,
		BLUE	= 4
	};

private:
	double r;
	double g;
	double b;
};

#endif

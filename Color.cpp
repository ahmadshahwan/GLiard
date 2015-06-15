#include "Color.h"

Color::Color(double red, double green, double blue)
{
	double *param[] = {&red, &green, &blue};
	for (int i=0; i<3; i++)
	{
		if (*param[i] > 1)
			*param[i] = 1;
		if (*param[i] < 0)
			*param[i] = 0;
	}
	r = red;
	g = green;
	b = blue;
}

Color::Color(int red, int green, int blue)
{
	Color((double) red / 256.0, (double) green / 256.0, (double) green / 256.0);
}

Color::Color(int color)
{
	switch (color)
	{
	case WHITE:
		Color(1.0, 1.0, 1.0);
		break;
	case BLACK:
		Color(0.0, 0.0, 0.0);
		break;
	case RED:
		Color(1.0, 0.0, 0.0);
		break;
	case GREEN:
		Color(0.0, 1.0, 0.0);
		break;
	case BLUE:
		Color(0.0, 0.0, 1.0);
		break;
	default:
		Color();
		break;
	}
}

Color::Color()
{
	Color(0.0, 0.0, 0.0);
}

float *Color::toArray() const
{
	float *result;
	result = new float[4];
	result[0] = (float) r;
	result[1] = (float) g;
	result[2] = (float) b;
	result[3] = 1.0f;
	return &result[0];
}

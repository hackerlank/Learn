#include "Vector.h"
#include "Math.h"

Vector::Vector()
{
	x = y = z = 0.0f;
}

Vector::Vector(const Vector& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

const Vector& Vector::operator=(const Vector& p)
{
	x = p.x;
	y = p.y;
	z = p.z;

	return *this;
}

const Vector& Vector::operator+(const Vector& p)
{
	x = x + p.x;
	y = y + p.y;
	z = z + p.z;

	return *this;
}

const Vector& Vector::operator-(const Vector& p)
{
	x = x - p.x;
	y = y - p.y;
	z = z - p.z;

	return *this;
}

const Vector& Vector::operator*(const float f)
{
	x = x * f;
	y = y * f;
	z = z * f;

	return *this;
}

bool Vector::operator==(const Vector& p) const
{
	bool isEqual = false;

	if(x == p.x && y == p.y && z == p.y)
	{
		isEqual = true;
	}

	return isEqual;
}

bool Vector::operator!=(const Vector& p) const
{
	return ! (*this == p);
}

void Vector::normalize()
{
	float t = x * x + y * y + z * z;
	if(t == 0.0f)
	{
		return;
	}

	t = Math::Q_rsqrt(t);

	x = x * t;
	y = y * t;
	z = z * t;
}
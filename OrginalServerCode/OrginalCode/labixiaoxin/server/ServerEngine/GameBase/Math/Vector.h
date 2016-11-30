#pragma once

class Vector
{
public:
	Vector();
	Vector(const Vector& p);

	const Vector& operator=(const Vector& p);
	const Vector& operator+(const Vector& p);
	const Vector& operator-(const Vector& p);
	const Vector& operator*(const float f);
	bool operator==(const Vector& p) const;
	bool operator!=(const Vector& p) const;

	void normalize();

	float x;
	float y;
	float z;
};
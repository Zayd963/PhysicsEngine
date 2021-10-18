#include "Vector2.h"
#include <math.h>
Vector2::Vector2(float _x, float _y)
	:x(_x), y(_y)
{
}

float Vector2::Mag()
{
	return sqrtf(x * x + y * y);
}

Vector2 Vector2::Normalize()
{
	float r = 1 / Mag();
	return Vector2(x * r, y * r);
}

Vector2 Vector2::operator+(const Vector2 &rhs)
{
	return Vector2(this->x + rhs.x, this->y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
	return Vector2(this->x - rhs.x, this->y - rhs.y);
}

Vector2 Vector2::operator*(const float& rhs)
{
	return Vector2(this->x * rhs, this->y * rhs);
}

Vector2 Vector2::operator/(const float& rhs)
{
	return Vector2(this->x / rhs, this->y / rhs);
}

Vector2 Vector2::operator+=(const Vector2& rhs)
{
	this->x += rhs.x; this->y += rhs.y; return *this;
}

Vector2 Vector2::operator-=(const Vector2& rhs)
{
	this->x -= rhs.x; this->y -= rhs.y; return *this;
}

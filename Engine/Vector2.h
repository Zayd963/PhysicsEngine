#pragma once
class Vector2
{
public:
	Vector2(float _x = 0, float _y = 0);
	
	float Mag();

	Vector2 Normalize();

	Vector2 operator + (const Vector2& rhs);
	Vector2 operator - (const Vector2& rhs);
	Vector2 operator * (const float& rhs);
	Vector2 operator / (const float& rhs);
	Vector2 operator += (const Vector2& rhs);
	Vector2 operator -= (const Vector2& rhs);

public:
	float x;
	float y;


};


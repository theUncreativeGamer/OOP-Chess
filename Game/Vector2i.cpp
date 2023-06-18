#include "Vector2i.h"

Vector2i::Vector2i() : x(0), y(0)
{
}

Vector2i::Vector2i(const int& x, const int& y) : x(x), y(y)
{
}

Vector2i::Vector2i(const Vector2i& rhs) : x(rhs.x), y(rhs.y)
{
}

bool Vector2i::InBounds(const int& width, const int& height)
{
	return x >= 0 && x < width && y >= 0 && y < height;
}

bool Vector2i::InBounds()
{
	return InBounds(8, 8);
}

Vector2i& Vector2i::operator=(const Vector2i& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

bool Vector2i::operator==(const Vector2i& rhs)
{
	return x == rhs.x && y == rhs.y;
}

bool operator==(const Vector2i& lhs, const Vector2i rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Vector2i& lhs, const Vector2i rhs)
{
	if (lhs.x < rhs.x)return true;
	else if (lhs.x > rhs.x) return false;
	else
	{
		if (lhs.y < rhs.y)return true;
		else return false;
	}
}

Vector2i operator+(const Vector2i& lhs, const Vector2i rhs)
{
	Vector2i newVec(lhs);
	newVec.x += rhs.x;
	newVec.y += rhs.y;
	return newVec;
}

Vector2i operator-(const Vector2i& lhs, const Vector2i rhs)
{
	Vector2i newVec(lhs);
	newVec.x += rhs.x;
	newVec.y += rhs.y;
	return newVec;
}

Vector2i operator*(const int& num, const Vector2i vec)
{
	Vector2i newVec(vec);
	newVec.x *= num;
	newVec.y *= num;
	return newVec;
}

Vector2i operator*(const Vector2i& vec, const int num)
{
	Vector2i newVec(vec);
	newVec.x *= num;
	newVec.y *= num;
	return newVec;
}

#pragma once
struct Vector2i
{
	int x;
	int y;

	Vector2i();
	Vector2i(const int& x, const int& y);
	Vector2i(const Vector2i& rhs);

	Vector2i& operator=(const Vector2i& rhs);
	friend Vector2i operator+(const Vector2i& lhs, const Vector2i rhs);
	friend Vector2i operator-(const Vector2i& lhs, const Vector2i rhs);
};

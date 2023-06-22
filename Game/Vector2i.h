#pragma once
#include <string>
struct Vector2i
{
	int x;
	int y;

	Vector2i();
	Vector2i(const int& x, const int& y);
	Vector2i(const Vector2i& rhs);

	bool InBounds(const int& width, const int& height);
	bool InBounds();

	Vector2i& operator=(const Vector2i& rhs);

	bool operator==(const Vector2i& rhs);

	friend bool operator==(const Vector2i& lhs, const Vector2i rhs);

	// Do not use this operator explicitly. This function is only for ordered containers.
	friend bool operator<(const Vector2i& lhs, const Vector2i rhs); 

	friend Vector2i operator+(const Vector2i& lhs, const Vector2i rhs);
	friend Vector2i operator-(const Vector2i& lhs, const Vector2i rhs);

	friend Vector2i operator*(const int& num, const Vector2i vec);
	friend Vector2i operator*(const Vector2i& vec, const int num);

	
};

// Convert a coordinate in the form of alphabet + number into a Vector2i.
Vector2i StringToCoordinate(const std::string& str);
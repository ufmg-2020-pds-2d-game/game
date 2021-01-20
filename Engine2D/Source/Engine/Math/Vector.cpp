#include "Engine\Math\Vector.h"

#include <cmath>

Vector::Vector() {
	x = 0.0f;
	y = 0.0f;
}

Vector::Vector(float a, float b) {
	x = a;
	y = b;
}

Vector::Vector(const Vector & other){
	this->x = other.x;
	this->y = other.y;
}

Vector & Vector::operator=(const Vector & other){
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Vector::~Vector(){

}


Vector Vector::operator+(const Vector& a) {
	return Vector(x + a.x, y + a.y);
}
Vector Vector::operator-(const Vector& a) {
	return Vector(x - a.x, y - a.y);
}
Vector Vector::operator*(const float& a) {
	return Vector(x*a, y*a);
}
Vector Vector::operator/(const float& a) {
	return Vector(x / a, y / a);
}


bool Vector::operator==(const Vector& a) {
	return x == a.x && y == a.y;
}


// Assignment operators
void Vector::operator+=(const Vector& a) {
	x += a.x; y += a.y;
}
void Vector::operator-=(const Vector& a) {
	x -= a.x; y -= a.y;
}
void Vector::operator*=(const float& a) {
	x *= a; y *= a;
}
void Vector::operator/=(const float& a) {
	x /= a; y /= a;
}


float Vector::Length() {
	return sqrt(x*x + y * y);
}

void Vector::Normalize() {
	float l = Length();
	if (l > 0.0f) {
		x /= l;
		y /= l;
	}
}

Vector Vector::Normalized() {
	float l = Length();
	if (l > 0.0f) {
		return Vector(x / l, y / l);
	}
	return Vector(0.0f, 0.0f);
}
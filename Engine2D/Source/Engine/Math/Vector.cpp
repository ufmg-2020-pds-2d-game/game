#include "Engine\Math\Vector.h"

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

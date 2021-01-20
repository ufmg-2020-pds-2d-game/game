#include "Engine/Components/Transform2D.h"

Transform2D::Transform2D() {
	position.x = 250.f;
	position.y = 250.f;

	rotation = 0.f;

	scale.x = 400.f;
	scale.y = 400.f;
}

Transform2D::Transform2D(Vector pos, Vector scl){
	position = pos;
	rotation = 0.f;
	scale = scl;
}

Transform2D::~Transform2D() {

}
#include "Engine/Components/Transform2D.h"

Transform2D::Transform2D() {
	position.x = 50.f;
	position.y = 50.f;

	rotation = 0.f;

	scale.x = 100.f;
	scale.y = 100.f;
}

Transform2D::~Transform2D() {

}
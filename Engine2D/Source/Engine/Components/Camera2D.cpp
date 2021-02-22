#include "Engine/Components/Camera2D.h"

#include "Engine.h"

Camera2D::Camera2D() {
	zoom = 1.f;
}

Camera2D::~Camera2D() {

}

Vector Camera2D::GetPosition(){
	auto t = GetEntity()->Get<Transform2D>();
	if (t) {
		return t->position;
	}
	return Vector(0.f, 0.f);
}

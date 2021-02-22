#include "Engine/Components/Camera2D.h"

#include "Engine.h"

Camera2D::Camera2D(Vector camOffset) {
	zoom = 1.f;
	offset = camOffset;
}

Camera2D::~Camera2D() {

}

Vector Camera2D::GetPosition(){
	Vector pos;

	auto t = GetEntity()->Get<Transform2D>();
	if (t) {
		pos = t->position;
	}
	pos -= offset;

	return pos * (-1);
}

void Camera2D::Update(){
	App* app = GetApp();

	app->camera.position = GetPosition();
	app->camera.zoom = zoom;
}

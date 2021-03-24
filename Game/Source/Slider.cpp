#include "Slider.h"

#include "Engine.h"

Slider::Slider(bool offsetY, float velocity) {
	speed = velocity;
	m_offsetY = offsetY;
}

Slider::~Slider() {

}

void Slider::Update() {
	Transform2D* t = GetEntity()->Get<Transform2D>();

	t->position.x -= speed * gs_platform_delta_time();

	if (t->position.x + t->scale.x < 0.f) {
		t->position.x += 100.f * NUM_COLUMNS;
		if (m_offsetY) {
			int r = std::rand() % 7;
			if (r == 0) {
				t->position.y = SLIDER_START_Y + 500.f;
			}
			else {
				t->position.y = SLIDER_START_Y - 100.f * r;
			}
		}
	}

	App* app = GetApp();
}
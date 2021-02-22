#include "Engine/Components/PlayerComponent.h"

#include "Engine.h"

PlayerComponent::PlayerComponent() {
	speed = 16.f;
	m_jumpForce = 0.f;
}

PlayerComponent::~PlayerComponent() {

}

void PlayerComponent::Update() {
	Transform2D* t = GetEntity()->Get<Transform2D>();
	
	if (gs_platform_key_down(GS_KEYCODE_A)) {
		t->position.x -= speed;
		t->scale.x = -std::abs(t->scale.x);
	}
	else if (gs_platform_key_down(GS_KEYCODE_D)) {
		t->position.x += speed;
		t->scale.x = std::abs(t->scale.x);
	}

	t->rotation = std::sin(t->position.x * 0.02f) * 0.16f;

	if (gs_platform_key_pressed(GS_KEYCODE_SPACE) || gs_platform_key_pressed(GS_KEYCODE_W)) {
		PlayAudio("jump_s");
		m_jumpForce = 50.f;
	}
	if (m_jumpForce > 0) {
		t->position.y -= m_jumpForce;
		m_jumpForce -= 5.f;
	}
}
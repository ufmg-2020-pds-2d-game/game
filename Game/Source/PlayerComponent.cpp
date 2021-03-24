#include "PlayerComponent.h"

#include <iostream>

#include "Engine.h"
#include "Slider.h"


PlayerComponent::PlayerComponent() {
	m_jumpForce = 0.f;
}

PlayerComponent::~PlayerComponent() {

}

void PlayerComponent::Update() {
	static bool flag = false;
	if (!flag) {
		flag = true;

		PlayAudio("music");
	}
	Transform2D* t = GetEntity()->Get<Transform2D>();
	
	t->position.x = 200.f;
	t->rotation = std::sin(gs_platform_elapsed_time() * 0.02f) * 0.16f;

	if (gs_platform_key_pressed(GS_KEYCODE_SPACE) || gs_platform_key_pressed(GS_KEYCODE_W)) {
		PlayAudio("jump_s");
		m_jumpForce = 60.f;
	}
	if (m_jumpForce > 0) {
		t->position.y -= m_jumpForce;
		m_jumpForce -= 450.f * gs_platform_delta_time();
	}

	SpawnCoins();
}

void PlayerComponent::SpawnCoins() {
	static int timer = 0;
	timer += 1;
}
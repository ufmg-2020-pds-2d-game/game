#include "PlayerComponent.h"

#include <iostream>

#include "Engine.h"

#include "Slider.h"
#include "Tag.h"


PlayerComponent::PlayerComponent() {
	m_score = 0;
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

	RigidBody2D* body = GetEntity()->Get<RigidBody2D>();
	if (body) {
		if (body->lastCollision) {
			auto tag = body->lastCollision->Get<Tag>();
			if (tag) {
				if (tag->name == "coin") {
					m_score += 1;
					auto t = body->lastCollision->Get<Transform2D>();
					if (t) {
						// Forçando a moeda a se regenerar
						t->position.x = -300.f;
					}
				}
				else if (tag->name == "zombie") {
					m_score -= 1;
					auto t = body->lastCollision->Get<Transform2D>();
					if (t) {
						// Forçando o zombi a se regenerar
						t->position.x = -300.f;
					}
				}
			}
		}
	}

	auto text = GetEntity()->Get<Text>();
	if (text) {
		text->text = "Score: " + std::to_string(m_score);
	}
}

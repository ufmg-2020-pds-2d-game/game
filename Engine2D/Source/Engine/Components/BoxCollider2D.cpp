#include "Engine/Components/BoxCollider2D.h"

#include "Engine/Engine.h"

BoxCollider2D::BoxCollider2D() {

}

BoxCollider2D::~BoxCollider2D() {

}

gs_aabb_t BoxCollider2D::GetBoundingBox(){
	gs_aabb_t b;
	b.min = { 0.f, 0.f };
	b.max = { 1.f, 1.f };

	if (GetEntity() == nullptr) {
		return b;
	}
	Transform2D* transform = GetEntity()->Get<Transform2D>();

	if (transform) {
		b.min = { transform->position.x, transform->position.y };
		b.max = { transform->position.x, transform->position.y };
		b.min.x -= std::abs(transform->scale.x) * 0.5f;
		b.min.y -= std::abs(transform->scale.y) * 0.5f;
		b.max.x += std::abs(transform->scale.x) * 0.5f;
		b.max.y += std::abs(transform->scale.y) * 0.5f;
	}

	return b;
}

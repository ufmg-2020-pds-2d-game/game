#include "Engine/Entity.h"

#include "Engine/App.h"
#include "Engine/Component.h"

#include "Engine.h"

Entity::Entity() {
	m_started = false;
}

Entity::~Entity() {
	for (auto c : m_components) {
		delete c;
	}
	m_components.clear();
}

void Entity::Start(){
	m_started = true;
	for (auto c : m_components) {
		c->Start();
	}
}

void Entity::Update(){
	for (auto c : m_components) {
		c->Update();
	}
}

void Entity::End(){
	for (auto c : m_components) {
		c->End();
	}
	m_started = false;
}

Entity * Entity::Factory(const std::string& image, FactoryType t){
	Entity* ent = new Entity();

	ent->Add(new Transform2D({ 0.f, 0.f }, {100.f, 100.f}));
	if (image != "") {
		ent->Add(new Image2D(image));
	}

	if (t != Entity::NO_COLLISION) {
		ent->Add(new BoxCollider2D());
	}
	if (t == Entity::DYNAMIC) {
		ent->Add(new RigidBody2D());
	}

	return ent;
}

Component * Entity::Add(Component * c){
	m_components.push_back(c);

	c->SetEntity(this);

	if (m_started) {
		c->Start();
	}
	return c;
}

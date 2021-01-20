#include "Entity.h"

#include "Engine/App.h"
#include "Component.h"

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

Component * Entity::Add(Component * c){
	m_components.push_back(c);

	c->SetEntity(this);

	if (m_started) {
		c->Start();
	}
	return c;
}

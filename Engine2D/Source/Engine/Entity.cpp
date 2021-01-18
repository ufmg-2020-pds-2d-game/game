#include "Entity.h"

#include "Engine/App.h"

Entity::Entity() {
	position.x = 50.f;
	position.y = 50.f;

	scale.x = 100.f;
	scale.y = 100.f;
}

Entity::~Entity() {

}

void Entity::Start(){

}

void Entity::Update(){

}

void Entity::Draw(App * app){

}

void Entity::AddComponent(Component * c){
	m_components.push_back(c);
}

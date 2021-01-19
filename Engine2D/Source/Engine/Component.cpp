#include "Component.h"

#include <iostream>

Component::Component(){
	m_entity = nullptr;
}

Component::~Component(){

}

void Component::Start(){
	std::cout << "Component: Start\n";
}

void Component::Update(){
	std::cout << "Component: Update\n";
}

Entity * Component::GetEntity(){
	return m_entity;
}

void Component::SetEntity(Entity* e){
	m_entity = e;
}

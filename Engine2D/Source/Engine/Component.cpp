#include "Engine/Component.h"

#include <iostream>

Component::Component(){
	m_entity = nullptr;
}

Component::~Component(){

}

void Component::Start(){
	
}

void Component::Update(){
	
}

void Component::End(){
	
}

Entity * Component::GetEntity(){
	return m_entity;
}

void Component::SetEntity(Entity* e){
	m_entity = e;
}

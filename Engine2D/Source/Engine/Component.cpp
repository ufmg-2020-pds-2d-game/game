#include "Component.h"

Component::Component(){
	m_entity = nullptr;
}

Component::~Component(){

}

void Component::Start(){

}

void Component::Update(){

}

Entity * Component::GetEntity(){
	return m_entity;
}

void Component::SetEntity(Entity* e){
	m_entity = e;
}

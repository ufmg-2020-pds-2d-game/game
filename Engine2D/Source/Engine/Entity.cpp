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
	auto renderer = app->GetRenderer();
	SDL_Rect rect;

	rect.x = position.x;
	rect.y = position.y;
	rect.w = scale.x;
	rect.h = scale.y;

	//SDL_RenderCopy(renderer, app->textures["food"], NULL, &rect);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

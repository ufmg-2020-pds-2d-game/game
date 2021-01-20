#include "Engine/Engine.h"

int main(int argc, char *argv[]) {
	App app;

	app.LoadTexture("food", "./Data/food.png");

	Entity* a = new Entity();

	a->Add(new Transform2D());
	a->Add(new Image2D("food"));

	a->Add(new BoxCollider2D());
	a->Add(new RigidBody2D());

	app.AddEntity(a);

	app.Run();

	return 0;
}
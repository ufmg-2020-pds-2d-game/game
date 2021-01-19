#include "Engine/App.h"
#include "Engine/Entity.h"
#include "Engine/Component.h"

int main(int argc, char *argv[]) {
	App app;

	//app.LoadTexture("food", "Data\\food.png");

	Entity* a = new Entity();
	a->Add(new Component());

	app.AddEntity(a);

	app.Run();

	return 0;
}
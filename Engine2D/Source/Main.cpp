#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine\App.h"
#include "Engine\Entity.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char *argv[]) {
	App app;

	app.LoadTexture("food", "Data\\food.png");

	Entity* a = new Entity();
	app.AddEntity(a);

	app.GameLoop();

	return 0;
}
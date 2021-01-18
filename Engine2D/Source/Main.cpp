/*#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine\App.h"
#include "Engine\Entity.h"

#define WIDTH 800
#define HEIGHT 600*/

#define GS_IMPL
#define GS_NO_HIJACK_MAIN

#include <Gunslinger/gs.h>


void update()
{
	if (gs_platform_key_pressed(GS_KEYCODE_ESC)) gs_engine_quit();
}

/*gs_app_desc_t gs_main(int32_t argc, char** argv){
	gs_app_desc_t app = {};
	app.update = update;
	return app;
}*/

int main(int argc, char *argv[]) {
	gs_app_desc_t app = { 0 };
	app.update = update;
	gs_engine_create(app)->run();  

	return 0;
}

/*int main(int argc, char *argv[]) {
	App app;

	app.LoadTexture("food", "Data\\food.png");

	Entity* a = new Entity();
	app.AddEntity(a);

	app.GameLoop();

	return res;
}*/
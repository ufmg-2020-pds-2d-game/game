/*#define GS_IMPL
#define GS_NO_HIJACK_MAIN
#include <Gunslinger/gs.h>*/

#include "Engine\App.h"
#include "Engine\Entity.h"

int main(int argc, char *argv[]) {
	App app;

	//app.LoadTexture("food", "Data\\food.png");

	Entity* a = new Entity();
	app.AddEntity(a);

	app.Run();

	return 0;
}
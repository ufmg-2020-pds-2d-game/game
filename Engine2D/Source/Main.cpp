#include <ctime>

#include "Engine/Engine.h"

int main(int argc, char *argv[]) {
	App app;

	std::srand(std::time(nullptr));

	// Carregando as texturas...
	app.LoadTexture("c_red", "./Data/character_roundRed.png");
	app.LoadTexture("c_purple", "./Data/character_squarePurple.png");	

	app.LoadTexture("tile", "./Data/tile.png");
	app.LoadTexture("tile_brick", "./Data/tile_brick.png");
	app.LoadTexture("tile_block", "./Data/tile_block.png");

	app.LoadTexture("cloud_a", "./Data/background_cloudA.png");
	app.LoadTexture("tree_a", "./Data/background_treeLarge.png");

	// Carregando sons...
	app.LoadAudio("jump_s", "./Data/sfx_movement_jump1.wav");

	// Adicionando uma nuvem...
	{
		Entity* a = new Entity();
		a->Add(new Transform2D({ 260.f, 170.f }, { 350.f, -175.f }));
		a->Add(new Image2D("cloud_a"));
		app.AddEntity(a);
	}
	// Adicionando uma arvore...
	{
		Entity* a = new Entity();
		a->Add(new Transform2D({ 650.f, 400.f }, { 200.f, -400.f }));
		a->Add(new Image2D("tree_a"));
		app.AddEntity(a);
	}
	// Adicionando uma Entidade para o Jogador...
	for (int i=0; i<3; i++){ 
		Entity* a = new Entity();

		a->Add(new Transform2D({ 200.f + 200.f * i, 200.f - 50.f * i }, {100.f, -100.f}));
		a->Add(new Image2D(i == 0 ? "c_red" : "c_purple"));

		a->Add(new BoxCollider2D());
		a->Add(new RigidBody2D());

		if (i == 0) {
			a->Add(new PlayerComponent());
		}

		app.AddEntity(a);
	}
	/// Adicionando Entidades para o Chão...
	for (int i=0; i<10; i++) {
		for (int j = 0; j < 3; j++) {
			if (j > 0 && std::rand() % 100 < 60) {
				break;
			}
			Entity* a = new Entity();

			a->Add(new Transform2D({ 100.f * i, 600.f - 100.f * j}, { 100.f, 100.f }));
			std::vector<std::string> names = { "tile", "tile_brick", "tile_block" };
			a->Add(new Image2D(names[std::rand() % 3]));

			a->Add(new BoxCollider2D());

			app.AddEntity(a);
		}
	}

	app.Run();

	return 0;
}
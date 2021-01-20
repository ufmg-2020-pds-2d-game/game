#include "Engine/Engine.h"

int main(int argc, char *argv[]) {
	App app;

	// Carregando as texturas...
	app.LoadTexture("c_red", "./Data/character_roundRed.png");

	app.LoadTexture("tile", "./Data/tile.png");
	app.LoadTexture("tile_brick", "./Data/tile_brick.png");
	app.LoadTexture("tile_block", "./Data/tile_block.png");

	app.LoadTexture("cloud_a", "./Data/background_cloudA.png");
	app.LoadTexture("tree_a", "./Data/background_treeLarge.png");

	// Adicionando uma nuvem...
	{
		Entity* a = new Entity();
		a->Add(new Transform2D({ 380.f, 70.f }, { 700.f, -350.f }));
		a->Add(new Image2D("cloud_a"));
		app.AddEntity(a);
	}
	// Adicionando uma arvore...
	{
		Entity* a = new Entity();
		a->Add(new Transform2D({ 680.f, 220.f }, { 300.f, -600.f }));
		a->Add(new Image2D("tree_a"));
		app.AddEntity(a);
	}
	// Adicionando uma Entidade para o Jogador...
	for (int i=0; i<3; i++){ 
		Entity* a = new Entity();

		a->Add(new Transform2D({ 200.f + 200.f * i, 200.f - 50.f * i }, {200.f, -200.f}));
		a->Add(new Image2D("c_red"));

		a->Add(new BoxCollider2D());
		a->Add(new RigidBody2D());

		app.AddEntity(a);
	}
	/// Adicionando Entidades para o Chão...
	for (int i=1; i<=10; i++) {
		Entity* a = new Entity();

		a->Add(new Transform2D({ 100.f * i, 600.f }, {200.f, 200.f}));
		std::vector<std::string> names = { "tile", "tile_brick", "tile_block" };
		a->Add(new Image2D(names[std::rand()%3]));

		a->Add(new BoxCollider2D());

		app.AddEntity(a);
	}

	app.Run();

	return 0;
}
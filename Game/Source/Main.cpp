#include <ctime>
#include <iostream>

#include "Engine.h"

#include "Slider.h"
#include "PlayerComponent.h"


int main(int argc, char *argv[]) {
	App app;

	std::srand(std::time(nullptr));
	
	// Carregando as texturas...
	app.LoadTexture("player", "./Data/char/char1.png");
	app.LoadTexture("zombie", "./Data/char/char2.png");

	app.LoadTexture("tile1", "./Data/map/tile1.png");
	app.LoadTexture("tile2", "./Data/map/tile2.png");
	app.LoadTexture("tile3", "./Data/map/tile3.png");
	app.LoadTexture("tile4", "./Data/map/tile4.png");

	app.LoadTexture("roof1", "./Data/map/tile5.png");
	app.LoadTexture("roof2", "./Data/map/tile6.png");

	app.LoadTexture("tree1", "./Data/map/tree1.png");
	app.LoadTexture("tree2", "./Data/map/tree2.png");

	app.LoadTexture("coin",		"./Data/char/coin.png");
	app.LoadTexture("coinRed",	"./Data/char/coinRed.png");

	app.LoadTexture("cloud_a", "./Data/map/cloud.png");

	// Carregando sons...
	app.LoadAudio("jump_s", "./Data/audio/sfx_movement_jump1.wav");
	app.LoadAudio("music",  "./Data/audio/Through the Portal.ogg");

	PlayAudio("music", 0.5f);

	// Camera
	app.camera.position = { 0.f, 40.f };
	app.camera.zoom = 0.9f;

	// Adicionando uma nuvem...
	for (int i = 0; i < 2; i++) {
		Entity* a = new Entity();
		a->Add(new Transform2D({ 260.f + 800.f * i, 170.f }, { 350.f, 175.f }));
		a->Add(new Image2D("cloud_a"));
		a->Add(new Slider(false, 100.f));
		app.AddEntity(a);
	}
	// Adicionando uma arvore...
	for (int i = 0; i < 2; i++) {
		Entity* a = new Entity();
		a->Add(new Transform2D({ 650.f + 1200.f * i, 450.f }, { 200.f, 400.f }));
		//a->Add(new Image2D("tree_a"));
		std::vector<std::string> names = { "tree1", "tree2" };
		a->Add(new Image2D(names[std::rand() % 2]));
		a->Add(new Slider(false, 100.f));
		app.AddEntity(a);
	}
	// Adicionando uma Entidade para o Jogador...
	for (int i = 0; i < 3; i++) {
		Entity* a = new Entity();

		a->Add(new Transform2D({ 200.f + 200.f * i, 200.f - 50.f * i }, { 100.f, 100.f }));
		a->Add(new Image2D(i == 0 ? "player" : "zombie"));

		a->Add(new BoxCollider2D(0.7f, 1.f));
		a->Add(new RigidBody2D());

		if (i == 0) {
			a->Add(new PlayerComponent());
			//a->Add(new Camera2D(Vector(400.f, 300.f)));

			auto text = new Text();

			text->position = { 50.f, 50.f };
			text->text = "Testing...";

			a->Add(text);
		}

		app.AddEntity(a);
	}
	/// Adicionando Entidades para o Chão...
	for (int i = -10; i < NUM_COLUMNS; i++) {
		for (int j = 0; j < 2; j++) {
			if (j > 0 && std::rand() % 100 < 70) {
				break;
			}
			Entity* a = new Entity();

			a->Add(new Transform2D({ 100.f * i, SLIDER_START_Y - 100.f * j }, { 100.f, 100.f }));
			std::vector<std::string> names = { "tile1", "tile2", "tile3", "tile4" };
			a->Add(new Image2D(names[std::rand() % 4]));
			a->Add(new Slider(j > 0));

			a->Add(new BoxCollider2D());

			app.AddEntity(a);
		}
		// E teto...
		{
			Entity* a = new Entity();

			a->Add(new Transform2D({ 100.f * i, 0.f }, { 100.f, 100.f }));
			std::vector<std::string> names = { "roof1", "roof2" };
			a->Add(new Image2D(names[std::rand() % 2]));
			a->Add(new Slider());

			a->Add(new BoxCollider2D());

			app.AddEntity(a);
		}
	}

	// As Moedas...
	for (int i = 0; i < 5; i++) {
		if (std::rand() % 100 < 60) {
			Entity* a = new Entity();

			a->Add(new Transform2D(
				{ 300.f + 300.f * i, 100.f + 50.f * (std::rand() % 10) },
				{ 300.f, 300.f }
			));
			a->Add(new Image2D("coin"));
			a->Add(new BoxCollider2D(0.2f, 0.2f));
			a->Add(new Slider(true));

			app.AddEntity(a);
		}
	}

	app.Run();
	return 0;
}
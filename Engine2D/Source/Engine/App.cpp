#include "Engine\App.h"

#include <iostream>

App::App() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw std::exception("Failed to Initialized SDL!");
	}

	m_window = SDL_CreateWindow("Game", 
		50, 
		50, 
		640, 480, 
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
	);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

}

App::~App() {
	for (auto text : textures) {
		SDL_DestroyTexture(text.second);
	}
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void App::LoadTexture(std::string name, std::string path) {
	int w, h;

	std::string texturePath = SDL_GetBasePath() + path;
	std::cout << "Texture: " << texturePath << "\n";

	textures[name] = IMG_LoadTexture(m_renderer, texturePath.c_str());
	SDL_QueryTexture(textures[name], NULL, NULL, &w, &h);
}

void App::GameLoop() {
	for (auto e : m_entities) {
		e->Start();
	}

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}

		for (auto e : m_entities) {
			e->Update();
		}
		
		//----------

		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		SDL_RenderClear(m_renderer);
		for (auto e : m_entities) {
			e->Draw(this);
		}

		SDL_RenderPresent(m_renderer);

	}
}

SDL_Renderer* App::GetRenderer() {
	return m_renderer;
}

void App::AddEntity(Entity* e) {
	m_entities.emplace_back(e);
}
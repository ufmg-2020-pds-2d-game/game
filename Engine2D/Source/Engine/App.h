#ifndef ENGINE_APP_H
#define ENGINE_APP_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.h"

class App {
public:
	App();
	virtual ~App();

	void GameLoop();

	void LoadTexture(std::string name, std::string path);

	std::unordered_map<std::string, SDL_Texture*> textures;

	SDL_Renderer* GetRenderer();

	void AddEntity(Entity* e);

private:
	std::vector<Entity*> m_entities;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};

#endif // !ENGINE_APP_H 
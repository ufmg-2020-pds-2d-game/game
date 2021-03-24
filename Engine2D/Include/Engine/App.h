#ifndef ENGINE_APP_H
#define ENGINE_APP_H

#include <unordered_map>
#include <vector>
#include <string>

#include <Gunslinger/gs.h>
#include <Gunslinger/util/gs_idraw.h>
#include <Gunslinger/util/gs_asset.h>

#include "Entity.h"

class Camera2D;

// Essa função vai chamar o PlaySound to App ativo.
void PlayAudio(const std::string& name, float volume = 1.0f);

// Retorna a instância principal do App
App* GetApp();

class App {
public:
	App();
	virtual ~App();

	virtual void Start();
	virtual void Update();
	virtual void End();

	void Run();
	
	gs_app_desc_t GetAppDesc() {
		return m_app;
	}
	
	void LoadTexture(const std::string& name, const std::string& path);
	void LoadAudio(const std::string& name, const std::string& path);

	void PlayAudio(const std::string& name, float volume = 1.0f);

	void AddEntity(Entity* e);

	float gravity;
	bool drawDebugAABB;

	struct {
		Vector position;
		float zoom;
		float rotation;
	} camera;
	bool forceQuit; // Used for unit testing!
protected:
	void UpdatePhysics();
	void Draw();
private:
	bool m_isRunning;

	std::vector<Entity*> m_entities;

	gs_engine_t* m_engine;
	gs_app_desc_t m_app;
	gs_command_buffer_t m_gcb; // Used for submitting rendering commands to graphics backend
	gs_immediate_draw_t m_gsi; // Immediate draw utility context
	//gs_asset_manager_t m_gsa;  // Asset manager for storing textures

	// Name -> Asset Handle lookup:
	//std::unordered_map<std::string, gs_asset_t> m_assetTable; 

	//
	std::unordered_map<std::string, gs_asset_texture_t> m_textures;
	std::unordered_map<std::string, gs_asset_audio_t> m_audios;
};

#endif // !ENGINE_APP_H 
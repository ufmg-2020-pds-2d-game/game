#define GS_IMPL
#define GS_NO_HIJACK_MAIN
#include <Gunslinger/gs.h>

#define GS_IMMEDIATE_DRAW_IMPL
#include <Gunslinger/util/gs_idraw.h>

#define GS_ASSET_IMPL
#include <Gunslinger/util/gs_asset.h>

#include "Engine/App.h"

#include <iostream>

#include "Engine/Engine.h"


static void AppInit(){
	App* app = gs_engine_user_data(App);
	//app->InitInternals();
	app->Start();
}

static void AppUpdate(){
	App* app = gs_engine_user_data(App);
	app->Update();
}

static void AppShutdown(){
	App* app = gs_engine_user_data(App);
	app->End();
}


App::App() {
	m_isRunning = false;

	m_app = { 0 };
	m_app.window_title = "Game";

	// Já que o Gunslinger é um framework em C, ele não aceita 
	// ponteiros para funções pertencentes a classes (métodos). 
	// Então essas três funções internas e estáticas foram criados 
	// como alternativa.
	m_app.init = AppInit;
	m_app.update = AppUpdate;
	m_app.shutdown = AppShutdown;
	m_app.user_data = (void*)this;

	m_engine = gs_engine_create(m_app);

	m_gcb = gs_command_buffer_new();
	m_gsi = gs_immediate_draw_new();
	m_gsa = gs_asset_manager_new();
}

App::~App() {
	for (auto e : m_entities) {
		delete e;
	}
	m_entities.clear();
	m_assetTable.clear();
}

void App::Start(){
	for (auto e : m_entities) {
		e->Start();
	}
}

void App::Update(){
	if (gs_platform_key_pressed(GS_KEYCODE_ESC)) {
		gs_engine_quit();
	}

	for (auto e : m_entities) {
		e->Update();
	}

	Draw();
}

void App::End(){

}


void App::Run() {
	m_isRunning = true;
	m_engine->run();
	//gs_engine_create(m_app)->run();
}

void App::LoadTexture(const std::string& name, const std::string& path) {
	// Essa struct descreve o formato interno da textura para ser desenhada
	// na tela. É necessário para trocar o filtro e impedir que as imagens
	// em pixel art fiquem embaçadas.
	gs_graphics_texture_desc_t desc = {};
	desc.format = GS_GRAPHICS_TEXTURE_FORMAT_RGBA8;
	desc.min_filter = GS_GRAPHICS_TEXTURE_FILTER_NEAREST;
	desc.mag_filter = GS_GRAPHICS_TEXTURE_FILTER_NEAREST;

	m_assetTable[name] = gs_assets_load_from_file(&m_gsa, gs_asset_texture_t, path.c_str(), &desc);
}

void App::AddEntity(Entity* e) {
	m_entities.emplace_back(e);

	if (m_isRunning) {
		e->Start();
	}
}

void App::Draw(){

}

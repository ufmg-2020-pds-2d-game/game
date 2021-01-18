#define GS_IMPL
#define GS_NO_HIJACK_MAIN
#include <Gunslinger/gs.h>

#define GS_IMMEDIATE_DRAW_IMPL
#include <Gunslinger/util/gs_idraw.h>

#define GS_ASSET_IMPL
#include <Gunslinger/util/gs_asset.h>

#include "Engine\App.h"

#include <iostream>

static void AppInit(){
	App* app = gs_engine_user_data(App);
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
}

App::~App() {

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
}

void App::End(){

}


void App::Run() {
	m_isRunning = true;
	gs_engine_create(m_app)->run();
}

void App::InitInternals(){
	m_gcb = gs_command_buffer_new();
	m_gsi = gs_immediate_draw_new();
	m_gsa = gs_asset_manager_new();
}

void App::LoadTexture(const std::string& name, const std::string& path) {

}

void App::AddEntity(Entity* e) {
	m_entities.emplace_back(e);

	if (m_isRunning) {
		e->Start();
	}
}
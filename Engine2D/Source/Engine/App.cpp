#define GS_IMPL
#define GS_NO_HIJACK_MAIN
#include <Gunslinger/gs.h>

#define GS_IMMEDIATE_DRAW_IMPL
#include <Gunslinger/util/gs_idraw.h>

#define GS_ASSET_IMPL
#include <Gunslinger/util/gs_asset.h>

#include "Engine/App.h"

#include <iostream>

#include "Engine.h"


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

//---------------------------------------------------------------------------//

void PlayAudio(const std::string& name, float volume) {
	App* app = gs_engine_user_data(App);

	app->PlayAudio(name, volume);
}

//---------------------------------------------------------------------------//

App::App() {
	gravity = 9.8f;
	drawDebugAABB = false;

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

	UpdatePhysics();
	Draw();
}

void App::End(){
	for (auto e : m_entities) {
		e->End();
	}
}


void App::Run() {
	m_isRunning = true;
	m_engine->run();
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

void App::LoadAudio(const std::string & name, const std::string & path){
	m_assetTable[name] = gs_assets_load_from_file(&m_gsa, gs_asset_audio_t, path.c_str());
}

void App::PlayAudio(const std::string & name, float volume){
	gs_asset_audio_t* ap = gs_assets_getp(&m_gsa, gs_asset_audio_t, m_assetTable[name]);

	gs_audio_play_source(ap->hndl, volume);
}

void App::AddEntity(Entity* e) {
	m_entities.emplace_back(e);

	if (m_isRunning) {
		e->Start();
	}
}

void App::UpdatePhysics(){
	// Esse método vai iterar sobre todas as entidades e:
	// 1 - Se houver um RigidBody2D, aplicar a gravidade no Transform2D
	// 2 - Se também houver um BoxCollider2D, irá iterar sobre todas as
	// outras entidades para detectar e resolver colisões.
	// Complexidade no pior caso: O(n²).

	for (auto e : m_entities) {
		Transform2D* transform = e->Get<Transform2D>();
		RigidBody2D* body = e->Get<RigidBody2D>();

		if (transform && body) {
			transform->position.y += gravity;

			BoxCollider2D* collider = e->Get<BoxCollider2D>();
			if (collider == nullptr) {
				continue;
			}

			// Tratar a colisão com as outras entidades:
			for (auto other : m_entities) {
				// Não tratar colisão contra a propria entidade...
				if (other == e) { continue; }

				Transform2D* otherT = other->Get<Transform2D>();
				BoxCollider2D* otherB = other->Get<BoxCollider2D>();

				if (otherT && otherB) {
					gs_aabb_t a = collider->GetBoundingBox();
					gs_aabb_t b = otherB->GetBoundingBox();

					// Algoritmo de detecção e colisão 
					// Axis-Aligned Bounding Box + resolução da colisão
					// com o algoritmo Minimum Translation Vector.
					// (Ambos fornecidos pelo framework gunslinger)

					if (gs_aabb_vs_aabb(&a, &b)) {
						gs_vec2 disp = gs_aabb_aabb_mtv(&a, &b);

						transform->position.x += disp.x;
						transform->position.y += disp.y;
					}
				}
			}
		}
	}
}

void App::Draw(){
	gsi_camera2D(&m_gsi);

	// Aqui iteramos sobre todas as entidades e, se elas tiverem
	// o necessario para serem desenhadas na tela (Transform2D + 
	// Image2D), desenhamos.
	for (auto e : m_entities) {
		Transform2D* transform = e->Get<Transform2D>();
		Image2D* image = e->Get<Image2D>();

		if (transform && image) {
			//transform->rotation += 0.1f;
			// Cada entidade precisa de uma matrix de transformação
			// diferente. Isso é necessário para que elas se movam
			// livremente pelo cenário.
			gsi_push_matrix(&m_gsi, GSI_MATRIX_MODELVIEW);

			// Aqui passamos a posição, rotação e escala da entidade,
			// através dos dados armazenados no Transform2D.
			gsi_transf(&m_gsi, transform->position.x, transform->position.y, 0.f);
			gsi_rotatefv(&m_gsi, transform->rotation, GS_ZAXIS);
			gsi_scalef(&m_gsi, transform->scale.x, transform->scale.y, 1.f);
			
			// Aqui obtemos a textura informada no Image2D e passamos
			// ela para ser utilizada.
			auto texture = gs_assets_getp(&m_gsa, gs_asset_texture_t, m_assetTable[image->imageName]);
			gsi_texture(&m_gsi, texture->hndl);

			// Finalmente, renderizamos um quadrado, que irá utilizar a
			// textura e o transform enviado anteriormente.
			gsi_rectvd(
				&m_gsi, gs_v2(-0.5f, -0.5f), gs_v2(1.0f, 1.0f), gs_v2(0.f, 0.f), 
				gs_v2(1.f, 1.f), gs_color(255, 255, 255, 255), 
				GS_GRAPHICS_PRIMITIVE_TRIANGLES
			);
			
			// Removendo a matriz da entidade, pois já finalizamos aqui...
			gsi_pop_matrix(&m_gsi);
		}
		// DEBUG: Desenhando o AABB
		BoxCollider2D* collider = e->Get<BoxCollider2D>();
		if (collider && drawDebugAABB) {
			gsi_push_matrix(&m_gsi, GSI_MATRIX_MODELVIEW);

			gs_aabb_t aabb = collider->GetBoundingBox();
			gs_handle(gs_graphics_texture_t) hndl = {};
			gsi_texture(&m_gsi, hndl);
			gsi_rectvx(&m_gsi, aabb.min, aabb.max, gs_v2(0.f, 0.f), gs_v2(1.f, 1.f), GS_COLOR_GREEN, GS_GRAPHICS_PRIMITIVE_LINES);
			
			gsi_pop_matrix(&m_gsi);
		}
	}

	// Aqui enviamos as isntruções de render para serem desenhadas.
	// A cor passada no terceiro parâmetro dessa função representa
	// a cor de fundo da tela.
	//gsi_render_pass_submit(&m_gsi, &m_gcb, gs_color(51, 153, 218, 255));
	gsi_render_pass_submit(&m_gsi, &m_gcb, gs_color(236, 236, 236, 255));
	gs_graphics_submit_command_buffer(&m_gcb);
}

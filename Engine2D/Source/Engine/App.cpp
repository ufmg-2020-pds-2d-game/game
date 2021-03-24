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

App* GetApp(){
	App* app = gs_engine_user_data(App);
	return app;
}

//---------------------------------------------------------------------------//

App::App() {
	gravity = 9.8f;
	drawDebugAABB = false;

	camera.position = Vector(0.f, 0.f);
	camera.zoom = 1.f;
	camera.rotation = 0.f;
	
	forceQuit = false;

	m_isRunning = false;

	m_app = { 0 };
	m_app.window_title = "Game";
	m_app.window_height = 720;
	m_app.window_width  = 1280;
	
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
}

App::~App() {
	for (auto e : m_entities) {
		delete e;
	}
	m_entities.clear();
	//m_assetTable.clear();

	m_textures.clear();
	m_audios.clear();
}

void App::Start(){
	m_isRunning = true;

	for (auto e : m_entities) {
		e->Start();
	}
}

void App::Update(){
	if (gs_platform_key_pressed(GS_KEYCODE_ESC) || forceQuit) {
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
	//*
	Start();

	//m_engine->run();
#ifdef GS_PLATFORM_IMPL_EMSCRIPTEN
	emscripten_set_main_loop(gs_engine_frame, (int32_t)m_app.frame_rate, true);
#else
	while (gs_engine_app()->is_running) {
		gs_engine_frame();
	}
#endif
	//*/
}

void App::LoadTexture(const std::string& name, const std::string& path) {
	// Antes de mais nada, vamos ver se o arquivo existe!
	if (!gs_platform_file_exists(path.c_str())) {
		//throw std::exception("Load Texture Error: File doesn't exist!");
	}

	gs_asset_texture_t tex0 = { 0 };

	// Descrevendo o formato interno da textura 
	// para ser desenhada na tela. 
	tex0.desc.format = GS_GRAPHICS_TEXTURE_FORMAT_RGBA8;
	tex0.desc.min_filter = GS_GRAPHICS_TEXTURE_FILTER_LINEAR;
	tex0.desc.mag_filter = GS_GRAPHICS_TEXTURE_FILTER_LINEAR;

	tex0.desc.wrap_s = GS_GRAPHICS_TEXTURE_WRAP_REPEAT;
	tex0.desc.wrap_t = GS_GRAPHICS_TEXTURE_WRAP_REPEAT;

	gs_asset_texture_load_from_file(path.c_str(), &tex0, NULL, false, false);

	m_textures[name] = tex0;
}

void App::LoadAudio(const std::string& name, const std::string& path) {
	// Antes de mais nada, vamos ver se o arquivo existe!
	if (!gs_platform_file_exists(path.c_str())) {
		//throw std::exception("Load Audio Error: File doesn't exist!");
	}

	gs_asset_audio_t aud0;
	gs_asset_audio_load_from_file(path.c_str(), &aud0);

	m_audios[name] = aud0;
}

void App::PlayAudio(const std::string & name, float volume){
	gs_audio_play_source(m_audios[name].hndl, volume);
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

	// Atualizando a posição rotação e escala (zoom) da câmera.
	{
		gsi_transf(&m_gsi, camera.position.x, camera.position.y, 0.f);
		gsi_rotatefv(&m_gsi, camera.rotation, GS_ZAXIS);
		gsi_scalef(&m_gsi, camera.zoom, camera.zoom, camera.zoom);
	}
	
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
			auto texture = m_textures[image->imageName];
			gsi_texture(&m_gsi, texture.hndl);

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

	for (auto e : m_entities) {
		Text* text = e->Get<Text>();

		if (text) {
			gsi_text(
				&m_gsi,
				text->position.x, text->position.y,
				text->text.c_str(),
				NULL, false,
				255, 255, 255, 255
			);
		}
	}

	// Aqui enviamos as isntruções de render para serem desenhadas.
	// A cor passada no terceiro parâmetro dessa função representa
	// a cor de fundo da tela.
	gsi_render_pass_submit(&m_gsi, &m_gcb, gs_color(51, 153, 218, 255));
	//gsi_render_pass_submit(&m_gsi, &m_gcb, gs_color(236, 236, 236, 255));
	gs_graphics_submit_command_buffer(&m_gcb);
}

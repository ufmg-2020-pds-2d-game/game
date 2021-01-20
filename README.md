##### Projeto desenvolvido durante o curso de Prática de Desenvolvimento de Software - UFMG 2020/2°

# Easy 2D Game Engine

![TitleImage](https://media.discordapp.net/attachments/783065895982334002/801538602579263508/unknown.png?width=753&height=427)

## Resumo
O objetivo do projeto é desenvolver uma **game engine** (ou **framework**) que permite usuários conseguirem criarem **Jogos 2D** de forma simples e eficiente, sem ter que se preocupar com detalhes menores de implementação. 

Ao final do desenvolvimento do motor, o time também pretende utilizar a mesma para criar um jogo básico de exemplo de funcionalidades. Além disso de acordo com o andar do projeto, caso o objetivo principal seja atingido o time poderá tentar implementar um sistema de ranking ou até mesmo facilitar o uso com a GameJolt API.

## Tecnologia Utilizada
Usariamos as seguintes ferramentas para o desenvolvimento:
- **Linguagem**: C++
- **Bibliotecas**: Gunslinger (https://github.com/MrFrenik/gunslinger)
- **Outras tecnologias**: Gamejolt Rest API

## Equipe
Os Integrantes da equipe são:
- Guilherme Teres Nunes (UnidayStudio)
- Bernardo Augusto de Oliveira Senna (Bernardo-Senna)
- Victor Hugo Nascimento Costa Val (Deheide)
- João Marcos Machado Couto (joaomcouto)

## Exemplos:
Jogo simples criado Utilizando o Projeto:
![Game](https://media.discordapp.net/attachments/748726391637409804/801537044576206897/unknown.png)

Código simples de exemplo de utilização:
```cpp
#include "Engine/Engine.h"

int main(int argc, char *argv[]) {
	App app;

	// Carregando as texturas...
	app.LoadTexture("c_red", "./Data/character_roundRed.png");
	app.LoadTexture("tile", "./Data/tile.png");

	// Carregando sons...
	app.LoadAudio("jump_s", "./Data/sfx_movement_jump1.wav");

	// Adicionando uma Entidade para o Jogador...
	{
		Entity* a = new Entity();

		a->Add(new Transform2D({ 200.f, 200.f }, {100.f, -100.f}));
		a->Add(new Image2D("c_red"));

		a->Add(new BoxCollider2D(0.6f, 0.9f));
		a->Add(new RigidBody2D());

		app.AddEntity(a);
	}
	/// Adicionando 10 Entidades para o Chão...
	for (int i=0; i<10; i++) {
		Entity* a = new Entity();

		a->Add(new Transform2D({ 100.f * i, 600.f}, { 100.f, 100.f }));
		a->Add(new Image2D(names["tile"]));
		a->Add(new BoxCollider2D());

		app.AddEntity(a);
	}

	app.Run();

	return 0;
}
```

## Gestão do projeto
As sprints serão controladas via Trello:
![Screenshot](https://media.discordapp.net/attachments/783065895982334002/795734782548901918/H5JS9eqTdbzOfm4V8L0dtmas2WN5f8D1g8cvjuXT4UAAAAASUVORK5CYII.png)

## Método de Desenvolvimento
O time planeja usar o scrumban, um método que mistura o scrum e o kanban (métodos ágeis). A ideia de usar esse método é fornecer alta adaptabilidade da sprint em questão de tasks, caso seja terminada todas as tasks antes que a sprint seja finalizada, seria possivel puxar tarefas da proxima que se encontra no backlog.

O scrumban também forneceria mais adaptabilidade caso uma sprint transbordasse no projeto, planejando melhor o mvp com o que já fora feito na passada. Assim um exemplo de divisão de sprints poderia ser facilmente criado: 
```diff
+ sprint 1 (criação da engine local)
+ sprint 2 ( iniciação do mvp do jogo a partir da engine)
+ sprint 3 ( finalização do jogo).
```
Neste exemplo caso a sprint 1 venha a falhar possamos mudar / adaptar o projeto facilmente 
ex:
```diff
- sprint 1 (criação da engine local) FALHA
+ sprint 2 ( finalização da engine local com facilitação do GameJoltAPI)
+ sprint 3 (finalização da facilitação do desenvolvimento com GameJolt).
```
Inicialmente **não** teremos sprint de produção, porém isso poderar ser alterado no futuro.

## Principais Features:
### Renderização 2D
O motor será capaz de carregar imagens do disco e renderliza-la na tela de forma simplificada, para produzir cenas 2D interessantes rápidamente.

### Sistema de Entity Component: 
Um "objeto" dentro do jogo nada mais é do que uma Entidade construída através de diferentes Componentes. Um Componente é uma Interface que pode ser sobrescrita para adicionar diferentes lógicas, variáveis, etc. Exemplo:
```cpp
Entity* a = new Entity();

a->Add(new Transform2D({ 200.f + 200.f * i, 200.f - 50.f * i }, {100.f, -100.f}));
a->Add(new Image2D(i == 0 ? "c_red" : "c_purple"));

a->Add(new BoxCollider2D(0.6f, 0.9f));
a->Add(new RigidBody2D());

if (i == 0) {
	a->Add(new PlayerComponent());
}

app.AddEntity(a);
```

### Cálculo de Física
O motor irá fazer o cálculo de física e gravidade automaticamente, utilizando como entrada as entidade e componentes adicionados na cena.

### Criação de Lógica rapidamente
Você pode criar uma classe que herda do Componente e implementar os métodos Start(), Update() e End() para adicionar lógicas personalizadas. 
Exemplo:
```cpp
class PlayerComponent : public Component {
public:
	PlayerComponent(){}
	virtual ~PlayerComponent(){}

	virtual void Update() override{
		// Movimentação básica de um personagem (esquerda e direita) através
		// da detecção de teclas do teclado.
		Transform2D* t = GetEntity()->Get<Transform2D>();
		
		if (gs_platform_key_down(GS_KEYCODE_A)) {
			t->position.x -= speed;
			t->scale.x = -std::abs(t->scale.x);
		}
		else if (gs_platform_key_down(GS_KEYCODE_D)) {
			t->position.x += speed;
			t->scale.x = std::abs(t->scale.x);
		}

		if (gs_platform_key_pressed(GS_KEYCODE_SPACE) || gs_platform_key_pressed(GS_KEYCODE_W)) {
			PlayAudio("jump_s");
			m_jumpForce = 50.f;
		}
		if (m_jumpForce > 0) {
			t->position.y -= m_jumpForce;
			m_jumpForce -= 5.f;
		}
	}

	float speed;
protected:
	float m_jumpForce;
};
```

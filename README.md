##### Projeto desenvolvido durante o curso de Prática de Desenvolvimento de Software - UFMG 2020/2°

# Easy 2D Game Engine

## Resumo
O objetivo do projeto é desenvolver uma **game engine** (ou **framework**) que permite usuários conseguirem criarem **Jogos 2D** de forma simples e eficiente, sem ter que se preocupar com detalhes menores de implementação. 

Ao final do desenvolvimento do motor, o time também pretende utilizar a mesma para criar um jogo básico de exemplo de funcionalidades.

## Tecnologia Utilizada
Usariamos as seguintes ferramentas para o desenvolvimento:
- **Linguagem**: C++
- **Bibliotecas**: SDL2, SDL2_Image

## Equipe
Os Integrantes da equipe são:
- Guilherme Teres Nunes (UnidayStudio)
- Bernardo Augusto de Oliveira Senna (Bernardo-Senna)
- Victor Hugo Nascimento Costa Val (Deheide)
- João Marcos Machado Couto (joaomcouto)

## Principais Features:
### Renderização 2D
O motor será capaz de carregar imagens do disco e renderliza-la na tela de forma simplificada, para produzir cenas 2D interessantes rápidamente.

### Sistema de Entity Component: 
Um "objeto" dentro do jogo nada mais é do que uma Entidade construída através de diferentes Componentes. Um Componente é uma Interface que pode ser sobrescrita para adicionar diferentes lógicas, variáveis, etc. Exemplo:
```cpp
// Vamos criar uma plataforma 2D. Primeiro criamos uma entidade vazia:
Entity* p1 = new Entity();
// Depois adicionamos um transform para que ela tenha posição e escala no mundo 2D:
p1->Add(new Transform(10.f, 20.f));
// Em seguida um renderizador de imagens para exibir a foto da plataforma:
p1->Add(new ImageRenderer("platform.png"));
// Finalmente, uma caixa de colisão para que o jogador possa ficar em cima da plataforma:
p1->Add(new CollisionBox()); 
```

### Cálculo de Física
O motor irá fazer o cálculo de física e gravidade automaticamente, utilizando como entrada as entidade e componentes adicionados na cena.

### Classe Scene:
Uma classe que pode ser sobrescrita para criar diferentes fases do Jogo de forma fácil, proporcionando ao usuário a habilidade de adicionar objetos, configurar a cor do céu, etc para cada level do game.

### Detecção de Inputs
Entradas dadas pelo jogador através do teclado e mouse serão automaticamente detectadas e armazenadas, provendo uma API simples de usar para obtê-las afim de criar um Jogo.
Exemplo:
```cpp
// Movimentação básica de um personagem (esquerda e direita) através
// da detecção de teclas do teclado.
float speed = 1.f;
		
if (keyPress(event::AKEY)){
	transform->position.x -= speed;
}
else if (keyPress(event::DKEY)){
	transform->position.x += speed;
}
```


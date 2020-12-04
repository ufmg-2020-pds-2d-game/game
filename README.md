##### Projeto desenvolvido durante o curso de Prática de Desenvolvimento de Software - UFMG 2020/2°

# Easy 2D Game Engine

## Resumo
O objetivo do projeto é desenvolver uma **game engine** (ou **framework**) que permite usuários conseguirem criarem **Jogos 2D** de forma simples e eficiente, sem ter que se preocupar com detalhes menores de implementação. 

Ao final do desenvolvimento do motor, o time também pretende utilizar a mesma para criar um jogo básico de exemplo de funcionalidades. Além disso de acordo com o andar do projeto, caso o objetivo principal seja atingido o time poderá tentar implementar um sistema de ranking ou até mesmo facilitar o uso com a GameJolt API.

## Tecnologia Utilizada
Usariamos as seguintes ferramentas para o desenvolvimento:
- **Linguagem**: C++
- **Bibliotecas**: SDL2, SDL2_Image
- **Outras tecnologias**: Gamejolt Rest API

## Equipe
Os Integrantes da equipe são:
- Guilherme Teres Nunes (UnidayStudio)
- Bernardo Augusto de Oliveira Senna (Bernardo-Senna)
- Victor Hugo Nascimento Costa Val (Deheide)
- João Marcos Machado Couto (joaomcouto)

## Método de Desenvolvimento
O time planeja usar o scrumban, um método que mistura o scrum e o kanban (métodos ágeis). A ideia de usar esse método é fornecer alta adaptabilidade da sprint em questão de tasks, caso seja terminada todas as tasks antes que a sprint seja finalizada, seria possivel puxar tarefas da proxima que se encontra no backlog.

O scrumban também forneceria mais adaptabilidade caso uma sprint transbordasse no projeto, planejando melhor o mvp com o que já fora feito na passada. Assim um exemplo de divisão de sprints poderia ser facilmente criado: 
```diff
+ sprint 1 (criação da engine local)
+ sprint 2 ( iniciação do mvp do jogo a partir da engine)
+ sprint 3 ( finalização do jogo).
```
Neste exemplo caso a sprint 1 venha a falhar possamos mudar adaptar o projeto facilmente 
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


#include "pch.h"
#include "CppUnitTest.h"
#include "TestMocks.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine2DTest{
	TEST_CLASS(VectorTest){
	public:
		
		/*====================
		Construtores da Classe
		====================*/


		TEST_METHOD(TestConstructor) {
			Vector v1(1.f, 2.f);

			Assert::AreEqual(v1.x, 1.f);
			Assert::AreEqual(v1.y, 2.f);
		}

		TEST_METHOD(TestConstructorDefault) {
			// O construtor padrão (quando o usuário não passa nenhum
			// parâmetro) deve inicializar o Vetor com os valores {0, 0}
			Vector v1;

			Assert::AreEqual(v1.x, 0.f);
			Assert::AreEqual(v1.y, 0.f);
		}

		TEST_METHOD(TestConstructorWithAB) {
			// Aqui o usuário pode passar os valore X, Y iniciais para
			// o vetor
			Vector v1(1.f, 2.f);

			Assert::AreEqual(v1.x, 1.f);
			Assert::AreEqual(v1.y, 2.f);
		}

		TEST_METHOD(TestCopyConstructor) {
			Vector v1(10.f, -5.f);

			// O vetor v2 é inicializado através do v1. Ou seja:
			// Ele deve copiar os valores X e Y de v1.
			Vector v2(v1);

			Assert::AreEqual(v2.x, v1.x);
			Assert::AreEqual(v2.y, v1.y);
		}        

		/*=============================
		Operadores de Matemática Básica
		=============================*/

		TEST_METHOD(TestOperatorPlus) {
			// Testa a soma de dois vetores, exemplo:
			// resultado = vetorA + vetorB
			Vector result = Vector(1.f, 12.f) + Vector(9.f, 8.f);

			Assert::AreEqual(result.x, 10.f);
			Assert::AreEqual(result.y, 20.f);
		}

		TEST_METHOD(TestOperatorMinus) {
			// Testa a subtração de dois vetores, exemplo:
			// resultado = vetorA - vetorB
			Vector result = Vector(5.f, 5.f) - Vector(10.f, 1.f);

			Assert::AreEqual(result.x, -5.f);
			Assert::AreEqual(result.y, 4.f);
		}

		TEST_METHOD(TestOperatorMultiply) {
			// Testa a multiplicação de um vetor por um escalar, exemplo:
			// resultado = vetorA * 2
			Vector result = Vector(1.f, 1.f) * 2.f;

			Assert::AreEqual(result.x, 2.f);
			Assert::AreEqual(result.y, 2.f);
		}

		TEST_METHOD(TestOperatorDivide) {
			// Testa a divisão de um vetor por um escalar, exemplo:
			// resultado = vetorA / 2
			Vector result = Vector(4.f, 4.f) / 2.f;

			Assert::AreEqual(result.x, 2.f);
			Assert::AreEqual(result.y, 2.f);
		}

		/*======================
		Operadores de Comparação
		======================*/

		TEST_METHOD(TestOperatorCompareEqual) {
			// Testa o operador "==" que verifica se dois vetores
			// são iguais
			bool result = Vector() == Vector(0.f, 0.f);

			Assert::AreEqual(result, true);
		}
				
		/*====================================
		Assignment Operators (+=, -=, *= e /=)
		====================================*/

		TEST_METHOD(TestAssignmentOperatorPlus) {
			// Testa a soma de dois vetores, exemplo:
			// vetorA += vetorB
			Vector result = Vector(1.f, 2.f); 
			result += Vector(9.f, 8.f);

			Assert::AreEqual(result.x, 10.f);
			Assert::AreEqual(result.y, 10.f);
		}

		TEST_METHOD(TestAssignmentOperatorMinus) {
			// Testa a subtração de dois vetores, exemplo:
			// vetorA -= vetorB
			Vector result = Vector(5.f, 5.f);
			result -= Vector(10.f, 1.f);

			Assert::AreEqual(result.x, -5.f);
			Assert::AreEqual(result.y, 4.f);
		}

		TEST_METHOD(TestAssignmentOperatorMultiply) {
			// Testa a multiplicação de um vetor por um escalar, exemplo:
			// vetorA *= 2
			Vector result = Vector(1.f, 1.f);
			result *= 2.f;

			Assert::AreEqual(result.x, 2.f);
			Assert::AreEqual(result.y, 2.f);
		}

		TEST_METHOD(TestAssignmentOperatorDivide) {
			// Testa a divisão de um vetor por um escalar, exemplo:
			// vetorA /= 2
			Vector result = Vector(4.f, 4.f);
			result /= 2.f;

			Assert::AreEqual(result.x, 2.f);
			Assert::AreEqual(result.y, 2.f);
		}

		
		/*===============================
		Métodos Diversos da classe Vector
		===============================*/

		TEST_METHOD(TestLength)	{
			// O length (comprimento do vetor) retorna a
			// hipotenusa h do vetor {X, Y} utilizando a fórmula de pitágoras: 
			//   |\		 | 
			//  x| \ h   |       ________
			//   |  \    |  h = V x² + y²
			//   |___\   | 
			//     y     | 

			Vector vec(2.0, 3.0);

			// Raiz quadrada de 13 porque 2 ao quadrado mais 3 ao quadrado é 13.
			Assert::AreEqual(vec.Length(), sqrt(13.0f));
		}

		TEST_METHOD(TestNormalize) {
			// O Método Normalize() serve para normalizar o vetor.
			// Um vetor normal é aquele que o seu comprimento é igual a 1.f!
			Vector vec(2.0, 3.0);

			// Esse é o método sendo testado:
			vec.Normalize();

			Assert::AreEqual(vec.Length(), 1.f);
		}

		TEST_METHOD(TestNormalized) {
			// Mesma utilidade do método anterior, a diferença é que ao invés
			// de normalizar o próprio vetor, esse método retorna uma cópia
			// normalizada do vetor em questão.
			Vector vec(2.0, 3.0);

			// Esse é o método sendo testado:
			Vector normalizedVec = vec.Normalized();

			Assert::AreEqual(normalizedVec.Length(), 1.f);
		}

	};

	TEST_CLASS(AppTests) {
	public:
		TEST_METHOD(AppDefaultValues) {
			// Teste para verificar se o App é inicializado com 
			// os valores padrões de forma adequada.
			App app;

			// Gravidade padrão
			Assert::AreEqual(app.gravity, 9.8f);

			// Valores padrões da câmera:
			Assert::IsTrue(app.camera.position == Vector(0.f, 0.f));
			Assert::AreEqual(app.camera.zoom, 1.f);
			Assert::AreEqual(app.camera.rotation, 0.f);

			// É necessário executar o jogo, mesmo que ele não faça nada.
			// Mas já que é um teste unitário, ativamos essa flag forceQuit
			// para que ele só seja executado por um frame e depois feche.
			app.forceQuit = true;
			app.Run();
		}

		void TestComponentVirtualMethodsCalledUtil(
			bool* calledStart = nullptr,	// Método Start()
			bool* calledUpdate = nullptr,	// Método Update()
			bool* calledEnd = nullptr		// Método End()
		) {
			// Esse é um teste um pouco mais ROBUSTO.
			//
			// NOTA: Essa é uma função para auxiliar no teste.
			// O teste em si (que basicamente apenas chama essa função variando
			// os parâmetros) é realizado nos tres metodos implementados
			// depois desse.
			//
			// Ele cria um mock, ver a classe "TestComponentVirtualMethods",
			// implementada no arquivo "TestMocks.h" para os detalhes. Mas
			// em poucas palavras:
			//
			// - SITUAÇÃO 1:
			// Quando uma entidade é adicionada ao jogo, o metodo "Start"
			// dessa entidade é chamado, que faz nada mais nada menos do que
			// chamar o "Start" de todos os componentes dentro da entidade.
			//
			// - SITUAÇÃO 2:
			// Quando uma entidade ESTÁ no jogo, TODOS OS FRAMES o metodo
			// "Update" dessa entidade é chamado. Da mesma forma que o Start,
			// ele apenas chama o "Update" dos componentes.
			//
			// - SITUAÇÃO 3:
			// Quando uma entidade é removida ao jogo (ou o jogo termina), 
			// o metodo "Start" dessa entidade é chamado, que é responsável por
			// chamar o "Start" de todos os componentes dentro da entidade.
			//
			// Logo, para testar esses metodos, um Mock para um Componente foi
			// criado, que define uma flag como true ao entrar em cada um desses
			// metodos.

			// Precisamos de uma instância do app...
			App app;

			// Vamos criar uma nova entidade e adicionar o mock
			// do componente para fazer o teste.
			auto ent = new Entity();

			// Criamos o componente de teste...
			auto testComponent = ent->New<TestComponentVirtualMethods>();

			// Passamos os endereços (ponteiros) das booleanas 
			// passadas como parâmetro nessa função.
			testComponent->calledStart = calledStart;
			testComponent->calledUpdate = calledUpdate;
			testComponent->calledEnd = calledEnd;

			// Finalmente, adicionamos essa entidade no jogo:
			app.AddEntity(ent);

			// Agora podemos executar o jogo por um frame:
			app.forceQuit = true;
			app.Run();

			// Não é necessário deletar a entidade nem o componente,
			// o app já faz isso.
		}

		TEST_METHOD(TestComponentStartCall) {
			bool calledStart = false;

			TestComponentVirtualMethodsCalledUtil(
				&calledStart,	// Método Start()
				nullptr,		// Método Update()
				nullptr			// Método End()
			);

			Assert::IsTrue(calledStart);
		}

		TEST_METHOD(TestComponentUpdateCall) {
			bool calledUpdate = false;

			TestComponentVirtualMethodsCalledUtil(
				nullptr,        // M�todo Start()
				&calledUpdate,    // M�todo Update()
				nullptr            // Metodo End()
			);

			Assert::IsTrue(calledUpdate);
		}

		TEST_METHOD(TestComponentEndCall) {
			bool calledEnd = false;

			TestComponentVirtualMethodsCalledUtil(
				nullptr,        // M�todo Start()
				nullptr,        // M�todo Update()
				&calledEnd        // Metodo End()
			);

			Assert::IsTrue(calledEnd);
		}

		/*=====================================================
		Testando o carregamento de arquivos (Texturas e Audios)
		=====================================================*/

		TEST_METHOD(AppLoadTextureSuccess) {
			// Verifica se, ao carregar uma textura que EXISTE, a engine
			// o faz sem problemas.
			App app;

			try {
				app.LoadTexture("c_red", "./../Game/Data/character_roundRed.png");
				Assert::IsTrue(true);
			}
			catch (std::exception e) {
				Assert::Fail();
			}

			// É necessário rodar a engine, mesmo que por um frame. 
			app.forceQuit = true;
			app.Run();
		}

		TEST_METHOD(AppLoadTextureFailure) {
			// Agora é o oposto: Se o usuário tentar carregar um arquivo que NÃO
			// existe, o motor deve lançar uma excessão!
			App app;

			try {
				app.LoadTexture("nop", "./Essa Textura Nao existe.png");
				Assert::Fail((const wchar_t*)"O codigo não deveria chegar aqui!");
			}
			catch (std::exception e) {
				// Identificou o erro e lançou a exceção!
				Assert::IsTrue(true);
			}

			// É necessário rodar a engine, mesmo que por um frame. 
			app.forceQuit = true;
			app.Run();
		}

		TEST_METHOD(AppLoadAudioSuccess) {
			// De forma similar ao teste da textura, verifica se a engine
			// consegue carregar um audio corretamente
			App app;

			try {
				app.LoadAudio("audio", "./../Game/Data/sfx_movement_jump1.wav");
				Assert::IsTrue(true);
			}
			catch (std::exception e) {
				Assert::Fail();
			}

			// É necessário rodar a engine, mesmo que por um frame. 
			app.forceQuit = true;
			app.Run();
		}

		TEST_METHOD(AppLoadAudioFailure) {
			// De forma similar ao teste da textura, verifica se a engine
			// lança uma exceção ao tentar carregar um aqui que não existe.
			App app;

			try {
				app.LoadAudio("nop", "./Esse Audio Nao existe.wav");
				Assert::Fail((const wchar_t*)"O codigo não deveria chegar aqui!");
			}
			catch (std::exception e) {
				// Identificou o erro e lançou a exceção!
				Assert::IsTrue(true);
			}

			// É necessário rodar a engine, mesmo que por um frame. 
			app.forceQuit = true;
			app.Run();
		}
	};

    // Testa a classe Entity
    TEST_CLASS(EntityTests) {
    public:
        // Verifica se, ao tentar obter um componente
        // que não foi adicionado a entidade, o retorno
        // é de fato nullptr.
        TEST_METHOD(TestGetComponentInvalid) {
            Entity entity;

            Component* t = entity.Get<Transform2D>();

            Assert::IsTrue(t == nullptr);
        }

        // Testa a capacidade de adicionar e obter de
        // volta um componente a uma entidade.
        TEST_METHOD(TestAddAndGetComponent) {
            Entity entity;
            entity.Add(new Transform2D());

            Component* t = entity.Get< Transform2D>();

            Assert::IsTrue(t != nullptr);
        }

        // Testa a criação de um novo componente usando
        // o método da entidade.
        TEST_METHOD(TestNewComponent) {
            Entity entity;

            auto t = entity.New<Transform2D>();

            Assert::IsTrue(t != nullptr);
        }
    };
}

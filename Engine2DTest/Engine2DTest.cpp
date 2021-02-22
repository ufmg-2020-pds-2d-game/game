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

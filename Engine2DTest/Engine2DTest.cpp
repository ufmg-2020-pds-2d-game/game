#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine2DTest
{
	TEST_CLASS(VectorTest)
	{
	public:
		
		TEST_METHOD(TestLength)
		{
			Vector vec(2.0, 3.0);
			Assert::AreEqual(vec.Length(), sqrt(13.0f));
		}


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

	};

    // Testa a classe Entity
    TEST_CLASS(EntityTests) 
    {
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

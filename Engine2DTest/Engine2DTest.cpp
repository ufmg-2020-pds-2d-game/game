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

		TEST_METHOD(TestConstructor) {
			Vector v1(1.f, 2.f);

			Assert::AreEqual(v1.x, 1.f);
			Assert::AreEqual(v1.y, 2.f);
		}


	};

    // Testa a classe Entity
    TEST_CLASS(EntityTests) 
    {
    public:
        // Verifica se, ao tentar obter um componente
        // que n�o foi adicionado a entidade, o retorno
        // � de fato nullptr.
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
    };
}

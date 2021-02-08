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
}

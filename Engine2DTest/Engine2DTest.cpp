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
	};
}

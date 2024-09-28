#include "pch.h"
#include "CppUnitTest.h"
#include <limits>
#include "../Domain/Cube.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(Ctor_NegativeSide_ExpectedException)
		{
			Assert::ExpectException<std::out_of_range>([]()
				{
					Cube cube{ -1 };
				}
			);
		}

		TEST_METHOD(GetVolume_ValidData_Success)
		{
			Cube cube{ 2 };
			const double expected = 8;
			const auto actual = cube.GetVolume();
			Assert::IsTrue(std::abs(expected - actual) <= std::numeric_limits<double>::epsilon());
		}

		TEST_METHOD(GetSurfaceArea_ValidData_Success)
		{
			Cube cube{ 2 };
			const double expected = 24;
			const auto actual = cube.GetSurfaceArea();
			Assert::IsTrue(std::abs(expected - actual) <= std::numeric_limits<double>::epsilon());
		}

		TEST_METHOD(ToString_ValidData_Success)
		{
			Cube cube{ 2 };
			const std::string expected = "Куб{сторона: 2}";
			auto actual = cube.ToString();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(OperatorLeftShift_ValidDate_Success)
		{
			Cube cube{ 2 };
			const std::string expected = "Куб{сторона: 2}";
			std::stringstream buffer;
			buffer << cube;
			auto actual = buffer.str();
			Assert::AreEqual(expected, actual);
		}
	};
}

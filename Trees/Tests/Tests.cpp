#include "pch.h"
#include "CppUnitTest.h"
#include "../RBTree/RTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(Ctor_SingleValue_Success)
		{
			RTree actual( 1 );
			RTree expected;
			RNode* expected_root;
			expected_root = new RNode(1);
			expected_root->color = node_colors::BLACK;
			expected.SetRoot(expected_root);
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(InsertValue_InsertSingleValue_Success)
		{
			RTree actual(2);
			RTree expected(2);
			actual.insert_item(1);
			RNode* expected_root = expected.GetRoot();
			expected_root->left = new RNode(1);
			Assert::IsTrue((actual == expected) && check_three(actual));
		}

		TEST_METHOD(CtorInitializer_MultipleValues_Success)
		{
			RTree actual{ 1, 2, 3 };
			RTree expected;
			expected.insert_item(1);
			expected.insert_item(2);
			expected.insert_item(3);
			Assert::IsTrue((actual == expected) && check_three(actual));
		}

		TEST_METHOD(CtorCopy_CopyTree_Success)
		{
			RTree expected{ 1, 2, 3 };
			RTree actual(expected);
			Assert::IsTrue((actual == expected) && check_three(actual));
		}

		TEST_METHOD(CtorMoveCopy_CopyTree_Success)
		{
			RTree expected{ 1, 2, 3 };
			RTree temp{ 1, 2, 3 };
			RTree actual(std::move(temp));
			Assert::IsTrue((actual == expected) && check_three(actual));
		}

		TEST_METHOD(AssignOperator_CopyTree_Success)
		{
			RTree expected{ 1, 2, 3 };
			RTree actual;
			actual = expected;
			Assert::IsTrue((actual == expected) && check_three(actual));
		}

		TEST_METHOD(AssignMoveOperator_CopyTree_Success)
		{
			RTree expected{ 1, 2, 3 };
			RTree temp{ 1, 2, 3 };
			RTree actual;
			actual = std::move(temp);
			Assert::IsTrue((actual == expected) && check_three(actual));
		}

		TEST_METHOD(FindItem_CorrectItem_Success)
		{
			RTree rbt{ 1, 2, 3 };
			RNode* actual = rbt.find_item(1);
			RNode expected;
			expected.key = 1;
			expected.parent = rbt.GetRoot();
			Assert::IsTrue(*actual == expected);
		}

		TEST_METHOD(FindItem_WrongItem_ExpectedException)
		{
			Assert::ExpectException<std::logic_error>([]() {
				RTree rbt{ 1, 2, 3 };
				rbt.find_item(4);
				});
		}

		TEST_METHOD(DeleteItem_CorrectItem_Success)
		{
			RTree actual{ 1, 2, 3 };
			RTree expected{ 2, 1 };
			actual.delete_item(3);
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(ToString_GetString_Success)
		{
			RTree rbt{ 1, 2, 3 };
			std::string actual = rbt.ToString();
			std::string expected = "1 2 3 ";
			Assert::IsTrue(actual == expected);
		}
	};
}

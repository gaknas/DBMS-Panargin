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
			Assert::IsTrue((actual == expected) && check_tree(actual));
		}

		TEST_METHOD(InsertItem_InsertCase1_Success)
		{
			RTree actual{};
			actual.insert_item(1);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(InsertItem_InsertCase2_Success)
		{
			RTree actual(2);
			actual.insert_item(1);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(InsertItem_InsertCase3_Success)
		{
			RTree actual{ 3, 2, 4 };
			actual.insert_item(1);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(InsertItem_InsertCase4_Success)
		{
			RTree actual{ 3, 1 };
			actual.insert_item(2);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(InsertItem_InsertCase5_Success)
		{
			RTree actual{ 3, 2 };
			actual.insert_item(1);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(CtorInitializer_MultipleValues_Success)
		{
			RTree actual{ 1, 2, 3 };
			RTree expected;
			expected.insert_item(1);
			expected.insert_item(2);
			expected.insert_item(3);
			Assert::IsTrue((actual == expected) && check_tree(actual));
		}

		TEST_METHOD(CtorCopy_CopyTree_Success)
		{
			RTree expected{ 1, 2, 3 };
			RTree actual(expected);
			Assert::IsTrue((actual == expected) && check_tree(actual));
		}

		TEST_METHOD(CtorMoveCopy_CopyTree_Success)
		{
			RTree expected{ 1, 2, 3 };
			RTree temp{ 1, 2, 3 };
			RTree actual(std::move(temp));
			Assert::IsTrue((actual == expected) && check_tree(actual));
		}

		TEST_METHOD(AssignOperator_CopyTree_Success)
		{
			RTree expected{ 1, 2, 3 };
			RTree actual;
			actual = expected;
			Assert::IsTrue((actual == expected) && check_tree(actual));
		}

		TEST_METHOD(AssignMoveOperator_CopyTree_Success)
		{
			RTree expected{ 1, 2, 3 };
			RTree temp{ 1, 2, 3 };
			RTree actual;
			actual = std::move(temp);
			Assert::IsTrue((actual == expected) && check_tree(actual));
		}

		TEST_METHOD(DeleteItem_CorrectItem_Success)
		{
			RTree actual{ 1, 2, 3 };
			RTree expected{ 2, 1 };
			actual.delete_item(3);
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(DeleteItem_DeleteCase1_Success)
		{
			RTree actual{ 2, 1 };
			actual.delete_item(2);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(DeleteItem_DeleteCase2_Success)
		{
			RTree actual{ 2, 1, 4, 3, 5 };
			actual.delete_item(1);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(DeleteItem_DeleteCase3_Success)
		{
			RTree actual{ 4, 2, 6, 1, 3, 5, 7 };
			actual.delete_item(2);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(DeleteItem_DeleteCase4_Success)
		{
			RTree actual{ 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
			actual.delete_item(2);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(DeleteItem_DeleteCase5_Success)
		{
			RTree actual{ 4, 2, 8, 1, 3, 6, 9, 5, 7 };
			actual.delete_item(2);
			Assert::IsTrue(check_tree(actual));
		}

		TEST_METHOD(DeleteItem_DeleteCase6_Success)
		{
			RTree actual{ 4, 2, 8, 1, 3, 6, 5, 7};
			actual.delete_item(2);
			Assert::IsTrue(check_tree(actual));
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

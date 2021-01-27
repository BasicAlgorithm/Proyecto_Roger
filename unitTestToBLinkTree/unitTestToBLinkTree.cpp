#include "pch.h"
#include "CppUnitTest.h"
#include "../source/b-link.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unitTestToBLinkTree
{
	TEST_CLASS(unitTestToBLinkTree)
	{
	public:
		//inserting numbers ascending from 1 to 10
		TEST_METHOD(TestMethod1)
		{
			EDA::Concurrent::BLinkTree<3,int> blink;
			for (int i = 1; i <= 10; i++) {
				blink.insert(i);
			}

			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[1], INT_MAX);
			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[2], INT_MAX);
			
			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[0], 7);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayValoresHijos[0], 3);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayValoresHijos[1], 5);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayValoresHijos[0], 9);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[0], 1);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[1], 2);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[1]->arrayValoresHijos[0], 3);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[1]->arrayValoresHijos[1], 4);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[2]->arrayValoresHijos[0], 5);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[2]->arrayValoresHijos[1], 6);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[0]->arrayValoresHijos[0], 7);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[0]->arrayValoresHijos[1], 8);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[1]->arrayValoresHijos[0], 9);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[1]->arrayValoresHijos[1], 10);

		}
		//inserting numbers descending from 10 to 1
		TEST_METHOD(TestMethod2)
		{
			EDA::Concurrent::BLinkTree<3, int> blink;
			for (int i = 10; i >= 1; i--) {
				blink.insert(i);
			}
			
			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[1], INT_MAX);
			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[2], INT_MAX);

			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[0], 7);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayValoresHijos[0], 3);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayValoresHijos[1], 5);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayValoresHijos[0], 9);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[0], 1);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[1], 2);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[1]->arrayValoresHijos[0], 3);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[1]->arrayValoresHijos[1], 4);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[2]->arrayValoresHijos[0], 5);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[2]->arrayValoresHijos[1], 6);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[0]->arrayValoresHijos[0], 7);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[0]->arrayValoresHijos[1], 8);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[1]->arrayValoresHijos[0], 9);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[1]->arrayValoresHijos[1], 10);

		}
		
		//inserting numbers descending from 10 to 1
		TEST_METHOD(TestMethod3)
		{
			EDA::Concurrent::BLinkTree<3, int> blink;
			for (int i = 1; i <= 10; i++) {
				blink.insert(i);
			}

			for (int i = 1; i <= 10; i++) {
				blink.insert(i);
			}

			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[1], INT_MAX);
			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[2], INT_MAX);

			Assert::AreEqual(blink.rootNodo->arrayValoresHijos[0], 7);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayValoresHijos[0], 3);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayValoresHijos[1], 5);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayValoresHijos[0], 9);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[0], 1);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[0]->arrayValoresHijos[1], 2);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[1]->arrayValoresHijos[0], 3);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[1]->arrayValoresHijos[1], 4);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[2]->arrayValoresHijos[0], 5);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[0]->arrayPunterosHijos[2]->arrayValoresHijos[1], 6);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[0]->arrayValoresHijos[0], 7);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[0]->arrayValoresHijos[1], 8);

			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[1]->arrayValoresHijos[0], 9);
			Assert::AreEqual(blink.rootNodo->arrayPunterosHijos[1]->arrayPunterosHijos[1]->arrayValoresHijos[1], 10);

		}
	};
}

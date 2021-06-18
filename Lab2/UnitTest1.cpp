#include "pch.h"
#include "CppUnitTest.h"

#include "../PPPP_Lab2/PPPP_Lab2.cpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	
	TEST_CLASS(UnitTest1) {
public:
	TEST_METHOD(test_0_0_0_0_0_0) {
		string exp = "5";
		Assert::AreEqual(to_test(0, 0, 0, 0, 0, 0), exp);
	}

	TEST_METHOD(test_1_1_1_1_1_1) {
		string exp = "1 -1 1";
		Assert::AreEqual(to_test(1, 1, 1, 1, 1, 1), exp);
	}

	TEST_METHOD(test_0_1_3_0_3_1) {
		string exp = "2";
		Assert::AreEqual(to_test(0, 1, 3, 0, 3, 1), exp);
	}

	TEST_METHOD(test_0_1_0_0_3_0) {
		string exp = "4 3";
		Assert::AreEqual(to_test(0, 1, 0, 0, 3, 0), exp);
	}

	TEST_METHOD(test_1_2_3_4_5_6) {
		string exp = "2 -4 4.5";
		Assert::AreEqual(to_test(1, 2, 3, 4, 5, 6), exp);
	}
	TEST_METHOD(test_0_5_5_0_7_7) {
		string exp = "4 1";
		Assert::AreEqual(to_test(0, 5, 5, 0, 7, 7), exp);
	}

	TEST_METHOD(test_1_0_1_5_0_5) {
		string exp = "2 0 1";
		Assert::AreEqual(to_test(1, 0, 1, 5, 0, 5), exp);
	}
	TEST_METHOD(test_0_2_0_6_10_30) {
		string exp = "4 -5";
		Assert::AreEqual(to_test(0, -2, 0, 6, 10, -30), exp);
	}
	TEST_METHOD(test_6_3_4_4_5_7) {
		string exp = "2 3 4";
		Assert::AreEqual(to_test(6, 3, 4, 4, 5, 7), exp);
	}

	};
}

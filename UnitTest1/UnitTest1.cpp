#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab9.3/lab9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestSort) {
            Note notes[3] = {
                {"John", "Doe", "1234567890", {1, 1, 1990}},
                {"Jane", "Smith", "0987654321", {2, 2, 1991}},
                {"Robert", "Johnson", "5556667777", {3, 3, 1992}}
            };

            Note expected[3] = {
                {"Jane", "Smith", "0987654321", {2, 2, 1991}},
                {"John", "Doe", "1234567890", {1, 1, 1990}},
                {"Robert", "Johnson", "5556667777", {3, 3, 1992}}
            };

            const size_t N = sizeof(notes) / sizeof(notes[0]);
            Sort(notes, N);

            for (size_t i = 0; i < N; ++i) {
                Assert::AreEqual(expected[i].phoneNumber, notes[i].phoneNumber);
            }
        }
	};
}
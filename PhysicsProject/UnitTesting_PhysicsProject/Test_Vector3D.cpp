#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vector3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting_PhysicsProject
{
	TEST_CLASS(Test_Vector3D)
	{
	public:
		
		TEST_METHOD(Vector_TestEqual)
		{
			Vector3D testVector1 = Vector3D(3, 2, 1);
			Vector3D testVector2 = Vector3D(3, 2, 1);
			Vector3D testVector3 = Vector3D(1, 2, 3);

			Assert::IsTrue(testVector1 == testVector2);
			Assert::IsFalse(testVector1 == testVector3);
		}

		TEST_METHOD(Vector_TestNotEqual)
		{
			Vector3D testVector1 = Vector3D(3, 2, 1);
			Vector3D testVector2 = Vector3D(3, 2, 1);
			Vector3D testVector3 = Vector3D(1, 2, 3);

			Assert::IsTrue(testVector1 != testVector3);
			Assert::IsFalse(testVector1 != testVector2);
		}

		TEST_METHOD(Vector_TestAdd)
		{
			Vector3D testVector1 = Vector3D(0, 0, 0);
			Vector3D testVector2 = Vector3D(1, 1, 1);
			Vector3D addedVector = testVector1 + testVector2;
			Vector3D expectedResult = Vector3D(1, 1, 1);

			Assert::IsTrue(addedVector == expectedResult);
		}

		TEST_METHOD(Vector_TestSubtract)
		{
			Vector3D testVector1 = Vector3D(1, 1, 1);
			Vector3D testVector2 = Vector3D(1, 1, 1);
			Vector3D subtractedVector = testVector1 - testVector2;
			Vector3D expectedResult = Vector3D(0, 0, 0);

			Assert::IsTrue(subtractedVector == expectedResult);
		}

		TEST_METHOD(Vector_TestMultiply)
		{
			Vector3D testVector1 = Vector3D(1, 1, 1);
			float multiplyValue = 2;
			Vector3D multipliedVector = testVector1 * multiplyValue;
			Vector3D expectedResult = Vector3D(2, 2, 2);

			Assert::IsTrue(multipliedVector == expectedResult);
		}

		TEST_METHOD(Vector_TestDevide)
		{
			Vector3D testVector1 = Vector3D(2, 2, 2);
			float devideValue = 2;
			Vector3D devideVector = testVector1 / devideValue;
			Vector3D expectedResult = Vector3D(1, 1, 1);

			Assert::IsTrue(devideVector == expectedResult);
		}

		TEST_METHOD(Vector_TestDot)
		{
			Vector3D testVector1 = Vector3D(1, 1, 1);
			Vector3D testVector2 = Vector3D(1, 1, 1);
			float dotValue = testVector1.Dot(testVector2);
			float expectedResult = 3;

			Assert::IsTrue(dotValue == expectedResult);
		}

		TEST_METHOD(Vector_TestCross)
		{
			Vector3D testVector1 = Vector3D(1, 0, 3);
			Vector3D testVector2 = Vector3D(3, 0, 1);
			Vector3D crossVector = testVector1.Cross(testVector2);
			Vector3D expectedResult = Vector3D(0, 8, 0);

			Assert::IsTrue(crossVector == expectedResult);
		}

		TEST_METHOD(Vector_TestNormalize)
		{
			Vector3D testVector1 = Vector3D(2, 0, 0);
			testVector1.Normalize();
			Vector3D expectedResult = Vector3D(1, 0, 0);

			Assert::IsTrue(testVector1 == expectedResult);
		}

	};
}
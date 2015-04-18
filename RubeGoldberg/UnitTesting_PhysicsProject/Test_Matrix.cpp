#include "stdafx.h"
#include "CppUnitTest.h"
#include "Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting_PhysicsProject
{
	TEST_CLASS(Test_Matrix)
	{
	public:
		
		TEST_METHOD(Test_MatrixSetValues)
		{
			float* matrix1Values = new float[6];
			matrix1Values[0] = 1;
			matrix1Values[1] = 2;
			matrix1Values[2] = 3;
			matrix1Values[3] = 4;
			matrix1Values[4] = 5;
			matrix1Values[5] = 6;

			Matrix testMatrix1 = Matrix(2, 3, matrix1Values);

			Assert::AreEqual(1.0f, testMatrix1.Get(0, 0));
			Assert::AreEqual(2.0f, testMatrix1.Get(0, 1));
			Assert::AreEqual(3.0f, testMatrix1.Get(0, 2));
			Assert::AreEqual(4.0f, testMatrix1.Get(1, 0));
			Assert::AreEqual(5.0f, testMatrix1.Get(1, 1));
			Assert::AreEqual(6.0f, testMatrix1.Get(1, 2));
		}

		TEST_METHOD(Test_MatrixMultiplication)
		{
			float* matrix1Values = new float[6];
			matrix1Values[0] = 1;
			matrix1Values[1] = 2;
			matrix1Values[2] = 3;
			matrix1Values[3] = 4;
			matrix1Values[4] = 5;
			matrix1Values[5] = 6;

			float* matrix2Values = new float[6];
			matrix2Values[0] = 7;
			matrix2Values[1] = 8;
			matrix2Values[2] = 9;
			matrix2Values[3] = 10;
			matrix2Values[4] = 11;
			matrix2Values[5] = 12;

			float* matrixResultValues = new float[4];
			matrixResultValues[0] = 58;
			matrixResultValues[1] = 64;
			matrixResultValues[2] = 139;
			matrixResultValues[3] = 154;

			Matrix testMatrix1 = Matrix(2, 3, matrix1Values);
			Matrix testMatrix2 = Matrix(3, 2, matrix2Values);
			Matrix resultMatrix = Matrix(2, 2, matrixResultValues);

			Matrix multipliedMatrix = testMatrix1 * testMatrix2;

			Assert::IsTrue(multipliedMatrix == resultMatrix);
		}

		TEST_METHOD(Test_MatrixAdd)
		{
			float* matrix1Values = new float[6];
			matrix1Values[0] = 1;
			matrix1Values[1] = 2;
			matrix1Values[2] = 3;
			matrix1Values[3] = 4;
			matrix1Values[4] = 5;
			matrix1Values[5] = 6;

			float* matrix2Values = new float[6];
			matrix2Values[0] = 7;
			matrix2Values[1] = 8;
			matrix2Values[2] = 9;
			matrix2Values[3] = 10;
			matrix2Values[4] = 11;
			matrix2Values[5] = 12;

			float* matrixResultValues = new float[6];
			matrixResultValues[0] = 8;
			matrixResultValues[1] = 10;
			matrixResultValues[2] = 12;
			matrixResultValues[3] = 14;
			matrixResultValues[4] = 16;
			matrixResultValues[5] = 18;

			Matrix testMatrix1 = Matrix(2, 3, matrix1Values);
			Matrix testMatrix2 = Matrix(2, 3, matrix2Values);
			Matrix resultMatrix = Matrix(2, 3, matrixResultValues);

			Matrix addedMatrix = testMatrix1 + testMatrix2;

			Assert::IsTrue(addedMatrix == resultMatrix);
		}

		TEST_METHOD(Test_MatrixSubtraction)
		{
			float* matrix1Values = new float[6];
			matrix1Values[0] = 1;
			matrix1Values[1] = 2;
			matrix1Values[2] = 3;
			matrix1Values[3] = 4;
			matrix1Values[4] = 5;
			matrix1Values[5] = 6;

			float* matrix2Values = new float[6];
			matrix2Values[0] = 7;
			matrix2Values[1] = 8;
			matrix2Values[2] = 9;
			matrix2Values[3] = 10;
			matrix2Values[4] = 11;
			matrix2Values[5] = 12;

			float* matrixResultValues = new float[6];
			matrixResultValues[0] = -6;
			matrixResultValues[1] = -6;
			matrixResultValues[2] = -6;
			matrixResultValues[3] = -6;
			matrixResultValues[4] = -6;
			matrixResultValues[5] = -6;

			Matrix testMatrix1 = Matrix(2, 3, matrix1Values);
			Matrix testMatrix2 = Matrix(2, 3, matrix2Values);
			Matrix resultMatrix = Matrix(2, 3, matrixResultValues);

			Matrix addedMatrix = testMatrix1 - testMatrix2;

			Assert::IsTrue(addedMatrix == resultMatrix);
		}

	};
}
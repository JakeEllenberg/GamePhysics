//======================================================================
//File: Matrix.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Matrix storage and operations
//======================================================================
#include "Matrix.h"
#include "Vector3D.h"

//======================================================================
Matrix::Matrix()
: Matrix(2, true)
{
}

//--------------------------------------------------------------------------------
Matrix::Matrix(const Matrix& rhs)
{
	m_NumRows = rhs.GetNumRows();
	m_NumColumns = rhs.GetNumColumns();
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];
	for (int i = 0; i < m_Size; ++i)
	{
		mp_Matrix[i] = rhs.mp_Matrix[i];
	}
}

//--------------------------------------------------------------------------------
Matrix::Matrix(int length, bool identiy)
: Matrix(length, length)
{
	if (identiy)
	{
		for (int row = 0; row < m_NumRows; row++)
		{
			mp_Matrix[row * m_NumRows + row] = 1;
		}
	}
}

//--------------------------------------------------------------------------------
Matrix::Matrix(int rows, int columns)
{
	initalizeMatrix(rows, columns);

	for (int i = 0; i < m_Size; ++i)
	{
		mp_Matrix[i] = 0;
	}
}
//--------------------------------------------------------------------------------
Matrix::Matrix(int rows, int columns, float* matrixValues)
{
	initalizeMatrix(rows, columns);

	for (int i = 0; i < m_Size; ++i)
	{
		mp_Matrix[i] = matrixValues[i];
	}
}

//--------------------------------------------------------------------------------
Matrix::~Matrix()
{
	delete [] mp_Matrix;
	mp_Matrix = nullptr;
}

//--------------------------------------------------------------------------------
void Matrix::initalizeMatrix(int rows, int columns)
{
	m_NumRows = rows;
	m_NumColumns = columns;
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];
}

//--------------------------------------------------------------------------------
void Matrix::Set(int row, int column, float value)
{
	mp_Matrix[row * m_NumColumns + column] = value;
}

//--------------------------------------------------------------------------------
float Matrix::Get(const int& row, const int& column) const
{
	return mp_Matrix[row * m_NumColumns + column];
}

//--------------------------------------------------------------------------------
Matrix Matrix::CombinedMatrix(const Matrix& rhs, bool add) const
{
	Matrix returnedMatrix = Matrix(m_NumRows, m_NumColumns);

	for (int row = 0; row < m_NumRows; row++)
	{
		for (int col = 0; col < m_NumColumns; col++)
		{
			add ? returnedMatrix.Set(row, col, Get(row, col) + rhs.Get(row, col)) :
				returnedMatrix.Set(row, col, Get(row, col) - rhs.Get(row, col));
		}
	}

	return returnedMatrix;
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator+(const Matrix& rhs) const
{
	if (!CheckSameSize(rhs))
	{
		return *this;
	}

	return CombinedMatrix(rhs, true);
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator-(const Matrix& rhs) const
{
	if (!CheckSameSize(rhs))
	{
		return *this;
	}

	return CombinedMatrix(rhs, false);
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator*(const Matrix& rhs) const
{
	if (m_NumColumns != rhs.GetNumRows())
	{
		return *this;
	}

	Matrix returnMatrix = Matrix(m_NumRows, rhs.GetNumColumns());

	for (int i = 0; i < m_NumRows; ++i)
	{
		for (int j = 0; j < returnMatrix.GetNumColumns(); ++j)
		{
			float value = 0;
			for (int k = 0; k < m_NumColumns; ++k)
			{
				value += Get(i, k) * rhs.Get(k, j);
			}
			returnMatrix.Set(i, j, value);
		}
	}

	return returnMatrix;
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator*(const float& rhs) const
{
	float* tempArray = new float[m_Size];

	for (int i = 0; i < m_Size; ++i)
	{
		tempArray[i] = mp_Matrix[i] * rhs;
	}

	return Matrix(m_NumRows, m_NumColumns, tempArray);
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator*(const Vector3D& rhs) const
{
	float* tempArray = new float[3];
	tempArray[0] = rhs.X;
	tempArray[1] = rhs.Y;
	tempArray[2] = rhs.Z;

	Matrix vectorMatrix = Matrix(3, 1, tempArray);

	return (*this * vectorMatrix);
}

//--------------------------------------------------------------------------------
Matrix& Matrix::operator=(const Matrix& rhs)
{
	m_NumRows = rhs.GetNumRows();
	m_NumColumns = rhs.GetNumColumns();
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];
	for (int i = 0; i < m_Size; ++i)
	{
		mp_Matrix[i] = rhs.mp_Matrix[i];
	}

	return *this;
}

//--------------------------------------------------------------------------------
bool Matrix::operator==(const Matrix& rhs) const
{
	if (!CheckSameSize(rhs))
	{
		return false;
	}

	for (int row = 0; row < m_NumRows; row++)
	{
		for (int col = 0; col < m_NumColumns; col++)
		{
			if (Get(row, col) != rhs.Get(row, col))
			{
				return false;
			}
		}
	}

	return true;
}

//--------------------------------------------------------------------------------
bool Matrix::operator!=(const Matrix& rhs) const
{
	return !(*this == rhs);
}

//======================================================================
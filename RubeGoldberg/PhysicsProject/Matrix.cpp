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
void Matrix::Set(int index, float value)
{
	mp_Matrix[index] = value;
}

//--------------------------------------------------------------------------------
float Matrix::Get(int index) const
{
	return mp_Matrix[index];
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
Vector3D Matrix::operator*(const Vector3D& rhs) const
{
	float* tempArray = new float[3];
	tempArray[0] = rhs.X;
	tempArray[1] = rhs.Y;
	tempArray[2] = rhs.Z;

	Matrix vectorMatrix = Matrix(3, 1, tempArray);
	vectorMatrix = *this * vectorMatrix;

	return Vector3D(vectorMatrix.Get(0), vectorMatrix.Get(1), vectorMatrix.Get(2));
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

//--------------------------------------------------------------------------------------------
float Matrix::Det()
{
	float ratio, det;
	Matrix m = *this;
	if (m_NumRows == m_NumColumns)
	{
		for (int i = 0; i < m_NumRows; i++)
		{
			for (int j = 0; j < m_NumColumns; j++)
			{
				if (j > i)
				{
					ratio = m.Get(j, i) / m.Get(i, i);

					for (int k = 0; k < m_NumRows; k++)
					{
						m.Set(j, k, (m.Get(j, k) - (ratio*m.Get(i, k))));
					}
				}
			}
		}
		det = 1;
		for (int i = 0; i < m_NumRows; i++)
		{
			det *= m.Get(i, i);
		}
		return det;
	}
	else
	{
		//Det does not exist.
		//For sake of returning to make inverse send 0
		return 0;
	}
}
//--------------------------------------------------------------------------------------------

//-----------http://www.sanfoundry.com/cpp-program-finds-inverse-graph-matrix/----------------
Matrix Matrix::InvMatrix() const
{
	Matrix inv = *this;
	if (inv.Det() != 0)
	{
		int n = inv.GetNumRows();
		int i, j, k;
		float d;
		for (int i = 1; i <= n; i++)
		{
			for (j = 1; j <= 2 * n; j++)
			{
				if (j == (i + n))
				{
					inv.Set(i, j, 1);
				}
			}
		}
		for (i = n; i > 1; i--)
		{
			if (inv.Get(i - 1, 1) < inv.Get(i, 1))
			{
				for (j = 1; j <= n * 2; j++)
				{
					d = inv.Get(i, j);
					inv.Set(i, j, inv.Get(i - 1, j));
					inv.Set(i - 1, j, d);
				}
			}
		}
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n * 2; j++)
			{
				if (j != i)
				{
					d = inv.Get(j, i) / inv.Get(i, i);
					for (k = 1; k <= n * 2; k++)
					{
						inv.Set(j, k, inv.Get(j, k) - (inv.Get(i, k) * d));
					}
				}
			}
		}
		for (i = 1; i <= n; i++)
		{
			d = inv.Get(i, i);
			for (j = 1; j <= n * 2; j++)
			{
				inv.Set(i, j, inv.Get(i, j) / d);
			}
		}
		return inv;
	}
	return Matrix(inv.GetNumRows(), inv.GetNumColumns());
}

Vector3D Matrix::Transform(const Vector3D vector)
{
	return (*this) * vector;
}

Vector3D Matrix::TransformInv(const Vector3D vector)
{
	return InvMatrix() * vector;
}

Vector3D Matrix::GetAxisVector(unsigned int index) const
{
	return Vector3D(mp_Matrix[index], mp_Matrix[index + 4], mp_Matrix[index + 8]);
}

Vector3D Matrix::TransformTranspose(const Vector3D vector)
{
	return TransposeMatrix().Transform(vector);
}

void Matrix::SetSkewSymetric(const Vector3D vector)
{
	mp_Matrix[0] = mp_Matrix[4] = mp_Matrix[8] = 0;
	mp_Matrix[1] = -vector.Z;
	mp_Matrix[2] = vector.Y;
	mp_Matrix[3] = vector.Z;
	mp_Matrix[5] = -vector.X;
	mp_Matrix[6] = -vector.Y;
	mp_Matrix[7] = vector.X;
}

Matrix Matrix::TransposeMatrix() const
{
	Matrix transpose = Matrix(m_NumRows, m_NumColumns);

	for (int i = 0; i < m_NumRows; i++)
	{
		for (int j = 0; j < m_NumColumns; j++)
		{
			transpose.mp_Matrix[i * m_NumColumns + j] = mp_Matrix[j * m_NumColumns + i];
			transpose.mp_Matrix[j * m_NumColumns + i] = mp_Matrix[i * m_NumColumns + j];
		}
	}

	return transpose;
}

//======================================================================
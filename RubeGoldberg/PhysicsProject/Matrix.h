//======================================================================
//File: Matrix.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Matrix storage and operations
//======================================================================
#ifndef MATRIX_H
#define MATRIX_H
//======================================================================
class Vector3D;
//======================================================================

class Matrix
{
public:
	Matrix();
	Matrix(const Matrix& rhs);
	Matrix(int rows, int columns);
	Matrix(int length, bool identiy);
	Matrix(int rows, int columns, float* matrixValues);
	~Matrix();

	void  Set(int row, int column, float value);
	float Get(const int& row,const int& column) const;

	Matrix operator+(const Matrix&) const;
	Matrix operator-(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	Matrix operator*(const float&) const;
	Vector3D operator*(const Vector3D&) const;
	Matrix& operator=(const Matrix&);
	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix&) const;

	Matrix CombinedMatrix(const Matrix& matrix2, bool add) const;

	inline int GetNumRows() const { return m_NumRows; };
	inline int GetNumColumns() const { return m_NumColumns; };
	inline bool CheckSameSize(const Matrix& rhs) const { return rhs.GetNumRows() == m_NumRows && rhs.GetNumColumns() == m_NumColumns; };

	void Set(int index, float value);
	float Get(int index) const;

	Matrix InvMatrix() const;
	float Det();

	Vector3D Transform(const Vector3D vector);

private:
	void initalizeMatrix(int rows, int columns);

private:
	float* mp_Matrix;
	int  m_NumRows;
	int  m_NumColumns;
	int m_Size;
};
#endif
//======================================================================
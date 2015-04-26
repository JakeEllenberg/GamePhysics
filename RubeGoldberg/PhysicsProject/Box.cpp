//======================================================================
//File: BOX.cpp
//Author: Jake Ellenberg
//Created: 4/26/2015
//======================================================================
#include "Box.h"

Box::Box(Vector3D halfSize)
{
	m_HalfSize = halfSize;

	m_Vertices[0] = m_Offset * Vector3D(-halfSize.X, -halfSize.Y, -halfSize.Z);
	m_Vertices[1] = m_Offset * Vector3D(-halfSize.X, -halfSize.Y, halfSize.Z);
	m_Vertices[2] = m_Offset * Vector3D(-halfSize.X, halfSize.Y, -halfSize.Z);
	m_Vertices[3] = m_Offset * Vector3D(-halfSize.X, halfSize.Y, halfSize.Z);
	m_Vertices[4] = m_Offset * Vector3D(halfSize.X, -halfSize.Y, -halfSize.Z);
	m_Vertices[5] = m_Offset * Vector3D(halfSize.X, -halfSize.Y, halfSize.Z);
	m_Vertices[6] = m_Offset * Vector3D(halfSize.X, halfSize.Y, -halfSize.Z);
	m_Vertices[7] = m_Offset * Vector3D(halfSize.X, halfSize.Y, halfSize.Z);
}


Box::~Box()
{
}

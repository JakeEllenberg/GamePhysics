#include "Cube.h"


Cube::Cube()
{
}


Cube::~Cube()
{
}


void Cube::Inititalize(Vector3D centerPosition, std::string texturePath, float length)
{
	Vector3D topLeftPos = centerPosition;
	topLeftPos.X -= length / 2.0f;
	topLeftPos.Y -= length / 2.0f;
	topLeftPos.Z -= length / 2.0f;
	Vector3D topRightPos = topLeftPos;
	topRightPos.X += length;
	Vector3D botLeftPos = topLeftPos;
	botLeftPos.Y += length;
	Vector3D botRightPos = topRightPos;
	botRightPos.Y += length;

	Vector3D topLeftPosClose = topLeftPos;
	topLeftPosClose.Z += length;
	Vector3D topRightPosClose = topRightPos;
	topRightPosClose.Z += length;
	Vector3D botLeftPosClose = botLeftPos;
	botLeftPosClose.Z += length;
	Vector3D botRightposClose = botRightPos;
	botRightposClose.Z += length;

	std::string filePath = texturePath;

	RenderObject* topLeftObject = new RenderObject();
	topLeftObject->Inititalize(1.0f, topLeftPos, filePath);
	m_Objects.push_back(topLeftObject);
	RenderObject* topRightObject = new RenderObject();
	topRightObject->Inititalize(1.0f, topRightPos, filePath);
	m_Objects.push_back(topRightObject);
	RenderObject* botLeftObject = new RenderObject();
	botLeftObject->Inititalize(1.0f, botLeftPos, filePath);
	m_Objects.push_back(botLeftObject);
	RenderObject* botRightObject = new RenderObject();
	botRightObject->Inititalize(1.0f, botRightPos, filePath);
	m_Objects.push_back(botRightObject);

	RenderObject* topLeftObjectClose = new RenderObject();
	topLeftObjectClose->Inititalize(1.0f, topLeftPosClose, filePath);
	m_Objects.push_back(topLeftObjectClose);
	RenderObject* topRightObjectClose = new RenderObject();
	topRightObjectClose->Inititalize(1.0f, topRightPosClose, filePath);
	m_Objects.push_back(topRightObjectClose);
	RenderObject* botLeftObjectClose = new RenderObject();
	botLeftObjectClose->Inititalize(1.0f, botLeftPosClose, filePath);
	m_Objects.push_back(botLeftObjectClose);
	RenderObject* botRightObjectClose = new RenderObject();
	botRightObjectClose->Inititalize(1.0f, botRightposClose, filePath);
	m_Objects.push_back(botRightObjectClose);

	//Conect the zs
	m_Rods.push_back(new RodContactGenerator(topLeftObject, topLeftObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(botLeftObject, botLeftObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(topRightObject, topRightObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(botRightObject, botRightObjectClose, length));

	//Conect the farside
	m_Rods.push_back(new RodContactGenerator(topLeftObject, topRightObject, length));
	m_Rods.push_back(new RodContactGenerator(topLeftObject, botLeftObject, length));
	m_Rods.push_back(new RodContactGenerator(botLeftObject, botRightObject, length));
	m_Rods.push_back(new RodContactGenerator(botRightObject, topRightObject, length));

	//connect the close side
	m_Rods.push_back(new RodContactGenerator(topLeftObjectClose, topRightObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(topLeftObjectClose, botLeftObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(botLeftObjectClose, botRightObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(botRightObjectClose, topRightObjectClose, length));

	//connect the diagonals
	m_Rods.push_back(new RodContactGenerator(botLeftObject, botRightObjectClose, botLeftPos.CalculateDistance(botRightposClose)));
	m_Rods.push_back(new RodContactGenerator(botRightObject, botLeftObjectClose, botLeftPosClose.CalculateDistance(botRightPos)));
	m_Rods.push_back(new RodContactGenerator(botLeftObject, topRightObject, botLeftPos.CalculateDistance(topRightPos)));
	m_Rods.push_back(new RodContactGenerator(botRightObject, topLeftObject, botRightPos.CalculateDistance(topLeftPos)));
	m_Rods.push_back(new RodContactGenerator(botLeftObjectClose, topRightObjectClose, botLeftPosClose.CalculateDistance(topRightPosClose)));
	m_Rods.push_back(new RodContactGenerator(botRightObjectClose, topLeftObjectClose, botRightposClose.CalculateDistance(topLeftPosClose)));
	m_Rods.push_back(new RodContactGenerator(topLeftObject, topRightObjectClose, topLeftPos.CalculateDistance(topRightPosClose)));
	m_Rods.push_back(new RodContactGenerator(topRightObject, topLeftObjectClose, topLeftPosClose.CalculateDistance(topRightPos)));
	m_Rods.push_back(new RodContactGenerator(botLeftObject, topLeftObjectClose, botLeftPos.CalculateDistance(topLeftPosClose)));
	m_Rods.push_back(new RodContactGenerator(topLeftObject, botLeftObjectClose, topLeftPos.CalculateDistance(botLeftPosClose)));
	m_Rods.push_back(new RodContactGenerator(botRightObject, topRightObjectClose, botRightPos.CalculateDistance(topRightPosClose)));
	m_Rods.push_back(new RodContactGenerator(topRightObject, botRightObjectClose, topRightPos.CalculateDistance(botRightposClose)));
}
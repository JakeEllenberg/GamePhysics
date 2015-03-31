#include "Tetrahedron.h"


Tetrahedron::Tetrahedron()
{
}


Tetrahedron::~Tetrahedron()
{
}


void Tetrahedron::Inititalize(Vector3D centerPosition, std::string texturePath, float length)
{
	std::string filePath = texturePath;

	Vector3D topPos = centerPosition;
	topPos.Y += length / 2.0f;
	topPos.X += length / 4.0f;
	topPos.Z -= length / 4.0f;
	Vector3D botLeftPos = centerPosition;
	botLeftPos.Y -= length / 2.0f;
	botLeftPos.Z -= length / 2.0f;
	botLeftPos.X -= length / 2.0f;
	Vector3D botRightPos = centerPosition;
	botRightPos.Y -= length / 2.0f;
	botRightPos.Z += length / 2.0f;
	botRightPos.X += length / 2.0f;
	Vector3D botCenterPos = botLeftPos;
	botCenterPos.X += length;
	botCenterPos.Z -= length / 2.0f;

	RenderObject* topObject = new RenderObject();
	topObject->Inititalize(1.0f, topPos, filePath);
	m_Objects.push_back(topObject);
	RenderObject* botLeftObject = new RenderObject();
	botLeftObject->Inititalize(1.0f, botLeftPos, filePath);
	m_Objects.push_back(botLeftObject);
	RenderObject* botRightObject = new RenderObject();
	botRightObject->Inititalize(1.0f, botRightPos, filePath);
	m_Objects.push_back(botRightObject);
	RenderObject* botCenterObject = new RenderObject();
	botCenterObject->Inititalize(1.0f, botCenterPos, filePath);
	m_Objects.push_back(botCenterObject);

	
	//Connect the bot with the the top
	m_Rods.push_back(new RodContactGenerator(botLeftObject, topObject, topPos.CalculateDistance(botLeftPos)));
	m_Rods.push_back(new RodContactGenerator(botRightObject, topObject, topPos.CalculateDistance(botRightPos)));
	m_Rods.push_back(new RodContactGenerator(botCenterObject, topObject, topPos.CalculateDistance(botCenterPos)));

	//Connect the bottom together
	m_Rods.push_back(new RodContactGenerator(botLeftObject, botRightObject, botLeftPos.CalculateDistance(botRightPos)));
	m_Rods.push_back(new RodContactGenerator(botLeftObject, botCenterObject, botLeftPos.CalculateDistance(botCenterPos)));
	m_Rods.push_back(new RodContactGenerator(botRightObject, botCenterObject, botRightPos.CalculateDistance(botCenterPos)));
}
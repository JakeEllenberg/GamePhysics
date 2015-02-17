//======================================================================
//File: PhysicsObject.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Defines extra infromation for planets
//======================================================================
#ifndef PLANET_H
#define PLANET_H
//======================================================================
#include "PhysicsObject.h"
#include <string>
class Planet : public PhysicsObject
{
public:
	Planet();
	~Planet();

	void Initialize(float radius = 0.1f, float mass = 0.0f, Vector3D initalPosition = Vector3D::Zero, Vector3D initalVelocity = Vector3D::Zero, std::string planetName = "", std::string texturePath = "");
	void Update(float sTime);
	void loadImage(std::string filePath);
	void Draw();
	inline std::string GetName() { return m_Name; };
private:
	std::string m_Name;
	GLuint m_Tex;
	GLUquadric* m_Quad;
};
#endif
//=======================================================================
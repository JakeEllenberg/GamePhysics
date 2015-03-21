//======================================================================
//File: GravityGenerator.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Adds the force for gravity between objects such as planets
//======================================================================
#ifndef GENERATOR_H
#define GENERATOR_H
enum GeneratorType
{
	GENERATOR = 0,
	FORCE_GENERATOR,
	EARTH_GRAVITY_GENERATOR,
	OBJECT_FORCE_GENERATOR, //All object force generator types MUST go below this point
	GRAVITY_GENERATOR
};
//======================================================================
class Generator
{
public:
	Generator();
	~Generator();

	inline GeneratorType GetType() { return m_Type; };
protected:
	GeneratorType m_Type;
};
#endif
//======================================================================
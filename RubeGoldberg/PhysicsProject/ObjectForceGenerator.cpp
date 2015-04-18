//======================================================================
//File: ObjetForceGenerator.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Base class for force generators
//======================================================================
#include "ObjectForceGenerator.h"
//======================================================================
ObjectForceGenerator::ObjectForceGenerator()
{
	m_Type = GeneratorType::OBJECT_FORCE_GENERATOR;
}

//--------------------------------------------------------------------------------
ObjectForceGenerator::~ObjectForceGenerator()
{
}

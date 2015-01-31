//======================================================================
//File: ForceGenerator.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Base class for force generators
//======================================================================
#include "ForceGenerator.h"

//======================================================================
ForceGenerator::ForceGenerator()
{
	m_Type = GeneratorType::FORCE_GENERATOR;
}

//--------------------------------------------------------------------------------
ForceGenerator::~ForceGenerator()
{
}

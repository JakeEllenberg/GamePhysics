//======================================================================
//File: PlanetSystem.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Creats and holds planets but does not own the planet objects
//======================================================================
#ifndef PLANET_SYSTEM_H
#define PLANET_SYSTEM_H
//======================================================================
#include <vector>
#include "Planet.h"
//======================================================================
class PlanetSystem
{
public:
	PlanetSystem();
	~PlanetSystem();
	void Initialize();
	inline const std::vector<Planet*> GetPlanets() const { return m_Planets; };
private:
	std::vector<Planet*> m_Planets;
};
#endif
//======================================================================
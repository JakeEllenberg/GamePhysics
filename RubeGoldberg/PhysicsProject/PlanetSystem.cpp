//======================================================================
//File: PlanetSystem.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Creats and holds planets but does not own the planet objects
//======================================================================
#include "PlanetSystem.h"

//======================================================================
PlanetSystem::PlanetSystem()
{
}

//--------------------------------------------------------------------------------
PlanetSystem::~PlanetSystem()
{
}

//--------------------------------------------------------------------------------
// http://en.wikipedia.org/wiki/Orbital_speed Gives Earth's velocity
// http://www.smartconversion.com/otherInfo/Mass_of_planets_and_the_Sun.aspx
// http://www.astronomynotes.com/tables/tablesb.htm
// http://www.sjsu.edu/faculty/watkins/orbital.htm Gives ratios for velocities
// Mass / Distance Conversions from Robert Bethune
// http://sciencenetlinks.com/interactives/messenger/psc/PlanetSize.html Provides size ratios
void PlanetSystem::Initialize()
{
	float dampening = 0.999999999999999999999f;
	
	Planet* sun = new Planet();
	sun->Initialize(.25f, 1.0f, Vector3D::Zero, Vector3D::Zero, "Sun", "Planet/sunmap.jpg");
	sun->SetDampening(dampening);
	m_Planets.push_back(sun);

	Planet* mercury = new Planet();
	mercury->Initialize(0.05f, 0.0000001666f, Vector3D(0.31f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0000003925392803303289f), "Mercury", "Planet/mercurymap.jpg");
	mercury->SetDampening(dampening);
	m_Planets.push_back(mercury);

	Planet* venus = new Planet();
	venus->Initialize(.1f, 0.000002447f, Vector3D(0.718f, 0, 0), Vector3D(0, 0, 0.0000002377854700252f), "Venus", "Planet/venusmap.jpg");
	venus->SetDampening(dampening);
	m_Planets.push_back(venus);


	Planet* mars = new Planet();
	mars->Initialize(0.08f, .0000003232f, Vector3D(1.38f, 0, 0), Vector3D(0, 0, .0000001624394778196f), "Mars", "Planet/mars_1k_color.jpg");
	mars->SetDampening(dampening);
	m_Planets.push_back(mars);

	Planet* earth = new Planet();
	earth->Initialize(.025f, 0.000003003f, Vector3D(0.98f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.000000202542989816901f), "Earth", "Planet/Earth.jpg");
	earth->SetDampening(dampening);
	m_Planets.push_back(earth);

	Planet* jupiter = new Planet();
	jupiter->Initialize(1.1f, .0009547919f, Vector3D(4.95f, 0, 0), Vector3D(0, 0, .0000000879036575732f), "Jupiter", "Planet/jupitermap.jpg");
	jupiter->SetDampening(dampening);
	m_Planets.push_back(jupiter);

	Planet* saturn = new Planet();
	saturn->Initialize(0.941f, .000285885f, Vector3D(9.02f, 0, 0), Vector3D(0, 0, .0000000654213857054f), "Saturn", "Planet/saturnmap.jpg");
	saturn->SetDampening(dampening);
	m_Planets.push_back(saturn);


	Planet* uranus = new Planet();
	uranus->Initialize(0.4f, .000043662f, Vector3D(18.3f, 0, 0), Vector3D(0, 0, .0000000461798016744f), "Uranus", "Planet/uranusmap.jpg");
	uranus->SetDampening(dampening);
	m_Planets.push_back(uranus);


	Planet* neptune = new Planet();
	neptune->Initialize(0.388f, .000051513f, Vector3D(30.0f, 0, 0), Vector3D(0, 0, .0000000368628241436f), "Neptune", "Planet/neptunemap.jpg");
	neptune->SetDampening(dampening);
	m_Planets.push_back(neptune);

	//Moon not quite working
	Planet* moon = new Planet();
	moon->Initialize(0.005f, 0.0000000000000123f, Vector3D(0.979f, 0, 0), Vector3D(0, 0, (float)(0.0000002059429908 + 0.000000007197722768554639)), "Moon", "Planet/moonmap1k.jpg");
	moon->SetDampening(dampening);
	m_Planets.push_back(moon);
	
}

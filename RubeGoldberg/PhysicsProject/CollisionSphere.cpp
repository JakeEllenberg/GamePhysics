//======================================================================
//File: CollisionDetector.h
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#include "CollisionSphere.h"

//======================================================================
CollisionSphere::CollisionSphere(RigidBody* rigidBody, Matrix offset)
:CollisionPrimitive(rigidBody, offset)
{
}


//======================================================================
CollisionSphere::~CollisionSphere()
{
}

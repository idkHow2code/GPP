// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "wall.h"

//=============================================================================
// default constructor
//=============================================================================
Wall::Wall() : Entity()
{
	spriteData.x = wallNS::X;              // location on screen
	spriteData.y = wallNS::Y;
	edge.left = -32;
	edge.top = -7;
	edge.right = 32;
	edge.bottom = 7;
	collisionType = entityNS::BOX;
	mass = wallNS::MASS;
	startFrame = wallNS::START_FRAME;    // first frame of ship animation
	endFrame = wallNS::END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);
}

int Wall::checkVoronoiRegion(Entity &ent, VECTOR2 &collisionVector)
{
	float min01, min03, max01, max03, center01, center03;

	computeRotatedBox();                    // prepare rotated box

											// project circle center onto edge01
	center01 = graphics->Vector2Dot(&edge01, ent.getCenter());
	min01 = center01 - ent.getRadius()*ent.getScale(); // min and max are Radius from center
	max01 = center01 + ent.getRadius()*ent.getScale();
	if (min01 > edge01Max || max01 < edge01Min) // if projections do not overlap
		return false;                       // no collision is possible

											// project circle center onto edge03
	center03 = graphics->Vector2Dot(&edge03, ent.getCenter());
	min03 = center03 - ent.getRadius()*ent.getScale(); // min and max are Radius from center
	max03 = center03 + ent.getRadius()*ent.getScale();
	if (min03 > edge03Max || max03 < edge03Min) // if projections do not overlap
		return false;                       // no collision is possible

											// circle projection overlaps box projection
											// check to see if circle is in voronoi region of collision box
	if (center01 < edge01Min && center03 < edge03Min)    // if circle in Voronoi0
		return 0;
	if (center01 > edge01Max && center03 < edge03Min)    // if circle in Voronoi1
		return 1;
	if (center01 > edge01Max && center03 > edge03Max)    // if circle in Voronoi2
		return 2;
	if (center01 < edge01Min && center03 > edge03Max)    // if circle in Voronoi3
		return 3;

}
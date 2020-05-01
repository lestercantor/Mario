#pragma once
#ifndef _COLLISIONS_
#define _COLLISIONS_
#include "Commons.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Box(Rect2D rect1, Rect2D rect2); 
	bool Circle(Circle2D circle1, Circle2D circle2);

private:
	Collisions();

	static Collisions* mInstance;
};

#endif // !_COLLISIONS_



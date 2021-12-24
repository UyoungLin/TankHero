#pragma once
#include "ImageManager.h"

class FourDirection
{
public:
	FourDirection();

	SimpleImage* setUp();
	SimpleImage* setDown();
	SimpleImage* setLeft();
	SimpleImage* setRight();

protected:
	SimpleImage up;
	SimpleImage down;
	SimpleImage left;
	SimpleImage right;
};



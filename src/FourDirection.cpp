#include "FourDirection.h"
#include "FourDirection.h"

FourDirection::FourDirection()
{
	up = ImageManager::get()->getImagebyURL("images/tankUp.png", true, false);
	down = ImageManager::get()->getImagebyURL("images/tankDown.png", true, false);
	left = ImageManager::get()->getImagebyURL("images/tankLeft.png", true, false);
	right = ImageManager::get()->getImagebyURL("images/tankRight.png", true, false);
}

SimpleImage* FourDirection::setUp()
{
	return &up;
}

SimpleImage* FourDirection::setDown()
{
	return &down;
}

SimpleImage* FourDirection::setLeft()
{
	return &left;
}

SimpleImage* FourDirection::setRight()
{
	return &right;
}

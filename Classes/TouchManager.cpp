#include "TouchManager.h"


TouchManager::TouchManager():
	timer(0),
	isLongPressing(false),
	containsTouchingPoint(false)
{
	
}

TouchManager::~TouchManager()
{

}

void TouchManager::reset()
{
	timer = 0;
	isLongPressing = false;
	containsTouchingPoint = false;
	hasMoved = false;
}


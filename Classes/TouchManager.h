#pragma  once

class TouchManager
{
public:

	TouchManager();
	~TouchManager();

	float timer;
	bool isLongPressing;
	bool containsTouchingPoint;
	bool hasMoved;

	void reset();

};
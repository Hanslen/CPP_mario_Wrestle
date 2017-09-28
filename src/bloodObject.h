#pragma once
#include "DisplayableObject.h"
class bloodObject :
	public DisplayableObject
{
public:
	bloodObject(BaseEngine* pEngine, int x);
	~bloodObject();
	int decreaseBlood;
	int xPos;
	void Draw();
	void DoUpdate(int changeBlood);
};

